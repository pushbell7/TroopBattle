// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "CommandButtonBase.generated.h"

enum class ECommandType;

/**
 * 
 */
UCLASS()
class TROOPBATTLE_API UCommandButtonBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), category = "UI")
	UTextBlock* Label;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), category = "UI")
	UButton* Button;
	
private:
	ECommandType CommandType;

public:
	virtual bool Initialize() override;

	UFUNCTION()
	void HandleClicked();


	void SetCommandType(ECommandType type);
};
