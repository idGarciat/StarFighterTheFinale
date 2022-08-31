// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Subscriber.h"
#include "Publisher.generated.h"

UCLASS()
class STARFIGHTER_API APublisher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties//
	APublisher();


private:
	//The Subscribers of this Publisher
	UPROPERTY()
		TArray<AActor*> Subscribers = TArray<AActor*>();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	//Add the pased Subscriber to the list
	virtual void Subscribe(AActor* Subscriber);
	//Remove the passed Subscriber from the list
	virtual void UnSubscribe(AActor* SubscriberToRemove);
	//Notify all the Subscribers that something has changed
	virtual void NotifySubscribers();


};
