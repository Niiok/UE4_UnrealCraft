// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_Character.h"
#include "AbilitySystemComponent.h"
//#include "GameplayTaskComponent.h"
#include "GAS/WC_AttributeSet_Sample.h"

//////////////////////////////////////////////////////////////////////////
// AWC_Character

AWC_Character::AWC_Character()
{
	UE_LOG(LogTemp, Warning, TEXT("wow character"));

	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	//AbilityComponent->
	GameplayTask = CreateDefaultSubobject<UGameplayTasksComponent>(TEXT("GameplayTask"));
}

inline UGameplayEffect* ConstructGameplayEffect(FString name)
{
	return NewObject<UGameplayEffect>(GetTransientPackage(), FName(*name));
}

inline FGameplayModifierInfo& AddModifier(
	UGameplayEffect* Effect,
	UProperty* Property,
	EGameplayModOp::Type Op,
	const FGameplayEffectModifierMagnitude& Magnitude)
{
	int32 index = Effect->Modifiers.Num();
	Effect->Modifiers.SetNum(index + 1);
	FGameplayModifierInfo& Info = Effect->Modifiers[index];
	Info.ModifierMagnitude = Magnitude;
	Info.ModifierOp = Op;
	Info.Attribute.SetUProperty(Property);
	return Info;
}

void AWC_Character::GameplayEffect_Sample()
{
	UGameplayEffect* RecoverHP = ConstructGameplayEffect("RecoverHP");

	UProperty* hpProperty = FindFieldChecked<UProperty>(
		UWC_AttributeSet_Sample::StaticClass(),
		GET_MEMBER_NAME_CHECKED(UWC_AttributeSet_Sample, HP));

	RecoverHP->DurationPolicy = EGameplayEffectDurationType::HasDuration;
	RecoverHP->DurationMagnitude = FScalableFloat(10.0f);
	RecoverHP->ChanceToApplyToTarget = 1.0f;
	RecoverHP->Period = 0.5f;

	AddModifier(RecoverHP, hpProperty, EGameplayModOp::Additive, FScalableFloat(50.0f));
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
