// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "WC_AttributeSet_Sample.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class WILDCRAFT_API UWC_AttributeSet_Sample : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attribute")
		float HP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attribute")
		float Mana;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attribute")
		float Speed;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attribute")

};
