// Fill out your copyright notice in the Description page of Project Settings.

#include "CommandButtonBase.h"
#include "TroopBattle/Subsystem/PlayerSelectionManagingSubsystem.h"
#include "TroopBattle/Actor/Pawn/UnitBase.h"


bool UCommandButtonBase::Initialize()
{
	bool result = Super::Initialize();

	Button->OnClicked.AddDynamic(this, &UCommandButtonBase::HandleClicked);

	return result;
}

void UCommandButtonBase::HandleClicked()
{
	UE_LOG(LogTemp, Log, TEXT("type : %s"),  EnumToString(CommandType));

	auto selectionSubsystem = GetWorld()->GetFirstLocalPlayerFromController()->GetSubsystem<UPlayerSelectionManagingSubsystem>();
	switch (CommandType)
	{
	case ECommandType::Move:
		// make callback to destination
		selectionSubsystem->RegistCallback(CommandType);
		break;
	default:
		selectionSubsystem->Command(CommandType);
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
		if (type == ECommandType::ChangeMovingMethod)
		{
			auto selectionManager = GetWorld()->GetFirstLocalPlayerFromController()->GetSubsystem<UPlayerSelectionManagingSubsystem>();
			auto unit = Cast<AUnitBase>(selectionManager->GetRepresentativeActor());
			Label->SetText(FText::FromString(EnumToString(unit->GetMovementStrategy())));
		}
		else
		{
			Label->SetText(FText::FromString(EnumToString(type)));
		}
	}
}
