// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayAbilitySet.h"
#include "AbilitySystemInterface.h"
#include "WC_Character.generated.h"

UCLASS()
class WILDCRAFT_API AWC_Character : public ACharacter
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

public:
	AWC_Character();

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



	// IAbilitySystemInterface��(��) ���� ��ӵ�
	virtual UAbilitySystemComponent * GetAbilitySystemComponent() const override;

	// IGameplayTagAssetInterface��(��) ���� ��ӵ�
	virtual void GetOwnedGameplayTags(FGameplayTagContainer & TagContainer) const override;
};
