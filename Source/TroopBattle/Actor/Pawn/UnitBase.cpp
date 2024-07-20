// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitBase.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Runtime/AIModule/Classes/Navigation/PathFollowingComponent.h>
#include "TroopBattle/Actor/Component/UnitPropertiesComponent.h"
#include "TroopBattle/Subsystem/PlayerSelectionManagingSubsystem.h"

// Sets default values
AUnitBase::AUnitBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PropertiesComponent = CreateDefaultSubobject<UUnitPropertiesComponent>(TEXT("PropertiesComponent"));
}

// Called when the game starts or when spawned
void AUnitBase::BeginPlay()
{
	Super::BeginPlay();

}

void AUnitBase::PossessedBy(AController* controller)
{
	Super::PossessedBy(controller);

	auto* aiController = dynamic_cast<AAIController*>(controller);
	aiController->ReceiveMoveCompleted.AddDynamic(this, &AUnitBase::HandleMoveCompleted);
}

// Called every frame
void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bObserving)
	{
		auto location = GetActorLocation();
		AccumulatedTime += DeltaTime;
		auto rotatedDirection = GetActorForwardVector().RotateAngleAxis(FMathf::Sin(AccumulatedTime) * 45, FVector::UpVector);
		auto endOfSight = location + rotatedDirection * 1000;

		DrawDebugLine(GetWorld(), location, endOfSight, FColor::Green);
		
		FHitResult hitResult;
		FCollisionQueryParams collisionParams;
		collisionParams.AddIgnoredActor(this); // Ignore the character itself
		bool bHit = GetWorld()->LineTraceSingleByChannel(hitResult, location, endOfSight, ECC_WorldDynamic, collisionParams);
		if (bHit)
		{
			UE_LOG(LogTemp, Log, TEXT("%s"), *hitResult.GetActor()->GetName());
		}
	}
}

// Called to bind functionality to input
void AUnitBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AUnitBase::SetCommand(ECommandType type)
{
	switch (type)
	{
	case ECommandType::ChangeMovingMethod:
		ChangeMovementStrategy( static_cast<EMovementStrategy>((static_cast<int>(MovementStrategy) + 1) % static_cast<int>(EMovementStrategy::Max)));
		break;
	case ECommandType::Observe:
		Observe();
		break;
	case ECommandType::Hold:

		break;
	case ECommandType::Stop:

		break;
	}
}

void AUnitBase::SetMovingPosition(const FVector& deltaPosition)
{
	TargetPosition = GetActorLocation() + deltaPosition;
	auto* aiController = GetInstigatorController<AAIController>();
	auto result = aiController->MoveToLocation(TargetPosition);
}

void AUnitBase::ChangeMovementStrategy(EMovementStrategy strategy)
{
	MovementStrategy = strategy;
}

void AUnitBase::Observe()
{
	bObserving = true;
}

void AUnitBase::HandleMoveCompleted(FAIRequestID requestId, EPathFollowingResult::Type result)
{
	UE_LOG(LogTemp, Log, TEXT("move is done"));
}


