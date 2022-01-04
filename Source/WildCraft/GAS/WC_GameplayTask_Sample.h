// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTask.h"
#include "Particles/ParticleSystem.h"
#include "WC_GameplayTask_Sample.generated.h"

/**
 * 
 */
UCLASS()
class WILDCRAFT_API UWC_GameplayTask_Sample : public UGameplayTask
{
	GENERATED_BODY()
	
public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, Category = "Task", meta = (AdvancedDisplay = "TaskOwner", BlueprintInternalUseOnly, DefaultToSelf))
		static UWC_GameplayTask_Sample* ConstructTask(
			TScriptInterface<IGameplayTaskOwnerInterface> TaskOwner,
			UParticleSystem* particleSystem,
			FVector location);

	UParticleSystem* ParticleSystem;
	FVector Location;
};
