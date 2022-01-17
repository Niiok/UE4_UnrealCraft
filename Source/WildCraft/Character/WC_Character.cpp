// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_Character.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
//#include "GameplayTaskComponent.h"
#include "GAS/WC_AttributeSet_Sample.h"
#include "Component/LimbComponent.h"

//////////////////////////////////////////////////////////////////////////
// AWC_Character

AWC_Character::AWC_Character()
{
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	Limb = CreateDefaultSubobject<ULimbComponent>(TEXT("Limb"));
	//AbilityComponent->
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

// IAbilitySystemInterface implementation
UAbilitySystemComponent * AWC_Character::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}
