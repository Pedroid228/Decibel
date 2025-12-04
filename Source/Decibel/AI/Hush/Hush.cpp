#include "Hush.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Components/AI_Hearing_Component/AI_Hearing_Component.h"
#include "Components/AI_Patrol_Component/AI_Patrol_Component.h"
#include "Components/StaticMeshComponent.h"

// AHush
//------------------------------------------------------------------------------------------------------------
AHush::AHush()
{
	Tags.Add(TEXT("Hush_Tag"));

	Hearing_Component = CreateDefaultSubobject<UAI_Hearing_Component>(TEXT("Hearing_Comp"));
	check(Hearing_Component != 0);

	Patrol_Component = CreateDefaultSubobject<UAI_Patrol_Component>(TEXT("Patrol_Comp"));
	check(Patrol_Component != 0);
}
//------------------------------------------------------------------------------------------------------------
void AHush::On_Save_Implementation(FActor_Save_Data &save_data)
{
	save_data.Actor_Class_Name = GetClass()->GetName();
	save_data.Transform = GetActorTransform();
}
//------------------------------------------------------------------------------------------------------------
void AHush::On_Load_Implementation(const FActor_Save_Data &save_data)
{
	SetActorTransform(save_data.Transform);
}
//------------------------------------------------------------------------------------------------------------
UBehaviorTree *AHush::Get_BT()
{
	return BT;
}
//------------------------------------------------------------------------------------------------------------
void AHush::BeginPlay()
{
	Super::BeginPlay();

	check(BT != 0);
}
//------------------------------------------------------------------------------------------------------------
