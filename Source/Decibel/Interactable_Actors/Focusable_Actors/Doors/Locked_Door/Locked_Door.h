#pragma once

#include "Interactable_Actors/Focusable_Actors/Doors/Hand_Door/Hand_Door.h"
#include "Locked_Door.generated.h"

// ALocked_Door
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API ALocked_Door: public AHand_Door
{
	GENERATED_BODY()

public:
	ALocked_Door();
	void Set_Lock(bool is_unlock);

protected:
	virtual void Tick(float delta_time);
	virtual void Update_Offset();
	virtual void On_Interact_End_Implementation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Close_Speed;

private:
	bool Is_Unlocked;
};
//------------------------------------------------------------------------------------------------------------
