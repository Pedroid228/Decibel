#pragma once

#include "Interactable_Actors/Interactable_Actor/Interactable_Actor.h"
#include "Interfaces/Saveable_Actor_Interface/Saveable_Actor_Interface.h"
#include "Focusable_Actor.generated.h"

class UAudioComponent;
class USound_Emitter_Component;

// AFocusable_Actor
//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract) class DECIBEL_API AFocusable_Actor: public AInteractable_Actor, public ISaveable_Actor_Interface
{
	GENERATED_BODY()

public:
	AFocusable_Actor();
	virtual void On_Save_Implementation(FActor_Save_Data &save_data);

protected:
	virtual void BeginPlay();
	virtual void Tick(float delta_time);
	virtual void On_Interact_Begin_Implementation(AActor *interacting_actor);
	virtual void On_Interact_End_Implementation();
	virtual FVector Get_Grip_Socket_Pos();
	void Update_Camera_To_Grip();
	void Update_Sound_Playback(float delta_time);
	void Start_Sound_Playing();
	void Stop_Sound_Playing();
	void Emit_Sound();

	bool Is_Interacting;
	bool Is_Moving;
	bool Is_Sound_Playing;
	bool Emit_Sound_At_Player;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound) ESound_Type Sound_Type;
	double Sound_Playback_Pos;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Sensivity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound) double Sound_Start_Threashhold;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound) double Sound_Reemit_Time_Sec;
	FVector2D Last_Mouse_Position;
	FVector2D Mouse_Move_Vector;
	FTimerHandle Emit_Sound_Timer_Handle;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) UAudioComponent *Audio_Component = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound) USoundBase *Moving_Sound = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) USound_Emitter_Component *Sound_Emitter_Component = 0;
	APlayerController *Player_Controller = 0;
	AActor *Interacting_Actor = 0;
};
//------------------------------------------------------------------------------------------------------------
