#pragma once

#include "Focusable_Actors/Focusable_Actor/Focusable_Actor.h"
#include "Handwheel.generated.h"

// AHandwheel
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API AHandwheel: public AFocusable_Actor
{
	GENERATED_BODY()

public:
	AHandwheel();

protected:
	virtual void Tick(float delta_time);
	void Update_Rotation();
};
//------------------------------------------------------------------------------------------------------------