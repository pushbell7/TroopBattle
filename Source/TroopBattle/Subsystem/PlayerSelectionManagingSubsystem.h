// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "PlayerSelectionManagingSubsystem.generated.h"

UENUM()
enum class ECommandType
{
	None,
	Move,
	ChangeMovingMethod,
	Stop,
	Observe,
	Hold,
};

static const TCHAR* EnumToString(ECommandType type)
{
	switch (type)
	{
	case ECommandType::None: return TEXT("None");
	case ECommandType::Move: return TEXT("Move");
	case ECommandType::ChangeMovingMethod: return TEXT("ChangeMovingMethod");
	case ECommandType::Stop: return TEXT("Stop");
	case ECommandType::Observe: return TEXT("Observe");
	case ECommandType::Hold: return TEXT("Hold");
	default: return TEXT("None");
	}
}

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

	TArray<ECommandType> GetEnabledCommands() const;

private:
	FVector GetCenterPosition() const;
};
