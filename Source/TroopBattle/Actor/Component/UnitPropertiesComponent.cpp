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

	auto randomPrototype = FMath::RandRange(0, static_cast<int32>(EUnitPrototype::Max) - 1);
	Prototype = static_cast<EUnitPrototype>(randomPrototype);


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

	// @TODO: from each unit, make commands they can
	switch (Prototype)
	{
	case EUnitPrototype::Fixed:
		result.Add(ECommandType::Attack);
		break;
	case EUnitPrototype::Movable:
		result.Add(ECommandType::Move);
		break;
	case EUnitPrototype::Attackable:
		result.Add(ECommandType::Attack);
		result.Add(ECommandType::Move);
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

