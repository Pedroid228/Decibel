#pragma once

#include "Components/SceneComponent.h"
#include "Data/Sound_Stimulus/Sound_Stimulus.h"

#include "Sound_Emitter_Component.generated.h"

// USound_Emitter_Component
//------------------------------------------------------------------------------------------------------------
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) class DECIBEL_API USound_Emitter_Component: public USceneComponent
{
	GENERATED_BODY()

public:
	USound_Emitter_Component(const FObjectInitializer &object_initializer);
	UFUNCTION(BlueprintCallable) void Emit_Sound_At_Pos(const FSound_Stimulus &sound);
	UFUNCTION(BlueprintCallable) void Emit_Sound_At_Component_Pos(FSound_Stimulus &sound);
};
//------------------------------------------------------------------------------------------------------------
