// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item/WC_ItemInstance.h"
#include "WC_ItemActor.generated.h"

UCLASS()
class WILDCRAFT_API AWC_ItemActor : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly)
		class UWC_ItemInstance* Item;

	class UStaticMeshComponent* StaticMesh;



public:	
	// Sets default values for this actor's properties
	AWC_ItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	virtual void _SetItemInstance(class UWC_ItemInstance* Instance_);


public:
	static AWC_ItemActor* New(class UWC_ItemInstance* Instance_, const FVector& Location_, const FRotator& Rotation_);
private:
	static TQueue<AWC_ItemActor*> _Pool;
};
