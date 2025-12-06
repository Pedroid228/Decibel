#include "Sound_Emitter_Component.h"

#include "Subsystems/Sounds_Manager_Subsystem/Sounds_Manager_Subsystem.h"

// USound_Emitter_Component
//------------------------------------------------------------------------------------------------------------
USound_Emitter_Component::USound_Emitter_Component(const FObjectInitializer &object_initializer)
{
}
//------------------------------------------------------------------------------------------------------------
void USound_Emitter_Component::Emit_Sound_At_Pos(const FSound_Stimulus &sound)
{
	USounds_Manager_Subsystem::Emit_Sound_At_Pos(sound);
}
//------------------------------------------------------------------------------------------------------------
void USound_Emitter_Component::Emit_Sound_At_Component_Pos(FSound_Stimulus &sound)
{
	sound.Pos = GetComponentLocation();
	USounds_Manager_Subsystem::Emit_Sound_At_Pos(sound);
}
//------------------------------------------------------------------------------------------------------------
