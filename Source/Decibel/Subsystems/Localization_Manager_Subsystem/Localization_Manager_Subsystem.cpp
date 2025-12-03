#include "Localization_Manager_Subsystem.h"

#include "Json_Utils/Json_Utils.h"

DEFINE_LOG_CATEGORY(Localization_Manager_Log);

// ULocalization_Manager_Subsystem
//------------------------------------------------------------------------------------------------------------
FString ULocalization_Manager_Subsystem::Json_Dictionaries_Dir = TEXT("Decibel/Localization/");
//------------------------------------------------------------------------------------------------------------
ULocalization_Manager_Subsystem::ULocalization_Manager_Subsystem(): Current_Language(ELanguage::None)
{
}
//------------------------------------------------------------------------------------------------------------
void ULocalization_Manager_Subsystem::Set_Language(ELanguage new_language)
{
	if (Current_Language == new_language)
		return;

	check(new_language != ELanguage::None);

	Load_Language_File(new_language);
	On_Language_Changed.Broadcast(new_language);

	Current_Language = new_language;
}
//------------------------------------------------------------------------------------------------------------
ELanguage ULocalization_Manager_Subsystem::Get_Language()
{
	return Current_Language;
}
//------------------------------------------------------------------------------------------------------------
FText ULocalization_Manager_Subsystem::Get_Value(const FString &key)
{
	FText result;
	const FString *value = Current_Dictionary.Find(key);
	
	if (value == 0)
	{
		UE_LOG(Localization_Manager_Log, Error, TEXT(">>>>>>[%hs] Key %s was not found"), __FUNCTION__, *key);
		return FText::FromString(TEXT("NoNe"));
	}

	result = FText::FromString(*value);
	return result;
}
//------------------------------------------------------------------------------------------------------------
FText ULocalization_Manager_Subsystem::Get_Variative_Value(const FString &key)
{
	int32 rand_index;
	FString rand_value;
	FText result;
	const TArray<FString> *value_array = Variations_Dictionary.Find(key);
	
	if (value_array == 0)
	{
		UE_LOG(Localization_Manager_Log, Error, TEXT(">>>>>>[%hs] Key %s was not found"), __FUNCTION__, *key);
		return FText::FromString(TEXT("NoNe"));
	}

	rand_index = FMath::RandRange(0, value_array->Num() - 1);
	rand_value = (*value_array)[rand_index];

	result = FText::FromString(rand_value);

	return result;
}
//------------------------------------------------------------------------------------------------------------
void ULocalization_Manager_Subsystem::Load_Language_File(ELanguage language)
{
	FString file_path;
	FString file_content;
	FString curr_key;
	TSharedPtr<FJsonObject> main_json_object = 0;

	file_path = Get_Language_File_Path(language);

	main_json_object = AJson_Utils::Read_To_Main_Json_Object(file_path);

	Current_Dictionary.Empty();
	Variations_Dictionary.Empty();

	for (const auto &entry : main_json_object->Values)
	{
		curr_key = entry.Key;

		if (entry.Value->Type == EJson::String)
			Current_Dictionary.Add(curr_key, entry.Value->AsString());
		else if (entry.Value->Type == EJson::Array)
		{
			const TArray<TSharedPtr<FJsonValue>> &variations_values = entry.Value->AsArray();
			Add_Variations(curr_key, variations_values);
		}
	}
}
//------------------------------------------------------------------------------------------------------------
void ULocalization_Manager_Subsystem::Add_Variations(const FString &key, const TArray<TSharedPtr<FJsonValue>> &variations_values)
{
	TArray<FString> variations;

	for (const auto &variation_value : variations_values)
	{
		if (variation_value->Type == EJson::String)
			variations.Add(variation_value->AsString());
	}

	if (variations.Num() > 0)
		Variations_Dictionary.Add(key, variations);
}
//------------------------------------------------------------------------------------------------------------
FString ULocalization_Manager_Subsystem::Get_Language_File_Path(ELanguage language)
{
	FString dictionaries_dir;
	FString language_folder;
	FString content_dir;
	FString file_name;
	FString file_path;

	switch (language)
	{
	case ELanguage::En:
		language_folder = TEXT("en");
		break;

	case ELanguage::Ru:
		language_folder = TEXT("ru");
		break;
	}

	file_name = language_folder + TEXT(".json");
	content_dir = FPaths::ProjectContentDir();

	file_path = FPaths::Combine(content_dir, Json_Dictionaries_Dir, language_folder, file_name);

	return file_path;
}
//------------------------------------------------------------------------------------------------------------
