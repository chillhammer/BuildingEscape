// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionTracker.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UPositionTracker::UPositionTracker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionTracker::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("The name is %s"), *GetOwner()->GetTransform().GetLocation().ToString());
}


// Called every frame
void UPositionTracker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

