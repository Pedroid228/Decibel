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
	virtual void On_Save_Implementation(FActor_Save_Data &save_data) override;
	virtual void On_Load_Implementation(const FActor_Save_Data &save_data) override;

protected:
	virtual void Tick(float delta_time);
	void Update_Offset();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Min_Offset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Max_Offset;

private:
	void Update_Pos();

	double Curr_Offset;
};
//------------------------------------------------------------------------------------------------------------
