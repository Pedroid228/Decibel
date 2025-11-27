#include "BTTask_Get_Patrol_Point.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/AI_Patrol_Component/AI_Patrol_Component.h"
#include "BehaviorTree/BehaviorTreeTypes.h"

// UBTTask_Get_Patrol_Point
//------------------------------------------------------------------------------------------------------------
UBTTask_Get_Patrol_Point::UBTTask_Get_Patrol_Point(const FObjectInitializer &object_initializer): Super(object_initializer)
{
	NodeName = TEXT("Get Patrol Point");
}
//------------------------------------------------------------------------------------------------------------
EBTNodeResult::Type UBTTask_Get_Patrol_Point::ExecuteTask(UBehaviorTreeComponent &owner_comp, uint8 *node_memory)
{
	FVector new_patrol_point;
	AAIController *ai_controller = 0;
	APawn *npc = 0;
	UBlackboardComponent *blackboard = 0;
	UAI_Patrol_Component *patrol_comp = 0;

	ai_controller = owner_comp.GetAIOwner();
	check(ai_controller != 0);

	npc = ai_controller->GetPawn();
	check(npc != 0);

	blackboard = owner_comp.GetBlackboardComponent();
	check(blackboard!= 0);

	patrol_comp = npc->GetComponentByClass<UAI_Patrol_Component>();
	check(patrol_comp != 0);

	new_patrol_point = patrol_comp->Get_Target_Point();
	blackboard->SetValueAsVector(Curr_Patrol_Point.SelectedKeyName, new_patrol_point);

	return EBTNodeResult::Succeeded;
}
//------------------------------------------------------------------------------------------------------------
