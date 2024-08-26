// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemMaster.h"


AItemMaster::AItemMaster()
{
	bReplicates = true;

	// Disable ticking by default
	PrimaryActorTick.bCanEverTick = true; // Ensures the actor can tick if needed
	PrimaryActorTick.bStartWithTickEnabled = false; // Disable tick at the start
}

void AItemMaster::BeginPlay()
{
	Super::BeginPlay();
	
}