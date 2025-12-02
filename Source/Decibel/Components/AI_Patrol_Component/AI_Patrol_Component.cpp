#include "AI_Patrol_Component.h"

#include "AI/Patrol_Points/Patrol_Points.h"
#include "Engine/TargetPoint.h"

// UAI_Patrol_Component
//------------------------------------------------------------------------------------------------------------
UAI_Patrol_Component::UAI_Patrol_Component(const FObjectInitializer &object_initializer): Super(object_initializer), Is_Enable_Patrolling(true), Is_Random_Patrol(false), Curr_Point_Index(0)
{
}
//------------------------------------------------------------------------------------------------------------
FVector UAI_Patrol_Component::Get_Target_Point()
{
	FVector new_target_point;
	if (Is_Random_Patrol)
		new_target_point = Get_Random_Target_Point();
	else
		new_target_point = Get_Next_Target_Point();

	return new_target_point;
}
//------------------------------------------------------------------------------------------------------------
void UAI_Patrol_Component::BeginPlay()
{
	Super::BeginPlay();

	if (Is_Enable_Patrolling)
		check(Patrol_Points != 0);
}
//------------------------------------------------------------------------------------------------------------
FVector UAI_Patrol_Component::Get_Next_Target_Point()
{
	int32 next_index;
	FVector next_point_pos;

	check(Patrol_Points != 0);

	next_index = (Curr_Point_Index + 1) % Patrol_Points->Num();
	next_point_pos = Patrol_Points->Get_Point_By_Index(next_index);
	Curr_Point_Index = next_index;

	return next_point_pos;
}
//------------------------------------------------------------------------------------------------------------
FVector UAI_Patrol_Component::Get_Random_Target_Point()
{
	int32 random_index = -1;
	FVector random_point_pos;

	check(Patrol_Points != 0);

	random_index = Curr_Point_Index;
	while (random_index == Curr_Point_Index)
		random_index = FMath::RandRange(0, Patrol_Points->Num() - 1);

	random_point_pos = Patrol_Points->Get_Point_By_Index(random_index);
	Curr_Point_Index = random_index;

	return random_point_pos;
}
//------------------------------------------------------------------------------------------------------------
