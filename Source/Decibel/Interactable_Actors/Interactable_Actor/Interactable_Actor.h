#pragma once

#include "GameFramework/Actor.h"
#include "Interfaces/Trace_Interaction_Interface/Trace_Interaction_Interface.h"
#include "Interactable_Actor.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UWidgetComponent;
class UInteraction_Widget;

// AInteractable_Actor
//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract) class DECIBEL_API AInteractable_Actor: public AActor, public ITrace_Interaction_Interface
{
	GENERATED_BODY()

public:
	AInteractable_Actor();
	virtual EInteraction_Type Get_Interaction_Type_Implementation();

protected:
	virtual void BeginPlay();
	virtual void On_Trace_Hit_Implementation(AActor *interacting_actor, UPrimitiveComponent *hit_component);
	virtual void On_Trace_Leave_Implementation();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) USceneComponent *Root_Scene = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Interaction_Tip) UWidgetComponent *Interaction_Tip_Widget_Component = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) UStaticMeshComponent *Mesh = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction_Tip) TSubclassOf<UInteraction_Widget> Interaction_Widget_BP_Class = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction_Tip) UTexture2D *Interaction_Tip_Texture = 0;


	EInteraction_Type Interaction_Type;
};
//------------------------------------------------------------------------------------------------------------
