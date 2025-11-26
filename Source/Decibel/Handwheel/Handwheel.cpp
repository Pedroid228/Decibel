#include "Handwheel.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// AHandwheel
//------------------------------------------------------------------------------------------------------------
AHandwheel::AHandwheel(): Is_Interacting(false), Sensivity(1.0)
{
	Root_Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Root_Scene_Comp"));
	check(Root_Scene != 0);
	SetRootComponent(Root_Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Comp"));
	check(Mesh != 0);
	Mesh->SetupAttachment(Root_Scene);

    PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	SetActorTickEnabled(false);
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
    FVector2D current_mouse_pos;
    FVector2D mouse_move_vector;
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

    player_controller->GetMousePosition(current_mouse_pos.X, current_mouse_pos.Y);
    mouse_move_vector = current_mouse_pos - Last_Mouse_Position;

    wheel_center_pos = GetActorLocation();
    grip_pos = Get_Grip_Socket_Pos();

	rotation_axis = GetActorForwardVector();
    from_center_to_grip = (grip_pos - wheel_center_pos).GetSafeNormal();
	tangent = FVector::CrossProduct(rotation_axis, from_center_to_grip).GetSafeNormal();

	camera_forward = player_controller->PlayerCameraManager->GetCameraRotation().Vector();
	camera_right = FVector::CrossProduct(FVector::UpVector, camera_forward).GetSafeNormal();
	camera_up = FVector::CrossProduct(camera_forward, camera_right).GetSafeNormal();

	world_mouse_move = -mouse_move_vector.X * camera_right + mouse_move_vector.Y * camera_up;

	projected_movement = FVector::DotProduct(world_mouse_move, tangent);
	rotation_angle = projected_movement * Sensivity;

    new_rotation = GetActorRotation();
    new_rotation.Roll += rotation_angle;
    SetActorRotation(new_rotation);

    Last_Mouse_Position = current_mouse_pos;
}
//------------------------------------------------------------------------------------------------------------
void AHandwheel::On_Trace_Hit_Implementation(AActor *interacting_actor, UPrimitiveComponent *hit_component)
{
}
//------------------------------------------------------------------------------------------------------------
void AHandwheel::On_Trace_Leave_Implementation()
{
}
//------------------------------------------------------------------------------------------------------------
void AHandwheel::On_Interact_Begin_Implementation(AActor *interacting_actor)
{
	FVector grip_pos;
	FVector player_view_pos;
	FVector to_target;
	FRotator player_view_rotation;
	FRotator target_rotation;
	UWorld *world = 0;
	APlayerController *player_controller;

	Is_Interacting = true;

	SetActorTickEnabled(true);

	world = GetWorld();
	check(world != 0);

	player_controller = world->GetFirstPlayerController();
	check(player_controller != 0);

	grip_pos = Get_Grip_Socket_Pos();
	
	player_controller->GetPlayerViewPoint(player_view_pos, player_view_rotation);

	to_target = grip_pos - player_view_pos;
    target_rotation = to_target.Rotation();

    player_controller->SetControlRotation(target_rotation);
}
//------------------------------------------------------------------------------------------------------------
void AHandwheel::On_Interact_End_Implementation()
{
	Is_Interacting = false;
	SetActorTickEnabled(false);
}
//------------------------------------------------------------------------------------------------------------
FVector AHandwheel::Get_Grip_Socket_Pos()
{
    FVector grip_pos;
    check(Mesh != 0);
	if (Mesh->DoesSocketExist(TEXT("Grip_Socket")))
    {
        grip_pos = Mesh->GetSocketLocation(TEXT("Grip_Socket") );
        return grip_pos;
    }
	else
		return FVector::ZeroVector;
}
//------------------------------------------------------------------------------------------------------------
