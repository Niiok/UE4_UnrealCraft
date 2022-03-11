// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WC_UIController.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class WILDCRAFT_API AWC_UIController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		TSubclassOf<UUserWidget> UIclass;

	UPROPERTY()
		UUserWidget* RootWidget;
};
