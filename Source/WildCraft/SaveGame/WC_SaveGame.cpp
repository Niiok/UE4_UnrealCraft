// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_SaveGame.h"

bool UWC_SaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, SaveSlotName, UserIndex);
}

bool UWC_SaveGame::Load()
{
	USaveGame* new_savegame = UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex);

	if (new_savegame)
	{
		*this = new_savegame;
		return true;
	}
	else
		return false;
}

//bool UWC_SaveGame::AsyncSave()
//{
//	return false;
//}
//
//bool UWC_SaveGame::AsyncLoad()
//{
//	return false;
//}
