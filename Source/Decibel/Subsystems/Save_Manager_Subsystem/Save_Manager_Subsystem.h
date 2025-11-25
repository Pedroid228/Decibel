#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "Save_Manager_Subsystem.generated.h"

struct FDecibel_Save_Data;
struct FActor_Save_Data;

// USave_Manager_Subsystem
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API USave_Manager_Subsystem: public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USave_Manager_Subsystem();

	void Save_Game();
	void Load_Save();

private:
	bool Try_Save_Actor(AActor *actor, FDecibel_Save_Data &decibel_save_data);
	void Save_Actor_Components(AActor *actor, FActor_Save_Data &actor_save_data);
	void Load_Actors_Save(const FDecibel_Save_Data &decibel_save_data);
	void Load_Actor_Components_Save(AActor *actor, const FActor_Save_Data &actor_save_data);
	FString Get_Save_Dir() const;
	FString Get_Save_File_Name() const;
	FString Get_Save_File_Path() const;
	TArray<FString> Get_All_Save_Files() const;
	FString Get_Last_Save_Path() const;

	static FString Save_Dir;
};
//------------------------------------------------------------------------------------------------------------
