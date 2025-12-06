#include "Keycard_Slot_Widget.h"
#include "Components/Image.h"

// UKeycard_Slot_Widget
//------------------------------------------------------------------------------------------------------------
UKeycard_Slot_Widget::UKeycard_Slot_Widget(const FObjectInitializer &object_initializer): Super(object_initializer)
{
}
//------------------------------------------------------------------------------------------------------------
void UKeycard_Slot_Widget::Set_Color(UMaterialInstanceDynamic *color_material)
{
	check(Color_Image != 0);
	check(color_material != 0);
	Color_Image->SetBrushFromMaterial(color_material);
}
//------------------------------------------------------------------------------------------------------------
void UKeycard_Slot_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	check(Color_Image != 0);
	check(Logo_Image != 0);
}
//------------------------------------------------------------------------------------------------------------
