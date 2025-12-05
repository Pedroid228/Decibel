#pragma once

#include "Interactable_Actors/Focusable_Actors/Focusable_Actor/Focusable_Actor.h"

#include "Hand_Door.generated.h"

// AHand_Door
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API AHand_Door: public AFocusable_Actor
{
	GENERATED_BODY()

public:
	AHand_Door();
	virtual void On_Save_Implementation(FActor_Save_Data &save_data);
	virtual void On_Load_Implementation(const FActor_Save_Data &save_data);

protected:
	virtual void Tick(float delta_time);
	virtual void On_Trace_Hit_Implementation(AActor *interacting_actor, UPrimitiveComponent *hit_component);
	virtual FVector Get_Grip_Socket_Pos();
	virtual void Update_Offset(float delta_time);
	void Update_Pos();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Min_Offset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Max_Offset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Max_Movement_Speed;
	double Curr_Offset;

private:
	bool Is_Player_In_Front();
	FVector Get_Socket_Pos_By_Name(const FName &socket_name);
};
//------------------------------------------------------------------------------------------------------------
