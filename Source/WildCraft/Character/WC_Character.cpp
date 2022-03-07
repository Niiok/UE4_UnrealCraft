// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_Character.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
//#include "GameplayTaskComponent.h"
#include "GAS/WC_AttributeSet_Character.h"
#include "Component/LimbComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "UI/WC_UserWidget_Character.h"
#include "VoxelComponents/VoxelNoClippingComponent.h"
#include "VoxelComponents/VoxelInvokerComponent.h"

//////////////////////////////////////////////////////////////////////////
// AWC_Character

AWC_Character::AWC_Character()
{
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	Limb = CreateDefaultSubobject<ULimbComponent>(TEXT("Limb"));

	Widget_HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	Widget_HPBar->SetupAttachment(GetMesh());
	Widget_HPBar->SetRelativeLocation(
		FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2));
	Widget_HPBar->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> hpbar_class(TEXT("WidgetBlueprint'/Game/WildCraft/UI/WB_HPBar.WB_HPBar_C'"));
	if (hpbar_class.Succeeded())
	{
		Widget_HPBar->SetWidgetClass(hpbar_class.Class);
		Widget_HPBar->SetDrawSize(FVector2D(150.0f, 50.0f));
	}

	NoClipping = CreateDefaultSubobject<UVoxelNoClippingComponent>(TEXT("NoClipping"));
	Invoker = CreateDefaultSubobject<UVoxelSimpleInvokerComponent>(TEXT("Invoker"));

	UCharacterMovementComponent* move_comp = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (move_comp)
		move_comp->MaxStepHeight = 75.0f;
}

//////////////////////////////////////////////////////////////////////////
// ue4 methods

void AWC_Character::BeginPlay()
{
	UE_LOG(LogTemp, Display, TEXT("Character : BeginPlay Start"));
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("Character : BeginPlay End"));

	MeshRelativeTransform = GetMesh()->GetRelativeTransform();

	/*Widget_HPBar->SetRelativeLocation(
		FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2));*/

}

float AWC_Character::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	FHitResult* hit = NULL;

	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		FPointDamageEvent* point_event = (FPointDamageEvent*)&DamageEvent;

		hit = &point_event->HitInfo;
	}/*
	else if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		FRadialDamageEvent* rad_event = (FRadialDamageEvent*)&DamageEvent;

		rad_event->
	}*/

	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UGameplayEffect* DamageGE = NewObject<UGameplayEffect>();
	DamageGE->DurationPolicy = EGameplayEffectDurationType::Instant;
	DamageGE->Modifiers.Add(FGameplayModifierInfo());
	DamageGE->Modifiers.Last().ModifierOp = EGameplayModOp::Additive;
	DamageGE->Modifiers.Last().Attribute = GetAttributeSet()->GetHealthAttribute();
	DamageGE->Modifiers.Last().ModifierMagnitude = FScalableFloat(-DamageAmount);
	DamageGE->GameplayCues.Add(FGameplayEffectCue(FGameplayTag::RequestGameplayTag(TEXT("When.Hit")), 1, 1));

	FGameplayEffectContextHandle context = GetAbilitySystemComponent()->MakeEffectContext();
	if (hit)
		context.AddHitResult(*hit);
	GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(DamageGE, 1.0f, context);

	return DamageAmount;
}

void AWC_Character::PossessedBy(AController * NewController)
{
	UE_LOG(LogTemp, Display, TEXT("Character : PossessedBy Start"));
	Super::PossessedBy(NewController);
	UE_LOG(LogTemp, Display, TEXT("Character : PossessedBy End"));

	//UWC_AttributeSet_Character* AttributeSet = GetAttributeSet();

	//((UWC_AttributeSet_Character*)AttributeSet)->OnHealthChanged.AddDynamic(this, &AWC_Character::HandleHealthChanged);

	auto widget = Cast<UWC_UserWidget_Character>(Widget_HPBar->GetUserWidgetObject());
	if (widget)
		widget->BindCharacter(this);
	
	OnHealthChangeDelegate.Broadcast(0, FGameplayTagContainer());
	//((UWC_AttributeSet_Character*)AttributeSet)->OnHealthChanged.Broadcast(0, FGameplayTagContainer());
}

void AWC_Character::PostInitializeComponents()
{
	UE_LOG(LogTemp, Display, TEXT("Character : PostInitializeComponent Start"));
	Super::PostInitializeComponents();
	UE_LOG(LogTemp, Display, TEXT("Character : PostInitializeComponent End"));

	if (AbilitySystem)
	{
		AbilitySystem->InitStats(UWC_AttributeSet_Character::StaticClass(), NULL);
	}
}


///////////////////
// original methods

const UWC_AttributeSet_Character* AWC_Character::GetAttributeSet() const
{
	if (GetAbilitySystemComponent() != nullptr)
		return GetAbilitySystemComponent()->GetSet<UWC_AttributeSet_Character>();
	else
		return nullptr;
}

void AWC_Character::SetRagdoll(bool bEnabled)
{
	if (bEnabled == bRagdoll)
		return;
	else
		bRagdoll = bEnabled;

	UCapsuleComponent* cap = GetCapsuleComponent();
	USkeletalMeshComponent* mesh = GetMesh();
	USpringArmComponent* spring = Cast<USpringArmComponent>(GetComponentByClass(USpringArmComponent::StaticClass()));


	if (bRagdoll)
	{
		mesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		mesh->SetSimulatePhysics(true);
		mesh->SetCollisionProfileName(TEXT("Ragdoll"));

		RootComponent = mesh;

		cap->AttachToComponent(mesh, 
			FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true));
		cap->SetMassOverrideInKg(NAME_None, 0.0f, true);
		cap->SetCollisionProfileName(TEXT("CharacterMesh"));

		if (spring)
		{
			spring->bDoCollisionTest = false;
			//spring->AttachToComponent(mesh, FAttachmentTransformRules::KeepRelativeTransform);
		}

		mesh->AddImpulse(mesh->GetRightVector()*mesh->GetMass()*100);

		GetController()->SetIgnoreMoveInput(true);
	}
	else
	{
		cap->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		cap->SetWorldLocation(mesh->GetRelativeLocation() + FVector(0, 0, cap->GetScaledCapsuleHalfHeight()));
		cap->SetWorldRotation(FRotator(0, mesh->GetRelativeRotation().Yaw - MeshRelativeTransform.Rotator().Yaw, 0));
		cap->SetMassOverrideInKg(NAME_None, 0.0f, false);
		cap->SetCollisionProfileName(TEXT("Pawn"));

		RootComponent = cap;

		mesh->SetSimulatePhysics(false);
		mesh->SetCollisionProfileName(TEXT("CharacterMesh"));
		mesh->AttachToComponent(cap, FAttachmentTransformRules::KeepWorldTransform);
		mesh->SetRelativeTransform(MeshRelativeTransform);

		GetController()->SetIgnoreMoveInput(false);

		if (spring)
		{
			spring->bDoCollisionTest = true;
			//spring->AttachToComponent(cap, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}

void AWC_Character::AddAbility(TSubclassOf<UGameplayAbility> Ability)
{
	FGameplayAbilitySpec spec(Ability);
	//spec.InputID = 5;
	//spec.

	AbilitySystem->GiveAbility(spec);
}

void AWC_Character::HandleDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, AWC_Character* InstigatorPawn, AActor* DamageCauser)
{
	OnDamaged(DamageAmount, HitInfo, DamageTags, InstigatorPawn, DamageCauser);
}

void AWC_Character::HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
{
	// We only call the BP callback if this is not the initial ability setup
	//if (bAbilitiesInitialized)
	{
		OnHealthChanged(DeltaValue, EventTags);
		OnHealthChangeDelegate.Broadcast(DeltaValue, EventTags);

		UE_LOG(LogTemp, Warning, TEXT("%f health left!"), GetAttributeSet()->GetHealth());

		if (GetAttributeSet()->GetHealth() == 0.0f)
		{
			SetRagdoll(true);
			if (GetLifeSpan() == 0.0f)
				SetLifeSpan(10.0f);

			AAIController* ai = Cast<AAIController>(GetController());
			if (ai)
			{
				UBrainComponent* brain = ai->GetBrainComponent();
				if (brain)
					brain->StopLogic(FString());
			}
		}
		else
		{
			SetRagdoll(false);
			if (GetLifeSpan() != 0.0f)
			{
				SetLifeSpan(0.0f);

				AAIController* ai = Cast<AAIController>(GetController());
				if (ai)
				{
					UBrainComponent* brain = ai->GetBrainComponent();
					if (brain)
						brain->RestartLogic();
				}
			}
		}
	}
}

void AWC_Character::HandleManaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
{
	//if (bAbilitiesInitialized)
	{
		OnManaChanged(DeltaValue, EventTags);
		OnManaChangeDelegate.Broadcast(DeltaValue, EventTags);
	}
}

void AWC_Character::HandleMoveSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
{
	// Update the character movement's walk speed
	GetCharacterMovement()->MaxWalkSpeed = GetAttributeSet()->GetMoveSpeed();

	//if (bAbilitiesInitialized)
	{
		OnMoveSpeedChanged(DeltaValue, EventTags);
		OnMoveSpeedChangeDelegate.Broadcast(DeltaValue, EventTags);
	}
}



//////////////////////////////////////////
// IAbilitySystemInterface implementation
UAbilitySystemComponent * AWC_Character::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

void AWC_Character::GetOwnedGameplayTags(FGameplayTagContainer & TagContainer) const
{
	return AbilitySystem->GetOwnedGameplayTags(TagContainer);
}
