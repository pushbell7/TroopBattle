// Fill out your copyright notice in the Description page of Project Settings.


#include "Commander.h"
#include <EnhancedInputComponent.h>

// Sets default values
ACommander::ACommander()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//TODO make resource loader from data asset
	static ConstructorHelpers::FObjectFinder<UInputAction> SelectActionResource(TEXT("/Script/EnhancedInput.InputAction'/Game/Common/Input/IA_Select.IA_Select'"));
	if (SelectActionResource.Succeeded())
	{
		SelectAction = SelectActionResource.Object;
	}


	static ConstructorHelpers::FObjectFinder<UInputAction> ScreenUpActionResource(TEXT("/Script/EnhancedInput.InputAction'/Game/Common/Input/IA_ScreenUp.IA_ScreenUp'"));
	if (ScreenUpActionResource.Succeeded())
	{
		ScreenUpAction = ScreenUpActionResource.Object;
	}


	static ConstructorHelpers::FObjectFinder<UInputAction> ScreenDownActionResource(TEXT("/Script/EnhancedInput.InputAction'/Game/Common/Input/IA_ScreenDown.IA_ScreenDown'"));
	if (ScreenDownActionResource.Succeeded())
	{
		ScreenDownAction = ScreenDownActionResource.Object;
	}


	static ConstructorHelpers::FObjectFinder<UInputAction> ScreenLeftActionResource(TEXT("/Script/EnhancedInput.InputAction'/Game/Common/Input/IA_ScreenLeft.IA_ScreenLeft'"));
	if (ScreenLeftActionResource.Succeeded())
	{
		ScreenLeftAction = ScreenLeftActionResource.Object;
	}


	static ConstructorHelpers::FObjectFinder<UInputAction> ScreenRightActionResource(TEXT("/Script/EnhancedInput.InputAction'/Game/Common/Input/IA_ScreenRight.IA_ScreenRight'"));
	if (ScreenRightActionResource.Succeeded())
	{
		ScreenRightAction = ScreenRightActionResource.Object;
	}


}

// Called when the game starts or when spawned
void ACommander::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACommander::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	constexpr float ScrollSpeed = 3.0f;
	SetActorLocation(GetActorLocation() + (MovingDirection * ScrollSpeed));
}

// Called to bind functionality to input
void ACommander::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	// 여기에서 'ETriggerEvent' 열거형 값을 변경하여 원하는 트리거 이벤트를 바인딩할 수 있습니다.
	Input->BindAction(SelectAction, ETriggerEvent::Triggered, this, &ACommander::HandleSelectAction);
	Input->BindAction(ScreenUpAction, ETriggerEvent::Triggered, this, &ACommander::HandleTestUpPressAction);
	Input->BindAction(ScreenDownAction, ETriggerEvent::Triggered, this, &ACommander::HandleTestDownPressAction);
	Input->BindAction(ScreenLeftAction, ETriggerEvent::Triggered, this, &ACommander::HandleTestLeftPressAction);
	Input->BindAction(ScreenRightAction, ETriggerEvent::Triggered, this, &ACommander::HandleTestRightPressAction);
	
}

void ACommander::HandleSelectAction(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("Handled"));
}

void ACommander::HandleTestUpPressAction(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		SetMovingDirectionX(-1);
	}
	else
	{
		SetMovingDirectionX(0);
	}
}

void ACommander::HandleTestDownPressAction(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		SetMovingDirectionX(1);
	}
	else
	{
		SetMovingDirectionX(0);
	}
}

void ACommander::HandleTestLeftPressAction(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		SetMovingDirectionY(1);
	}
	else
	{
		SetMovingDirectionY(0);
	}
}

void ACommander::HandleTestRightPressAction(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		SetMovingDirectionY(-1);
	}
	else
	{
		SetMovingDirectionY(0);
	}
}

void ACommander::SetMovingDirectionX(float X)
{
	MovingDirection.X = X;
}

void ACommander::SetMovingDirectionY(float Y)
{
	MovingDirection.Y = Y;
}


