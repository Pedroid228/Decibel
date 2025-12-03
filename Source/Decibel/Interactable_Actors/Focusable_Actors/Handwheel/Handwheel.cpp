#include "Handwheel.h"

#include "Interactable_Actors/Focusable_Actors/Doors//Controlled_Door/Controlled_Door.h"

// ALever
//------------------------------------------------------------------------------------------------------------
AHandwheel::AHandwheel(): Min_Angle(0.0), Max_Angle(360.0), Curr_Angle(0.0)
{
	Curr_Angle = Min_Angle;
}
//------------------------------------------------------------------------------------------------------------
void AHandwheel::On_Save_Implementation(FActor_Save_Data &save_data)
{
	Super::On_Save_Implementation(save_data);

	save_data.Handwheel_Angle = Curr_Angle;
}
//------------------------------------------------------------------------------------------------------------
void AHandwheel::On_Load_Implementation(const FActor_Save_Data &save_data)
{
	Super::On_Load_Implementation(save_data);

	Curr_Angle = save_data.Handwheel_Angle;
	Update_Rotation();
	Update_Controlling_Door();
}
//------------------------------------------------------------------------------------------------------------
void AHandwheel::BeginPlay()
{
	Super::BeginPlay();

	check(Controlled_Door != 0);
}
//------------------------------------------------------------------------------------------------------------
void AHandwheel::Tick(float delta_time)
{
	Super::Tick(delta_time);

	if (Is_Interacting)
	{
		Update_Angle();
		Update_Controlling_Door();
	}
}
//------------------------------------------------------------------------------------------------------------
void AHandwheel::Update_Angle()
{
	double projected_movement;
	double additive_rotation_angle;
	FVector wheel_center_pos;
	FVector grip_pos;
	FVector from_center_to_grip, tangent;
	FVector world_mouse_move;
	FVector forward, right, up;

	wheel_center_pos = GetActorLocation();
	grip_pos = Get_Grip_Socket_Pos();

	forward = GetActorForwardVector();
	right = GetActorRightVector();
	up = GetActorUpVector();

	from_center_to_grip = (grip_pos - wheel_center_pos).GetSafeNormal();
	tangent = FVector::CrossProduct(up, from_center_to_grip).GetSafeNormal();

	world_mouse_move = Mouse_Move_Vector.X * right + Mouse_Move_Vector.Y * -forward;

	projected_movement = FVector::DotProduct(world_mouse_move, tangent);
	additive_rotation_angle = projected_movement * Sensivity;

	Curr_Angle = FMath::Clamp(Curr_Angle + additive_rotation_angle, Min_Angle, Max_Angle);

	Update_Rotation();
}
//------------------------------------------------------------------------------------------------------------
void AHandwheel::Update_Rotation()
{
	FRotator curr_rotation;
	FRotator new_rotation;

	check(Mesh != 0);

	curr_rotation = Mesh->GetRelativeRotation();
	new_rotation = curr_rotation;

	new_rotation.Yaw = Curr_Angle;
	Mesh->SetRelativeRotation(new_rotation);
}
//------------------------------------------------------------------------------------------------------------
void AHandwheel::Update_Controlling_Door()
{
	double complete_percent;

	check(Controlled_Door != 0);
	complete_percent = (Curr_Angle - Min_Angle) / (Max_Angle - Min_Angle);
	Controlled_Door->Update_Pos_Offset(complete_percent);
}
//------------------------------------------------------------------------------------------------------------
