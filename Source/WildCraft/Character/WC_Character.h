// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayAbilitySet.h"
#include "AbilitySystemInterface.h"
#include "GameplayTask.h"
#include "WC_Character.generated.h"

UCLASS()
class WILDCRAFT_API AWC_Character : public ACharacter
	, public IAbilitySystemInterface, public IGameplayTaskOwnerInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability"/*",meta=(AllowPrivateAccess=true))*/)
		UGameplayAbilitySet* AbilitySet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability"/*",meta=(AllowPrivateAccess=true))*/)
		class UAbilitySystemComponent* AbilitySystem;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
		UGameplayTasksComponent* GameplayTask;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
		UParticleSystem* particleSystem;


public:
	AWC_Character();

	void GameplayEffect_Sample();


public:

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


	// IGameplayTaskOwnerInterface을(를) 통해 상속됨
	virtual UGameplayTasksComponent* GetGameplayTasksComponent(const UGameplayTask& Task) const override { return GameplayTask; }

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override {}

	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override {}

	virtual AActor* GetGameplayTaskOwner(const UGameplayTask* Task) const override { return Task->GetOwnerActor(); }
};
