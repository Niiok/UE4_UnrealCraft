// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VoxelCharacter.h"
#include "GameplayAbilitySet.h"
#include "AbilitySystemInterface.h"
#include "Status/RPG_StatusInterface.h"
#include "Items/RPG_InventoryInterface.h"
#include "WC_CharacterBase.generated.h"

UCLASS()
class WILDCRAFT_API AWC_CharacterBase : public AVoxelCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWC_CharacterBase();

//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;

public:
	virtual IRPG_StatusInterface* GetStatus() { return NULL; } //PURE_VIRTUAL(AWC_CharacterBase::GetStatus);
	virtual IRPG_InventoryInterface* GetInventory() { return NULL; } //PURE_VIRTUAL(AWC_CharacterBase::GetInventory);
};
