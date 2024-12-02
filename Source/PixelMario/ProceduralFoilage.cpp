#include "ProceduralFoilage.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/Engine.h"


AProceduralFoilage::AProceduralFoilage()
{
	PrimaryActorTick.bCanEverTick = true;

	InstancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
	InstancedStaticMeshComponent->SetupAttachment(RootComponent);

	InstancedStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	InstancedStaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	NumRows = 5;
	NumColumns = 5;

	StaticMesh = nullptr;
}

void AProceduralFoilage::BeginPlay()
{
	Super::BeginPlay();
}

void AProceduralFoilage::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called every frame
void AProceduralFoilage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AProceduralFoilage::SpawnFoilage()
{
	if (StaticMesh && InstancedStaticMeshComponent)
	{
		InstancedStaticMeshComponent->SetStaticMesh(StaticMesh);

		FVector StaticMeshBoxExtent = StaticMesh->GetBoundingBox().GetExtent();

		SpaceBetweenRow = StaticMeshBoxExtent.X;
		SpaceBetweenColumn = StaticMeshBoxExtent.Y;

		for (int Row = 1; Row <= NumRows; Row++)
		{
			for (int Col = 1; Col <= NumColumns; Col++)
			{
				FVector InstanceLocation = FVector(Row * SpaceBetweenRow, Col * SpaceBetweenColumn, 0);
				FTransform InstanceTransform(FRotator::ZeroRotator, InstanceLocation, FVector(1, 1, 1));
				InstancedStaticMeshComponent->AddInstance(InstanceTransform);
			}
		}
	}
}

void AProceduralFoilage::SetStaticMesh(UStaticMesh* InStaticMesh)
{
	StaticMesh = InStaticMesh;
}

UStaticMesh* AProceduralFoilage::GetStaticMesh()
{
	return StaticMesh;
}

void AProceduralFoilage::SetRowColumn(int InRow, int InColumn)
{
	NumRows = InRow;
	NumColumns = InColumn;
}
