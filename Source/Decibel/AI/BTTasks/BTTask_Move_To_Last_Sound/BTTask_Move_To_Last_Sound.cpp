#include "BTTask_Move_To_Last_Sound.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Data/Sound_Stimulus/Sound_Stimulus.h"

// UBTTask_Move_To_Last_Sound
//------------------------------------------------------------------------------------------------------------
UBTTask_Move_To_Last_Sound::UBTTask_Move_To_Last_Sound(const FObjectInitializer &object_initializer): Super(object_initializer), Is_Waiting(false), Wait_Time(2.0), Acceptance_Radius(10.0)
{
	NodeName = TEXT("Move To Last Sound");
	bNotifyTick = true;
}
//------------------------------------------------------------------------------------------------------------
EBTNodeResult::Type UBTTask_Move_To_Last_Sound::ExecuteTask(UBehaviorTreeComponent &owner_comp, uint8 *node_memory)
{
	FVector start_target_pos;

	AI_Controller = owner_comp.GetAIOwner();
	check(AI_Controller != 0);

	NPC = AI_Controller->GetPawn();
	check(NPC != 0);

	Blackboard = owner_comp.GetBlackboardComponent();
	check(Blackboard != 0);

	start_target_pos = Blackboard->GetValueAsVector(Curr_Sound_Pos_Key.SelectedKeyName);
	Start_Move_To_Target(start_target_pos);

	return EBTNodeResult::InProgress;
}
//------------------------------------------------------------------------------------------------------------
void UBTTask_Move_To_Last_Sound::TickTask(UBehaviorTreeComponent &owner_comp, uint8 *node_memory, float delta_seconds)
{
	bool is_moving;
	bool has_high_priority_sound;
	ESound_Type last_sound_type;
	double distance_to_target;
	FVector npc_pos;
	FVector new_target_pos;

	check(Blackboard != 0);
	new_target_pos = Blackboard->GetValueAsVector(Curr_Sound_Pos_Key.SelectedKeyName);
	last_sound_type = (ESound_Type)Blackboard->GetValueAsEnum(Curr_Sound_Type_Key.SelectedKeyName);
	has_high_priority_sound = Blackboard->GetValueAsBool(Has_High_Priority_Sound_Key.SelectedKeyName);

	if (Is_Waiting)
		Waiting(owner_comp, delta_seconds);

	if (has_high_priority_sound)
	{
		if (last_sound_type == ESound_Type::High_Priority && new_target_pos != Curr_Target_Pos)  // Only high priority sound can replace other high priority sound
			Start_Move_To_Target(new_target_pos);
	}
	else
	{  // No high priority, reaction on all sound

		if (new_target_pos != Curr_Target_Pos)
			Start_Move_To_Target(new_target_pos);
	}

	check(NPC != 0);
	npc_pos = NPC->GetActorLocation();
	distance_to_target = FVector::Distance(npc_pos, Curr_Target_Pos);

	is_moving = AI_Controller->IsFollowingAPath();

	if (!is_moving)
	{  // Start Waiting

		Is_Waiting = true;
	}
	else
	{
		Curr_Wait_Time = 0.0f;
		Is_Waiting = false;
	}
}
//------------------------------------------------------------------------------------------------------------
void UBTTask_Move_To_Last_Sound::Start_Move_To_Target(const FVector &new_target_pos)
{
	check(AI_Controller != 0);
	AI_Controller->MoveToLocation(new_target_pos, Acceptance_Radius);
	Curr_Target_Pos = new_target_pos;
}
//------------------------------------------------------------------------------------------------------------
void UBTTask_Move_To_Last_Sound::Waiting(UBehaviorTreeComponent &owner_comp, float delta_seconds)
{
	Curr_Wait_Time += delta_seconds;

	if (Curr_Wait_Time >= Wait_Time)
		Complete_Task(owner_comp);
}
//------------------------------------------------------------------------------------------------------------
void UBTTask_Move_To_Last_Sound::Complete_Task(UBehaviorTreeComponent &owner_comp)
{
	Blackboard->SetValueAsVector("Curr_Heard_Sound_Pos", FVector::ZeroVector);
	Blackboard->SetValueAsEnum("Curr_Heard_Sound_Type", (uint8)ESound_Type::None);
	Blackboard->SetValueAsBool("Has_Heard_Sound", false);
	Blackboard->SetValueAsBool("Has_High_Priority_Sound", false);
	Curr_Target_Pos = FVector::ZeroVector;

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
}
//------------------------------------------------------------------------------------------------------------
