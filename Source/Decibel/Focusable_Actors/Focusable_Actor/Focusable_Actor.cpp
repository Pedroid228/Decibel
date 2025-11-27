#include "Focusable_Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// AFocusable_Actor
//------------------------------------------------------------------------------------------------------------
AFocusable_Actor::AFocusable_Actor(): Is_Interacting(false), Sensivity(1.0), Last_Mouse_Position(FVector2D::ZeroVector), Mouse_Move_Vector(FVector2D::ZeroVector)
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
void AFocusable_Actor::Tick(float delta_time)
{
	UWorld *world = 0;
	APlayerController *player_controller = 0;
	FVector2D current_mouse_pos;

	world = GetWorld();
	check(world != 0);

	player_controller = world->GetFirstPlayerController();
	check(player_controller != 0);

    player_controller->GetMousePosition(current_mouse_pos.X, current_mouse_pos.Y);
    Mouse_Move_Vector = current_mouse_pos - Last_Mouse_Position;

	Last_Mouse_Position = current_mouse_pos;
}
//------------------------------------------------------------------------------------------------------------
void AFocusable_Actor::On_Trace_Hit_Implementation(AActor *interacting_actor, UPrimitiveComponent *hit_component)
{
}
//------------------------------------------------------------------------------------------------------------
void AFocusable_Actor::On_Trace_Leave_Implementation()
{
}
//------------------------------------------------------------------------------------------------------------
void AFocusable_Actor::On_Interact_Begin_Implementation(AActor *interacting_actor)
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
void AFocusable_Actor::On_Interact_End_Implementation()
{
	Is_Interacting = false;
	SetActorTickEnabled(false);
}
//------------------------------------------------------------------------------------------------------------
FVector AFocusable_Actor::Get_Grip_Socket_Pos()
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
