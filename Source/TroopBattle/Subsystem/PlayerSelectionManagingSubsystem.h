// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "PlayerSelectionManagingSubsystem.generated.h"

UENUM()
enum class ECommandType
{
	Move,
};

/**
 * 
 */
UCLASS()
class TROOPBATTLE_API UPlayerSelectionManagingSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TArray<AActor*> SelectedActors;

public:

	UFUNCTION(BlueprintCallable)
	const TArray<AActor*>& GetSelectedActors() const;
	UFUNCTION(BlueprintCallable)
	AActor* GetRepresentativeActor() const;

	UFUNCTION(BlueprintCallable)
	void AddSelection(AActor* selectedActor);
	UFUNCTION(BlueprintCallable)
	void ResetSelection();

	UFUNCTION(BlueprintCallable)
	void Command(ECommandType type, const FVector& targetPosition);

private:
	FVector GetCenterPosition() const;
};
