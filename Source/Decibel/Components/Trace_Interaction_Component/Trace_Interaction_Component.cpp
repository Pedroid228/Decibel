#include "Trace_Interaction_Component.h"

#include "CollisionQueryParams.h"
#include "Interfaces/Trace_Interaction_Interface/Trace_Interaction_Interface.h"

// UTrace_Interaction_Component
//------------------------------------------------------------------------------------------------------------
UTrace_Interaction_Component::UTrace_Interaction_Component(const FObjectInitializer &object_initializer): Super(object_initializer), Start(FVector::ZeroVector), End(FVector::ZeroVector), Length(100.0)
{
}
//------------------------------------------------------------------------------------------------------------
AActor *UTrace_Interaction_Component::Get_Interactable_Actor() const
{
	return Curr_Actor;
}
//------------------------------------------------------------------------------------------------------------
UPrimitiveComponent *UTrace_Interaction_Component::Get_Interactable_Component() const
{
	return Curr_Component;
}
//------------------------------------------------------------------------------------------------------------
void UTrace_Interaction_Component::Frame_Line_Trace(const FVector &start, const FVector &direction)
{
	bool has_hit;
	FHitResult hit_result;
	FVector end;
	FCollisionQueryParams trace_params;
	AActor *owner = 0;
	AActor *hitted_actor = 0;
	UPrimitiveComponent *hitted_component = 0;

	owner = GetOwner();
	check(owner != 0);

	trace_params.AddIgnoredActor(owner);

	end = start + direction * Length;

	// DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 0.5f); // !!! Debug
	has_hit = GetWorld()->LineTraceSingleByChannel(hit_result, start, end, ECC_Visibility, trace_params);

	if (has_hit)
	{
		hitted_actor = hit_result.GetActor();
		check(hitted_actor != 0);

		hitted_component = hit_result.GetComponent();
		check(hitted_component != 0);

		if (hitted_actor->Implements<UTrace_Interaction_Interface>())
		{
			if (Curr_Actor != hitted_actor)
				Curr_Actor = hitted_actor;

			if (Curr_Component != hitted_component)
			{
				Curr_Component = hitted_component;
				ITrace_Interaction_Interface::Execute_On_Trace_Hit(Curr_Actor, owner, Curr_Component);
			}
		}
	}
	else
	{
		Curr_Actor = 0;
		Curr_Component = 0;
	}
}
//------------------------------------------------------------------------------------------------------------
