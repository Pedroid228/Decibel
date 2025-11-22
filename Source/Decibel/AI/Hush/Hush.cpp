#include "Hush.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Components/AI_Hearing_Component/AI_Hearing_Component.h"
#include "Components/StaticMeshComponent.h"

// AHush
//------------------------------------------------------------------------------------------------------------
AHush::AHush()
{
	Hearing_Component = CreateDefaultSubobject<UAI_Hearing_Component>(TEXT("Hearing_Comp"));
	check(Hearing_Component != 0);
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
