// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_EquipComponent.h"
#include "Engine/TriggerSphere.h"
#include "Engine/TriggerCapsule.h"
#include "Components/SphereComponent.h"
#include "Engine.h"

// Sets default values for this component's properties
UWC_EquipComponent::UWC_EquipComponent()
{
	Equipments.Init(NULL, (int)EEquipmentSlot::EnumMax);

}


// Called when the game starts
void UWC_EquipComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}