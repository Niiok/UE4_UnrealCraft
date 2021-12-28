// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WC_SaveGame_Character.generated.h"

/**
 * 
 */
UCLASS()
class WILDCRAFT_API UWC_SaveGame_Character : public USaveGame
{
	GENERATED_BODY()
	
		// ID (dna)

		// state
			// died or not
			// buff, debuff

		// items (inventory)
			// useable tool
			// backpack
			// wearing

		// skill
			// useable action
			// knowledge

		// stats ?
			// strength, vitality, ...

		// level ?

};
