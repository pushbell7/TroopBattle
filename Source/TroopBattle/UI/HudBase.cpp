// Fill out your copyright notice in the Description page of Project Settings.


#include "HudBase.h"
#include "CommanderHudWidgetBase.h"

AHudBase::AHudBase()
{
	static ConstructorHelpers::FClassFinder<UCommanderHudWidgetBase> WidgetBlueprint(TEXT("/Game/UI/WBP_GameHudWidget.WBP_GameHudWidget_C"));
	if (WidgetBlueprint.Succeeded())
	{
		CommanderWidget = CreateWidget(GetWorld(), WidgetBlueprint.Class, "Widget");
	}	
}

void AHudBase::BeginPlay()
{
	Super::BeginPlay();

	if (CommanderWidget)
	{
		CommanderWidget->AddToViewport();
	}
}

void AHudBase::RefreshCommanderWidget()
{
	if (auto widget = Cast<UCommanderHudWidgetBase>(CommanderWidget))
	{
		widget->RefreshCommandButtons();
	}
}
