// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_UserWidget_Character.h"
#include "Character/WC_Character.h"
#include "GAS/WC_AttributeSet_Character.h"

void UWC_UserWidget_Character::BindCharacter(AWC_Character * character)
{
	if (character == nullptr)
		return;

	AttributeSet = character->GetAttributeSet();

	if (bUpdateOnHealthChange)
		character->OnHealthChangeDelegate.AddUObject(this, &UWC_UserWidget_Character::Update);

	if (bUpdateOnManaChange)
		character->OnManaChangeDelegate.AddUObject(this, &UWC_UserWidget_Character::Update);
		
	if(bUpdateOnMoveSpeedChange)
		character->OnMoveSpeedChangeDelegate.AddUObject(this, &UWC_UserWidget_Character::Update);

}
