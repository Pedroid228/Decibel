#pragma once

#include "Interactable_Actors/Interactable_Actor/Interactable_Actor.h"
#include "Interfaces/Saveable_Actor_Interface/Saveable_Actor_Interface.h"
#include "Focusable_Actor.generated.h"

// AFocusable_Actor
//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract) class DECIBEL_API AFocusable_Actor: public AInteractable_Actor, public ISaveable_Actor_Interface
{
	GENERATED_BODY()

public:
	AFocusable_Actor();
	virtual void On_Save_Implementation(FActor_Save_Data &save_data);

protected:
	virtual void Tick(float delta_time);
	virtual void On_Interact_Begin_Implementation(AActor *interacting_actor);
	virtual void On_Interact_End_Implementation();
	virtual FVector Get_Grip_Socket_Pos();
	void Update_Camera_To_Grip();

	bool Is_Interacting;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Sensivity;
	FVector2D Last_Mouse_Position;
	FVector2D Mouse_Move_Vector;
	APlayerController *Player_Controller = 0;
};
//------------------------------------------------------------------------------------------------------------
