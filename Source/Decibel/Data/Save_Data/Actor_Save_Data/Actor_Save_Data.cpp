#include "Actor_Save_Data.h"

// FActor_Save_Data
//------------------------------------------------------------------------------------------------------------
FActor_Save_Data::FActor_Save_Data(): Hand_Door_Offset(0.0), Lever_Angle(0.0), Transform(FTransform::Identity)
{
}
//------------------------------------------------------------------------------------------------------------




// FAstronaut_Save_Data
//------------------------------------------------------------------------------------------------------------
FAstronaut_Save_Data::FAstronaut_Save_Data(): Has_Key_Card(false)
{
}
//------------------------------------------------------------------------------------------------------------




// FHearing_Component_Save_Data
//------------------------------------------------------------------------------------------------------------
FHearing_Component_Save_Data::FHearing_Component_Save_Data()
: Has_Heard_Sound(false), Has_High_Priority_Sound(false), Curr_Heard_Sound_Type(ESound_Type::None), Curr_Heard_Sound_Pos(FVector::ZeroVector)
{
}
//------------------------------------------------------------------------------------------------------------
FHearing_Component_Save_Data::FHearing_Component_Save_Data(bool has_heard_sound, bool has_high_priority_sound, ESound_Type curr_heard_sound_type, const FVector &curr_heard_sound_pos)
: Has_Heard_Sound(has_heard_sound), Has_High_Priority_Sound(has_high_priority_sound), Curr_Heard_Sound_Type(curr_heard_sound_type), Curr_Heard_Sound_Pos(curr_heard_sound_pos)
{
}
//------------------------------------------------------------------------------------------------------------
