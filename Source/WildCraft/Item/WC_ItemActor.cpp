// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_ItemActor.h"

// Sets default values
AWC_ItemActor::AWC_ItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWC_ItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWC_ItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

