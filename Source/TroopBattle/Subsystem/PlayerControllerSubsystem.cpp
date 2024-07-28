// Fill out your copyright notice in the Description page of Project Settings.


#include "TroopBattle/Subsystem/PlayerControllerSubsystem.h"
#include "PlayerControllerSubsystem.h"

ULocalPlayer* UPlayerControllerSubsystem::GetLocalPlayer() const
{
	if (GetController().IsValid())
	{
		return GetController()->GetLocalPlayer();
	}
	return nullptr;
}

TWeakObjectPtr<APlayerController> UPlayerControllerSubsystem::GetController() const
{
	return *(GetWorld()->GetPlayerControllerIterator() + GetWorld()->PlayerNum);
}
