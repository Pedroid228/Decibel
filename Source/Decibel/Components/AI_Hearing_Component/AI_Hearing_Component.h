#pragma once

#include "Components/ActorComponent.h"
#include "Data/Sound_Stimulus/Sound_Stimulus.h"
#include "Interfaces/Saveable_Actor_Component_Interface/Saveable_Actor_Component_Interface.h"

#include "AI_Hearing_Component.generated.h"

class AAIController;

// UAI_Hearing_Component
//------------------------------------------------------------------------------------------------------------
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) class DECIBEL_API UAI_Hearing_Component: public UActorComponent, public ISaveable_Actor_Component_Interface
{
	GENERATED_BODY()

public:
	UAI_Hearing_Component(const FObjectInitializer &object_initializer);
	virtual void On_Save_Implementation(FActor_Component_Save_Data &save_data) override;
	virtual void On_Load_Implementation(const FActor_Component_Save_Data &save_data) override;

protected:
	virtual void BeginPlay();

private:
	UFUNCTION() void Process_Sound_Stimulus(const FSound_Stimulus &sound);
	void Update_Blackboard();

	FHearing_Component_Save_Data Hearing_Component_Save_Data;

	AActor *Owner = 0;
	AAIController *AI_Controller = 0;
};
//------------------------------------------------------------------------------------------------------------
