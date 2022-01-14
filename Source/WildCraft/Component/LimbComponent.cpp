// Fill out your copyright notice in the Description page of Project Settings.


#include "LimbComponent.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
ULimbComponent::ULimbComponent()
{
	SocketName_LeftHand = TEXT("hand_l");
	SocketName_RightHand = TEXT("hand_r");
	SocketName_LeftFoot = TEXT("ball_l");
	SocketName_RightFoot = TEXT("ball_r");
	SocketName_Extra1 = TEXT("");
	SocketName_Extra2 = TEXT("");
	SocketName_Extra3 = TEXT("");
	SocketName_Extra4 = TEXT("");

	LimbSpheres.Init(NULL, (int)ELimb::EnumTotal);
	// ...

	//generate spheres
}


// Called when the game starts
void ULimbComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < (int)ELimb::EnumTotal; ++i)
	{
		if (GetSocketName((ELimb)i) == TEXT(""))
			continue;

		LimbSpheres[i] = NewObject<USphereComponent>(GetOwner(), GetSocketName((ELimb)i));
		LimbSpheres[i]->RegisterComponent();
		LimbSpheres[i]->SetupAttachment(GetOwner()->GetRootComponent());
		if (LimbSpheres[i]->bWantsInitializeComponent)
			LimbSpheres[i]->InitializeComponent();

		//LimbSpheres[i] = Cast<UPrimitiveComponent>(GetOwner()->CreateDefaultSubobject<USphereComponent>(GetSocketName((ELimb)i)));
		LimbSpheres[i]->SetRelativeScale3D(FVector(0.2, 0.2, 0.2));


		LimbSpheres[i]->AttachToComponent(
			Cast<ACharacter>(GetOwner())->GetMesh(),
			FAttachmentTransformRules(
				EAttachmentRule::SnapToTarget,
				EAttachmentRule::SnapToTarget,
				EAttachmentRule::KeepRelative,
				true),
			GetSocketName((ELimb)i)
		);

		LimbSpheres[i]->OnComponentBeginOverlap.AddDynamic(this, &ULimbComponent::OnLimbBeginOverlapFunc);

		LimbSpheres[i]->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Block);
		LimbSpheres[i]->SetVisibility(true);
	}

	// ...
	// change channel
	// not visible
	
}

FName ULimbComponent::GetSocketName(ELimb limb)
{
	switch (limb)
	{
	case ELimb::LH:
		return SocketName_LeftHand;
	case ELimb::RH:
		return SocketName_RightHand;
	case ELimb::LF:
		return SocketName_LeftFoot;
	case ELimb::RF:
		return SocketName_RightFoot;
	case ELimb::E1:
		return SocketName_Extra1;
	case ELimb::E2:
		return SocketName_Extra1;
	case ELimb::E3:
		return SocketName_Extra1;
	case ELimb::E4:
		return SocketName_Extra1;
	default:
		return FName();
	}
}

void ULimbComponent::OnLimbBeginOverlapFunc(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == GetOwner())
		return;

	if (LimbSpheres.Find(OtherComp) != INDEX_NONE)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, FString::Printf(TEXT("%s hitted by %s"), *OverlappedComponent->GetName(), *OtherActor->GetActorLabel()));
	//,*(actor->GetVelocity() - other->GetVelocity()).ToString()));
	//UE_LOG(LogTemp, Display, TEXT("wow"));
}
