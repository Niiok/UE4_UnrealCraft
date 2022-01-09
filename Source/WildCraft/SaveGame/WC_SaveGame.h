// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "WC_SaveGame.generated.h"

/**
 *	
 */
UCLASS()
class WILDCRAFT_API UWC_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int32 UserIndex;


//public:
//	FAsyncSaveGameToSlotDelegate AsyncSaveDelegate;
//	FAsyncLoadGameFromSlotDelegate AsyncLoadDelegate;

public:
	UFUNCTION(BlueprintCallable)
		bool Save();
	UFUNCTION(BlueprintCallable)
		bool Load();
	//UFUNCTION(BlueprintCallable)
	//	bool AsyncSave();
	//UFUNCTION(BlueprintCallable)
	//	bool AsyncLoad();

protected:
	virtual void operator=(USaveGame*) PURE_VIRTUAL(UWC_SaveGame::operator=(USaveGame*), );
};
