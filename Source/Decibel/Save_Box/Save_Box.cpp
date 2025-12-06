#include "Save_Box.h"
#include "Components/BoxComponent.h"
#include "Astronaut/Astronaut.h"
#include "Decibel_Game_Instance/Decibel_Game_Instance.h"

// ASave_Box
//------------------------------------------------------------------------------------------------------------
ASave_Box::ASave_Box()
{
	Save_Trigger_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Save_Trigger_Component"));
	check(Save_Trigger_Collision != 0);
	Save_Trigger_Collision->SetupAttachment(GetRootComponent());
	Save_Trigger_Collision->SetGenerateOverlapEvents(true);
	Save_Trigger_Collision->OnComponentBeginOverlap.AddDynamic(this, &ASave_Box::Save_Game);
}
//------------------------------------------------------------------------------------------------------------
void ASave_Box::On_Save_Implementation(FActor_Save_Data &save_data)
{
	save_data.Actor_Class_Name = GetClass()->GetName();
	save_data.Is_Save_Box_Active = Is_Active;
}
//------------------------------------------------------------------------------------------------------------
void ASave_Box::On_Load_Implementation(const FActor_Save_Data &save_data)
{
	Save_Trigger_Collision->SetGenerateOverlapEvents(save_data.Is_Save_Box_Active);
}
//------------------------------------------------------------------------------------------------------------
void ASave_Box::Save_Game(UPrimitiveComponent *overlapped_component, AActor *other_actor, UPrimitiveComponent *other_comp, int32 other_body_index, bool from_sweep, const FHitResult &sweep_result)
{
	AAstronaut *astronaut = 0;
	UDecibel_Game_Instance *decibel_game_inst = 0;

	astronaut = Cast<AAstronaut>(other_actor);
	if (astronaut != 0)
	{
		decibel_game_inst = GetGameInstance<UDecibel_Game_Instance>();
		check(decibel_game_inst != 0);

		decibel_game_inst->Save_Curr_Game();

		Is_Active = false;
		Save_Trigger_Collision->SetGenerateOverlapEvents(false);
	}
}
//------------------------------------------------------------------------------------------------------------

