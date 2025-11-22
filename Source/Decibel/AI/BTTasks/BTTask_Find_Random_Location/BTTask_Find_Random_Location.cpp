#include "BTTask_Find_Random_Location.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

// Hush_AIController
//------------------------------------------------------------------------------------------------------------
UBTTask_Find_Random_Location::UBTTask_Find_Random_Location(const FObjectInitializer &object_initializer): Super(object_initializer), Search_Radius(1500.0f)
{
	NodeName = TEXT("Find Random Location in Nav Mesh");
}
//------------------------------------------------------------------------------------------------------------
EBTNodeResult::Type UBTTask_Find_Random_Location::ExecuteTask(UBehaviorTreeComponent &owner_comp, uint8 *node_memory)
{
	FVector origin;
	FNavLocation nav_loc;
	AAIController *ai_conroller = 0;
	APawn *npc = 0;
	UWorld *world = 0;
	UNavigationSystemV1 *nav_sys = 0;
	UBlackboardComponent *blackboard_comp = 0;

	ai_conroller = owner_comp.GetAIOwner();
	check(ai_conroller != 0);

	npc = ai_conroller->GetPawn();
	check(npc != 0);

	origin = npc->GetActorLocation();

	world = GetWorld();
	check(world != 0);

	nav_sys = UNavigationSystemV1::GetCurrent(world);
	check(nav_sys != 0);

	if (nav_sys->GetRandomPointInNavigableRadius(origin, Search_Radius, nav_loc))
	{
		blackboard_comp = owner_comp.GetBlackboardComponent();
		check(blackboard_comp);
		blackboard_comp->SetValueAsVector(GetSelectedBlackboardKey(), nav_loc.Location);
	}

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
//------------------------------------------------------------------------------------------------------------
