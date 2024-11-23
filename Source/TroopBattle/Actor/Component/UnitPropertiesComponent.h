// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitPropertiesComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TROOPBATTLE_API UUnitPropertiesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	enum class EUnitPrototype
	{
		Infantry,
		Artillery,
		Armor,
		Max
	};

	// Sets default values for this component's properties
	UUnitPropertiesComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	TArray<enum class ECommandType> GetCommandsWhichCanDo() const;

	int GetMaster() const { return Master; }
	void SetMaster(int master) { Master = master; }

	float GetSpeed() const { return Speed; }
	void SetSpeed(float speed) { Speed = speed; }


private:
	UPROPERTY(replicated)
	int Master;

	UPROPERTY(replicated)
	int32 Stamina;

	UPROPERTY(replicated)
	float Speed;

	UPROPERTY(replicated)
	int32 Accuracy;

	UPROPERTY(replicated)
	int32 Avoidance;

	EUnitPrototype Prototype;
};
