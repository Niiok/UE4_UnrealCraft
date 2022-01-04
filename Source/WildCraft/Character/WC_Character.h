// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayAbilitySet.h"
#include "AbilitySystemInterface.h"
#include "WC_Character.generated.h"

UCLASS()
class WILDCRAFT_API AWC_Character : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = "true"))
		UGameplayAbilitySet* AbilitySet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = "true"))
		class UAbilitySystemComponent* AbilitySystem;



public:
	AWC_Character();

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator,
		AActor * DamageCauser
	) override;

	virtual void PostInitializeComponents() override;

	// IAbilitySystemInterface을(를) 통해 상속됨
	virtual UAbilitySystemComponent * GetAbilitySystemComponent() const override;
};
