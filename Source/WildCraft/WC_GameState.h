// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
//#include "SaveGame/WC_SaveGame_World.h"
#include "WC_GameState.generated.h"

/**
 * 
 */
UCLASS()
class WILDCRAFT_API AWC_GameState : public AGameStateBase
{
	GENERATED_BODY()
	
private:
	class UWC_SaveGame_World* SaveGame;
public:
	class UWC_SaveGame_World* GetSaveGame() { return SaveGame; }
};
