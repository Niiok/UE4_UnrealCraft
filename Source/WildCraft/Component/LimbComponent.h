// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LimbComponent.generated.h"


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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WILDCRAFT_API ULimbComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Limb", meta = (AllowPrivateAccess = true))
		FName SocketName_LeftHand;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Limb", meta = (AllowPrivateAccess = true))
		FName SocketName_RightHand;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Limb", meta = (AllowPrivateAccess = true))
		FName SocketName_LeftFoot;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Limb", meta = (AllowPrivateAccess = true))
		FName SocketName_RightFoot;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Limb", meta = (AllowPrivateAccess = true))
		FName SocketName_Extra1;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Limb", meta = (AllowPrivateAccess = true))
		FName SocketName_Extra2;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Limb", meta = (AllowPrivateAccess = true))
		FName SocketName_Extra3;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Limb", meta = (AllowPrivateAccess = true))
		FName SocketName_Extra4;

	TArray<UPrimitiveComponent*> LimbSpheres;

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
		ECollisionResponse GetLimbCollisionResponse(ELimb limb);

private:
	FName GetSocketName(ELimb limb);

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
	UFUNCTION()
		void OnLimbHitFunc(
			UPrimitiveComponent* HitComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpulse,
			const FHitResult& Hit
		);
};
