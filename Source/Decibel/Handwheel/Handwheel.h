#pragma once

#include "GameFramework/Actor.h"
#include "Interfaces/Trace_Interaction_Interface/Trace_Interaction_Interface.h"
#include "Handwheel.generated.h"

class USceneComponent;
class UStaticMeshComponent;

// AHandwheel
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API AHandwheel: public AActor, public ITrace_Interaction_Interface
{
	GENERATED_BODY()

public:
	AHandwheel();

protected:
	virtual void Tick(float delta_time);
	void Update_Rotation();

	virtual void On_Trace_Hit_Implementation(AActor *interacting_actor, UPrimitiveComponent *hit_component);
	virtual void On_Trace_Leave_Implementation();
	virtual void On_Interact_Begin_Implementation(AActor *interacting_actor);
	virtual void On_Interact_End_Implementation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) USceneComponent *Root_Scene = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UStaticMeshComponent *Mesh = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) double Sensivity;

private:
	FVector Get_Grip_Socket_Pos();

	FVector2D Last_Mouse_Position;
	bool Is_Interacting;
};
//------------------------------------------------------------------------------------------------------------