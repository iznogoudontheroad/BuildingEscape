// Copyright Ben Tristem 2016.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "OpenDoor2.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor2 : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor2();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere)
	float OpenAngle = 0.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	

	float DoorCLoseDelay = 1.0f;
	float lastDoorOpenTime;

	void OpenDoor();
	void CloseDoor();

	AActor* Owner;
		
	float GetTotalMassOfActorsOnPlate();
	
};
