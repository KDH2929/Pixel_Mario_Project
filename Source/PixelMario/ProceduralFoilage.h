#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralFoilage.generated.h"

UCLASS()
class PIXELMARIO_API AProceduralFoilage : public AActor
{
	GENERATED_BODY()

public:
	AProceduralFoilage();

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnFoilage();

	UFUNCTION(BlueprintCallable)
	void SetStaticMesh(UStaticMesh* InStaticMesh);

	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetStaticMesh();

	UFUNCTION(BlueprintCallable)
	void SetRowColumn(int InRow, int InColumn);


protected:

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* InstancedStaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumRows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumColumns;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float SpaceBetweenRow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float SpaceBetweenColumn;

};

