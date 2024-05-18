// Fill out your copyright notice in the Description page of Project Settings.


#include "CommanderHudWidgetBase.h"
#include <Components/PanelWidget.h>
#include <TroopBattle/Subsystem/PlayerSelectionManagingSubsystem.h>

bool UCommanderHudWidgetBase::Initialize()
{
	if(Super::Initialize() == false) return false;

	Init();
	return true;
}

void UCommanderHudWidgetBase::Init()
{
	UE_LOG(LogTemp, Log, TEXT("Init"));	
	Reset();
}


void UCommanderHudWidgetBase::RefreshCommandButtons()
{
	UE_LOG(LogTemp, Log, TEXT("RefreshCommandButtons"));

	auto selectionManager = GetWorld()->GetFirstLocalPlayerFromController()->GetSubsystem<UPlayerSelectionManagingSubsystem>();
	if (selectionManager->GetSelectedActors().Num() > 0)
	{
		for (auto* child : CommanderButtonContainer->GetAllChildren())
		{
			child->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		Reset();
	}
}

void UCommanderHudWidgetBase::Reset()
{
	for (auto* child : CommanderButtonContainer->GetAllChildren())
	{
		child->SetVisibility(ESlateVisibility::Hidden);
	}
}
