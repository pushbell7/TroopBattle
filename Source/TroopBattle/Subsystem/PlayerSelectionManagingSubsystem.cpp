// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSelectionManagingSubsystem.h"
#include "TroopBattle/Actor/Pawn/UnitBase.h"
#include "TroopBattle/Actor/Component/UnitPropertiesComponent.h"

const TArray<AActor*>& UPlayerSelectionManagingSubsystem::GetSelectedActors() const
{
	return SelectedActors;
}

AActor* UPlayerSelectionManagingSubsystem::GetRepresentativeActor() const
{
	if (SelectedActors.IsEmpty())
	{
		return nullptr;
	}
	constexpr int TEMPORARY_REPRESENTATIVE_ACTOR_INDEX = 0;
	return SelectedActors[TEMPORARY_REPRESENTATIVE_ACTOR_INDEX];
}

void UPlayerSelectionManagingSubsystem::AddSelection(AActor* selectedActor)
{
	SelectedActors.Add(selectedActor);
}

void UPlayerSelectionManagingSubsystem::ResetSelection()
{
	SelectedActors.Reset();
}

void UPlayerSelectionManagingSubsystem::Command(ECommandType type, const FVector& targetPosition)
{
	switch (type)
	{
	case ECommandType::Move:
	{
		auto deltaPosition = targetPosition - GetCenterPosition();
		for (auto* actor : SelectedActors)
		{
			if (auto* unit = dynamic_cast<AUnitBase*>(actor))
			{
				unit->SetMovingPosition(deltaPosition);
			}
		}
	}
		break;
	default:
		break;
	}
}

void UPlayerSelectionManagingSubsystem::Command(ECommandType type)
{
	for (auto* actor : SelectedActors)
	{
		if (auto* unit = dynamic_cast<AUnitBase*>(actor))
		{
			unit->SetCommand(type);
		}
	}
}

TArray<ECommandType> UPlayerSelectionManagingSubsystem::GetEnabledCommands() const
{
	TMap<ECommandType, int32> tableToGetCommon;
	
	// get actor info and assemble common functions actors can
	for (auto* actor : SelectedActors)
	{
		if (auto unit = Cast<AUnitBase>(actor))
		{
			auto unitProperties = unit->GetComponentByClass<UUnitPropertiesComponent>();
			auto commands = unitProperties->GetCommandsWhichCanDo();
			for (auto command : commands)
			{
				tableToGetCommon.FindOrAdd(command)++;
			}
		}
	}

	TArray<ECommandType> result;
	int32 selectedActorsCount = SelectedActors.Num();

	if (selectedActorsCount == 0) return result;

	for (auto command : tableToGetCommon)
	{
		if (command.Value == selectedActorsCount)
		{
			result.Add(command.Key);
		}
	}

	return result;
}

bool UPlayerSelectionManagingSubsystem::HasCallback() const
{
	return RegistedAction != ECommandType::None;
}

void UPlayerSelectionManagingSubsystem::RegistCallback(ECommandType type)
{
	RegistedAction = type;
}

void UPlayerSelectionManagingSubsystem::RemoveCallback()
{
	RegistedAction = ECommandType::None;
}

void UPlayerSelectionManagingSubsystem::RunCallback(const FVector& targetPosition)
{
	Command(RegistedAction, targetPosition);
	RemoveCallback();
}

FVector UPlayerSelectionManagingSubsystem::GetCenterPosition() const
{
	FVector result = FVector::Zero();
	if (SelectedActors.Num() > 0)
	{
		for (const auto* actor : SelectedActors)
		{
			result += actor->GetActorLocation();
		}
		result /= SelectedActors.Num();
	}
	return result;
}
