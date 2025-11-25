#include "Sounds_Manager_Subsystem.h"

#include "Engine/World.h"

// USounds_Manager_Subsystem
//------------------------------------------------------------------------------------------------------------
FSound_Stimulus_Delegate USounds_Manager_Subsystem::On_Sound_Stimulus_Emit;
//------------------------------------------------------------------------------------------------------------
USounds_Manager_Subsystem::USounds_Manager_Subsystem()
{
}
//------------------------------------------------------------------------------------------------------------
void USounds_Manager_Subsystem::Emit_Sound_At_Pos(const FSound_Stimulus &sound)
{
	On_Sound_Stimulus_Emit.Broadcast(sound);
}
//------------------------------------------------------------------------------------------------------------
