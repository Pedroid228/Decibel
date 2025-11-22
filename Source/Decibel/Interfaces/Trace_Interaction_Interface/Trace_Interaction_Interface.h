#pragma once

#include "UObject/Interface.h"

#include "Trace_Interaction_Interface.generated.h"

// UTrace_Interaction_Interface
//------------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI, Blueprintable) class UTrace_Interaction_Interface: public UInterface
{
	GENERATED_BODY()
};
//------------------------------------------------------------------------------------------------------------

// ITrace_Interaction_Interface
//------------------------------------------------------------------------------------------------------------
class ITrace_Interaction_Interface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void On_Trace_Hit(AActor *InteractingActor, UPrimitiveComponent *HitComponent);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void On_Trace_Leave();
};
//------------------------------------------------------------------------------------------------------------
