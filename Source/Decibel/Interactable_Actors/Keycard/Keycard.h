#pragma once

#include "Data/Interaction_Type/Interaction_Type.h"
#include "Data/Keycard_Type/Keycard_Type.h"
#include "Interactable_Actors/Interactable_Actor/Interactable_Actor.h"
#include "Interfaces/Saveable_Actor_Interface/Saveable_Actor_Interface.h"

#include "Keycard.generated.h"

// AKeycard
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API AKeycard: public AInteractable_Actor, public ISaveable_Actor_Interface
{
	GENERATED_BODY()

public:
	AKeycard();
	virtual void On_Save_Implementation(FActor_Save_Data &save_data);
	virtual void On_Load_Implementation(const FActor_Save_Data &save_data) override;

protected:
	virtual void On_Interact_Begin_Implementation(AActor *interacting_actor);
	UPROPERTY(EditAnywhere, BlueprintReadOnly) EKeycard_Type Type;

private:
	void Hide();

	bool Is_Collected;
};
//------------------------------------------------------------------------------------------------------------
