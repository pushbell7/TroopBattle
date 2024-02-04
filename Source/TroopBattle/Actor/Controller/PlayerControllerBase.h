// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class TROOPBATTLE_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	class UInputMappingContext* InputMappingContext;

	class UBlueprint* TestUnit;
public:
	APlayerControllerBase();
	~APlayerControllerBase();

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* aPawn) override;


};
