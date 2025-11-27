#pragma once

#include "GameFramework/Actor.h"
#include "Interfaces/Trace_Interaction_Interface/Trace_Interaction_Interface.h"
#include "Focusable_Actor.generated.h"

class USceneComponent;
class UStaticMeshComponent;

// AFocusable_Actor
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API AFocusable_Actor: public AActor, public ITrace_Interaction_Interface
{
	GENERATED_BODY()

public:
	AFocusable_Actor();

protected:
	virtual void Tick(float delta_time);
	virtual void On_Trace_Hit_Implementation(AActor *interacting_actor, UPrimitiveComponent *hit_component);
	virtual void On_Trace_Leave_Implementation();
	virtual void On_Interact_Begin_Implementation(AActor *interacting_actor);
	virtual void On_Interact_End_Implementation();
	FVector Get_Grip_Socket_Pos();

	bool Is_Interacting;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Sensivity;
	FVector2D Last_Mouse_Position;
	FVector2D Mouse_Move_Vector;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) USceneComponent *Root_Scene = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UStaticMeshComponent *Mesh = 0;
};
//------------------------------------------------------------------------------------------------------------