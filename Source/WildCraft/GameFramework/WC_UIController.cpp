// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_UIController.h"
#include "Blueprint/UserWidget.h"


// Called when the game starts or when spawned
void AWC_UIController::BeginPlay()
{
	Super::BeginPlay();

	check(UIclass);
	RootWidget = CreateWidget(this, UIclass, "RootWidget");
	check(RootWidget);
	RootWidget->AddToViewport();

	FInputModeUIOnly InputModeParam;
	InputModeParam.SetWidgetToFocus(RootWidget->TakeWidget());

	SetInputMode(InputModeParam);

	bShowMouseCursor = true;
}