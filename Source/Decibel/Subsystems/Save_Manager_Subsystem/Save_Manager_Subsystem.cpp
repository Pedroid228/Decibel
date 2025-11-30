#include "Save_Manager_Subsystem.h"
#include "Json_Utils/Json_Utils.h"
#include "Interfaces/Saveable_Actor_Interface/Saveable_Actor_Interface.h"
#include "Interfaces/Saveable_Actor_Component_Interface/Saveable_Actor_Component_Interface.h"
#include "Kismet/GameplayStatics.h"
#include "Data/Save_Data/Decibel_Save_Data/Decibel_Save_Data.h"

// USave_Manager_Subsystem
//------------------------------------------------------------------------------------------------------------
FString USave_Manager_Subsystem::Save_Dir = "Game_Saves";
//------------------------------------------------------------------------------------------------------------
USave_Manager_Subsystem::USave_Manager_Subsystem()
{
}
//------------------------------------------------------------------------------------------------------------
void USave_Manager_Subsystem::Save_Game()
{
	FString save_path;
	FDecibel_Save_Data decibel_save_data;
	UStruct *save_data_class = 0;
	UWorld *world = 0;
	TArray<AActor*> world_actors;

	world = GetWorld();
	check(world != 0);

	decibel_save_data.Map_Name = FName(world->GetMapName());
	UGameplayStatics::GetAllActorsOfClass(world, AActor::StaticClass(), world_actors);

	for (AActor *world_actor : world_actors)
		Try_Save_Actor(world_actor, decibel_save_data);

	save_path = Get_Save_File_Path();
	AJson_Utils::Write_Save_Data(save_path, decibel_save_data);
}
//------------------------------------------------------------------------------------------------------------
void USave_Manager_Subsystem::Load_Save()
{
	FString save_path;
    FDecibel_Save_Data decibel_save_data;
	UWorld *world = 0;

	save_path = Get_Last_Save_Path();
    if (!AJson_Utils::Read_Save_Data(save_path, decibel_save_data))
        return;

	world = GetWorld();
	check(world != 0);
	UGameplayStatics::OpenLevel(world, decibel_save_data.Map_Name);

	FCoreUObjectDelegates::PostLoadMapWithWorld.AddWeakLambda(this, [this, decibel_save_data](UWorld *world) {
		check(world != 0);
		Load_Actors_Save(decibel_save_data);
		FCoreUObjectDelegates::PostLoadMapWithWorld.RemoveAll(this);
	});
}
//------------------------------------------------------------------------------------------------------------
bool USave_Manager_Subsystem::Try_Save_Actor(AActor *actor, FDecibel_Save_Data &decibel_save_data)
{
	FActor_Save_Data actor_save_data;

	check(actor != 0);

	if (actor->Implements<USaveable_Actor_Interface>())
	{
		ISaveable_Actor_Interface::Execute_On_Save(actor, actor_save_data);
		Save_Actor_Components(actor, actor_save_data);
		decibel_save_data.Actors_Save_Data.Add(actor_save_data);
		return true;
	}

	return false;
}
//------------------------------------------------------------------------------------------------------------
void USave_Manager_Subsystem::Save_Actor_Components(AActor *actor, FActor_Save_Data &actor_save_data)
{
	FActor_Component_Save_Data actor_component_save_data;
	TSet<UActorComponent*> actor_components;

	actor_components = actor->GetComponents();

	for (UActorComponent *actor_component : actor_components)
	{
		if (actor_component->Implements<USaveable_Actor_Component_Interface>())
		{
			ISaveable_Actor_Component_Interface::Execute_On_Save(actor_component, actor_component_save_data);
			actor_save_data.Components_Save_Data.Add(actor_component_save_data);
		}
	}
}
//------------------------------------------------------------------------------------------------------------
void USave_Manager_Subsystem::Load_Actors_Save(const FDecibel_Save_Data &decibel_save_data)
{
	FString actor_path_name;
	UWorld *world = 0;
	TArray<AActor*> world_actors;
	TMap<FString, AActor*> actors_names_map;

	world = GetWorld();
	check(world != 0);

    UGameplayStatics::GetAllActorsOfClass(world, AActor::StaticClass(), world_actors);

    for (AActor* world_actor : world_actors)
    {
		check(world_actor != 0);

        if (world_actor->Implements<USaveable_Actor_Interface>())
		{
			actor_path_name = GetPathNameSafe(world_actor);
            actors_names_map.Add(actor_path_name, world_actor);
        }
    }

	for (const FActor_Save_Data &actor_save_data : decibel_save_data.Actors_Save_Data)
	{
		AActor** actor = actors_names_map.Find(actor_save_data.Actor_Path_Name);
		check(actor != 0 && *actor != 0);
		ISaveable_Actor_Interface::Execute_On_Load(*actor, actor_save_data);
		Load_Actor_Components_Save(*actor, actor_save_data);
	}
}
//------------------------------------------------------------------------------------------------------------
void USave_Manager_Subsystem::Load_Actor_Components_Save(AActor *actor, const FActor_Save_Data &actor_save_data)
{
	FString component_path_name;
	TSet<UActorComponent*> actor_components;
	TMap<FString, UActorComponent*> components_names_map;

	check(actor != 0);

	for (UActorComponent* actor_component : actor_components)
    {
		check(actor_component != 0);

        if (actor_component->Implements<USaveable_Actor_Component_Interface>())
		{
			component_path_name = GetPathNameSafe(actor_component);
            components_names_map.Add(component_path_name, actor_component);
        }
    }

	for (const FActor_Component_Save_Data &component_save_data : actor_save_data.Components_Save_Data)
	{
		UActorComponent** actor_component = components_names_map.Find(component_save_data.Component_Path_Name);
		check(actor_component != 0 && *actor_component != 0);
		ISaveable_Actor_Component_Interface::Execute_On_Load(*actor_component, component_save_data);
	}
}
//------------------------------------------------------------------------------------------------------------
FString USave_Manager_Subsystem::Get_Save_Dir() const
{
	return FPaths::ProjectSavedDir() / Save_Dir;
}
//------------------------------------------------------------------------------------------------------------
FString USave_Manager_Subsystem::Get_Save_File_Name() const
{
	FString file_name;
	FDateTime now;

	now = FDateTime::Now();
	file_name = FString::Printf(TEXT("Save_%s.json"), *now.ToString(TEXT("%Y-%m-%d_%H-%M-%S")));

	return file_name;
}
//------------------------------------------------------------------------------------------------------------
FString USave_Manager_Subsystem::Get_Save_File_Path() const
{
	FString save_dir;
	FString file_path;
	FString file_name;

	save_dir = Get_Save_Dir();
	file_name = Get_Save_File_Name();
	file_path = save_dir / file_name;

	return file_path;
}
//------------------------------------------------------------------------------------------------------------
FString USave_Manager_Subsystem::Get_Last_Save_Path() const
{
    TArray<FString> save_files = Get_All_Save_Files();
    
    if (save_files.Num() > 0)
        return save_files[0];
    
    return FString();
}
//------------------------------------------------------------------------------------------------------------
TArray<FString> USave_Manager_Subsystem::Get_All_Save_Files() const
{
	FString save_dir;
    TArray<FString> save_files;

	save_dir = Get_Save_Dir();
    
    IFileManager::Get().FindFiles(save_files, *(save_dir / TEXT("*.json")), true, false);
    
    for (FString &save_file : save_files)
        save_file = save_dir / save_file;

    save_files.Sort([](const FString &a, const FString &b) {return a > b; });
    
    return save_files;
}
//------------------------------------------------------------------------------------------------------------
