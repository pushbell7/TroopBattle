// Fill out your copyright notice in the Description page of Project Settings.


#include "CommanderHudWidgetBase.h"
#include <Components/PanelWidget.h>
#include <TroopBattle/Subsystem/PlayerSelectionManagingSubsystem.h>
#include <Components/HorizontalBox.h>
#include "CommandButtonBase.h"

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
	
	auto commands = selectionManager->GetEnabledCommands();
	int commandIndex = 0;
	for (auto* child : CommanderButtonContainer->GetAllChildren())
	{
		if (auto* horizontalBox = Cast<UHorizontalBox>(child))
		{
			for (int i = 0; i < horizontalBox->GetChildrenCount(); ++i)
			{
				if (auto button = dynamic_cast<UCommandButtonBase*>(horizontalBox->GetChildAt(i)))
				{
					ECommandType type = ECommandType::None;
					if (commandIndex < commands.Num())
					{
						type = commands[commandIndex];
					}
					button->SetCommandType(type);
					commandIndex++;
				}
			}
		}
	}
}

void UCommanderHudWidgetBase::Reset()
{
	for (auto* child : CommanderButtonContainer->GetAllChildren())
	{
		if (auto* horizontalBox = Cast<UHorizontalBox>(child))
		{
			for (auto button : horizontalBox->GetAllChildren())
			{
				dynamic_cast<UCommandButtonBase*>(button)->SetCommandType(ECommandType::None);
			}
		}
	}
}
