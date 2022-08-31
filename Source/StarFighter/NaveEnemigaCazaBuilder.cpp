// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveEnemigaCazaBuilder.h"
#include "Materials/Material.h"
#include "Engine/CollisionProfile.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ANaveEnemigaCazaBuilder::ANaveEnemigaCazaBuilder()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/*static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialMesh(TEXT("MaterialInterface'/Game/TwinStick/Meshes/OrangeMaterial.OrangeMaterial'"));


	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		FVector SpawnLocation = FVector(200.0f, -200.0f, 60.0f);
		FRotator SpawnRotator = FRotator(0.0f, -90.0f, 0.0f);

		NaveEnemiga = World->SpawnActor<ANaveEnemiga>(SpawnLocation, SpawnRotator);


		NaveEnemiga->GetShipMeshComponent()->SetMaterial(0, MaterialMesh.Object);

		NaveEnemiga->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

	}*/
	
}

// Called when the game starts or when spawned
void ANaveEnemigaCazaBuilder::BeginPlay()
{
	Super::BeginPlay();
	

	NaveEnemiga = GetWorld()->SpawnActor<ANaveEnemiga>(ANaveEnemiga::StaticClass());
	NaveEnemiga->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called every frame
void ANaveEnemigaCazaBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANaveEnemigaCazaBuilder::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANaveEnemigaCazaBuilder::BuildSistemaDefensa()
{
	if (!NaveEnemiga)
	{
		UE_LOG(LogTemp, Warning, TEXT("BuildSistemaDefensa(): NaveEnemiga es NULL, asegurese de inicializar correctamente esta clase"));
	}
	NaveEnemiga->SetSistemaDefensa("Sistema de Defensa NaVeEnemiga Caza");

}

void ANaveEnemigaCazaBuilder::BuildSistemaAtaque()
{
	if (!NaveEnemiga)
	{
		UE_LOG(LogTemp, Warning, TEXT("BuildSistemaDefensa(): NaveEnemiga es NULL, asegurese de inicializar correctamente esta clase"));
	}

	NaveEnemiga->SetSistemaAtaque("Sistema de ataque NaveEnemiga Caza");
}

void ANaveEnemigaCazaBuilder::BuildSistemaDesplazamiento()
{
	if (!NaveEnemiga)
	{
		UE_LOG(LogTemp, Warning, TEXT("BuildSistemaDefensa(): NaveEnemiga es NULL, asegurese de inicializar correctamente esta clase"));
	}

	NaveEnemiga->SetSistemaDesplazamiento("Sistema de Desplazamiento NaveEnemiga Caza");
}

void ANaveEnemigaCazaBuilder::BuildSistemaCamuflaje()
{
	if (!NaveEnemiga)
	{
		UE_LOG(LogTemp, Warning, TEXT("BuildSistemaDefensa(): NaveEnemiga es NULL, asegurese de inicializar correctamente esta clase"));
	}

	NaveEnemiga->SetSistemaCamuflaje("Sistema de camuflaje NaveEnemiga Caza");
}

ANaveEnemiga* ANaveEnemigaCazaBuilder::GetNaveEnemiga()
{
	return NaveEnemiga;
}

