// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_ItemInstance.h"

bool UWC_ItemInstance::_loaded = false;
TMap<int, const FWC_ItemIdeal> UWC_ItemInstance::_ideals;

	
UWC_ItemInstance::UWC_ItemInstance()
{
	if (!_loaded)
		_Load();
}


UWC_ItemInstance * UWC_ItemInstance::New(int ID_, int level_, int count_)
{
	UWC_ItemInstance* new_item = NewObject<UWC_ItemInstance>();

	new_item->Ideal = _GetIdeal(ID_);

	new_item->ID = ID_;
	new_item->Count = count_;
	new_item->Level = level_;
	new_item->Life = new_item->Ideal->MaxLife;

	return new_item;
}



void UWC_ItemInstance::_Load()
{
	if (_loaded)
		return;

	const FString reference = TEXT("DataTable'/Game/WildCraft/Item/ItemIdeal.ItemIdeal'");

	ConstructorHelpers::FObjectFinder<UDataTable> helper(*reference);
	if (helper.Succeeded())
	{
		UDataTable* table = helper.Object;
		TArray<FWC_ItemIdeal*> temp_array;

		table->GetAllRows<FWC_ItemIdeal>("", temp_array);

		for (auto i : temp_array)
		{
			if (i->ID != 0)
				_ideals.Add(i->ID, *i);

			//UE_LOG(LogTemp, Error, TEXT("item data found : %d, %s"), i->ID, *(i->Name.ToString()));
		}

		_loaded = true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("item data not found!"));
	}
}

const FWC_ItemIdeal * UWC_ItemInstance::_GetIdeal(int ID_)
{
	return _ideals.Find(ID_);
}
