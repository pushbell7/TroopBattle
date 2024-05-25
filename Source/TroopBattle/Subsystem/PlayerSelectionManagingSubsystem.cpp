// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSelectionManagingSubsystem.h"
#include "TroopBattle/Actor/Pawn/UnitBase.h"

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

TArray<ECommandType> UPlayerSelectionManagingSubsystem::GetEnabledCommands() const
{
	TArray<ECommandType> result;
	
	// get actor info and assemble common functions actors can
	for (auto* actor : SelectedActors)
	{
		if (auto* controller = actor->GetInstigatorController<APlayerController>())
		{
			//controller->GetPlayerState<APlayerState>();
		}
	}

	//temporary setting
	if (SelectedActors.IsEmpty()) return result;

	result.Add(ECommandType::Move);
	result.Add(ECommandType::Stop);
	result.Add(ECommandType::None);

	result.Add(ECommandType::Attack);
	result.Add(ECommandType::None);
	result.Add(ECommandType::None);

	result.Add(ECommandType::None);
	result.Add(ECommandType::None);

	return result;
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
