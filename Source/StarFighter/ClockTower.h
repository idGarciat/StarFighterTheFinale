// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Publisher.h"
#include "ClockTower.generated.h"

/**
 * 
 */
UCLASS()
class STARFIGHTER_API AClockTower : public APublisher
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AClockTower();
private:
	//The current time of this Clock Tower
	FString Time;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	//Called when the time of this Clock Tower has changed
	void TimeChanged();

	//Set the time of this Clock Tower

	void SetTimeOfDay(FString myTime);

	//Return the time of this Clock Tower//

	FORCEINLINE FString GetTime() { return Time; }

};
