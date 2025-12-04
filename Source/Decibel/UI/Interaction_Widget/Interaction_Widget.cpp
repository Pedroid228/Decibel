#include "Interaction_Widget.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"

// UInteraction_Widget
//------------------------------------------------------------------------------------------------------------
UInteraction_Widget::UInteraction_Widget(const FObjectInitializer &object_initializer): Super(object_initializer)
{
}
//------------------------------------------------------------------------------------------------------------
void UInteraction_Widget::Set_Texture(UTexture2D *texture)
{
	check(Interaction_Image != 0);
	check(texture != 0);
	Interaction_Image->SetBrushFromTexture(texture);
}
//------------------------------------------------------------------------------------------------------------
void UInteraction_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	check(Interaction_Image != 0);
}
//------------------------------------------------------------------------------------------------------------
