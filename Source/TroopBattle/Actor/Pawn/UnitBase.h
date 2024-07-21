// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Runtime/AIModule/Classes/AIController.h>
#include "UnitBase.generated.h"

enum class ECommandType;

UENUM()
enum class EMovementStrategy
{
	Walk,
	Crawling,
	TacticalMovement,
	Chasing,
	EscapingRunning,
	Max
};
static const TCHAR* EnumToString(EMovementStrategy type)
{
	switch (type)
	{
	case EMovementStrategy::Walk: return TEXT("Walk");
	case EMovementStrategy::Crawling: return TEXT("Crawling");
	case EMovementStrategy::TacticalMovement: return TEXT("TacticalMovement");
	case EMovementStrategy::Chasing: return TEXT("Chasing");
	case EMovementStrategy::EscapingRunning: return TEXT("EscapingRunning");
	default: return TEXT("None");
	}
}

UCLASS()
class TROOPBATTLE_API AUnitBase : public ACharacter
{
	GENERATED_BODY()

private:
	FVector TargetPosition;

	UPROPERTY(VisibleAnywhere)
	class UUnitPropertiesComponent* PropertiesComponent;

	EMovementStrategy MovementStrategy;
	bool bObserving;
	float AccumulatedTime;
	float ObservingDistance;
	float ObservingAngleDegree;
	float ObservingAngleSpeed;

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

	void SetCommand(ECommandType type);
	void SetMovingPosition(const FVector& deltaPosition);
	EMovementStrategy GetMovementStrategy() const { return MovementStrategy; }
	void ChangeMovementStrategy(EMovementStrategy strategy);
	void Observe();

private:
	UFUNCTION()
	void HandleMoveCompleted(FAIRequestID requestId, EPathFollowingResult::Type result);
};
