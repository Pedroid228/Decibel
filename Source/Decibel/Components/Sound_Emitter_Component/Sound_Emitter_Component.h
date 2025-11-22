#pragma once

#include "Components/ActorComponent.h"
#include "Data/Sound_Stimulus/Sound_Stimulus.h"

#include "Sound_Emitter_Component.generated.h"

// USound_Emitter_Component
//------------------------------------------------------------------------------------------------------------
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) class DECIBEL_API USound_Emitter_Component: public UActorComponent
{
	GENERATED_BODY()

public:
	USound_Emitter_Component(const FObjectInitializer &object_initializer);
	UFUNCTION(BlueprintCallable) void Emit_Sound_At_Pos(const FSound_Stimulus &sound);
};
//------------------------------------------------------------------------------------------------------------
