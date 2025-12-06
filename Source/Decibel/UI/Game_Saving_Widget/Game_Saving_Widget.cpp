#include "Game_Saving_Widget.h"
#include "Components/TextBlock.h"
#include "Subsystems/Localization_Manager_Subsystem/Localization_Manager_Subsystem.h"

// UGame_Saving_Widget
//------------------------------------------------------------------------------------------------------------
UGame_Saving_Widget::UGame_Saving_Widget(const FObjectInitializer &object_initializer): Super(object_initializer)
{

}
//------------------------------------------------------------------------------------------------------------
void UGame_Saving_Widget::NativeConstruct()
{
	UGameInstance *game_inst = 0;
	ULocalization_Manager_Subsystem *localization_manager = 0;

	Super::NativeConstruct();

	game_inst = GetGameInstance();
	check(game_inst != 0);

	localization_manager = game_inst->GetSubsystem<ULocalization_Manager_Subsystem>();
	check(localization_manager != 0);

	check(Saving_Text != 0);
	Saving_Text->SetText(localization_manager->Get_Value(TEXT("Game_Saved")));
}
//------------------------------------------------------------------------------------------------------------
