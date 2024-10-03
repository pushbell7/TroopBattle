// Fill out your copyright notice in the Description page of Project Settings.


#include "TroopBattle/Actor/BattleGameMode.h"
#include "TroopBattle/Actor/Controller/PlayerControllerBase.h"
#include "TroopBattle/Actor/Pawn/Commander.h"
#include "TroopBattle/UI/HudBase.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/PlayerStart.h>

ABattleGameMode::ABattleGameMode()
	: AGameMode()
{
	PlayerControllerClass = APlayerControllerBase::StaticClass();
	DefaultPawnClass = ACommander::StaticClass();
	HUDClass = AHudBase::StaticClass();
}

void ABattleGameMode::RestartPlayer(AController* NewPlayer)
{
	if (NewPlayer == nullptr || NewPlayer->IsPendingKillPending())
	{
		return;
	}

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), actors);

	TArray<AActor*> candidates;
	for (AActor* startingActor : actors)
	{
		if (UsedStarting.Find(startingActor) == INDEX_NONE)
		{
			candidates.Add(startingActor);
		}
	}

	AActor* selected = nullptr;
	if (candidates.Num() > 0)
	{
		selected = candidates[FMath::Rand() % candidates.Num()];
		UsedStarting.Add(selected);
	}
	else if(UsedStarting.Num() > 0)
	{
		selected = UsedStarting[FMath::Rand() % UsedStarting.Num()];
	}
	RestartPlayerAtPlayerStart(NewPlayer, selected);
}
