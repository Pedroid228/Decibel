#include "Save_Manager_Subsystem.h"
#include "Json_Utils/Json_Utils.h"
#include "Interfaces/Saveable_Actor_Interface/Saveable_Actor_Interface.h"
#include "Interfaces/Saveable_Actor_Component_Interface/Saveable_Actor_Component_Interface.h"
#include "Kismet/GameplayStatics.h"
#include "Data/Save_Data/Decibel_Save_Data/Decibel_Save_Data.h"

// USave_Manager_Subsystem
//------------------------------------------------------------------------------------------------------------
FString USave_Manager_Subsystem::Save_Dir = "Game_Saves";
FString USave_Manager_Subsystem::Screenshots_Dir = "Game_Screenshots";
//------------------------------------------------------------------------------------------------------------
USave_Manager_Subsystem::USave_Manager_Subsystem()
{
}
//------------------------------------------------------------------------------------------------------------
void USave_Manager_Subsystem::Save_Game(int32 slot_index)
{
	FString save_path;
	FString map_name;
	FDecibel_Save_Data decibel_save_data;
	UStruct *save_data_class = 0;
	UWorld *world = 0;
	TArray<AActor*> world_actors;

	world = GetWorld();
	check(world != 0);

	map_name = world->GetMapName();
	map_name.RemoveFromStart(world->StreamingLevelsPrefix);
	decibel_save_data.Map_Name = FName(map_name);

	Create_Screenshot(slot_index);

	UGameplayStatics::GetAllActorsOfClass(world, AActor::StaticClass(), world_actors);

	for (AActor *world_actor : world_actors)
		Try_Save_Actor(world_actor, decibel_save_data);

	save_path = Get_Save_File_Path(slot_index);
	AJson_Utils::Write_Save_Data(save_path, decibel_save_data);
}
//------------------------------------------------------------------------------------------------------------
void USave_Manager_Subsystem::Load_Save(int32 slot_index)
{
	FString save_path;
    FDecibel_Save_Data decibel_save_data;
	UWorld *world = 0;

	save_path = Get_Save_File_Path(slot_index);
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
FString USave_Manager_Subsystem::Get_Screenshot_Path(int32 slot_index)
{
	FString screen_name;
	FString screens_dir;
	FString screen_path;

	screen_name = FString::Printf(TEXT("Screenshot_%d.png"), slot_index);
	screens_dir = Get_Screenshots_Dir();
    screen_path = screens_dir / screen_name;

	return screen_path;
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
	FString actor_class_name;
	UWorld *world = 0;
	TArray<AActor*> world_actors;
	TMap<FString, TArray<AActor*>> actors_by_class;
	TArray<AActor*>* actors_array = 0;
	AActor *actor_to_load = 0;

	world = GetWorld();
	check(world != 0);

    UGameplayStatics::GetAllActorsOfClass(world, AActor::StaticClass(), world_actors);

    for (AActor* world_actor : world_actors)
    {
		check(world_actor != 0);

        if (world_actor->Implements<USaveable_Actor_Interface>())
		{
			actor_class_name = world_actor->GetClass()->GetName();
            actors_by_class.FindOrAdd(actor_class_name).Add(world_actor);
        }
    }

	for (const FActor_Save_Data &actor_save_data : decibel_save_data.Actors_Save_Data)
	{
		actors_array = actors_by_class.Find(actor_save_data.Actor_Class_Name);
		if (actors_array == 0)
			continue;

		check(actors_array != 0 && !actors_array->IsEmpty());

		actor_to_load = (*actors_array)[0];
		check(actor_to_load != 0);

		actors_array->RemoveAt(0);

		ISaveable_Actor_Interface::Execute_On_Load(actor_to_load, actor_save_data);
		Load_Actor_Components_Save(actor_to_load, actor_save_data);
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
FString USave_Manager_Subsystem::Get_Screenshots_Dir() const
{
	return FPaths::ProjectSavedDir() / Screenshots_Dir;
}
//------------------------------------------------------------------------------------------------------------
//FString USave_Manager_Subsystem::Get_Save_File_Time() const
//{
//	FString file_time;
//	FDateTime now;
//
//	now = FDateTime::Now();
//	file_time = now.ToString(TEXT("%Y-%m-%d_%H-%M-%S"));
//
//	return file_time;
//}
//------------------------------------------------------------------------------------------------------------
FString USave_Manager_Subsystem::Get_Save_File_Path(int32 slot_index) const
{
	FString save_dir;
	FString file_path;
	FString file_name;

	save_dir = Get_Save_Dir();
	file_name = FString::Printf(TEXT("Save_%d.json"), slot_index);
	file_path = save_dir / file_name;

	return file_path;
}
//------------------------------------------------------------------------------------------------------------
//TArray<FString> USave_Manager_Subsystem::Get_All_Save_Files() const
//{
//	FString save_dir;
//    TArray<FString> save_files;
//
//	save_dir = Get_Save_Dir();
//    
//    IFileManager::Get().FindFiles(save_files, *(save_dir / TEXT("*.json")), true, false);
//    
//    for (FString &save_file : save_files)
//        save_file = save_dir / save_file;
//
//    save_files.Sort([](const FString &a, const FString &b) {return a > b; });
//    
//    return save_files;
//}
//------------------------------------------------------------------------------------------------------------
void USave_Manager_Subsystem::Create_Screenshot(int32 slot_index)
{
	FString file_path = Get_Screenshot_Path(slot_index);
    FScreenshotRequest::RequestScreenshot(file_path, false, false);
}
//------------------------------------------------------------------------------------------------------------
