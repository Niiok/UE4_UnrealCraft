// Fill out your copyright notice in the Description page of Project Settings.


#include "LimbComponent.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"

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

	LimbPrimitives.Init(NULL, (int)ELimb::ELIMB_MAX);
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

		//LimbPrimitives[i] = Cast<UPrimitiveComponent>(CreateDefaultSubobject<USphereComponent>(GetSocketName((ELimb)i)));

		USphereComponent* NewComponent = NewObject<USphereComponent>(GetOwner(), GetSocketName((ELimb)i));
		check(NewComponent);
		LimbPrimitives[i] = NewComponent;

		NewComponent->OnComponentCreated();
		NewComponent->RegisterComponent();
		if (NewComponent->bWantsInitializeComponent)
			NewComponent->InitializeComponent();
		//NewComponent->SetupAttachment(Cast<ACharacter>(GetOwner())->GetMesh(), GetSocketName((ELimb)i));

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

		// physic, collision, overlap
		NewComponent->SetCollisionProfileName(TEXT("OverlapAll"));
		//NewComponent->SetNotifyRigidBodyCollision(true);
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
		LimbPrimitives[(int)limb]->SetCollisionResponseToAllChannels(response);
		switch (response)
		{
		case ECR_Ignore:
			LimbPrimitives[(int)limb]->SetHiddenInGame(true);
			LimbPrimitives[(int)limb]->SetVisibility(false);
			break;
		case ECR_Overlap:
		case ECR_Block:
			HitRecord.Empty();
			LimbPrimitives[(int)limb]->SetHiddenInGame(false);
			LimbPrimitives[(int)limb]->SetVisibility(true);
			break;
		case ECR_MAX:
			break;
		default:
			break;
		}
		break;
	}
}

ECollisionResponse ULimbComponent::GetLimbCollisionResponse(ELimb limb) const
{
	switch (limb)
	{
	case ELimb::ELIMB_MAX:
		return ECollisionResponse::ECR_MAX;

	default:
		if (GetSocketName(limb) == FName())
			return ECollisionResponse::ECR_MAX;
		else
			return LimbPrimitives[(int)limb]->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn);
	}
}

FName ULimbComponent::GetSocketName(ELimb limb) const
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
		return SocketName_Extra2;
	case ELimb::E3:
		return SocketName_Extra3;
	case ELimb::E4:
		return SocketName_Extra4;
	default:
		return FName();
	}
}

FGameplayTag ULimbComponent::GetGameplayTag(ELimb limb) const
{
	switch (limb)
	{
	case ELimb::LH:
		return FGameplayTag::RequestGameplayTag(TEXT("What.LeftHand"));
	case ELimb::RH:
		return FGameplayTag::RequestGameplayTag(TEXT("What.RightHand"));
	case ELimb::LF:
		return FGameplayTag::RequestGameplayTag(TEXT("What.LeftFoot"));
	case ELimb::RF:
		return FGameplayTag::RequestGameplayTag(TEXT("What.RightFoot"));

	case ELimb::E1:
		return FGameplayTag::RequestGameplayTag(TEXT("What.ExtraLimb1"));
	case ELimb::E2:
		return FGameplayTag::RequestGameplayTag(TEXT("What.ExtraLimb2"));
	case ELimb::E3:
		return FGameplayTag::RequestGameplayTag(TEXT("What.ExtraLimb3"));
	case ELimb::E4:
		return FGameplayTag::RequestGameplayTag(TEXT("What.ExtraLimb4"));
	default:
		return FGameplayTag();
	}
}

ELimb ULimbComponent::FindLimb(UPrimitiveComponent * component) const
{
	int index = LimbPrimitives.Find(component);

	switch (index)
	{
	case (int)ELimb::LH:
		return ELimb::LH;
	case (int)ELimb::RH:
		return ELimb::RH;
	case (int)ELimb::LF:
		return ELimb::LF;
	case (int)ELimb::RF:
		return ELimb::RF;

	case (int)ELimb::E1:
		return ELimb::E1;
	case (int)ELimb::E2:
		return ELimb::E2;
	case (int)ELimb::E3:
		return ELimb::E3;
	case (int)ELimb::E4:
		return ELimb::E4;

	default:
		return ELimb::ELIMB_MAX;
	}
}

void ULimbComponent::OnLimbBeginOverlapFunc(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == GetOwner())
		return;
	if (LimbPrimitives.Contains(OtherComp))
		return;
	if (HitRecord.Contains(OtherActor))
		return;
	else
		HitRecord.Add(OtherActor);

	//FHitResult hit = SweepResult;

	FGameplayEventData gameplay_event;
	gameplay_event.Target = OtherActor;
	gameplay_event.Instigator = GetOwner();
	gameplay_event.OptionalObject = Cast<APawn>(GetOwner())->GetController();
	gameplay_event.EventMagnitude = OverlappedComponent->GetPhysicsLinearVelocity().Size();
	//gameplay_event.ContextHandle.AddHitResult(hit);

	FGameplayTag tag = GetGameplayTag(FindLimb(OverlappedComponent));

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), tag, gameplay_event);

	if (OtherComp->IsSimulatingPhysics() == true)
	{
		//UKismetSystemLibrary::SphereTraceSingle(
		//	GetWorld(), OverlappedComponent->GetComponentLocation(), OtherComp->GetComponentLocation(), Cast<USphereComponent>(OverlappedComponent)->GetScaledSphereRadius(), ETraceTypeQuery::TraceTypeQuery1, )

		OtherComp->AddImpulseAtLocation(OverlappedComponent->GetPhysicsLinearVelocity() * OtherComp->GetMass(), OverlappedComponent->GetComponentLocation());
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Cyan, FString::Printf(TEXT("simulating")));
	}
}