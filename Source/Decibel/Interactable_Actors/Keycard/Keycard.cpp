#include "Keycard.h"
#include "Astronaut/Astronaut.h"

// AKeycard
//------------------------------------------------------------------------------------------------------------
AKeycard::AKeycard(): Type(EKeycard_Type::None)
{
	Interaction_Type = EInteraction_Type::Instant;
}
//------------------------------------------------------------------------------------------------------------
void AKeycard::On_Load_Implementation(const FActor_Save_Data &save_data)
{
	if (save_data.Astronaut_Save_Data.Keycards_Inventory.Contains(Type))
		Destroy();
}
//------------------------------------------------------------------------------------------------------------
void AKeycard::On_Interact_Begin_Implementation(AActor *interacting_actor)
{
	AAstronaut *astronaut = 0;
	UWorld *world = 0;

	astronaut = Cast<AAstronaut>(interacting_actor);
	check(astronaut != 0);
	astronaut->Add_Keycard_By_Type(Type);
	Destroy();
}
//------------------------------------------------------------------------------------------------------------
