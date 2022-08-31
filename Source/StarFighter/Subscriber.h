// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Subscriber.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USubscriber : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class STARFIGHTER_API ISubscriber
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.//
public:

	virtual void Update(class APublisher* Publisher) = 0;
};
