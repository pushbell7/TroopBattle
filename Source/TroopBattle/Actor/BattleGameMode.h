// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BattleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TROOPBATTLE_API ABattleGameMode : public AGameMode
{
	GENERATED_BODY()
	
private:
	TArray<AActor*> UsedStarting;

public:
	ABattleGameMode();
	virtual void RestartPlayer(AController* NewPlayer) override;
};
