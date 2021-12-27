// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"

USTRUCT(BlueprintType)
struct FItemIdea : public FTableRowBase
{
	GENERATED_BODY()

public:
	//UPROPERTY(EditAnywhere)

	// ID
	// name

	// 2d image
	// 3d model

	// max stack count
	// max llfe (durability)
	// weight

	// droppable
	// consumeable
	// usable
	// equipable
	// tradable
	// disassemable
	// splicable

	// burnable
	// metalic


		// instance data
			// level
			// count
			// life (durability)
};