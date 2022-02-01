// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "WC_AttributeSet_Character.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

//DECLARE_EVENT_FiveParams(UWC_AttributeSet_Character, FWC_AttributeEvent_Damage, float, const FHitResult&, const struct FGameplayTagContainer&, class AWC_Character*, AActor*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FWC_AttributeEvent_Damage, float, DamageAmount, const FHitResult&, HitInfo, const struct FGameplayTagContainer&, DamageTags, AWC_Character*, InstigatorCharacter, AActor*, DamageCauser);
//DECLARE_EVENT_TwoParams(UWC_AttributeSet_Character, FWC_AttributeEvent, float, const struct FGameplayTagContainer&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWC_AttributeEvent, float, DeltaValue, const struct FGameplayTagContainer&, EventTags);

/**
 * 
 */
UCLASS()
class WILDCRAFT_API UWC_AttributeSet_Character : public UAttributeSet
{
	GENERATED_BODY()
public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Current Health, when 0 we expect owner to die. Capped by MaxHealth */
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Attribute", ReplicatedUsing = "OnRep_Health")
		FGameplayAttributeData Health;
	FWC_AttributeEvent OnHealthChanged;
	ATTRIBUTE_ACCESSORS(UWC_AttributeSet_Character, Health)
	
	/** MaxHealth is its own attribute, since GameplayEffects may modify it */
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Attribute", ReplicatedUsing = "OnRep_MaxHealth")
		FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UWC_AttributeSet_Character, MaxHealth)

	/** Current Mana, used to execute special abilities. Capped by MaxMana */
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Attribute", ReplicatedUsing = "OnRep_Mana")
		FGameplayAttributeData Mana;
	FWC_AttributeEvent OnManaChanged;
	ATTRIBUTE_ACCESSORS(UWC_AttributeSet_Character, Mana)

	/** MaxMana is its own attribute, since GameplayEffects may modify it */
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Attribute", ReplicatedUsing = "OnRep_MaxMana")
		FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UWC_AttributeSet_Character, MaxMana)

	/** AttackPower of the attacker is multiplied by the base Damage to reduce health, so 1.0 means no bonus */
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Attribute", ReplicatedUsing = "OnRep_AttackPower")
		FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UWC_AttributeSet_Character, AttackPower)

	/** Base Damage is divided by DefensePower to get actual damage done, so 1.0 means no bonus */
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Attribute", ReplicatedUsing = "OnRep_DefensePower")
		FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UWC_AttributeSet_Character, DefensePower)

	/** MoveSpeed affects how fast characters can move */
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Attribute", ReplicatedUsing = "OnRep_MoveSpeed")
		FGameplayAttributeData MoveSpeed;
	FWC_AttributeEvent OnMoveSpeedChanged;
	ATTRIBUTE_ACCESSORS(UWC_AttributeSet_Character, MoveSpeed)

	/** Damage is a 'temporary' attribute used by the DamageExecution to calculate final damage, which then turns into -Health */
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Attribute")
		FGameplayAttributeData Damage;
	FWC_AttributeEvent_Damage OnDamaged;
	ATTRIBUTE_ACCESSORS(UWC_AttributeSet_Character, Damage)

protected:
	/** Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes. (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before) */
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

	// These OnRep functions exist to make sure that the ability system internal representations are synchronized properly during replication
	UFUNCTION()
		virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_Mana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_MaxMana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_AttackPower(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_DefensePower(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldValue);
};
