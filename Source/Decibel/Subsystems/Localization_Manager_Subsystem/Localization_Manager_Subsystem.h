#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Data/Localization_Data/Localization_Data.h"
#include "Localization_Manager_Subsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Localization_Manager_Log, All, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_Language_Changed, ELanguage, new_language);

// ULocalization_Manager_Subsystem
//------------------------------------------------------------------------------------------------------------
UCLASS() class DECIBEL_API ULocalization_Manager_Subsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    ULocalization_Manager_Subsystem();
    void Set_Language(ELanguage new_language);
    ELanguage Get_Language();
    FText Get_Value(const FString &key);
    FText Get_Variative_Value(const FString &key);


    FOn_Language_Changed On_Language_Changed;

private:
    void Load_Language_File(ELanguage language);
    void Add_Variations(const FString &key, const TArray<TSharedPtr<FJsonValue>> &variations_values);
    FString Get_Language_File_Path(ELanguage language);

    ELanguage Current_Language;
    TMap<FString, FString> Current_Dictionary;
    TMap<FString, TArray<FString>> Variations_Dictionary;

    static FString Json_Dictionaries_Dir;
};
//------------------------------------------------------------------------------------------------------------
