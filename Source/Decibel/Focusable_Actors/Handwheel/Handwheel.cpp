#include "Handwheel.h"
#include "Controlled_Door/Controlled_Door.h"

// ALever
//------------------------------------------------------------------------------------------------------------
AHandwheel::AHandwheel(): Min_Rotation_Angle(0.0), Max_Rotation_Angle(360.0), Curr_Rotation_Angle(0.0)
{
	Curr_Rotation_Angle = Min_Rotation_Angle;
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
	double complete_percent;

	Super::Tick(delta_time);

    if (Is_Interacting)
	{
		Update_Rotation();

		check(Controlled_Door != 0);
		complete_percent = Curr_Rotation_Angle / Max_Rotation_Angle;
		Controlled_Door->Update_Pos_Offset(complete_percent);
	}
}
//------------------------------------------------------------------------------------------------------------
void AHandwheel::Update_Rotation()
{
	double projected_movement;
	double additive_rotation_angle;
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
	additive_rotation_angle = projected_movement * Sensivity;

	Curr_Rotation_Angle = FMath::Clamp(Curr_Rotation_Angle + additive_rotation_angle, Min_Rotation_Angle, Max_Rotation_Angle);

    new_rotation = GetActorRotation();
    new_rotation.Roll = Curr_Rotation_Angle;
    SetActorRotation(new_rotation);
}
//------------------------------------------------------------------------------------------------------------
