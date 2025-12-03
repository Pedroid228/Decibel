#include "Hand_Door.h"
#include "Components/WidgetComponent.h"

// AHand_Door
//------------------------------------------------------------------------------------------------------------
AHand_Door::AHand_Door(): Min_Offset(0.0), Max_Offset(0.1), Curr_Offset(0.0)
{
	Curr_Offset = Min_Offset;
}
//------------------------------------------------------------------------------------------------------------
void AHand_Door::On_Save_Implementation(FActor_Save_Data &save_data)
{
	Super::On_Save_Implementation(save_data);

	save_data.Hand_Door_Offset = Curr_Offset;
}
//------------------------------------------------------------------------------------------------------------
void AHand_Door::On_Load_Implementation(const FActor_Save_Data &save_data)
{
	Super::On_Load_Implementation(save_data);

	Curr_Offset = save_data.Hand_Door_Offset;
	Update_Pos();
}
//------------------------------------------------------------------------------------------------------------
void AHand_Door::Tick(float delta_time)
{
	Super::Tick(delta_time);

	if (Is_Interacting)
		Update_Offset();
}
//------------------------------------------------------------------------------------------------------------
void AHand_Door::On_Trace_Hit_Implementation(AActor *interacting_actor, UPrimitiveComponent *hit_component)
{
	FVector relative_pos;
	FRotator rotation;
	FName socket_name;

	Super::On_Trace_Hit_Implementation(interacting_actor, hit_component);

	if (Is_Player_In_Front() )
	{
		rotation = FRotator(0.0, 90.0, 0.0);
		socket_name = TEXT("Front_Grip_Socket");
	}
	else
	{
		rotation = FRotator(0.0, 270.0, 0.0);
		socket_name = TEXT("Back_Grip_Socket");
	}

	check(Mesh->DoesSocketExist(socket_name));
	check(Interaction_Tip_Widget_Component != 0);

	Interaction_Tip_Widget_Component->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, socket_name);

	relative_pos = FVector(-10.0, 0.0, 0.0);
	Interaction_Tip_Widget_Component->SetRelativeLocation(relative_pos);
	Interaction_Tip_Widget_Component->SetRelativeRotation(rotation);
}
//------------------------------------------------------------------------------------------------------------
FVector AHand_Door::Get_Grip_Socket_Pos()
{
	FVector grip_pos;

	if (Is_Player_In_Front() )
		grip_pos = Get_Socket_Pos_By_Name(TEXT("Front_Grip_Socket"));
	else
		grip_pos = Get_Socket_Pos_By_Name(TEXT("Back_Grip_Socket"));

	return grip_pos;
}
//-----------------------------------------------------------------------------------------------------------
void AHand_Door::Update_Offset()
{
	double horizontal_movement;	

	if (Is_Player_In_Front())
		horizontal_movement = -Mouse_Move_Vector.X * Sensivity;
	else
		horizontal_movement = Mouse_Move_Vector.X * Sensivity;

	Curr_Offset = FMath::Clamp(Curr_Offset + horizontal_movement, Min_Offset, Max_Offset);

	Update_Pos();
}
//------------------------------------------------------------------------------------------------------------
void AHand_Door::Update_Pos()
{
	FVector move_dir;
	FVector new_pos;

	move_dir = FVector(-1.0, 0.0, 0.0);
	new_pos = move_dir * Curr_Offset;
	Mesh->SetRelativeLocation(new_pos);
}
//------------------------------------------------------------------------------------------------------------
bool AHand_Door::Is_Player_In_Front()
{
	double dot_product;
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

	dot_product = FVector::DotProduct(GetActorRightVector(), from_door_to_player);

	if (dot_product >= 0.0)
		return true;
	else
		return false;
}
//------------------------------------------------------------------------------------------------------------
FVector AHand_Door::Get_Socket_Pos_By_Name(const FName &socket_name)
{
	FVector socket_pos;
	check(Mesh != 0);

	if (Mesh->DoesSocketExist(socket_name))
	{
		socket_pos = Mesh->GetSocketLocation(socket_name);
		return socket_pos;
	}
	else
		return FVector::ZeroVector;
}
//------------------------------------------------------------------------------------------------------------
