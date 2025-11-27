#pragma once

#include "Components/ActorComponent.h"
#include "Data/Sound_Stimulus/Sound_Stimulus.h"

#include "Footsteps_Sound_Component.generated.h"

// EAstronaut_State
//------------------------------------------------------------------------------------------------------------
UENUM() enum class EAstronaut_State: uint8
{
	Idle,
	Walk,
	Crouch,
	Sprint
};
//------------------------------------------------------------------------------------------------------------

// UFootsteps_Sound_Component
//------------------------------------------------------------------------------------------------------------
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) class DECIBEL_API UFootsteps_Sound_Component: public UActorComponent
{
	GENERATED_BODY()

public:
	UFootsteps_Sound_Component(const FObjectInitializer &object_initializer);
	void Set_State(EAstronaut_State new_state);

protected:
	virtual void BeginPlay();
    UPROPERTY(EditAnywhere) double Footstep_Interval_Walk;
    UPROPERTY(EditAnywhere) double Footstep_Interval_Sprint;
    UPROPERTY(EditAnywhere) USoundBase *Footstep_Sound = 0;

private:
	void Start_Footsteps();
	void Stop_Footsteps();
    void Play_Footstep_Sound();
	void Emit_Sound(AActor *owner, const FVector &owner_pos);

	ESound_Type Sound_Type;
	double Curr_Footstep_Interval;
    FTimerHandle Footsteps_Timer_Handle;
};
//------------------------------------------------------------------------------------------------------------
