#pragma once

#include "Interactable_Actors/Focusable_Actors/Focusable_Actor/Focusable_Actor.h"

#include "Lever.generated.h"

// ALever
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API ALever: public AFocusable_Actor
{
	GENERATED_BODY()

public:
	ALever();
	virtual void On_Save_Implementation(FActor_Save_Data &save_data) override;
	virtual void On_Load_Implementation(const FActor_Save_Data &save_data) override;

protected:
	virtual void Tick(float delta_time);
	void Update_Angle();
	void Update_Rotation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Min_Angle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Max_Angle;

private:
	double Curr_Angle;
};
//------------------------------------------------------------------------------------------------------------
