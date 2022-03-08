// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_ItemInstance.h"
#include "GameFramework/WC_GameInstance.h"
#include "Kismet/GameplayStatics.h"

	
UWC_ItemInstance::UWC_ItemInstance()
{
}


UWC_ItemInstance * UWC_ItemInstance::New(int ID_, int Level_, int Count_)
{
	UWC_ItemInstance* new_item = NewObject<UWC_ItemInstance>();

	new_item->Ideal = new_item->FindIdeal(ID_);

	new_item->ID = ID_;
	new_item->Count = Count_;
	new_item->Level = Level_;
	new_item->Life = new_item->Ideal->MaxLife;

	return new_item;
}


const FWC_ItemIdeal * UWC_ItemInstance::FindIdeal(int ID_)
{
	UWC_GameInstance* gi = Cast<UWC_GameInstance>(UGameplayStatics::GetGameInstance(this));

	return gi->GetItemIdeal(ID_);
}
