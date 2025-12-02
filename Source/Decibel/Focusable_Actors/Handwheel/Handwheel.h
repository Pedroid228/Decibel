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
	virtual void On_Save_Implementation(FActor_Save_Data &save_data) override;
	virtual void On_Load_Implementation(const FActor_Save_Data &save_data) override;

protected:
	virtual void BeginPlay();
	virtual void Tick(float delta_time);
	void Update_Angle();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Min_Angle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Max_Angle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) AControlled_Door *Controlled_Door = 0;

private:
	void Update_Rotation();
	void Update_Controlling_Door();

	double Curr_Angle;
};
//------------------------------------------------------------------------------------------------------------
