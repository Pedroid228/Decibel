#pragma once

#include "Focusable_Actors/Focusable_Actor/Focusable_Actor.h"
#include "Lever.generated.h"

// ALever
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API ALever: public AFocusable_Actor
{
	GENERATED_BODY()

public:
	ALever();

protected:
	virtual void Tick(float delta_time);
	void Update_Rotation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Min_Angle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Max_Angle;

private:
	double Curr_Angle;
};
//------------------------------------------------------------------------------------------------------------