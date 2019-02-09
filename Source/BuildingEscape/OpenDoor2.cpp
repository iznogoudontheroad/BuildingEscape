// Copyright Ben Tristem 2016.

#include "BuildingEscape.h"
#include "OpenDoor2.h"
#define OUT


// Sets default values for this component's properties
UOpenDoor2::UOpenDoor2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor2::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	
	
	// ...
	
}

void UOpenDoor2::OpenDoor()
{
	

	
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor2::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.f, 90.0f, 0.f));
}

// Called every frame
void UOpenDoor2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorsOnPlate() > 30.f)
	{
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - lastDoorOpenTime > DoorCLoseDelay) {
		CloseDoor();
		
	}
	
	// ...
}

float UOpenDoor2::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.f;
	
	//Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	//iterate through thjem and add teh masses
	for (const AActor* actor : OverlappingActors) {
		TotalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on PressurePlate"), *actor->GetName());
		
	}
	
	
	return TotalMass;

}

