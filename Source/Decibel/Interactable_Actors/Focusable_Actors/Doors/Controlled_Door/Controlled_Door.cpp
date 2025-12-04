#include "Controlled_Door.h"

// AControlled_Door
//------------------------------------------------------------------------------------------------------------
AControlled_Door::AControlled_Door(): Min_Offset(0.0), Max_Offset(50.0)
{
	Root_Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Root_Scene_Comp"));
	check(Root_Scene != 0);
	SetRootComponent(Root_Scene);

	Left_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left_Mesh_Comp"));
	check(Left_Mesh != 0);
	Left_Mesh->SetupAttachment(Root_Scene);

	Right_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right_Mesh_Comp"));
	check(Right_Mesh != 0);
	Right_Mesh->SetupAttachment(Root_Scene);

	PrimaryActorTick.bCanEverTick = false;
}
//------------------------------------------------------------------------------------------------------------
void AControlled_Door::Update_Pos_Offset(double percent)
{
	double curr_offset;
	FVector new_left_relative_pos, new_right_relative_pos;

	curr_offset = FMath::Lerp(Min_Offset, Max_Offset, percent);

	new_left_relative_pos = FVector(0.0, -curr_offset, 0.0);
	Left_Mesh->SetRelativeLocation(new_left_relative_pos);

	new_right_relative_pos = FVector(0.0, curr_offset, 0.0);
	Right_Mesh->SetRelativeLocation(new_right_relative_pos);
}
//------------------------------------------------------------------------------------------------------------
void AControlled_Door::BeginPlay()
{
	Super::BeginPlay();

	Update_Pos_Offset(0.0);
}
//------------------------------------------------------------------------------------------------------------
