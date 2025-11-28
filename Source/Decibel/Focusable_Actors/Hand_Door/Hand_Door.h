#pragma once

#include "Focusable_Actors/Focusable_Actor/Focusable_Actor.h"
#include "Hand_Door.generated.h"

// AHand_Door
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API AHand_Door: public AFocusable_Actor
{
	GENERATED_BODY()

public:
	AHand_Door();

protected:
	virtual void Tick(float delta_time);
	void Update_Position();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Min_Offset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Max_Offset;

private:
	double Curr_Offset;
};
//------------------------------------------------------------------------------------------------------------