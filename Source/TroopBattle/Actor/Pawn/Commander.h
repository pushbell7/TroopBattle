// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Commander.generated.h"

UCLASS()
class TROOPBATTLE_API ACommander : public APawn
{
	GENERATED_BODY()
private:

	UPROPERTY(VisibleAnywhere)
	class UInputAction* SelectAction;

	UPROPERTY(VisibleAnywhere)
	class UInputAction* ScreenUpAction;
	UPROPERTY(VisibleAnywhere)
	class UInputAction* ScreenDownAction;
	UPROPERTY(VisibleAnywhere)
	class UInputAction* ScreenLeftAction;
	UPROPERTY(VisibleAnywhere)
	class UInputAction* ScreenRightAction;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;

	FVector MovingDirection;
	FVector2D SelectionStartPosition;
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

private:
	void HandleSelectingAction(const struct FInputActionValue& Value);
	void HandleTestUpPressAction(const struct FInputActionValue& Value);
	void HandleTestDownPressAction(const struct FInputActionValue& Value);
	void HandleTestLeftPressAction(const struct FInputActionValue& Value);
	void HandleTestRightPressAction(const struct FInputActionValue& Value);

	void SetMovingDirectionX(float X);
	void SetMovingDirectionY(float Y);

};
