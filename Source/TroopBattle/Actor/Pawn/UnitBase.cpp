// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitBase.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Runtime/AIModule/Classes/Navigation/PathFollowingComponent.h>
// Sets default values
AUnitBase::AUnitBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnitBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AUnitBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AUnitBase::SetMovingPosition(const FVector& deltaPosition)
{
	ChangeState(EAction::Move);
	TargetPosition = GetActorLocation() + deltaPosition;
	auto* aiController = GetInstigatorController<AAIController>();
	//aiController->ReceiveMoveCompleted.AddUObject(this, &AUnitBase::HandleMoveCompleted);
	auto result = aiController->MoveToLocation(TargetPosition);
}

void AUnitBase::ChangeState(EAction action)
{
	CurrentState = action;
}

void AUnitBase::HandleMoveCompleted(FAIRequestID requestId, EPathFollowingResult::Type result)
{
	ChangeState(EAction::Stop);
	UE_LOG(LogTemp, Log, TEXT("move is done"));
}


