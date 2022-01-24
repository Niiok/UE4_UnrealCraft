// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VoxelCharacter.h"
#include "GameplayAbilitySet.h"
#include "AbilitySystemInterface.h"
#include "WC_Character.generated.h"

UCLASS()
class WILDCRAFT_API AWC_Character : public AVoxelCharacter
	, public IAbilitySystemInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Ability"/*",meta=(AllowPrivateAccess=true))*/)
		class UAbilitySystemComponent* AbilitySystem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability"/*",meta=(AllowPrivateAccess=true))*/)
		UGameplayAbilitySet* AbilitySet;

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

public:
	AWC_Character();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void AddAbility(TSubclassOf<UGameplayAbility> Ability);

public:

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator,
		AActor * DamageCauser
	) override;

	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable)
		void SetRagdoll(bool bEnabled);

	UFUNCTION(BlueprintCallable)
		inline bool IsRagdoll() { return bRagdoll; }



	// IAbilitySystemInterface을(를) 통해 상속됨
	virtual UAbilitySystemComponent * GetAbilitySystemComponent() const override;

	// IGameplayTagAssetInterface을(를) 통해 상속됨
	virtual void GetOwnedGameplayTags(FGameplayTagContainer & TagContainer) const override;
};
