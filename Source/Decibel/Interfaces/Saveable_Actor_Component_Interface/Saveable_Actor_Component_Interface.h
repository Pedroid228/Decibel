#pragma once

#include "Data/Save_Data/Actor_Save_Data/Actor_Save_Data.h"
#include "UObject/Interface.h"

#include "Saveable_Actor_Component_Interface.generated.h"

// USaveable_Actor_Component_Interface
//------------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI, Blueprintable) class USaveable_Actor_Component_Interface: public UInterface
{
	GENERATED_BODY()
};
//------------------------------------------------------------------------------------------------------------

// ISaveable_Actor_Component_Interface
//------------------------------------------------------------------------------------------------------------
class ISaveable_Actor_Component_Interface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void On_Save(FActor_Component_Save_Data &save_data);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void On_Load(const FActor_Component_Save_Data &save_data);
};
//------------------------------------------------------------------------------------------------------------
