// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_Character.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
//#include "GameplayTaskComponent.h"
#include "GAS/WC_AttributeSet_Sample.h"
#include "Component/LimbComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/WidgetComponent.h"

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
}

void AWC_Character::AddAbility(TSubclassOf<UGameplayAbility> Ability)
{
	FGameplayAbilitySpec spec(Ability);
	//spec.InputID = 5;
	//spec.

	AbilitySystem->GiveAbility(spec);
}


//////////////////////////////////////////////////////////////////////////
// overrides

float AWC_Character::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	UGameplayEffect damage;
	damage

	if (CurrentHP != 0)
		CurrentHP = FMath::Clamp<float>(CurrentHP - DamageAmount, 0, MaxHP);

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AWC_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (AbilitySystem)
	{
		AbilitySystem->InitStats(UWC_AttributeSet_Sample::StaticClass(), NULL);
	}
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

		if (spring)
		{
			spring->bDoCollisionTest = true;
			//spring->AttachToComponent(cap, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}

// IAbilitySystemInterface implementation
UAbilitySystemComponent * AWC_Character::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

void AWC_Character::GetOwnedGameplayTags(FGameplayTagContainer & TagContainer) const
{
	return AbilitySystem->GetOwnedGameplayTags(TagContainer);
}
