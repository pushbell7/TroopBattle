// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommanderHudBase.generated.h"

/**
 * 
 */
UCLASS()
class TROOPBATTLE_API UCommanderHudBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init();
	void RefreshCommandButtons();
};
