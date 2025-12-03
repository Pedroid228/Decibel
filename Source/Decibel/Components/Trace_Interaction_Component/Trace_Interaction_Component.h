#pragma once

#include "Components/ActorComponent.h"

#include "Trace_Interaction_Component.generated.h"

// UTrace_Interaction_Component
//------------------------------------------------------------------------------------------------------------
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) class DECIBEL_API UTrace_Interaction_Component: public UActorComponent
{
	GENERATED_BODY()

public:
	UTrace_Interaction_Component(const FObjectInitializer &object_initializer);
	void Frame_Line_Trace(const FVector &start, const FVector &direction);
	AActor *Get_Interactable_Actor() const;
	UPrimitiveComponent *Get_Interactable_Component() const;

protected:
	UPROPERTY(EditAnywhere) float Sphere_Radius;
	UPROPERTY(EditAnywhere) double Length;

private:
	FVector Start;
	FVector End;
	AActor *Curr_Actor = 0;
	UPrimitiveComponent *Curr_Component = 0;
};
//------------------------------------------------------------------------------------------------------------
