// Fill out your copyright notice in the Description page of Project Settings.


#include "Commander.h"
#include <EnhancedInputComponent.h>
#include <Camera/CameraComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include "../../Subsystem/PlayerSelectionManagingSubsystem.h"

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

	static ConstructorHelpers::FObjectFinder<UInputAction> CommandActionResource(TEXT("/Script/EnhancedInput.InputAction'/Game/Common/Input/IA_Command.IA_Command'"));
	if (CommandActionResource.Succeeded())
	{
		CommandAction = CommandActionResource.Object;
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

	SelectionBox = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, TEXT("/Script/Engine.Blueprint'/Game/Actors/SelectionBox.SelectionBox'")));

}

// Called when the game starts or when spawned
void ACommander::BeginPlay()
{
	Super::BeginPlay();

	CameraComponent = GetComponentByClass<UCameraComponent>();
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
	Input->BindAction(SelectAction, ETriggerEvent::Triggered, this, &ACommander::HandleSelectingAction);
	Input->BindAction(CommandAction, ETriggerEvent::Triggered, this, &ACommander::HandleCommandAction);

	Input->BindAction(ScreenUpAction, ETriggerEvent::Triggered, this, &ACommander::HandleTestUpPressAction);
	Input->BindAction(ScreenDownAction, ETriggerEvent::Triggered, this, &ACommander::HandleTestDownPressAction);
	Input->BindAction(ScreenLeftAction, ETriggerEvent::Triggered, this, &ACommander::HandleTestLeftPressAction);
	Input->BindAction(ScreenRightAction, ETriggerEvent::Triggered, this, &ACommander::HandleTestRightPressAction);
	
}

void ACommander::HandleSelectingAction(const FInputActionValue& Value)
{
	if (auto* playerController = GetController<APlayerController>())
	{
		FVector2D mousePosition;
		playerController->GetMousePosition(mousePosition.X, mousePosition.Y);

		if (SelectionStartPosition.IsZero())
		{
			GetWorld()->GetFirstLocalPlayerFromController()->GetSubsystem<UPlayerSelectionManagingSubsystem>()->ResetSelection();

			FHitResult hitResult;
			playerController->GetHitResultAtScreenPosition(mousePosition, ECollisionChannel::ECC_GameTraceChannel1, false, hitResult);
			SelectionStartPosition = hitResult.Location;
		}
		else
		{
			if (Value.Get<bool>())
			{
				// draw rect from SelectionStartPosition to mousePosition on HUD
			}
			else
			{
				FHitResult hitResult;
				playerController->GetHitResultAtScreenPosition(mousePosition, ECollisionChannel::ECC_GameTraceChannel1, false, hitResult);				
				FVector endPosition = hitResult.Location;

				FTransform transform;
				transform.SetLocation((SelectionStartPosition + endPosition) / 2);
				auto* actor = GetWorld()->SpawnActor<AActor>(SelectionBox->GeneratedClass, transform);

				FVector scale = (endPosition - SelectionStartPosition) / 2;
				actor->SetActorRelativeScale3D(FVector(FMath::Abs(scale.X), FMath::Abs(scale.Y), FMath::Abs(scale.Z) + 10));

				const auto& selectedActors = GetWorld()->GetFirstLocalPlayerFromController()->GetSubsystem<UPlayerSelectionManagingSubsystem>()->GetSelectedActors();
				UE_LOG(LogTemp, Log, TEXT("selected : %d"), selectedActors.Num());
				SelectionStartPosition = FVector::ZeroVector;
			}
		}
	}
}

void ACommander::HandleCommandAction(const FInputActionValue& Value)
{
	if (auto* playerController = GetController<APlayerController>())
	{
		FVector2D mousePosition;
		playerController->GetMousePosition(mousePosition.X, mousePosition.Y);

		FHitResult hitResult;
		playerController->GetHitResultAtScreenPosition(mousePosition, ECollisionChannel::ECC_GameTraceChannel1, false, hitResult);

		GetWorld()->GetFirstLocalPlayerFromController()->GetSubsystem<UPlayerSelectionManagingSubsystem>()->Command(ECommandType::Move, hitResult.Location);

	}
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


