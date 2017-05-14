// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetInput();
	void SetPhysicsHandle();

private:
	FVector location;
	FRotator rotation;
	APlayerController* PController;
	float reach = 100.f;
	FVector GrabLocation;
	UPhysicsHandleComponent* PhysicsHandler = nullptr;
	UInputComponent* Input = nullptr;
	void Grab();
	void Release();
	FHitResult GetFirstPhysicsBodyInReach();
	void UpdateGrabLocation();
	void SetController();
};