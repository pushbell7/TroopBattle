// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitSelector.h"
#include <Components/BoxComponent.h>
#include "TroopBattle/Subsystem/PlayerSelectionManagingSubsystem.h"

// Sets default values
AUnitSelector::AUnitSelector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetBoxExtent(FVector(1, 1, 1));
	BoxComponent->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	BoxComponent->bHiddenInGame = false;
}

// Called when the game starts or when spawned
void AUnitSelector::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(1.0f);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AUnitSelector::OnBeginOverlapped);
}

// Called every frame
void AUnitSelector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnitSelector::OnBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto selectionManager = GetWorld()->GetSubsystem<UPlayerSelectionManagingSubsystem>();
	selectionManager->AddSelection(OtherActor);
}

