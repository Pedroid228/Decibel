#pragma once

#include "Components/ActorComponent.h"
#include "Data/Sound_Stimulus/Sound_Stimulus.h"
#include "Interfaces/Saveable_Actor_Interface/Saveable_Actor_Interface.h"
#include "AI_Hearing_Component.generated.h"

class AAIController;

// UAI_Hearing_Component
//------------------------------------------------------------------------------------------------------------
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) class DECIBEL_API UAI_Hearing_Component: public UActorComponent
{
	GENERATED_BODY()

public:
	UAI_Hearing_Component(const FObjectInitializer &object_initializer);

protected:
	virtual void BeginPlay();

private:
	UFUNCTION() void Process_Sound_Stimulus(const FSound_Stimulus &sound);

	AActor *Owner = 0;
	AAIController *AI_Controller = 0;
};
//------------------------------------------------------------------------------------------------------------
