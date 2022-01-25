// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WC_Struct.h"
#include "WC_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class WILDCRAFT_API UWC_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UWC_GameInstance();

	virtual void Init() override;
	
	const FWC_CharacterIdeal* GetCharacterIdeal(FString name) const;
	const FWC_ItemIdeal* GetItemIdeal(int id) const;

private:
	UPROPERTY()
		const class UDataTable* CharacterTable;
	UPROPERTY()
		const class UDataTable* ItemTable;
};
