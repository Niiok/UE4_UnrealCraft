// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_Character.h"
#include "AbilitySystemComponent.h"
#include "GAS/WC_AttributeSet_Sample.h"

//////////////////////////////////////////////////////////////////////////
// AWC_Character

AWC_Character::AWC_Character()
{
	UE_LOG(LogTemp, Warning, TEXT("wow character"));

	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilityComponent"));
	//AbilityComponent->
}



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
