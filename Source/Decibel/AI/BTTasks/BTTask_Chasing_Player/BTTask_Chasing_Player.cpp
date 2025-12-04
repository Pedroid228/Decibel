#include "BTTask_Chasing_Player.h"

#include "AI/Hush/Hush.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

// UBTTask_Chasing_Player
//------------------------------------------------------------------------------------------------------------
UBTTask_Chasing_Player::UBTTask_Chasing_Player(FObjectInitializer const &object_initializer): Acceptance_Radius(20.0f), Lose_Distance(400.0)
{
	NodeName = "Chasing Seen Player";
	bNotifyTick = true;
}
//------------------------------------------------------------------------------------------------------------
EBTNodeResult::Type UBTTask_Chasing_Player::ExecuteTask(UBehaviorTreeComponent &owner_comp, uint8 *node_memory)
{
	ACharacter *target_character = 0;

	AI_Controller = owner_comp.GetAIOwner();
	check(AI_Controller != 0);

	Blackboard_Comp = owner_comp.GetBlackboardComponent();
	check(Blackboard_Comp != 0);

	target_character = Get_Target_Character();
	AI_Controller->MoveToActor(target_character, Acceptance_Radius);

	return EBTNodeResult::InProgress;
}
//------------------------------------------------------------------------------------------------------------
void UBTTask_Chasing_Player::TickTask(UBehaviorTreeComponent &owner_comp, uint8 *node_memory, float delta_seconds)
{
	bool is_in_chasing_range;
	FVector npc_pos;
	APawn *npc_pawn = 0;
	ACharacter *target_character = 0;

	check(Blackboard_Comp != 0);
	check(AI_Controller != 0);

	is_in_chasing_range = Blackboard_Comp->GetValueAsBool(Is_Player_In_Chasing_Range_Key.SelectedKeyName);
	if (!is_in_chasing_range)
	{
		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
		return;
	}

	npc_pawn = AI_Controller->GetPawn();
	check(npc_pawn != 0);
	npc_pos = npc_pawn->GetActorLocation();

	target_character = Get_Target_Character();

	AI_Controller->MoveToActor(target_character, Acceptance_Radius);
}
//------------------------------------------------------------------------------------------------------------
ACharacter *UBTTask_Chasing_Player::Get_Target_Character()
{
	UObject *player_obj = 0;
	ACharacter *target_character;

	check(Blackboard_Comp != 0);
	check(AI_Controller != 0);

	player_obj = Blackboard_Comp->GetValueAsObject(Player_Character_Key.SelectedKeyName);
	check(player_obj != 0);

	target_character = Cast<ACharacter>(player_obj);
	check(target_character != 0);

	return target_character;
}
//------------------------------------------------------------------------------------------------------------
