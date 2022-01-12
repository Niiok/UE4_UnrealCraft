// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerBase.h"
#include "Character/WC_Player.h"
#include "WC_EquipComponent.generated.h"


UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
	Head,
	Chest,
	Legs,
	Hands,
	Feet,
	EnumMax
};

UENUM(BlueprintType)
enum class EEquipmentCollision : uint8
{
	LH,
	RH,
	LF,
	RF,
	E1,
	E2,
	E3,
	EnumMax
};

DECLARE_EVENT_ThreeParams(UWC_EquipComponent, FEquipmentTriggerBeginOverlapSignature, AActor*, ATriggerBase*, AWC_Player*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WILDCRAFT_API UWC_EquipComponent : public UActorComponent
{
	GENERATED_BODY()


private:
	TArray<class AWC_ItemActor*> Equipments;// ((int)EEquipmentSlot::EnumMax);
	TArray<class ATriggerBase*> Triggers;// ((int)EEquipmentCollision::EnumMax);


public:	
	// Sets default values for this component's properties
	UWC_EquipComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		

public:
	FEquipmentTriggerBeginOverlapSignature OnTriggerBeginOverlap[(int)EEquipmentCollision::EnumMax];
	UFUNCTION()
		void OnTriggerBeginOverlapFunc(AActor* actor, AActor* other);
};
