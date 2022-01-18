// Fill out your copyright notice in the Description page of Project Settings.


#include "LimbComponent.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
ULimbComponent::ULimbComponent()
{
	SocketName_LeftHand = TEXT("hand_l");
	SocketName_RightHand = TEXT("hand_r");
	SocketName_LeftFoot = TEXT("foot_l");
	SocketName_RightFoot = TEXT("foot_r");
	SocketName_Extra1 = FName();
	SocketName_Extra2 = FName();
	SocketName_Extra3 = FName();
	SocketName_Extra4 = FName();

	LimbSpheres.Init(NULL, (int)ELimb::ELIMB_MAX);
	// ...

	//generate spheres
}


// Called when the game starts
void ULimbComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < (int)ELimb::ELIMB_MAX; ++i)
	{
		if (GetSocketName((ELimb)i) == TEXT(""))
			continue;

		//LimbSpheres[i] = Cast<UPrimitiveComponent>(CreateDefaultSubobject<USphereComponent>(GetSocketName((ELimb)i)));

		USphereComponent* NewComponent = NewObject<USphereComponent>(GetOwner(), GetSocketName((ELimb)i));
		check(NewComponent);
		LimbSpheres[i] = NewComponent;

		NewComponent->OnComponentCreated();
		NewComponent->RegisterComponent();
		NewComponent->SetupAttachment(GetOwner()->GetRootComponent());
		if (NewComponent->bWantsInitializeComponent)
			NewComponent->InitializeComponent();

		UE_LOG(LogTemp, Display, TEXT("Generated %s"), *GetSocketName((ELimb)i).ToString());

		//NewComponent->SetRelativeScale3D(FVector(0.2, 0.2, 0.2));
		NewComponent->SetSphereRadius(DefaultRadius);
		NewComponent->AttachToComponent(
			Cast<ACharacter>(GetOwner())->GetMesh(),
			FAttachmentTransformRules(
				EAttachmentRule::SnapToTarget,
				EAttachmentRule::SnapToTarget,
				EAttachmentRule::KeepRelative,
				true),
			GetSocketName((ELimb)i)
		);

		NewComponent->OnComponentBeginOverlap.AddDynamic(this, &ULimbComponent::OnLimbBeginOverlapFunc);
		NewComponent->OnComponentHit.AddDynamic(this, &ULimbComponent::OnLimbHitFunc);


		// physic, collision, overlap
		NewComponent->SetGenerateOverlapEvents(true);
		NewComponent->SetVisibility(true);
		NewComponent->SetHiddenInGame(false);
		NewComponent->SetCollisionProfileName(TEXT("BlockAll") );
		NewComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		NewComponent->UpdateCollisionProfile();


		//NewComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Block);
	}	
	SetLimbCollisionResponse(ELimb::ELIMB_MAX, ECollisionResponse::ECR_Ignore);
}

void ULimbComponent::SetLimbCollisionResponse(ELimb limb, ECollisionResponse response)
{

	switch (limb)
	{
	case ELimb::ELIMB_MAX:
		for (int i = 0; i < (int)ELimb::ELIMB_MAX; ++i)
			SetLimbCollisionResponse((ELimb)i, response);
		break;

	default:
		if (GetSocketName(limb) == FName())
			return;
		LimbSpheres[(int)limb]->SetCollisionResponseToAllChannels(response);
		switch (response)
		{
		case ECR_Ignore:
			LimbSpheres[(int)limb]->SetHiddenInGame(true);
			LimbSpheres[(int)limb]->SetVisibility(false);
			break;
		case ECR_Overlap:
		case ECR_Block:
			LimbSpheres[(int)limb]->SetHiddenInGame(false);
			LimbSpheres[(int)limb]->SetVisibility(true);
			break;
		case ECR_MAX:
			break;
		default:
			break;
		}
		break;
	}
}

ECollisionResponse ULimbComponent::GetLimbCollisionResponse(ELimb limb)
{
	switch (limb)
	{
	case ELimb::ELIMB_MAX:
		return ECollisionResponse::ECR_MAX;

	default:
		if (GetSocketName(limb) == FName())
			return ECollisionResponse::ECR_MAX;
		else
			return LimbSpheres[(int)limb]->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn);
	}
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

void ULimbComponent::OnLimbHitFunc(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{	
	if (OtherActor == GetOwner())
		return;

	if (LimbSpheres.Find(OtherComp) != INDEX_NONE)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, FString::Printf(TEXT("%s hitted by %s"), *HitComponent->GetName(), *OtherActor->GetActorLabel()));
}
