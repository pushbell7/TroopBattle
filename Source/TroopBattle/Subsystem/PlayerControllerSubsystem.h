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

	ULocalPlayer* GetLocalPlayer() const;
	TWeakObjectPtr<APlayerController> GetController() const;
};
