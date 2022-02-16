// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "WC_UserWidget_Character.generated.h"

/**
 * 
 */
UCLASS()
class WILDCRAFT_API UWC_UserWidget_Character : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bUpdateOnHealthChange = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bUpdateOnManaChange = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bUpdateOnMoveSpeedChange = false;

	UPROPERTY(BlueprintReadOnly)
		class UWC_AttributeSet_Character* AttributeSet;

public:
	UFUNCTION(BlueprintCallable)
		void BindCharacter(class AWC_Character* attribute);

	UFUNCTION(BlueprintImplementableEvent)
		void Update(float DeltaValue, const struct FGameplayTagContainer& EventTags);
};
