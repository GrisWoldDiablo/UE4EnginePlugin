// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCube.h"
#include <Components/StaticMeshComponent.h>

// Sets default values
AMyCube::AMyCube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void AMyCube::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyCube::OnConstruction(const FTransform& Transform)
{
	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, GetEnumAsString());
	switch (MaterialOptionsEnum)
	{
	case ESelectorEnum::VE_Option1:
		if (MatOption1 != nullptr)
		{
			StaticMesh->SetMaterial(0, MatOption1);
		}		
		break;
	case ESelectorEnum::VE_Option2:
		if (MatOption2 != nullptr)
		{
			StaticMesh->SetMaterial(0, MatOption2);
		}		
		break;
	case ESelectorEnum::VE_Option3:
		if (MatOption3 != nullptr)
		{
			StaticMesh->SetMaterial(0, MatOption3);
		}
		break;
	}
}

