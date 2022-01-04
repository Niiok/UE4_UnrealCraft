// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_GameplayTask_Sample.h"
#include "Kismet/GameplayStatics.h"

void UWC_GameplayTask_Sample::Activate()
{
	Super::Activate();

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, Location);
}


UWC_GameplayTask_Sample * UWC_GameplayTask_Sample::ConstructTask(TScriptInterface<IGameplayTaskOwnerInterface> TaskOwner, UParticleSystem * particleSystem, FVector location)
{
	UWC_GameplayTask_Sample* task = NewTask<UWC_GameplayTask_Sample>(TaskOwner);

	if (task)
	{
		task->ParticleSystem = particleSystem;
		task->Location = location;
	}
	return task;
}
