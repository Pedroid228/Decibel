#include "Hand_Door.h"

// AHand_Door
//------------------------------------------------------------------------------------------------------------
AHand_Door::AHand_Door(): Min_Offset(0.0), Max_Offset(0.1), Curr_Offset(0.0)
{
	Curr_Offset = Min_Offset;
}
//------------------------------------------------------------------------------------------------------------
void AHand_Door::Tick(float delta_time)
{
	Super::Tick(delta_time);

    if (Is_Interacting)
		Update_Position();
}
//------------------------------------------------------------------------------------------------------------
void AHand_Door::Update_Position()
{
    double horizontal_movement;
    FVector move_dir;
    FVector new_pos;
    FVector door_pos;
    FVector player_pos;
    FVector from_door_to_player;
    UWorld *world = 0;
	APlayerController *player_controller;
    APawn *player_pawn;

	world = GetWorld();
	check(world != 0);

	player_controller = world->GetFirstPlayerController();
	check(player_controller != 0);

    player_pawn = player_controller->GetPawn();
    check(player_pawn != 0);

    player_pos = player_pawn->GetActorLocation();
    door_pos = GetActorLocation();

    from_door_to_player = (player_pos - door_pos).GetSafeNormal();

    move_dir = FVector(-1.0, 0.0, 0.0);

    if (FVector::DotProduct(GetActorRightVector(), from_door_to_player) < 0)
        horizontal_movement = Mouse_Move_Vector.X * Sensivity;
    else
        horizontal_movement = -Mouse_Move_Vector.X * Sensivity;

    Curr_Offset = FMath::Clamp(Curr_Offset + horizontal_movement, Min_Offset, Max_Offset);

    new_pos = move_dir * Curr_Offset;
    Mesh->SetRelativeLocation(new_pos);
}
//------------------------------------------------------------------------------------------------------------
