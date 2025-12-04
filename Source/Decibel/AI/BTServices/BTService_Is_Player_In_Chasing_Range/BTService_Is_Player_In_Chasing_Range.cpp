#include "BTService_Is_Player_In_Chasing_Range.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

// UBTService_Is_Player_In_Chasing_Range
//------------------------------------------------------------------------------------------------------------
UBTService_Is_Player_In_Chasing_Range::UBTService_Is_Player_In_Chasing_Range(): Chasing_Range(450.0)
{
	bNotifyTick = true;
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player In Range");
}
//------------------------------------------------------------------------------------------------------------
void UBTService_Is_Player_In_Chasing_Range::TickNode(UBehaviorTreeComponent &owner_comp, uint8 *node_memory, float delta_seconds)
{
	double distance;
	APawn *player_pawn = 0;
	APawn *npc_pawn = 0;
	UWorld *world;
	AAIController *ai_controller = 0;
	APlayerController *player_controller = 0;
	UBlackboardComponent *blackboard_comp = 0;

	Super::TickNode(owner_comp, node_memory, delta_seconds);

	world = GetWorld();
	check(world != 0);

	player_controller = world->GetFirstPlayerController();
	if (player_controller == 0)
		return;

	ai_controller = owner_comp.GetAIOwner();
	check(ai_controller != 0);

	blackboard_comp = owner_comp.GetBlackboardComponent();
	check(blackboard_comp != 0);

	player_pawn = player_controller->GetPawn();
	check(player_pawn != 0);

	npc_pawn = ai_controller->GetPawn();
	check(npc_pawn != 0);

	distance = npc_pawn->GetDistanceTo(player_pawn);

	if (distance < Chasing_Range)
	{
		blackboard_comp->SetValueAsBool(Is_Player_Chasing_In_Range.SelectedKeyName, true);
		blackboard_comp->SetValueAsObject(Player_Character_Key.SelectedKeyName, player_pawn);
	}
	else
	{
		blackboard_comp->SetValueAsBool(Is_Player_Chasing_In_Range.SelectedKeyName, false);
		blackboard_comp->SetValueAsObject(Player_Character_Key.SelectedKeyName, 0);
	}
}
//------------------------------------------------------------------------------------------------------------
