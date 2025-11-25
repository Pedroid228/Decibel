#pragma once

#include "Data/Save_Data/Actor_Save_Data/Actor_Save_Data.h"
#include "UObject/Interface.h"
#include "Saveable_Actor_Interface.generated.h"

// USaveable_Actor_Interface
//------------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI, Blueprintable) class USaveable_Actor_Interface : public UInterface
{
    GENERATED_BODY()
};
//------------------------------------------------------------------------------------------------------------



// ISaveable_Actor_Interface
//------------------------------------------------------------------------------------------------------------
class ISaveable_Actor_Interface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void On_Save(FActor_Save_Data &save_data);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void On_Load(const FActor_Save_Data &save_data);
};
//------------------------------------------------------------------------------------------------------------
