// Fill out your copyright notice in the Description page of Project Settings.


#include "TroopBattle/Subsystem/PlayerControllerSubsystem.h"
#include "PlayerControllerSubsystem.h"
#include "TroopBattle/Subsystem/PlayerSelectionManagingSubsystem.h"
#include <GameFramework/PlayerState.h>

int UPlayerControllerSubsystem::GetMyPlayerId() const
{
	return GetWorld()->GetFirstPlayerController()->GetPlayerState<APlayerState>()->GetPlayerId();
}

APlayerController* UPlayerControllerSubsystem::GetMyController() const
{
	return GetController(GetMyPlayerId());
}

APlayerController* UPlayerControllerSubsystem::GetController(int playerIndex) const
{
	for (auto iter = GetWorld()->GetPlayerControllerIterator(); iter; iter++)
	{
		if (iter->Get()->GetPlayerState<APlayerState>()->GetPlayerId() == playerIndex)
		{
			return iter->Get();
		}
	}
	return nullptr;
}

UPlayerSelectionManagingSubsystem* UPlayerControllerSubsystem::GetSelectionManager() const
{
	return GetWorld()->GetSubsystem<UPlayerSelectionManagingSubsystem>();
}
