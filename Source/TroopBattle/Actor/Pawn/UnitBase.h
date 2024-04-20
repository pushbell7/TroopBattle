// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Runtime/AIModule/Classes/AIController.h>
#include "UnitBase.generated.h"

UCLASS()
class TROOPBATTLE_API AUnitBase : public ACharacter
{
	GENERATED_BODY()

private:
	enum class EAction
	{
		Stop,
		Move,
	};

	EAction CurrentState;
	FVector TargetPosition;

public:
	// Sets default values for this character's properties
	AUnitBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* controller) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void SetMovingPosition(const FVector& deltaPosition);
	void ChangeState(EAction action);

private:
	UFUNCTION()
	void HandleMoveCompleted(FAIRequestID requestId, EPathFollowingResult::Type result);
};
