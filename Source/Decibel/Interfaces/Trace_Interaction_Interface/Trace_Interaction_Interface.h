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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void On_Trace_Hit(AActor *interacting_actor, UPrimitiveComponent *hit_component);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void On_Trace_Leave();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void On_Interact_Begin(AActor *interacting_actor);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void On_Interact_End();
};
//------------------------------------------------------------------------------------------------------------
