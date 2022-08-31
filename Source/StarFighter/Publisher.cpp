// Fill out your copyright notice in the Description page of Project Settings.


#include "Publisher.h"

APublisher::APublisher()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
// Called when the game starts or when spawned
void APublisher::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void APublisher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void APublisher::Subscribe(AActor* Subscriber)
{
	//Add the passed Subscriber
	Subscribers.Add(Subscriber);
}
void APublisher::UnSubscribe(AActor* SubscriberToRemove)
{
	//Remove the passed Subscriber
	Subscribers.Remove(SubscriberToRemove);
}
void APublisher::NotifySubscribers()
{
	//Loop for each Subscriber
	for (AActor* Actor : Subscribers)
	{
		//Cast each of them to a concrete Subscriber
		ISubscriber* Sub = Cast<ISubscriber>(Actor);
		if (Sub)
		{
			//Notify each of them that something has changed, so they can execute their own routine//
			Sub->Update(this);
		}
	}
}
