#include "Controlled_Door.h"

// AControlled_Door
//------------------------------------------------------------------------------------------------------------
AControlled_Door::AControlled_Door(): Min_Offset(0.0), Max_Offset(50.0)
{
	Root_Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Root_Scene_Comp"));
	check(Root_Scene != 0);
	SetRootComponent(Root_Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Comp"));
	check(Mesh != 0);
	Mesh->SetupAttachment(Root_Scene);

    PrimaryActorTick.bCanEverTick = false;
}
//------------------------------------------------------------------------------------------------------------
void AControlled_Door::Update_Pos_Offset(double percent)
{
	double curr_offset;
	FVector new_relative_pos;

	curr_offset = FMath::Lerp(Min_Offset, Max_Offset, percent);

    new_relative_pos = FVector(-curr_offset, 0.0, 0.0);
    Mesh->SetRelativeLocation(new_relative_pos);
}
//------------------------------------------------------------------------------------------------------------
void AControlled_Door::BeginPlay()
{
	Super::BeginPlay();

	Update_Pos_Offset(0.0);
}
//------------------------------------------------------------------------------------------------------------
