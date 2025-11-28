#pragma once

#include "Focusable_Actors/Focusable_Actor/Focusable_Actor.h"
#include "Handwheel.generated.h"

class AControlled_Door;

// AHandwheel
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API AHandwheel: public AFocusable_Actor
{
	GENERATED_BODY()

public:
	AHandwheel();

protected:
	virtual void BeginPlay();
	virtual void Tick(float delta_time);
	void Update_Rotation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Min_Rotation_Angle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Max_Rotation_Angle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) AControlled_Door *Controlled_Door = 0;

private:
	double Curr_Rotation_Angle;
};
//------------------------------------------------------------------------------------------------------------