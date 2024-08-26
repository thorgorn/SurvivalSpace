// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemMaster.generated.h"

UCLASS()
class SURVIVALSPACE_API AItemMaster : public AActor
{
	GENERATED_BODY()
	
public:

	//--------------------------------------------------------------------------------------------
	// ITEM MASTER CONSTRUCTOR
	//--------------------------------------------------------------------------------------------
	
	AItemMaster();

protected:

	//--------------------------------------------------------------------------------------------
	// ITEM MASTER PROPERTIES & VARIABLES
	//--------------------------------------------------------------------------------------------
	
	virtual void BeginPlay() override;
	
};
