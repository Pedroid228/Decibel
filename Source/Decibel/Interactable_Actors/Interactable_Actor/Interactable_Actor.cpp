#include "Interactable_Actor.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/Interaction_Widget/Interaction_Widget.h"

// AInteractable_Actor
//------------------------------------------------------------------------------------------------------------
AInteractable_Actor::AInteractable_Actor(): Interaction_Type(EInteraction_Type::None)
{
	Root_Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Root_Scene_Comp"));
	check(Root_Scene != 0);
	SetRootComponent(Root_Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Comp"));
	check(Mesh != 0);
	Mesh->SetupAttachment(Root_Scene);

	Interaction_Tip_Widget_Component = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction_Tip_Widget_Comp"));
	check(Interaction_Tip_Widget_Component != 0);
	Interaction_Tip_Widget_Component->SetupAttachment(Mesh);

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	SetActorTickEnabled(false);
}
//------------------------------------------------------------------------------------------------------------
EInteraction_Type AInteractable_Actor::Get_Interaction_Type_Implementation()
{
	return Interaction_Type;
}
//------------------------------------------------------------------------------------------------------------
void AInteractable_Actor::BeginPlay()
{
	UUserWidget *interaction_user_widget = 0;
	UInteraction_Widget *interaction_widget = 0;
	Super::BeginPlay();

	check(Interaction_Tip_Texture != 0);
	check(Interaction_Widget_BP_Class != 0);
	check(Interaction_Tip_Widget_Component != 0);
	Interaction_Tip_Widget_Component->SetWidgetClass(Interaction_Widget_BP_Class);

	interaction_user_widget = Interaction_Tip_Widget_Component->GetWidget();
	check(interaction_user_widget != 0);

	interaction_widget = Cast<UInteraction_Widget>(interaction_user_widget);
	check(interaction_widget != 0);

	interaction_widget->Set_Texture(Interaction_Tip_Texture);

	Interaction_Tip_Widget_Component->SetVisibility(false);
}
//------------------------------------------------------------------------------------------------------------
void AInteractable_Actor::On_Trace_Hit_Implementation(AActor *interacting_actor, UPrimitiveComponent *hit_component)
{
	Interaction_Tip_Widget_Component->SetVisibility(true);
}
//------------------------------------------------------------------------------------------------------------
void AInteractable_Actor::On_Trace_Leave_Implementation()
{
	Interaction_Tip_Widget_Component->SetVisibility(false);
}
//------------------------------------------------------------------------------------------------------------