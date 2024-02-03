// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"



APlayerControllerBase::APlayerControllerBase()
{
	bShowMouseCursor = true;
}

APlayerControllerBase::~APlayerControllerBase() = default;

void APlayerControllerBase::OnPossess(APawn* aPawn)
{
	UE_LOG(LogTemp, Log, TEXT("possess %s"), *aPawn->GetHumanReadableName());
}