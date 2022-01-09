// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "WC_ItemInstance.generated.h"

USTRUCT(BlueprintType)
struct FWC_ItemIdeal : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		int ID;
	UPROPERTY(EditAnywhere)
		int MaxCount;
	UPROPERTY(EditAnywhere)
		float MaxLife;
	UPROPERTY(EditAnywhere)
		int Weight;

	UPROPERTY(EditAnywhere)
		FText Name;
	UPROPERTY(EditAnywhere)
		class UTexture2D* Image;
	UPROPERTY(EditAnywhere)
		class UStaticMesh* Model;


	UPROPERTY(EditAnywhere)
		uint8 Equipable : 1;
	UPROPERTY(EditAnywhere)
		uint8 Consumable : 1;

	UPROPERTY(EditAnywhere)
		uint8 Volatile : 1;
	UPROPERTY(EditAnywhere)
		uint8 Conductive : 1;

	UPROPERTY(EditAnywhere)
		uint8 Droppable : 1;
	UPROPERTY(EditAnywhere)
		uint8 Tradable : 1;
	UPROPERTY(EditAnywhere)
		uint8 Disassemable : 1;
	UPROPERTY(EditAnywhere)
		uint8 Splicable : 1;
};

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
	const FWC_ItemIdeal* Ideal;



public:
	UWC_ItemInstance();

	UFUNCTION(BlueprintCallable)
		static UWC_ItemInstance* New(int ID_, int Level_ = 1, int Count_ = 1);





private:
	static bool _Loaded;
	static TMap<int, const FWC_ItemIdeal> _Ideals;

	static void _Load();

	static const FWC_ItemIdeal* _GetIdeal(int ID_);
};
