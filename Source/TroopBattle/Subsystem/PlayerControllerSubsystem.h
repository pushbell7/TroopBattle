// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PlayerControllerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TROOPBATTLE_API UPlayerControllerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	

public:

	int GetMyPlayerId() const;
	APlayerController* GetMyController() const;
	APlayerController* GetController(int playerIndex) const;

	class UPlayerSelectionManagingSubsystem* GetSelectionManager() const;
	
};
