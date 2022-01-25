// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_GameInstance.h"
#include "Engine/DataTable.h"


UWC_GameInstance::UWC_GameInstance()
{
	//static ConstructorHelpers::FObjectFinder<UDataTable> table(
	//	TEXT("")
	//	);
	//check(table.Succeeded());
	//AttributeTable = table.Object;
	//check(AttributeTable->GetRowMap().Num() > 0);
}	
  
void UWC_GameInstance::Init()
{
	Super::Init();

	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, )
}

const FWC_CharacterIdeal * UWC_GameInstance::GetCharacterIdeal(FString name) const
{
	return CharacterTable->FindRow<FWC_CharacterIdeal>(*name, TEXT(""));
}

const FWC_ItemIdeal * UWC_GameInstance::GetItemIdeal(int id) const
{
	return ItemTable->FindRow<FWC_ItemIdeal>(*FString::FromInt(id), TEXT(""));
}

