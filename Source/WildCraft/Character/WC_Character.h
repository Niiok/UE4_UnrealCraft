// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VoxelCharacter.h"
#include "GameplayAbilitySet.h"
#include "AbilitySystemInterface.h"
#include "WC_Character.generated.h"

class UWC_AttributeSet_Character;

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

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Ability"/*",meta=(AllowPrivateAccess=true))*/)
		float MaxHP = 100.0f;
		float CurrentHP;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "UI"/*",meta=(AllowPrivateAccess=true))*/)
		class UWidgetComponent* Widget_HPBar;

private:
		FTransform MeshRelativeTransform;
		bool bRagdoll = false;
		//class AAIController* AiController;

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
		const UWC_AttributeSet_Character* GetAttributeSet() const;

	UFUNCTION(BlueprintCallable)
		void SetRagdoll(bool bEnabled);

	UFUNCTION(BlueprintCallable)
		inline bool IsRagdoll() { return bRagdoll; }

protected:
	UFUNCTION(BlueprintCallable)
		void AddAbility(TSubclassOf<UGameplayAbility> Ability);


	// IAbilitySystemInterface을(를) 통해 상속됨
	virtual UAbilitySystemComponent * GetAbilitySystemComponent() const override;

	// IGameplayTagAssetInterface을(를) 통해 상속됨
	virtual void GetOwnedGameplayTags(FGameplayTagContainer & TagContainer) const override;
};
