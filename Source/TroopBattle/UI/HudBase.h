// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HudBase.generated.h"

/**
 * 
 */
UCLASS()
class TROOPBATTLE_API AHudBase : public AHUD
{
	GENERATED_BODY()
	
public:
	AHudBase();

	virtual void BeginPlay() override;

	void RefreshCommanderWidget();

private:
	UPROPERTY()
	class UUserWidget* CommanderWidget;
};
