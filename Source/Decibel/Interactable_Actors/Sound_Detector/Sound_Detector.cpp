#include "Sound_Detector.h"

#include "Components/AudioComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/Dashboard_Gauge_Widget/Dashboard_Gauge_Widget.h"
#include "Kismet/GameplayStatics.h"

// ASound_Detector
//------------------------------------------------------------------------------------------------------------
ASound_Detector::ASound_Detector(): Min_Distance_To_Hush(200.0), Max_Distance_To_Hush(1500.0), Min_Needle_Angle(-60.0), Max_Needle_Angle(60.0), Is_Grabbed(false), Is_Active(false)
{
	Tags.Add(TEXT("Sound_Detector_Tag"));

	Interaction_Type = EInteraction_Type::Instant;
	check(Interaction_Tip_Widget_Component != 0);
	Interaction_Tip_Widget_Component->SetupAttachment(Mesh);

	Dashboard_Gauge_Widget_Component = CreateDefaultSubobject<UWidgetComponent>(TEXT("Dashboard_Gauge_Widget_Comp"));
	check(Dashboard_Gauge_Widget_Component != 0);
	Dashboard_Gauge_Widget_Component->SetupAttachment(Mesh);

	Detector_Audio_Component = CreateDefaultSubobject<UAudioComponent>(TEXT("Detector_Audio_Comp"));
	check(Detector_Audio_Component != 0);
	Detector_Audio_Component->SetupAttachment(Mesh);

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	SetActorTickEnabled(true);
}
//------------------------------------------------------------------------------------------------------------
void ASound_Detector::Set_Active(bool is_active)
{
	if (Is_Active == is_active)
		return;

	check(Detector_Audio_Component != 0);

	if (is_active)
		Detector_Audio_Component->Play();
	else
		Detector_Audio_Component->Stop();
		
	SetActorTickEnabled(is_active);
	Is_Active = is_active;
}
//------------------------------------------------------------------------------------------------------------
void ASound_Detector::BeginPlay()
{
	UUserWidget *dashboard_gauge_user_widget = 0;

	Super::BeginPlay();

	check(Detector_Meta_Sound != 0);
	check(Detector_Audio_Component != 0);

	Detector_Audio_Component->SetSound(Detector_Meta_Sound);
	Set_Active(true);

	check(Dashboard_Gauge_Widget_Component != 0);
	dashboard_gauge_user_widget = Dashboard_Gauge_Widget_Component->GetWidget();
	check(dashboard_gauge_user_widget != 0);
	Dashboard_Gauge_Widget = Cast<UDashboard_Gauge_Widget>(dashboard_gauge_user_widget);
	check(Dashboard_Gauge_Widget != 0);
	Dashboard_Gauge_Widget->Set_Needle_Angles(Max_Needle_Angle, Min_Needle_Angle);
}
//------------------------------------------------------------------------------------------------------------
void ASound_Detector::Tick(float delta_time)
{
	double ratio;
	double distance_to_hush;


	Super::Tick(delta_time);

	distance_to_hush = Get_Min_Distance_To_Hush();
	ratio = distance_to_hush / (Max_Distance_To_Hush - Min_Distance_To_Hush);
	ratio = FMath::Clamp(ratio, 0.0, 1.0);
	ratio = 1.0 - ratio;

	check(Detector_Audio_Component != 0);
	Detector_Audio_Component->SetFloatParameter(TEXT("Hush_Sound_Ratio"), (float)ratio);

	check(Dashboard_Gauge_Widget != 0);
	Dashboard_Gauge_Widget->Set_Target_Ratio(ratio);
}
//------------------------------------------------------------------------------------------------------------
void ASound_Detector::On_Interact_Begin_Implementation(AActor *interacting_actor)
{
	Is_Grabbed = true;

	check(Mesh != 0);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	check(Interaction_Tip_Widget_Component != 0);
	Interaction_Tip_Widget_Component->SetVisibility(false);

	if (Interaction_Sound != 0)
		Audio_Component->Play();
}
//------------------------------------------------------------------------------------------------------------
void ASound_Detector::On_Trace_Hit_Implementation(AActor *interacting_actor, UPrimitiveComponent *hit_component)
{
	if (!Is_Grabbed)
		Super::On_Trace_Hit_Implementation(interacting_actor, hit_component);
}
//------------------------------------------------------------------------------------------------------------
void ASound_Detector::On_Trace_Leave_Implementation()
{
	if (!Is_Grabbed)
		Super::On_Trace_Leave_Implementation();
}
//------------------------------------------------------------------------------------------------------------
double ASound_Detector::Get_Min_Distance_To_Hush()
{
	double min_distance_sq = MAX_dbl;
	double min_distance = min_distance_sq;
	double curr_distance_sq;
	FVector detector_pos;
	FVector hush_pos;
	TArray<AActor *> hush_actors;

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Hush_Tag"), hush_actors);

	if (hush_actors.IsEmpty())
		return min_distance;

	detector_pos = GetActorLocation();

	for (AActor *hush_actor : hush_actors)
	{
		check(hush_actor != 0);

		hush_pos = hush_actor->GetActorLocation();
		curr_distance_sq = FVector::DistSquared(detector_pos, hush_pos);

		if (curr_distance_sq < min_distance_sq)
			min_distance_sq = curr_distance_sq;
	}

	min_distance = FMath::Sqrt(min_distance_sq);

	return min_distance;
}
//------------------------------------------------------------------------------------------------------------
