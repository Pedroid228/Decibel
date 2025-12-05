#include "Keycard_Scanner.h"
#include "Interactable_Actors/Focusable_Actors/Doors/Locked_Door/Locked_Door.h"
#include "Astronaut/Astronaut.h"
#include "Components/WidgetComponent.h"

// AKeycard_Scanner
//------------------------------------------------------------------------------------------------------------
AKeycard_Scanner::AKeycard_Scanner(): Keycard_Type(EKeycard_Type::None), Open_Time_Sec(6.0), Is_Unlocked(false)
{
	Interaction_Type = EInteraction_Type::Instant;
}
//------------------------------------------------------------------------------------------------------------
void AKeycard_Scanner::BeginPlay()
{
	Super::BeginPlay();
	check(Locked_Door != 0);
	check(Keycard_Type != EKeycard_Type::None);
}
//------------------------------------------------------------------------------------------------------------
void AKeycard_Scanner::On_Interact_Begin_Implementation(AActor *interacting_actor)
{
	bool has_keycard;
	AAstronaut *astronaut = 0;
	UWorld *world = 0;

	astronaut = Cast<AAstronaut>(interacting_actor);
	check(astronaut != 0);
	has_keycard = astronaut->Has_Keycard_Of_Type(Keycard_Type);

	check(Locked_Door != 0)
	Locked_Door->Set_Lock(has_keycard);

	Is_Unlocked = true;

	world = GetWorld();
	check(world != 0);
	FTimerManager &timer_manger = world->GetTimerManager();
	timer_manger.ClearTimer(Door_Unlocked_Timer_Handle);
	timer_manger.SetTimer(Door_Unlocked_Timer_Handle, this, &AKeycard_Scanner::Block_Door, Open_Time_Sec, false);
}
//------------------------------------------------------------------------------------------------------------
void AKeycard_Scanner::Block_Door()
{
	Is_Unlocked = false;
	Locked_Door->Set_Lock(false);
}
//------------------------------------------------------------------------------------------------------------
