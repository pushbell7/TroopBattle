// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommanderHudWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class TROOPBATTLE_API UCommanderHudWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), category="UI")
	UPanelWidget* CommanderButtonContainer;

public:

	virtual bool Initialize() override;

	void Init();
	void RefreshCommandButtons();

private:
	void Reset();

	UFUNCTION()
	void HandleClicked();
};
