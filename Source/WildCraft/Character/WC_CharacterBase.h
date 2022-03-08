// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VoxelCharacter.h"
#include "GameplayAbilitySet.h"
#include "AbilitySystemInterface.h"
#include "WC_CharacterBase.generated.h"

UCLASS()
class WILDCRAFT_API AWC_CharacterBase : public AVoxelCharacter
	, public IAbilitySystemInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWC_CharacterBase();

//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;

public:	
	// IAbilitySystemInterface을(를) 통해 상속됨
	virtual UAbilitySystemComponent * GetAbilitySystemComponent() const override { return NULL; }

	// IGameplayTagAssetInterface을(를) 통해 상속됨
	virtual void GetOwnedGameplayTags(FGameplayTagContainer & TagContainer) const override PURE_VIRTUAL(AWC_CharacterBase::GetAbilitySystemComponent);

};
