// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSelectionManagingSubsystem.h"

const TArray<AActor*>& UPlayerSelectionManagingSubsystem::GetSelectedActors() const
{
	return SelectedActors;
}

void UPlayerSelectionManagingSubsystem::AddSelection(AActor* selectedActor)
{
	SelectedActors.Add(selectedActor);
}

void UPlayerSelectionManagingSubsystem::ResetSelection()
{
	SelectedActors.Reset();
}
