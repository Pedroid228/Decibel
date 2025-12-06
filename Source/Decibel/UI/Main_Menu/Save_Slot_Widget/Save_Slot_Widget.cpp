#include "Save_Slot_Widget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Decibel_Game_Instance/Decibel_Game_Instance.h"
#include "ImageUtils.h"
#include "Subsystems/Save_Manager_Subsystem/Save_Manager_Subsystem.h"
#include "Subsystems/Localization_Manager_Subsystem/Localization_Manager_Subsystem.h"

// USave_Slot_Widget
//------------------------------------------------------------------------------------------------------------
USave_Slot_Widget::USave_Slot_Widget(const FObjectInitializer &object_initializer): Super(object_initializer), State(ESlot_Save_State::None), Slot_Index(0)
{
}
//------------------------------------------------------------------------------------------------------------
void USave_Slot_Widget::Setup(int32 slot_index, ESlot_Save_State state)
{
	Slot_Index = slot_index;
	State = state;

	Setup_Text();
	Setup_Image();
}
//------------------------------------------------------------------------------------------------------------
void USave_Slot_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	check(Slot_Button != 0);
	Slot_Button->OnClicked.AddDynamic(this, &USave_Slot_Widget::On_Clicked);

	Slot_Button->OnHovered.AddDynamic(this, &USave_Slot_Widget::Set_Hovered_Image);
	Slot_Button->OnUnhovered.AddDynamic(this, &USave_Slot_Widget::Set_Unhovered_Image);
	Set_Unhovered_Image();
}
//------------------------------------------------------------------------------------------------------------
void USave_Slot_Widget::NativeOnListItemObjectSet(UObject *list_item)
{
	USave_Slot_Widget *save_slot = 0;

	check(list_item != 0);

	IUserObjectListEntry::NativeOnListItemObjectSet(list_item);

	save_slot = Cast<USave_Slot_Widget>(list_item);
	check(save_slot != 0);

	Setup(save_slot->Slot_Index, save_slot->State);
}
//------------------------------------------------------------------------------------------------------------
void USave_Slot_Widget::Setup_Text()
{
	FText base_text;
	FString full_text;
	UGameInstance *game_inst = 0;
	ULocalization_Manager_Subsystem *localization_manager = 0;

	Super::NativeConstruct();

	game_inst = GetGameInstance();
	check(game_inst != 0);

	localization_manager = game_inst->GetSubsystem<ULocalization_Manager_Subsystem>();
	check(localization_manager != 0);

	check(Slot_Number_Text != 0);
	base_text = localization_manager->Get_Value(TEXT("Slot"));
	full_text = FString::Printf(TEXT("%s %d"), *base_text.ToString(), Slot_Index);

	Slot_Number_Text->SetText(FText::FromString(full_text));
}
//------------------------------------------------------------------------------------------------------------
void USave_Slot_Widget::Setup_Image()
{
	FString screenshot_path;
	UTexture2D *texture = 0;
	UGameInstance *game_inst = 0;
	USave_Manager_Subsystem *save_manager_subsys = 0;

	game_inst = GetGameInstance();
	check(game_inst != 0);

	save_manager_subsys = game_inst->GetSubsystem<USave_Manager_Subsystem>();
	check(save_manager_subsys != 0);

	screenshot_path = save_manager_subsys->Get_Screenshot_Path(Slot_Index);

	texture = FImageUtils::ImportFileAsTexture2D(screenshot_path);
	if (texture == 0)
		return;

	check(Screenshot_Image != 0);
	Screenshot_Image->SetBrushFromTexture(texture);
}
//------------------------------------------------------------------------------------------------------------
void USave_Slot_Widget::On_Clicked()
{
	UDecibel_Game_Instance *decibel_game_inst = GetGameInstance<UDecibel_Game_Instance>();

	check(decibel_game_inst != 0);

	if (State == ESlot_Save_State::Load_Game)
		decibel_game_inst->Load_Game(Slot_Index);
	else if (State == ESlot_Save_State::New_Game)
		decibel_game_inst->New_Game(Slot_Index);
}
//------------------------------------------------------------------------------------------------------------
void USave_Slot_Widget::Set_Hovered_Image()
{
	check(BG_Image != 0);
	check(Hovered_Image != 0);
	BG_Image->SetBrushFromTexture(Hovered_Image);
}
//------------------------------------------------------------------------------------------------------------
void USave_Slot_Widget::Set_Unhovered_Image()
{
	check(BG_Image != 0);
	check(Default_Image != 0);
	BG_Image->SetBrushFromTexture(Default_Image);
}
//------------------------------------------------------------------------------------------------------------
