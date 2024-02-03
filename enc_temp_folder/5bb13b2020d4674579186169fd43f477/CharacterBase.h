// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class TROOPBATTLE_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere)
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(VisibleAnywhere)
	class UInputAction* SelectAction;

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void HandleSelectAction(const struct FInputActionValue& Value);
};
