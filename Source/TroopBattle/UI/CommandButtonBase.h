// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "CommandButtonBase.generated.h"
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
};
