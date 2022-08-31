// Copyright Epic Games, Inc. All Rights Reserved.


#include "StarFighterGameModeBase.h"
#include "NaveTerrestreEnemiga01.h"
#include "NaveAcuatica.h"
#include "InventoryActor.h"
#include "NewNaveNodriza.h"
#include "Singleton.h"

#include "DirectorNaveEnemigaBuilder.h"
#include "NaveEnemigaCazaBuilder.h"
#include "NaveEnemiga.h"
void AStarFighterGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UWorld* const World = GetWorld();
	//auto ne = SpawnNave<ANaveTerrestreEnemiga01>();


	//GetWorldTimerManager().SetTimer(AcuaticaTimerHandle, this, &AStarFighterGameModeBase::SpawnNave, 03.0f, true, 2.0f);//cada cierto tiempo creamos una NaveAcuatica extra en el mapa con el SpawnNave

	GetWorldTimerManager().SetTimer(AcuaticaTimerHandle1, this, &AStarFighterGameModeBase::SpawnCapsulas, 02.0f, true, 1.0f);


	//SpawnNave();
	//============================================================================================================================



	/*PejeX = rand() % 100 + 1;
	PejeY = rand() % 100 + 1;
	ejeX = rand() % 200 + 1;
	ejeY = rand() % 200 + 1;

	World->SpawnActor<ANewNaveNodriza>(FVector(PejeX, PejeY, 200.0f), FRotator::ZeroRotator);
	World->SpawnActor<ANaveAcuatica>(FVector(ejeX, ejeY, 112.0f), FRotator::ZeroRotator);*/


		/*UWorld* const World = GetWorld();


		ejeX = rand() % 200 + 1;
		ejeY = rand() % 200 + 1;

		World->SpawnActor<ANewNaveNodriza>(FVector(ejeX, ejeY, 112.0f), FRotator::ZeroRotator);

		UE_LOG(LogTemp, Warning, TEXT("Se creo nodriza"));*/


		//singleton=========================================================================================================================================
				/*for (int i = 0; i <= 4; i++)
				{
					ANewNaveNodriza* SpawnedNodriza = GetWorld()->SpawnActor<ANewNaveNodriza>(FVector(100, 100, 112.0f), FRotator::ZeroRotator);

					if (SpawnedNodriza)
					{
						//If the Spawn succeeds, set the Spawned inventory to the local one and log the success string
						Nodriza = SpawnedNodriza;
						GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("%s has been created"), *Nodriza->GetName()));
					}
				}*/

				//===================================================================================================================================================


				//ANewNaveNodriza* None = ASingleton::GetInstancia();

	//Spawn Builder and Engineer
	//NaveEnemigoCazaBuilder = GetWorld()->SpawnActor<ANaveEnemigaCazaBuilder>(ANaveEnemigaCazaBuilder::StaticClass());
	//Director = GetWorld()->SpawnActor<ADirectorNaveEnemigaBuilder>(ADirectorNaveEnemigaBuilder::StaticClass());
	////Set the Builder for the Engineer and create the buildings
	//Director->SetNaveEnemigaBuilder(NaveEnemigoCazaBuilder);
	//Director->ConstruirNaveEnemiga();
	////Get the Engineer's Lodging and Logs the created buildings
	//ANaveEnemiga* NaveEnemiga = Director->GetNaveEnemiga();
	//NaveEnemiga->CaracteristicasNaveEnemiga();


}

AStarFighterGameModeBase::AStarFighterGameModeBase()
{
	/*UE_LOG(LogTemp, Warning, TEXT("Dentro de constructor en GameModeBase"));
	GetWorld()->SpawnActor<ANaveTerrestreEnemiga01>(FVector::ZeroVector, FRotator::ZeroRotator);*/

	//SpawnNave<ANaveTerrestreEnemiga01>();

}

void AStarFighterGameModeBase::SpawnNave()
{
	UE_LOG(LogTemp, Warning, TEXT("aparecio una Naveacuatica"));
	UWorld* const World = GetWorld();

	
	ejeX = rand() % 2000 + 1;
	ejeY = rand() % 2000 + 1;

	World->SpawnActor<ANaveAcuatica>(FVector(ejeX, ejeY, 112.0f), FRotator::ZeroRotator);//me crea una NaveAcuatica en un cierto lugar aleatorio

}

void AStarFighterGameModeBase::SpawnCapsulas()
{


	UWorld* const World = GetWorld();


	PejeX = rand() %700 -500;


	World->SpawnActor<AInventoryActor>(FVector(900, PejeX, 112.0f), FRotator::ZeroRotator);
}

