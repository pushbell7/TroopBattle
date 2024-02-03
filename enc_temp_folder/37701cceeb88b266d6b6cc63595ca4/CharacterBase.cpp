// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include <EnhancedInputComponent.h>
#include <InputMappingContext.h>
#include <EnhancedInputSubsystems.h>

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextResource(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Common/Input/IMC_TestInputMap.IMC_TestInputMap'"));
	if (InputMappingContextResource.Succeeded())
	{
		InputMappingContext = InputMappingContextResource.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> SelectActionResource(TEXT("/Script/EnhancedInput.InputAction'/Game/Common/Input/IA_Select.IA_Select'"));
	if (SelectActionResource.Succeeded())
	{
		SelectAction = SelectActionResource.Object;
	}
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// TODO : move to controller
	if (APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	// 여기에서 'ETriggerEvent' 열거형 값을 변경하여 원하는 트리거 이벤트를 바인딩할 수 있습니다.
	Input->BindAction(SelectAction, ETriggerEvent::Triggered, this, &ACharacterBase::HandleSelectAction);

}

void ACharacterBase::HandleSelectAction(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("Handled"));
}

