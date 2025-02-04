// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	ActorThatOpensDoors = GetWorld()->GetFirstPlayerController()->GetPawn();


}

void UOpenDoor::OpenDoor()
{
	FRotator rotation = FRotator(0.f, 80.f, 0.f);
	Owner->SetActorRotation(rotation);
	isDoorOpen = true;
	DoorLastOpenTime = GetWorld()->GetTimeSeconds();
}

void UOpenDoor::CloseDoor()
{
	FRotator rotation = FRotator(0.f, 0.f, 0.f);
	Owner->SetActorRotation(rotation);
	isDoorOpen = false;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (pressurePlate->IsOverlappingActor(ActorThatOpensDoors))
	{
		OpenDoor();
	}

	if (GetWorld()->GetTimeSeconds() - DoorLastOpenTime > Doortimedelay)
	{
		CloseDoor();
	}
	// ...
}

