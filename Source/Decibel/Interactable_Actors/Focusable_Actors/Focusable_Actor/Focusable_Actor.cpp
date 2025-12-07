#include "Focusable_Actor.h"

#include "Components/AudioComponent.h"
#include "Components/Sound_Emitter_Component/Sound_Emitter_Component.h"
#include "Components/WidgetComponent.h"

// AFocusable_Actor
//------------------------------------------------------------------------------------------------------------
AFocusable_Actor::AFocusable_Actor()
: Is_Interacting(false), Is_Moving(false), Is_Sound_Playing(false), Emit_Sound_At_Player(true), Sound_Type(ESound_Type::None), Sensivity(1.0), Sound_Start_Threashhold(0.01), Sound_Reemit_Time_Sec(1.0), Last_Mouse_Position(FVector2D::ZeroVector),
  Mouse_Move_Vector(FVector2D::ZeroVector)
{
	Interaction_Type = EInteraction_Type::Hold_And_Drag;
	check(Interaction_Tip_Widget_Component != 0);
	Interaction_Tip_Widget_Component->SetupAttachment(Mesh, TEXT("Grip_Socket"));

	Sound_Emitter_Component = CreateDefaultSubobject<USound_Emitter_Component>(TEXT("Sound_Emitter_Comp"));
	check(Sound_Emitter_Component != 0);
	Sound_Emitter_Component->SetupAttachment(Mesh);
}
//------------------------------------------------------------------------------------------------------------
void AFocusable_Actor::On_Save_Implementation(FActor_Save_Data &save_data)
{
	save_data.Actor_Class_Name = GetClass()->GetName();
}
//------------------------------------------------------------------------------------------------------------
void AFocusable_Actor::Tick(float delta_time)
{
	UWorld *world = 0;
	APlayerController *player_controller = 0;
	FVector2D current_mouse_pos;

	Super::Tick(delta_time);

	if (Is_Interacting)
	{
		world = GetWorld();
		check(world != 0);

		player_controller = world->GetFirstPlayerController();
		check(player_controller != 0);

		player_controller->GetMousePosition(current_mouse_pos.X, current_mouse_pos.Y);
		Mouse_Move_Vector = current_mouse_pos - Last_Mouse_Position;

		Last_Mouse_Position = current_mouse_pos;

		Update_Camera_To_Grip();
	}
}
//------------------------------------------------------------------------------------------------------------
void AFocusable_Actor::On_Interact_Begin_Implementation(AActor *interacting_actor)
{
	UWorld *world = 0;

	Is_Interacting = true;
	Emit_Sound_At_Player = true;

	Interacting_Actor = interacting_actor;
	check(Interacting_Actor != 0);

	SetActorTickEnabled(true);

	world = GetWorld();
	check(world != 0);

	Player_Controller = world->GetFirstPlayerController();
	check(Player_Controller != 0);

	Update_Camera_To_Grip();

	Interaction_Tip_Widget_Component->SetVisibility(false);
}
//------------------------------------------------------------------------------------------------------------
void AFocusable_Actor::On_Interact_End_Implementation()
{
	Is_Interacting = false;

	check(Player_Controller != 0);
	Player_Controller = 0;

	Interaction_Tip_Widget_Component->SetVisibility(true);

	if (Is_Sound_Playing)
		Stop_Sound_Playing();

	SetActorTickEnabled(false);
}
//------------------------------------------------------------------------------------------------------------
FVector AFocusable_Actor::Get_Grip_Socket_Pos()
{
	FVector grip_pos;
	check(Mesh != 0);
	if (Mesh->DoesSocketExist(TEXT("Grip_Socket")))
	{
		grip_pos = Mesh->GetSocketLocation(TEXT("Grip_Socket"));
		return grip_pos;
	}
	else
		return FVector::ZeroVector;
}
//------------------------------------------------------------------------------------------------------------
void AFocusable_Actor::Update_Camera_To_Grip()
{
	FVector grip_pos;
	FVector player_view_pos;
	FVector to_target;
	FRotator player_view_rotation;
	FRotator target_rotation;

	grip_pos = Get_Grip_Socket_Pos();

	Player_Controller->GetPlayerViewPoint(player_view_pos, player_view_rotation);

	to_target = grip_pos - player_view_pos;
	target_rotation = to_target.Rotation();

	Player_Controller->SetControlRotation(target_rotation);
}
//------------------------------------------------------------------------------------------------------------
void AFocusable_Actor::Update_Sound_Playback(float delta_time)
{
	double curr_pitch_mul;

	check(Audio_Component != 0);

	if (Interaction_Sound == 0)
		return;

	if (Is_Moving)
	{
		curr_pitch_mul = 1.0;

		if (Is_Sound_Playing)
		{
			if (!Audio_Component->IsPlaying())
				Audio_Component->Play();
		}
		if (!Is_Sound_Playing)
			Start_Sound_Playing();

		Audio_Component->SetPitchMultiplier(curr_pitch_mul);

		Sound_Playback_Pos += delta_time * Audio_Component->PitchMultiplier;
	}
	else if (Is_Sound_Playing)
	{
		Stop_Sound_Playing();
	}
}
//------------------------------------------------------------------------------------------------------------
void AFocusable_Actor::Start_Sound_Playing()
{
	UWorld *world = GetWorld();
	check(world != 0);

	world->GetTimerManager().SetTimer(Emit_Sound_Timer_Handle, this, &AFocusable_Actor::Emit_Sound, Sound_Reemit_Time_Sec, true, Sound_Reemit_Time_Sec);

	Audio_Component->Play(Sound_Playback_Pos);
	Is_Sound_Playing = true;
}
//------------------------------------------------------------------------------------------------------------
void AFocusable_Actor::Stop_Sound_Playing()
{
	UWorld *world = GetWorld();
	check(world != 0);

	world->GetTimerManager().ClearTimer(Emit_Sound_Timer_Handle);

	Audio_Component->SetPitchMultiplier(0.0);
	Audio_Component->Stop();
	Is_Sound_Playing = false;
}
//------------------------------------------------------------------------------------------------------------
void AFocusable_Actor::Emit_Sound()
{
	FSound_Stimulus sound_stimulus;
	FVector player_pos;

	check(Interacting_Actor != 0);
	player_pos = Interacting_Actor->GetActorLocation();

	check(Sound_Emitter_Component != 0);
	sound_stimulus = FSound_Stimulus(Sound_Type, player_pos, this);

	if (Emit_Sound_At_Player)
		Sound_Emitter_Component->Emit_Sound_At_Pos(sound_stimulus);
}
//------------------------------------------------------------------------------------------------------------
