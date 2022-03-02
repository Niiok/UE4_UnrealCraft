// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
//#include "SaveGame/WC_SaveGame_Character.h"
#include "WC_PlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerStateChangeDelegate);

/**
 * 
 */
UCLASS()
class WILDCRAFT_API AWC_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
private:
	class UWC_SaveGame_Character* SaveGame;
public:
	class UWC_SaveGame_Character* GetSaveGame() { return SaveGame; }
};
