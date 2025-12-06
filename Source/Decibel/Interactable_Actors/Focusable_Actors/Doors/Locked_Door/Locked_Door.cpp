#include "Locked_Door.h"

// ALocked_Door
//------------------------------------------------------------------------------------------------------------
ALocked_Door::ALocked_Door(): Is_Unlocked(false), Close_Speed(5.0)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	SetActorTickEnabled(true);
}
//------------------------------------------------------------------------------------------------------------
void ALocked_Door::Set_Lock(bool is_unlock)
{
	Is_Unlocked = is_unlock;
}
//------------------------------------------------------------------------------------------------------------
void ALocked_Door::Tick(float delta_time)
{
	double new_offset;

	Super::Tick(delta_time);

	if (!Is_Unlocked && Curr_Offset != Min_Offset)
	{
		Is_Moving = true;
		Emit_Sound_At_Player = false;
		new_offset = FMath::FInterpConstantTo(Curr_Offset, Min_Offset, delta_time, Close_Speed);
		Curr_Offset = new_offset;
		Update_Sound_Playback(delta_time);
		Update_Pos();

		if (Curr_Offset == Min_Offset)
		{
			SetActorTickEnabled(false);
			Is_Moving = false;
		}
	}
}
//------------------------------------------------------------------------------------------------------------
void ALocked_Door::Update_Offset(float delta_time)
{
	if (Is_Unlocked)
		Super::Update_Offset(delta_time);
}
//------------------------------------------------------------------------------------------------------------
void ALocked_Door::On_Interact_End_Implementation()
{
	Super::On_Interact_End_Implementation();
	SetActorTickEnabled(true);
}
//------------------------------------------------------------------------------------------------------------
