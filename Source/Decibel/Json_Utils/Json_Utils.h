#pragma once

DECLARE_LOG_CATEGORY_EXTERN(Json_Utils_Log, All, All);

struct FDecibel_Save_Data;

// AJson_Utils
//------------------------------------------------------------------------------------------------------------
class AJson_Utils
{
public:
	AJson_Utils();
	static bool Write_Save_Data(const FString &file_path, const FDecibel_Save_Data &input_data);
	static bool Read_Save_Data(const FString &file_path, FDecibel_Save_Data &input_data);
	static TSharedPtr<FJsonObject> Read_To_Main_Json_Object(const FString &file_path);
};
//------------------------------------------------------------------------------------------------------------
