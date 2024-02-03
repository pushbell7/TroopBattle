// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

#include <InputMappingContext.h>
#include <EnhancedInputSubsystems.h>


APlayerControllerBase::APlayerControllerBase()
{
	bShowMouseCursor = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextResource(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Common/Input/IMC_TestInputMap.IMC_TestInputMap'"));
	if (InputMappingContextResource.Succeeded())
	{
		InputMappingContext = InputMappingContextResource.Object;
	}
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
}