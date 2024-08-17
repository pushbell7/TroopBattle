// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>
#include "UnitSelector.generated.h"

UCLASS()
class TROOPBATTLE_API AUnitSelector : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class UBoxComponent* BoxComponent;

public:	
	// Sets default values for this actor's properties
	AUnitSelector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UFUNCTION()
	void OnBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
