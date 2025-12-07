#include "Keycards_Widget.h"
#include "Components/Image.h"

// UKeycards_Widget
//------------------------------------------------------------------------------------------------------------
UKeycards_Widget::UKeycards_Widget(const FObjectInitializer &object_initializer): Super(object_initializer)
{

}
//------------------------------------------------------------------------------------------------------------
void UKeycards_Widget::Add_Keycard(EKeycard_Type keycard_type)
{
	switch (keycard_type)
	{
	case EKeycard_Type::Yellow:
		Yellow_Keycard->SetVisibility(ESlateVisibility::Visible);
		break;

	case EKeycard_Type::Blue:
		Blue_Keycard->SetVisibility(ESlateVisibility::Visible);
		break;

	case EKeycard_Type::Red:
		Red_Keycard->SetVisibility(ESlateVisibility::Visible);
		break;
	}
}
//------------------------------------------------------------------------------------------------------------
void UKeycards_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	check(Yellow_Keycard != 0);
	check(Blue_Keycard != 0);
	check(Red_Keycard != 0);

	Yellow_Keycard->SetVisibility(ESlateVisibility::Collapsed);
	Blue_Keycard->SetVisibility(ESlateVisibility::Collapsed);
	Red_Keycard->SetVisibility(ESlateVisibility::Collapsed);
}
//------------------------------------------------------------------------------------------------------------