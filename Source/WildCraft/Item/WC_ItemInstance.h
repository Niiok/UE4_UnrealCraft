// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WC_ItemInstance.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class WILDCRAFT_API UWC_ItemInstance : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
		int ID;
	UPROPERTY(VisibleAnywhere)
		float Life;
	UPROPERTY(VisibleAnywhere)
		int Count;
	UPROPERTY(VisibleAnywhere)
		int Level;

private:
	const struct FWC_ItemIdeal* Ideal;

public:
	UWC_ItemInstance();

	UFUNCTION(BlueprintCallable)
		static UWC_ItemInstance* New(int ID_, int Level_ = 1, int Count_ = 1);

private:
	const struct FWC_ItemIdeal* FindIdeal(int ID_);
};
