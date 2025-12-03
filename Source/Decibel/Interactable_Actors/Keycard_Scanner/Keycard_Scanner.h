#pragma once

#include "Interactable_Actors/Interactable_Actor/Interactable_Actor.h"
#include "Interfaces/Trace_Interaction_Interface/Trace_Interaction_Interface.h"
#include "Data/Interaction_Type/Interaction_Type.h"
#include "Keycard_Scanner.generated.h"

class ALocked_Door;

// AKeycard_Scanner
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API AKeycard_Scanner: public AInteractable_Actor
{
	GENERATED_BODY()

public:
	AKeycard_Scanner();

protected:
	virtual void BeginPlay();
	virtual void On_Interact_Begin_Implementation(AActor *interacting_actor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Open_Time_Sec;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) ALocked_Door *Locked_Door = 0;

private:
	void Block_Door();

	bool Is_Unlocked;
	FTimerHandle Door_Unlocked_Timer_Handle;
};
//------------------------------------------------------------------------------------------------------------
