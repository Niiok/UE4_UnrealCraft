// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_UserWidget_Character.h"
#include "Character/WC_Character.h"
#include "GAS/WC_AttributeSet_Character.h"

void UWC_UserWidget_Character::BindCharacter(AWC_Character * attribute)
{
	if (attribute == nullptr)
		return;

	AttributeSet = attribute->GetAttributeSet();

	//if (bUpdateOnHealthChange)
	//	attribute->OnHealthChanged.AddDynamic(this, &UWC_UserWidget_Character::Update);

	//if (bUpdateOnManaChange)
	//	attribute->OnManaChanged.AddDynamic(this, &UWC_UserWidget_Character::Update);
	//	
	//if(bUpdateOnMoveSpeedChange)
	//	attribute->OnMoveSpeedChanged.AddDynamic(this, &UWC_UserWidget_Character::Update);

}
