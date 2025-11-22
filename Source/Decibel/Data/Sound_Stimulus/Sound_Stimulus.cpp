#include "Sound_Stimulus.h"

// FSound_Stimulus
//------------------------------------------------------------------------------------------------------------
TMap<ESound_Type, double> FSound_Stimulus::Sounds_Range = {
    {       ESound_Type::Silent,  35000.0},
    {       ESound_Type::Normal,  15000.0},
    {         ESound_Type::Loud,  15000.0},
    {ESound_Type::High_Priority, 100000.0}
};
//------------------------------------------------------------------------------------------------------------
FSound_Stimulus::FSound_Stimulus(): Type(ESound_Type::None), Pos(FVector::ZeroVector)
{
}
//------------------------------------------------------------------------------------------------------------
FSound_Stimulus::FSound_Stimulus(ESound_Type type, const FVector &pos, AActor *instigator): Type(type), Pos(pos), Instigator(instigator)
{
}
//------------------------------------------------------------------------------------------------------------
