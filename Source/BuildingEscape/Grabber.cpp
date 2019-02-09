// Copyright Ben Tristem 2016.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	Reach = 100.f;
	FindPhysicsHandleComponent();
	SetupInputComponent();

}

void UGrabber::SetupInputComponent(){
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The InputComponent of Object %s was not found"), *GetOwner()->GetName());
	}
}

void UGrabber::FindPhysicsHandleComponent()
{
	//Find the physics handle of the actor
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>(); 
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Component not found"));
	}	
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("The Object is grabbed"));

	///Line Trace and see if we reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	///if we hit something then attach a physics handle
	if (ActorHit) 
	{
		PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}

}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("The Object is released"));
	PhysicsHandle->ReleaseComponent();
}


void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (PhysicsHandle->GrabbedComponent)
	{
		//Change the position of the grabbed object to the End of teh Reachline
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
	
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach() 
{
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FHitResult HitResult;

	GetWorld()->LineTraceSingleByObjectType(OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters);
	
	return HitResult;
}

FVector UGrabber::GetReachLineEnd() {
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);
	
	return PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
}

FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);

	return PlayerViewPointLocation;
}


