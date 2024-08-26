// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemMaster.h"


AItemMaster::AItemMaster()
{
	bReplicates = true;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AItemMaster::BeginPlay()
{
	Super::BeginPlay();
	
}