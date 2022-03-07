// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WC_GameplayAbility_Sample.generated.h"

/**
 * 
 */
UCLASS()
class WILDCRAFT_API UWC_GameplayAbility_Sample : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	// ----------------------------------------------------------------------------------------------------------------
	//
	//	The important functions:
	//	
	//		CanActivateAbility()	- const function to see if ability is activatable. Callable by UI etc
	//
	//		TryActivateAbility()	- Attempts to activate the ability. Calls CanActivateAbility(). Input events can call this directly.
	//								- Also handles instancing-per-execution logic and replication/prediction calls.
	//		
	//		CallActivateAbility()	- Protected, non virtual function. Does some boilerplate 'pre activate' stuff, then calls ActivateAbility()
	//
	//		ActivateAbility()		- What the abilities *does*. This is what child classes want to override.
	//	
	//		CommitAbility()			- Commits reources/cooldowns etc. ActivateAbility() must call this!
	//		
	//		CancelAbility()			- Interrupts the ability (from an outside source).
	//
	//		EndAbility()			- The ability has ended. This is intended to be called by the ability to end itself.
	//	
	// ----------------------------------------------------------------------------------------------------------------

	virtual bool CanActivateAbility
	(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo * ActorInfo,
		const FGameplayTagContainer * SourceTags,
		const FGameplayTagContainer * TargetTags,
		OUT FGameplayTagContainer * OptionalRelevantTags
	) const override {
		return true;
	}

	virtual bool CheckCost
	(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo * ActorInfo,
		OUT FGameplayTagContainer * OptionalRelevantTags
	) const override {
		return true;
		//return Super::CheckCost(Handle, ActorInfo, OptionalRelevantTags);
	}

	virtual void ActivateAbility
	(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo * ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData * TriggerEventData
	) override {}

	virtual void InputPressed
	(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo * ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo
	) override {}
};
