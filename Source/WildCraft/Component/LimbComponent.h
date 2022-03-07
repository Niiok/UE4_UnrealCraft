// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "LimbComponent.generated.h"


/*
Enum used in LimbComponent.
L : Left
R : Right
H : Hand
F : Foot
 */
UENUM(BlueprintType)
enum class ELimb : uint8
{
	LH,
	RH,
	LF,
	RF,
	E1,
	E2,
	E3,
	E4,
	ELIMB_MAX
};

//DECLARE_EVENT_ThreeParams(ULimbComponent, FLimbOverlapSignature, AActor*, ATriggerBase*, AWC_Player*);

/*
Generate GameplayEvent with corresponding GameplayTag when limb overlap something.
Using in multiplayer game is not recommended. (coupling of game logic with animation)
 */
UCLASS(ClassGroup = "Custom", meta = (BlueprintSpawnableComponent))
class WILDCRAFT_API ULimbComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Limb", meta = (AllowPrivateAccess = true))
		FName SocketName_LeftHand;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Limb", meta = (AllowPrivateAccess = true))
		FName SocketName_RightHand;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Limb", meta = (AllowPrivateAccess = true))
		FName SocketName_LeftFoot;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Limb", meta = (AllowPrivateAccess = true))
		FName SocketName_RightFoot;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Limb", meta = (AllowPrivateAccess = true))
		FName SocketName_Extra1;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Limb", meta = (AllowPrivateAccess = true))
		FName SocketName_Extra2;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Limb", meta = (AllowPrivateAccess = true))
		FName SocketName_Extra3;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Limb", meta = (AllowPrivateAccess = true))
		FName SocketName_Extra4;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Limb", meta = (AllowPrivateAccess = true))
		float DefaultRadius = 10;

	TArray<UPrimitiveComponent*> LimbPrimitives;
	TSet<AActor*> HitRecord;

public:	
	// Sets default values for this component's properties
	ULimbComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:
	UFUNCTION(BlueprintCallable)
		void SetLimbCollisionResponse(ELimb limb, ECollisionResponse response);

	UFUNCTION(BlueprintCallable)
		ECollisionResponse GetLimbCollisionResponse(ELimb limb) const;

private:
	FName GetSocketName(ELimb limb) const;
	FGameplayTag GetGameplayTag(ELimb limb) const;
	ELimb FindLimb(UPrimitiveComponent* component) const;

private:
	UFUNCTION()
		void OnLimbBeginOverlapFunc(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep, 
			const FHitResult & SweepResult
		);
};
