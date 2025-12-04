#include "AI_Hearing_Component.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Subsystems/Sounds_Manager_Subsystem/Sounds_Manager_Subsystem.h"

// UAI_Hearing_Component
//------------------------------------------------------------------------------------------------------------
UAI_Hearing_Component::UAI_Hearing_Component(const FObjectInitializer &object_initializer): Super(object_initializer)
{
	PrimaryComponentTick.bCanEverTick = true;
}
//------------------------------------------------------------------------------------------------------------
void UAI_Hearing_Component::On_Save_Implementation(FActor_Component_Save_Data &save_data)
{
	save_data.Component_Class_Name = GetClass()->GetName();
	save_data.Hearing_Component_Save_Data = Hearing_Component_Save_Data;
}
//------------------------------------------------------------------------------------------------------------
void UAI_Hearing_Component::On_Load_Implementation(const FActor_Component_Save_Data &save_data)
{
	Hearing_Component_Save_Data = save_data.Hearing_Component_Save_Data;
	Update_Blackboard();
}
//------------------------------------------------------------------------------------------------------------
void UAI_Hearing_Component::BeginPlay()
{
	UGameInstance *game_instance = 0;
	USounds_Manager_Subsystem *sounds_manager_subsystem = 0;

	Super::BeginPlay();

	Owner = GetOwner();
	check(Owner != 0);

	AI_Controller = Owner->GetInstigatorController<AAIController>();
	check(AI_Controller != 0);

	// Add delegate on sound emit
	game_instance = Owner->GetGameInstance();
	check(game_instance != 0);

	sounds_manager_subsystem = game_instance->GetSubsystem<USounds_Manager_Subsystem>();
	check(sounds_manager_subsystem) sounds_manager_subsystem->On_Sound_Stimulus_Emit.AddDynamic(this, &UAI_Hearing_Component::Process_Sound_Stimulus);
}
//------------------------------------------------------------------------------------------------------------
void UAI_Hearing_Component::Process_Sound_Stimulus(const FSound_Stimulus &sound)
{
	FVector npc_pos;
	UBlackboardComponent *blackboard = 0;
	double *sound_range;

	check(sound.Type != ESound_Type::None);

	check(Owner != 0);
	npc_pos = Owner->GetActorLocation();
	sound_range = sound.Sounds_Range.Find(sound.Type);
	check(sound_range != 0);
	if (FVector::Distance(npc_pos, sound.Pos) < *sound_range)
	{
		check(AI_Controller != 0);
		blackboard = AI_Controller->GetBlackboardComponent();
		check(blackboard != 0);

		Hearing_Component_Save_Data.Has_Heard_Sound = blackboard->GetValueAsBool("Has_Heard_Sound");

		if (!Hearing_Component_Save_Data.Has_Heard_Sound)
			AI_Controller->StopMovement();

		Hearing_Component_Save_Data.Curr_Heard_Sound_Pos = sound.Pos;
		Hearing_Component_Save_Data.Curr_Heard_Sound_Type = sound.Type;
		Hearing_Component_Save_Data.Has_Heard_Sound = true;

		Update_Blackboard();

		if (Hearing_Component_Save_Data.Curr_Heard_Sound_Type == ESound_Type::High_Priority)
			Hearing_Component_Save_Data.Has_High_Priority_Sound = true;
	}
}
//------------------------------------------------------------------------------------------------------------
void UAI_Hearing_Component::Update_Blackboard()
{
	UBlackboardComponent *blackboard = 0;

	check(AI_Controller != 0);
	blackboard = AI_Controller->GetBlackboardComponent();
	check(blackboard != 0);

	blackboard->SetValueAsVector("Curr_Heard_Sound_Pos", Hearing_Component_Save_Data.Curr_Heard_Sound_Pos);
	blackboard->SetValueAsEnum("Curr_Heard_Sound_Type", (uint8)Hearing_Component_Save_Data.Curr_Heard_Sound_Type);
	blackboard->SetValueAsBool("Has_Heard_Sound", Hearing_Component_Save_Data.Has_Heard_Sound);
	blackboard->SetValueAsBool("Has_High_Priority_Sound", Hearing_Component_Save_Data.Has_High_Priority_Sound);
}
//------------------------------------------------------------------------------------------------------------
