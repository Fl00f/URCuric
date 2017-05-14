// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	// ...
	SetController();
	SetPhysicsHandle();
	SetInput();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	PController->GetPlayerViewPoint(location, rotation);

	UpdateGrabLocation();

	if (PhysicsHandler->GrabbedComponent)
	{
		PhysicsHandler->SetTargetLocation(GrabLocation);
	}

}

void UGrabber::SetInput()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (Input)
	{
		///bind input to actions
		Input->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		Input->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UInputComponent was not found on %s"), *(GetOwner()->GetName()));
	}
}

void UGrabber::SetPhysicsHandle()
{
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandler)
	{
		///Do something once handler is found

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UPhysicsHandleComponent was not found on %s"), *(GetOwner()->GetName()));
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Error, TEXT("Press"));
	FHitResult result = GetFirstPhysicsBodyInReach();

	if (result.GetActor())
	{

		UPrimitiveComponent* comp = result.GetComponent();

		PhysicsHandler->GrabComponentAtLocationWithRotation(comp,
			NAME_None,
			comp->GetOwner()->GetTargetLocation(),
			rotation
		);

		///UE_LOG(LogTemp, Error, TEXT("%s"), *(PhysicsHandler->GrabbedComponent->GetOwner()->GetName()));

	}

}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Error, TEXT("Release"));
	PhysicsHandler->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{

	FHitResult hit;
	///What in the wild fuck is this?
	FCollisionQueryParams queryParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(OUT hit,
		location,
		GrabLocation,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		queryParams
	);

	return hit;
}

void UGrabber::UpdateGrabLocation()
{
	GrabLocation = location + rotation.Vector() * reach;
}

void UGrabber::SetController()
{
	PController = GetWorld()->GetFirstPlayerController();
}

