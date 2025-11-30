#include "Decibel_Game_Instance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Subsystems/Save_Manager_Subsystem/Save_Manager_Subsystem.h"

// UDecibel_Game_Instance
//------------------------------------------------------------------------------------------------------------
UDecibel_Game_Instance::UDecibel_Game_Instance()
{
}
//------------------------------------------------------------------------------------------------------------
void UDecibel_Game_Instance::Init()
{
	Super::Init();

	Save_Manager = GetSubsystem<USave_Manager_Subsystem>();
	check(Save_Manager != 0);

	Main_Menu();
}
//------------------------------------------------------------------------------------------------------------
void UDecibel_Game_Instance::Main_Menu()
{
	Open_Level(TEXT("Menu_Map"));
}
//------------------------------------------------------------------------------------------------------------
void UDecibel_Game_Instance::New_Game()
{
	Open_Level(TEXT("Test_Map"));

	FCoreUObjectDelegates::PostLoadMapWithWorld.AddWeakLambda(this, [this](UWorld *world) { 
		check(Save_Manager != 0);
		Save_Manager->Save_Game();
	});	
}
//------------------------------------------------------------------------------------------------------------
void UDecibel_Game_Instance::Load_Game()
{
	check(Save_Manager != 0);
	Save_Manager->Load_Save();
}
//------------------------------------------------------------------------------------------------------------
void UDecibel_Game_Instance::Quit_Game()
{
	UWorld *world = 0;
	APlayerController *player_controller = 0;

	world = GetWorld();
	check(world != 0);

	player_controller = world->GetFirstPlayerController();
	check(player_controller != 0);

	UKismetSystemLibrary::QuitGame(world, player_controller, EQuitPreference::Quit, false);
}
//------------------------------------------------------------------------------------------------------------
void UDecibel_Game_Instance::Open_Level(const FName &map_name)
{
	UWorld *world = 0;

	world = GetWorld();
	check(world != 0);
	UGameplayStatics::OpenLevel(world, map_name);
}
//------------------------------------------------------------------------------------------------------------
