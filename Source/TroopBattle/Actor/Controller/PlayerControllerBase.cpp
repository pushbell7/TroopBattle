// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

#include <InputMappingContext.h>
#include <EnhancedInputSubsystems.h>
#include <GameFramework/PlayerState.h>

#include "TroopBattle/Actor/Pawn/UnitBase.h"
#include "TroopBattle/Subsystem/PlayerControllerSubsystem.h"
#include "TroopBattle/Actor/Component/UnitPropertiesComponent.h"
#include "TroopBattle/Actor/Pawn/Commander.h"


APlayerControllerBase::APlayerControllerBase()
{
	bShowMouseCursor = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextResource(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Common/Input/IMC_TestInputMap.IMC_TestInputMap'"));
	if (InputMappingContextResource.Succeeded())
	{
		InputMappingContext = InputMappingContextResource.Object;
	}

	TestUnit = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, TEXT("/Script/Engine.Blueprint'/Game/Actors/Characters/BP_TestUnit.BP_TestUnit'")));
}

APlayerControllerBase::~APlayerControllerBase() = default;

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->AddMappingContext(InputMappingContext, 0);
	}
}

void APlayerControllerBase::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	UE_LOG(LogTemp, Log, TEXT("possess %s"), *aPawn->GetHumanReadableName());

	auto* commander = Cast<ACommander>(aPawn);
	int index = GetPlayerState<APlayerState>()->GetPlayerId();
	commander->RequestSpawnCommand(index, aPawn->GetActorLocation());
}

void APlayerControllerBase::SpawnTestActor(const FTransform& transform)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	auto actor = GetWorld()->SpawnActor<ACharacter>(TestUnit->GeneratedClass, transform, SpawnParams);
	if (actor == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("cant spawn actor"));
		return;
	}
	int index = GetPlayerState<APlayerState>()->GetPlayerId();
	actor->GetComponentByClass<UUnitPropertiesComponent>()->SetMaster(index);
}
