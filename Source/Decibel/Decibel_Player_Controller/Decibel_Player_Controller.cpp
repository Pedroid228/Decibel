#include "Decibel_Player_Controller.h"
#include "Subsystems/Save_Manager_Subsystem/Save_Manager_Subsystem.h"

// ADecibel_Player_Controller
//------------------------------------------------------------------------------------------------------------
ADecibel_Player_Controller::ADecibel_Player_Controller(const FObjectInitializer &object_initializer)
{
}
//------------------------------------------------------------------------------------------------------------
void ADecibel_Player_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();
    InputComponent->BindAction("Load_Save", IE_Pressed, this, &ADecibel_Player_Controller::Load_Save);  // !!! Debug
    InputComponent->BindAction("Save_Game", IE_Pressed, this, &ADecibel_Player_Controller::Save_Game);  // !!! Debug
}
//------------------------------------------------------------------------------------------------------------
void ADecibel_Player_Controller::Load_Save()
{
    UGameInstance *game_inst = 0;
    USave_Manager_Subsystem *save_manager_subsys = 0;

    game_inst = GetGameInstance();
    check(game_inst != 0);

    save_manager_subsys = game_inst->GetSubsystem<USave_Manager_Subsystem>();
    check(save_manager_subsys != 0);

    save_manager_subsys->Load_Save(0);
}
//------------------------------------------------------------------------------------------------------------
void ADecibel_Player_Controller::Save_Game()
{
    UGameInstance *game_inst = 0;
    USave_Manager_Subsystem *save_manager_subsys = 0;

    game_inst = GetGameInstance();
    check(game_inst != 0);

    save_manager_subsys = game_inst->GetSubsystem<USave_Manager_Subsystem>();
    check(save_manager_subsys != 0);

    save_manager_subsys->Save_Game(0);
}
//------------------------------------------------------------------------------------------------------------
