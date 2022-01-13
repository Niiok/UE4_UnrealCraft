// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_EquipComponent.h"
#include "Engine/TriggerSphere.h"
#include "Engine/TriggerCapsule.h"
#include "Components/SphereComponent.h"
#include "Engine.h"

// Sets default values for this component's properties
UWC_EquipComponent::UWC_EquipComponent()
{
	Equipments.Init(NULL, (int)EEquipmentSlot::EnumMax);
	Triggers.Init(NULL, (int)EEquipmentCollision::EnumMax);

}


// Called when the game starts
void UWC_EquipComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	for (int i = 0; i < (int)EEquipmentCollision::EnumMax; ++i)
		switch ((EEquipmentCollision)i)
		{
		case EEquipmentCollision::LH:
		case EEquipmentCollision::RH:
		case EEquipmentCollision::LF:
		case EEquipmentCollision::RF:
			Triggers[i] = GetWorld()->SpawnActor<ATriggerSphere>();
			Triggers[i]->SetActorScale3D(FVector(0.2, 0.2, 0.2));
			break;
		case EEquipmentCollision::E1:
		case EEquipmentCollision::E2:
		case EEquipmentCollision::E3:
			//Triggers[i] = GetWorld()->SpawnActor<ATriggerCapsule>();
			break;
		default:
			break;
		}

	Triggers[(int)EEquipmentCollision::LH]->AttachToComponent(
		Cast<ACharacter>(GetOwner())->GetMesh(),
		FAttachmentTransformRules(
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepRelative,
			true),
		TEXT("hand_l")
	);
	Triggers[(int)EEquipmentCollision::RH]->AttachToComponent(
		Cast<ACharacter>(GetOwner())->GetMesh(),
		FAttachmentTransformRules(
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepRelative, true),
		TEXT("hand_r")
	);
	Triggers[(int)EEquipmentCollision::LF]->AttachToComponent(
		Cast<ACharacter>(GetOwner())->GetMesh(),
		FAttachmentTransformRules(
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepRelative, true),
		TEXT("ball_l")
	);
	Triggers[(int)EEquipmentCollision::RF]->AttachToComponent(
		Cast<ACharacter>(GetOwner())->GetMesh(),
		FAttachmentTransformRules(
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepRelative, true),
		TEXT("ball_r")
	);

	Triggers[(int)EEquipmentCollision::LH]->OnActorBeginOverlap.AddDynamic(this, &UWC_EquipComponent::OnTriggerBeginOverlapFunc);
	Triggers[(int)EEquipmentCollision::RH]->OnActorBeginOverlap.AddDynamic(this, &UWC_EquipComponent::OnTriggerBeginOverlapFunc);
	Triggers[(int)EEquipmentCollision::LF]->OnActorBeginOverlap.AddDynamic(this, &UWC_EquipComponent::OnTriggerBeginOverlapFunc);
	Triggers[(int)EEquipmentCollision::RF]->OnActorBeginOverlap.AddDynamic(this, &UWC_EquipComponent::OnTriggerBeginOverlapFunc);

	Triggers[(int)EEquipmentCollision::LH]->SetActorLabel(TEXT("Left Hand Trigger"));
	Triggers[(int)EEquipmentCollision::RH]->SetActorLabel(TEXT("Right Hand Trigger"));
	Triggers[(int)EEquipmentCollision::LF]->SetActorLabel(TEXT("Left Foot Trigger"));
	Triggers[(int)EEquipmentCollision::RF]->SetActorLabel(TEXT("Right Foot Trigger"));
	
}

void UWC_EquipComponent::OnTriggerBeginOverlapFunc(AActor * actor, AActor * other)
{
	if (other == GetOwner())
		return;

	if (Triggers.Find(other) != INDEX_NONE)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, FString::Printf(TEXT("%s hitted by %s"), *other->GetActorLabel(), *actor->GetActorLabel()));
	//,*(actor->GetVelocity() - other->GetVelocity()).ToString()));
	//UE_LOG(LogTemp, Display, TEXT("wow"));
}

