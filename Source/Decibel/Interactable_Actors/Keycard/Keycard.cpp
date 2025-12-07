#include "Keycard.h"
#include "Astronaut/Astronaut.h"
#include "Components/AudioComponent.h"

// AKeycard
//------------------------------------------------------------------------------------------------------------
AKeycard::AKeycard(): Type(EKeycard_Type::None), Is_Collected(false)
{
	Interaction_Type = EInteraction_Type::Instant;
}
//------------------------------------------------------------------------------------------------------------
void AKeycard::On_Save_Implementation(FActor_Save_Data &save_data)
{
	save_data.Actor_Class_Name = GetClass()->GetName();
	save_data.Is_Keycard_Collected = Is_Collected; 
}
//------------------------------------------------------------------------------------------------------------
void AKeycard::On_Load_Implementation(const FActor_Save_Data &save_data)
{
	if (save_data.Is_Keycard_Collected)
		Hide();
}
//------------------------------------------------------------------------------------------------------------
void AKeycard::OnConstruction(const FTransform &transform)
{
	Super::OnConstruction(transform);

	if (Base_Color_Material == 0 || Type == EKeycard_Type::None)
		return;

	MI_Color = UMaterialInstanceDynamic::Create(Base_Color_Material, this);
	check(MI_Color != 0);
	check(Mesh != 0);
	Mesh->SetMaterial(0, MI_Color);

	const FLinearColor *new_color = FKeycard_Color_Data::Colors.Find(Type);
	check(new_color != 0);
	MI_Color->SetVectorParameterValue(TEXT("Color"), *new_color);
}
//------------------------------------------------------------------------------------------------------------
void AKeycard::On_Interact_Begin_Implementation(AActor *interacting_actor)
{
	AAstronaut *astronaut = 0;
	UWorld *world = 0;

	astronaut = Cast<AAstronaut>(interacting_actor);
	check(astronaut != 0);
	astronaut->Add_Keycard_By_Type(Type);
	Hide();

	if (Interaction_Sound != 0)
		Audio_Component->Play();
}
//------------------------------------------------------------------------------------------------------------
void AKeycard::Hide()
{
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	Is_Collected = true;
}
//------------------------------------------------------------------------------------------------------------
