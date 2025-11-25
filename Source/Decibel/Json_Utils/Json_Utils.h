#pragma once

DECLARE_LOG_CATEGORY_EXTERN(Json_Utils_Log, All, All);

struct FDecibel_Save_Data;

// AJson_Utils
//------------------------------------------------------------------------------------------------------------
class AJson_Utils
{
public:
	AJson_Utils();
	static bool Write_Save_Data(const FString &file_name, const FDecibel_Save_Data &input_data);
	static bool Read_Save_Data(const FString &file_name, FDecibel_Save_Data &input_data);
};
//------------------------------------------------------------------------------------------------------------
