#include "Decibel_Button_Widget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Subsystems/Localization_Manager_Subsystem/Localization_Manager_Subsystem.h"
#include "Animation/WidgetAnimation.h"

// UDecibel_Button_Widget
//------------------------------------------------------------------------------------------------------------
UDecibel_Button_Widget::UDecibel_Button_Widget(const FObjectInitializer &object_initializer): Super(object_initializer)
{
}
//------------------------------------------------------------------------------------------------------------
void UDecibel_Button_Widget::Set_Text_By_Key(const FString &key)
{
	UGameInstance *game_inst = 0;
	ULocalization_Manager_Subsystem *localization_manager = 0;

	game_inst = GetGameInstance();
	check(game_inst != 0);

	localization_manager = game_inst->GetSubsystem<ULocalization_Manager_Subsystem>();
	check(localization_manager != 0);

	check(Button_Text != 0);
	Button_Text->SetText(localization_manager->Get_Value(key));
}
//------------------------------------------------------------------------------------------------------------
FOnButtonClickedEvent &UDecibel_Button_Widget::Get_On_Clicked()
{
	return Hitbox->OnClicked;
}
//------------------------------------------------------------------------------------------------------------
void UDecibel_Button_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	check(Hitbox != 0);
	check(Button_Text != 0);
	check(Button_Image != 0);
	check(Default_Image != 0);
	check(Hovered_Image != 0);

	Hitbox->OnHovered.AddDynamic(this, &UDecibel_Button_Widget::Set_Hovered_Image);
	Hitbox->OnUnhovered.AddDynamic(this, &UDecibel_Button_Widget::Set_Unhovered_Image);

	Set_Unhovered_Image();
}
//------------------------------------------------------------------------------------------------------------
void UDecibel_Button_Widget::Set_Hovered_Image()
{
	check(Button_Image != 0);
	check(Hovered_Image != 0);
	Button_Image->SetBrushFromTexture(Hovered_Image);
}
//------------------------------------------------------------------------------------------------------------
void UDecibel_Button_Widget::Set_Unhovered_Image()
{
	check(Button_Image != 0);
	check(Default_Image != 0);
	Button_Image->SetBrushFromTexture(Default_Image);
}
//------------------------------------------------------------------------------------------------------------

