// Fill out your copyright notice in the Description page of Project Settings.


#include "TroopBattle/Subsystem/PlayerControllerSubsystem.h"
#include "PlayerControllerSubsystem.h"
#include "TroopBattle/Subsystem/PlayerSelectionManagingSubsystem.h"
#include <GameFramework/PlayerState.h>

UPlayerControllerSubsystem::UPlayerControllerSubsystem()
{
	static ConstructorHelpers::FObjectFinder<UPhysicalMaterialSettingsDataAsset> physicalMaterialDataAsset(TEXT("/Script/TroopBattle.PhysicalMaterialSettingsDataAsset'/Game/Data/DA_PhysicalMaterialSetting.DA_PhysicalMaterialSetting'"));
	if (physicalMaterialDataAsset.Succeeded())
	{
		PhysicalMaterialSettingsDataAsset = physicalMaterialDataAsset.Object;
	}
}

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
