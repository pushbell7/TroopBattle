// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitPropertiesComponent.h"
#include <Net/UnrealNetwork.h>
#include "Troopbattle/Subsystem/PlayerSelectionManagingSubsystem.h"

// Sets default values for this component's properties
UUnitPropertiesComponent::UUnitPropertiesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void UUnitPropertiesComponent::BeginPlay()
{
	Super::BeginPlay();

	// temporary setting

	Prototype = EUnitPrototype::Infantry;


}


// Called every frame
void UUnitPropertiesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<ECommandType> UUnitPropertiesComponent::GetCommandsWhichCanDo() const
{
	auto result = TArray<ECommandType>();

	result.Add(ECommandType::Stop);

	switch (Prototype)
	{
	case EUnitPrototype::Infantry:
		result.Add(ECommandType::Move);
		result.Add(ECommandType::ChangeMovingMethod);
		result.Add(ECommandType::Stop);
		result.Add(ECommandType::Observe);
		result.Add(ECommandType::Hold);
		break;
	case EUnitPrototype::Artillery:
		result.Add(ECommandType::Observe);
		result.Add(ECommandType::Hold);
		break;
	case EUnitPrototype::Armor:
		result.Add(ECommandType::Move);
		result.Add(ECommandType::Observe);
		result.Add(ECommandType::Hold);
		break;
	default:
		return TArray<ECommandType>();
	}

	return result;
}

void UUnitPropertiesComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UUnitPropertiesComponent, Stamina);
	DOREPLIFETIME(UUnitPropertiesComponent, Speed);
	DOREPLIFETIME(UUnitPropertiesComponent, Accuracy);
	DOREPLIFETIME(UUnitPropertiesComponent, Avoidance);
}

