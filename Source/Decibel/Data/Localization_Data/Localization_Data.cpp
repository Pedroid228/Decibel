#include "Localization_Data.h"

// FLocalization_Data
//------------------------------------------------------------------------------------------------------------
const TMap<FString, ELanguage> FLocalization_Data::Languages = {
    {TEXT("English"), ELanguage::En},
    {TEXT("Русский"), ELanguage::Ru}
};
//------------------------------------------------------------------------------------------------------------
const TMap<ELanguage, FString> FLocalization_Data::Reverse_Languages = {
    {ELanguage::En, TEXT("English")},
    {ELanguage::Ru, TEXT("Русский")}
};
//------------------------------------------------------------------------------------------------------------
