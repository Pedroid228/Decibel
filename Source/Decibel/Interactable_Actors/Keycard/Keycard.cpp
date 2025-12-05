#include "Keycard.h"
#include "Astronaut/Astronaut.h"

// AKeycard
//------------------------------------------------------------------------------------------------------------
AKeycard::AKeycard(): Type(EKeycard_Type::None), Is_Collected(false)
{
	Interaction_Type = EInteraction_Type::Instant;
}
//------------------------------------------------------------------------------------------------------------
void AKeycard::On_Save_Implementation(FActor_Save_Data &save_data)
{
	save_data.Actor_Class_Name = GetClass()->GetName();
	save_data.Is_Keycard_Collected = Is_Collected; 
}
//------------------------------------------------------------------------------------------------------------
void AKeycard::On_Load_Implementation(const FActor_Save_Data &save_data)
{
	if (save_data.Is_Keycard_Collected)
		Hide();
}
//------------------------------------------------------------------------------------------------------------
void AKeycard::On_Interact_Begin_Implementation(AActor *interacting_actor)
{
	AAstronaut *astronaut = 0;
	UWorld *world = 0;

	astronaut = Cast<AAstronaut>(interacting_actor);
	check(astronaut != 0);
	astronaut->Add_Keycard_By_Type(Type);
	Hide();
}
//------------------------------------------------------------------------------------------------------------
void AKeycard::Hide()
{
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	Is_Collected = true;
}
//------------------------------------------------------------------------------------------------------------
