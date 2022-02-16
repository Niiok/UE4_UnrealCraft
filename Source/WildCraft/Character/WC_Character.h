// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VoxelCharacter.h"
#include "GameplayAbilitySet.h"
#include "AbilitySystemInterface.h"
#include "WC_Character.generated.h"

class UWC_AttributeSet_Character;

DECLARE_EVENT_FiveParams(AWC_Character, FWC_AttributeEvent_Damage, float, const FHitResult&, const struct FGameplayTagContainer&, class AWC_Character*, AActor*);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FWC_AttributeEvent_Damage, float, DamageAmount, const FHitResult&, HitInfo, const struct FGameplayTagContainer&, DamageTags, AWC_Character*, InstigatorCharacter, AActor*, DamageCauser);
DECLARE_EVENT_TwoParams(AWC_Character, FWC_AttributeEvent, float, const struct FGameplayTagContainer&);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWC_AttributeEvent, float, DeltaValue, const struct FGameplayTagContainer&, EventTags);

/*
Every combatable Characters in this game inherited by this class.
*/
UCLASS()
class WILDCRAFT_API AWC_Character : public AVoxelCharacter
	, public IAbilitySystemInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Ability"/*",meta=(AllowPrivateAccess=true))*/)
		class UAbilitySystemComponent* AbilitySystem;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability"/*",meta=(AllowPrivateAccess=true))*/)
		//UGameplayAbilitySet* AbilitySet;

	//const class UWC_AttributeSet_Character* AttributeSet;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Ability"/*",meta=(AllowPrivateAccess=true))*/)
		class ULimbComponent* Limb;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "UI"/*",meta=(AllowPrivateAccess=true))*/)
		class UWidgetComponent* Widget_HPBar;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Voxel"/*",meta=(AllowPrivateAccess=true))*/)
		class UVoxelNoClippingComponent* NoClipping;

private:
		FTransform MeshRelativeTransform;
		bool bRagdoll = false;
		//class AAIController* AiController;
		//UGameplayEffect* DamageGE;

public:
	AWC_Character();


	///////////////
	// ue4 methods
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:
	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator,
		AActor * DamageCauser
	) override;

	virtual void PostInitializeComponents() override;


	///////////////////
	// original methods
public:
	UFUNCTION(BlueprintCallable)
		UWC_AttributeSet_Character * GetAttributeSet() const;

	UFUNCTION(BlueprintCallable)
		void SetRagdoll(bool bEnabled);

	UFUNCTION(BlueprintCallable)
		inline bool IsRagdoll() { return bRagdoll; }

protected:
	UFUNCTION(BlueprintCallable)
		void AddAbility(TSubclassOf<UGameplayAbility> Ability);

	/**
	 * Called when character takes damage, which may have killed them
	 *
	 * @param DamageAmount Amount of damage that was done, not clamped based on current health
	 * @param HitInfo The hit info that generated this damage
	 * @param DamageTags The gameplay tags of the event that did the damage
	 * @param InstigatorCharacter The character that initiated this damage
	 * @param DamageCauser The actual actor that did the damage, might be a weapon or projectile
	 */
	UFUNCTION(BlueprintImplementableEvent)
		void OnDamaged(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, AWC_Character* InstigatorCharacter, AActor* DamageCauser);

	/**
	 * Called when health is changed, either from healing or from being damaged
	 * For damage this is called in addition to OnDamaged/OnKilled
	 *
	 * @param DeltaValue Change in health value, positive for heal, negative for cost. If 0 the delta is unknown
	 * @param EventTags The gameplay tags of the event that changed mana
	 */
	UFUNCTION(BlueprintImplementableEvent)
		void OnHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	/**
	 * Called when mana is changed, either from healing or from being used as a cost
	 *
	 * @param DeltaValue Change in mana value, positive for heal, negative for cost. If 0 the delta is unknown
	 * @param EventTags The gameplay tags of the event that changed mana
	 */
	UFUNCTION(BlueprintImplementableEvent)
		void OnManaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	/**
	 * Called when movement speed is changed
	 *
	 * @param DeltaValue Change in move speed
	 * @param EventTags The gameplay tags of the event that changed mana
	 */
	UFUNCTION(BlueprintImplementableEvent)
		void OnMoveSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

public:
	// Called from RPGAttributeSet, these call BP events above
	virtual void HandleDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, AWC_Character* InstigatorCharacter, AActor* DamageCauser);
	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleManaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleMoveSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	FWC_AttributeEvent_Damage OnDamageDelegate;
	FWC_AttributeEvent OnHealthChangeDelegate;
	FWC_AttributeEvent OnManaChangeDelegate;
	FWC_AttributeEvent OnMoveSpeedChangeDelegate;


	// IAbilitySystemInterface을(를) 통해 상속됨
	virtual UAbilitySystemComponent * GetAbilitySystemComponent() const override;

	// IGameplayTagAssetInterface을(를) 통해 상속됨
	virtual void GetOwnedGameplayTags(FGameplayTagContainer & TagContainer) const override;
};
