#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterialSetting.generated.h"

UENUM()
enum class ETerrainType
{
    Default,
    Water,
    Ice,
    Mud,
};

USTRUCT(BlueprintType)
struct FPhysicalMaterialSetting
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical Material Settings")
    UPhysicalMaterial* PhysicalMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical Material Settings")
    ETerrainType TerrainType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical Material Settings")
    bool bCanAttack;

};

UCLASS(BlueprintType)
class TROOPBATTLE_API UPhysicalMaterialSettingsDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    // List of settings for different Physical Materials
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical Material Settings")
    TArray<FPhysicalMaterialSetting> PhysicalMaterialSettings;
};