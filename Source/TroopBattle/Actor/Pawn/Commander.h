// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UnitBase.h"
#include "Commander.generated.h"

UCLASS()
class TROOPBATTLE_API ACommander : public APawn
{
	GENERATED_BODY()
private:

	UPROPERTY(VisibleAnywhere)
	class UInputAction* SelectAction;
	UPROPERTY(VisibleAnywhere)
	class UInputAction* CommandAction;

	UPROPERTY(VisibleAnywhere)
	class UInputAction* ScreenUpAction;
	UPROPERTY(VisibleAnywhere)
	class UInputAction* ScreenDownAction;
	UPROPERTY(VisibleAnywhere)
	class UInputAction* ScreenLeftAction;
	UPROPERTY(VisibleAnywhere)
	class UInputAction* ScreenRightAction;

	UPROPERTY(VisibleAnywhere)
	class UInputAction* Test1Action;
	UPROPERTY(VisibleAnywhere)
	class UInputAction* Test2Action;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;

	FVector MovingDirection;
	FVector SelectionStartPosition;
public:
	// Sets default values for this character's properties
	ACommander();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Server, Reliable)
	void RequestCommand(const TArray<AActor*>& units, ECommandType commandType);
	void RequestCommand_Implementation(const TArray<AActor*>& units, ECommandType commandType);

	UFUNCTION(Server, Reliable)
	void RequestTargetCommand(const TArray<AActor*>& units, ECommandType commandType, FVector targetPosition);
	void RequestTargetCommand_Implementation(const TArray<AActor*>& units, ECommandType commandType, FVector targetPosition);

private:
	void HandleSelectingAction(const struct FInputActionValue& Value);
	void HandleCommandAction(const struct FInputActionValue& Value);
	void HandleTestUpPressAction(const struct FInputActionValue& Value);
	void HandleTestDownPressAction(const struct FInputActionValue& Value);
	void HandleTestLeftPressAction(const struct FInputActionValue& Value);
	void HandleTestRightPressAction(const struct FInputActionValue& Value);

	void HandleTest1PressAction(const struct FInputActionValue& Value);
	void HandleTest2PressAction(const struct FInputActionValue& Value);

	void SetMovingDirectionX(float X);
	void SetMovingDirectionY(float Y);

};
