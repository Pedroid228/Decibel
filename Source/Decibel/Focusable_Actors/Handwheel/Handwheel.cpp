#include "Handwheel.h"

// ALever
//------------------------------------------------------------------------------------------------------------
AHandwheel::AHandwheel()
{
}
//------------------------------------------------------------------------------------------------------------
void AHandwheel::Tick(float delta_time)
{
	Super::Tick(delta_time);

    if (Is_Interacting)
		Update_Rotation();
}
//------------------------------------------------------------------------------------------------------------
void AHandwheel::Update_Rotation()
{
	double projected_movement;
	double rotation_angle;
    UWorld *world = 0;
    APlayerController *player_controller = 0;
    FVector wheel_center_pos;
    FVector grip_pos;
    FVector from_center_to_grip, tangent;
	FVector world_mouse_move;
	FVector rotation_axis;
	FVector camera_forward, camera_right, camera_up;
	FRotator new_rotation;

    world = GetWorld();
	check(world != 0);

	player_controller = world->GetFirstPlayerController();
	check(player_controller != 0);

    wheel_center_pos = GetActorLocation();
    grip_pos = Get_Grip_Socket_Pos();

	rotation_axis = GetActorForwardVector();
    from_center_to_grip = (grip_pos - wheel_center_pos).GetSafeNormal();
	tangent = FVector::CrossProduct(rotation_axis, from_center_to_grip).GetSafeNormal();

	camera_forward = player_controller->PlayerCameraManager->GetCameraRotation().Vector();
	camera_right = FVector::CrossProduct(FVector::UpVector, camera_forward).GetSafeNormal();
	camera_up = FVector::CrossProduct(camera_forward, camera_right).GetSafeNormal();

	world_mouse_move = -Mouse_Move_Vector.X * camera_right + Mouse_Move_Vector.Y * camera_up;

	projected_movement = FVector::DotProduct(world_mouse_move, tangent);
	rotation_angle = projected_movement * Sensivity;

    new_rotation = GetActorRotation();
    new_rotation.Roll += rotation_angle;
    SetActorRotation(new_rotation);
}
//------------------------------------------------------------------------------------------------------------
