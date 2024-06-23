// Fill out your copyright notice in the Description page of Project Settings.

#include "CommandButtonBase.h"
#include "TroopBattle/Subsystem/PlayerSelectionManagingSubsystem.h"


bool UCommandButtonBase::Initialize()
{
	bool result = Super::Initialize();

	Button->OnClicked.AddDynamic(this, &UCommandButtonBase::HandleClicked);

	return result;
}

void UCommandButtonBase::HandleClicked()
{
	UE_LOG(LogTemp, Log, TEXT("type : %s"),  EnumToString(CommandType));
	switch (CommandType)
	{
	case ECommandType::Move:
		// make callback to destination
		break;
	case ECommandType::ChangeMovingMethod:
		// change internal state
		break;
	case ECommandType::Stop:
		// change internal state
		break;
	case ECommandType::Observe:
		// change internal state
		break;
	case ECommandType::Hold:
		// change internal state
		break;
	}
}

void UCommandButtonBase::SetCommandType(ECommandType type)
{
	if (CommandType == type) return;

	CommandType = type;

	if (type == ECommandType::None)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		SetVisibility(ESlateVisibility::Visible);
		Label->SetText(FText::FromString(EnumToString(type)));
	}
}
