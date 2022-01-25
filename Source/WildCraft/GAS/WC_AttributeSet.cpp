// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_AttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Character/WC_Character.h"

void UWC_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWC_AttributeSet, Health);
	DOREPLIFETIME(UWC_AttributeSet, MaxHealth);
	DOREPLIFETIME(UWC_AttributeSet, Mana);
	DOREPLIFETIME(UWC_AttributeSet, MaxMana);
	DOREPLIFETIME(UWC_AttributeSet, AttackPower);
	DOREPLIFETIME(UWC_AttributeSet, DefensePower);
	DOREPLIFETIME(UWC_AttributeSet, MoveSpeed);
}

void UWC_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWC_AttributeSet, Health, OldValue);
}

void UWC_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWC_AttributeSet, MaxHealth, OldValue);
}

void UWC_AttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWC_AttributeSet, Mana, OldValue);
}

void UWC_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWC_AttributeSet, MaxMana, OldValue);
}

void UWC_AttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWC_AttributeSet, AttackPower, OldValue);
}

void UWC_AttributeSet::OnRep_DefensePower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWC_AttributeSet, DefensePower, OldValue);
}

void UWC_AttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWC_AttributeSet, MoveSpeed, OldValue);
}

void UWC_AttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void UWC_AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// This is called whenever attributes change, so for max health/mana we want to scale the current totals to match
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	else if (Attribute == GetMaxManaAttribute())
	{
		AdjustAttributeForMaxChange(Mana, MaxMana, NewValue, GetManaAttribute());
	}
}

//void UWC_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
//{
//	Super::PostGameplayEffectExecute(Data);
//
//	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
//	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
//	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
//
//	// Compute the delta between old and new, if it is available
//	float DeltaValue = 0;
//	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
//	{
//		// If this was additive, store the raw delta value to be passed along later
//		DeltaValue = Data.EvaluatedData.Magnitude;
//	}
//
//	// Get the Target actor, which should be our owner
//	AActor* TargetActor = nullptr;
//	AController* TargetController = nullptr;
//	AWC_Character* TargetCharacter = nullptr;
//	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
//	{
//		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
//		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
//		TargetCharacter = Cast<AWC_Character>(TargetActor);
//	}
//
//	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
//	{
//		// Get the Source actor
//		AActor* SourceActor = nullptr;
//		AController* SourceController = nullptr;
//		AWC_Character* SourceCharacter = nullptr;
//		if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
//		{
//			SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
//			SourceController = Source->AbilityActorInfo->PlayerController.Get();
//			if (SourceController == nullptr && SourceActor != nullptr)
//			{
//				if (APawn* Pawn = Cast<APawn>(SourceActor))
//				{
//					SourceController = Pawn->GetController();
//				}
//			}
//
//			// Use the controller to find the source pawn
//			if (SourceController)
//			{
//				SourceCharacter = Cast<AWC_Character>(SourceController->GetPawn());
//			}
//			else
//			{
//				SourceCharacter = Cast<AWC_Character>(SourceActor);
//			}
//
//			// Set the causer actor based on context if it's set
//			if (Context.GetEffectCauser())
//			{
//				SourceActor = Context.GetEffectCauser();
//			}
//		}
//
//		// Try to extract a hit result
//		FHitResult HitResult;
//		if (Context.GetHitResult())
//		{
//			HitResult = *Context.GetHitResult();
//		}
//
//		// Store a local copy of the amount of damage done and clear the damage attribute
//		const float LocalDamageDone = GetDamage();
//		SetDamage(0.f);
//
//		if (LocalDamageDone > 0)
//		{
//			// Apply the health change and then clamp it
//			const float OldHealth = GetHealth();
//			SetHealth(FMath::Clamp(OldHealth - LocalDamageDone, 0.0f, GetMaxHealth()));
//
//			if (TargetCharacter)
//			{
//				// This is proper damage
//				TargetCharacter->HandleDamage(LocalDamageDone, HitResult, SourceTags, SourceCharacter, SourceActor);
//
//				// Call for all health changes
//				TargetCharacter->HandleHealthChanged(-LocalDamageDone, SourceTags);
//			}
//		}
//	}
//	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
//	{
//		// Handle other health changes such as from healing or direct modifiers
//		// First clamp it
//		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
//
//		if (TargetCharacter)
//		{
//			// Call for all health changes
//			TargetCharacter->HandleHealthChanged(DeltaValue, SourceTags);
//		}
//	}
//	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
//	{
//		// Clamp mana
//		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
//
//		if (TargetCharacter)
//		{
//			// Call for all mana changes
//			TargetCharacter->HandleManaChanged(DeltaValue, SourceTags);
//		}
//	}
//	else if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute())
//	{
//		if (TargetCharacter)
//		{
//			// Call for all movespeed changes
//			TargetCharacter->HandleMoveSpeedChanged(DeltaValue, SourceTags);
//		}
//	}
//}
