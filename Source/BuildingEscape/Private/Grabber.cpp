// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


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

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	

	if (PhysicsHandle) {
		UE_LOG(LogTemp, Warning, TEXT("The Component Owner is: %s\n"), *PhysicsHandle->GetOwner()->GetName());
	} else {
		UE_LOG(LogTemp, Error, TEXT("%s does not have Physics Handle.\n"), *GetOwner()->GetName());
	}

	if (Input) {
		UE_LOG(LogTemp, Warning, TEXT("Input Found! \n"));
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s does not have Input Component.\n"), *GetOwner()->GetName());
	}
	
}

//Ray-cast and Pick up
void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grabbed."));
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Released."));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator pRot;
	FVector pPos;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(pPos, pRot);
	//UE_LOG(LogTemp, Warning, TEXT("The position is: %s\nThe Rotation is: %s\n\n"), *pPos.ToString(), *pRot.ToString());

	DrawDebugLine(GetWorld(), pPos, pPos + pRot.Vector()*ArmReach, FColor(255, 0, 0), false, -1.f, (uint8)'\000', 2.f);

	FHitResult result;
	const FCollisionObjectQueryParams params(ECC_PhysicsBody);
	const FCollisionQueryParams params2(TEXT(""), false, GetOwner());
	bool hit = GetWorld()->LineTraceSingleByObjectType(result, pPos, pPos + pRot.Vector()*ArmReach, params, params2);
	if (hit) {
		UE_LOG(LogTemp, Warning, TEXT("The object is: %s\n"), *result.GetActor()->GetName());
	}
}

