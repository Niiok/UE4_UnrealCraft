// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "WC_Struct.generated.h"

USTRUCT(BlueprintType)
struct FWC_CharacterIdeal : public FTableRowBase
{
	GENERATED_BODY()

public:
	FWC_CharacterIdeal() {}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
		int Level;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
		float MaxHealth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
		float MaxMana;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
		float AttackPower;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
		float DefensePower;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
		float MoveSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
		int DropExp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
		int NextExp;
};



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