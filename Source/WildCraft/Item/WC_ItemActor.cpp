// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_ItemActor.h"


TQueue<AWC_ItemActor*> AWC_ItemActor::_Pool;


// Sets default values
AWC_ItemActor::AWC_ItemActor()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}

// Called when the game starts or when spawned
void AWC_ItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWC_ItemActor::_SetItemInstance(UWC_ItemInstance * Instance_)
{
}

AWC_ItemActor * AWC_ItemActor::New(UWC_ItemInstance * Instance_, const FVector& Location_, const FRotator& Rotation_)
{
	AWC_ItemActor* ret;

	if (_Pool.IsEmpty())
		ret = Instance_->GetWorld()->SpawnActor<AWC_ItemActor>(Location_, Rotation_);
	else
		_Pool.Dequeue(ret);

	ret->SetHidden(false);

	ret->_SetItemInstance(Instance_);

	return ret;
}
