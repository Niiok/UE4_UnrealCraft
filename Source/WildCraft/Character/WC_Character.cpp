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

//////////////////////////////////////////////////////////////////////////
// AWC_Character

AWC_Character::AWC_Character()
{
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	Limb = CreateDefaultSubobject<ULimbComponent>(TEXT("Limb"));
	CurrentHP = MaxHP;
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
}

void AWC_Character::BeginPlay()
{
	Super::BeginPlay();

	MeshRelativeTransform = GetMesh()->GetRelativeTransform();

	/*Widget_HPBar->SetRelativeLocation(
		FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2));*/

	const UWC_AttributeSet_Character* AttributeSet = GetAttributeSet();

	((UWC_AttributeSet_Character*)AttributeSet)->OnHealthChanged.AddDynamic(this, &AWC_Character::HandleHealthChanged);
	((UWC_AttributeSet_Character*)AttributeSet)->OnHealthChanged.Broadcast(0, FGameplayTagContainer());


}


//////////////////////////////////////////////////////////////////////////
// ue4 methods

float AWC_Character::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	UGameplayEffect* effect = NewObject<UGameplayEffect>();
	effect->DurationPolicy = EGameplayEffectDurationType::Instant;
	int index = effect->Modifiers.Num();
	effect->Modifiers.SetNum(index + 1);
	FGameplayModifierInfo& info = effect->Modifiers[index];
	info.ModifierOp = EGameplayModOp::Additive;
	info.Attribute = GetAttributeSet()->GetHealthAttribute();
	info.ModifierMagnitude = FScalableFloat(-DamageAmount);

	GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(effect, 1.0f, GetAbilitySystemComponent()->MakeEffectContext());

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AWC_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

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
	UCapsuleComponent* cap = GetCapsuleComponent();
	USkeletalMeshComponent* mesh = GetMesh();
	USpringArmComponent* spring = Cast<USpringArmComponent>(GetComponentByClass(USpringArmComponent::StaticClass()));

	bRagdoll = bEnabled;

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

		if (GetAttributeSet()->GetHealth() == 0.0f)
			SetRagdoll(true);
	}
}

void AWC_Character::HandleManaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
{
	//if (bAbilitiesInitialized)
	{
		OnManaChanged(DeltaValue, EventTags);
	}
}

void AWC_Character::HandleMoveSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
{
	// Update the character movement's walk speed
	GetCharacterMovement()->MaxWalkSpeed = GetAttributeSet()->GetMoveSpeed();

	//if (bAbilitiesInitialized)
	{
		OnMoveSpeedChanged(DeltaValue, EventTags);
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
