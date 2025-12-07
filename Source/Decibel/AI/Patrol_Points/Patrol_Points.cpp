#include "Patrol_Points.h"

// APatrol_Points
//------------------------------------------------------------------------------------------------------------
APatrol_Points::APatrol_Points()
{
}
//------------------------------------------------------------------------------------------------------------
int32 APatrol_Points::Num()
{
	return Points.Num();
}
//------------------------------------------------------------------------------------------------------------
FVector APatrol_Points::Get_Point_By_Index(int32 index)
{
	FVector local_point, world_point;
	FTransform actor_transform;

	check(Points.IsValidIndex(index))
	local_point= Points[index];

	actor_transform = GetActorTransform();
	world_point = actor_transform.TransformPosition(local_point);

	return world_point;
}
//------------------------------------------------------------------------------------------------------------
