// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "Misc/HierarchicalLogArchive.h"
#include "GameFramework/Info.h"

#include "WorldPartition.h"
#include "WorldPartition/DataLayer/DataLayersID.h"
#include "WorldPartition/HLOD/HLODLayer.h"
#include "WorldPartitionRuntimeHash.h"
#include "WorldPartitionRuntimeSpatialHashCell.h"
#include "WorldPartitionRuntimeSpatialHashGridPreviewer.h"
#include "WorldPartitionRuntimeSpatialHash.generated.h"

typedef UE::Math::TIntVector3<int64> FGridCellCoord;
typedef UE::Math::TIntVector2<int64> FGridCellCoord2;

USTRUCT()
struct FSpatialHashStreamingGridLayerCell
{
	GENERATED_USTRUCT_BODY()

	FSpatialHashStreamingGridLayerCell() = default;

	// Move constructor.
	FSpatialHashStreamingGridLayerCell(const FSpatialHashStreamingGridLayerCell& Other) = delete;
	FSpatialHashStreamingGridLayerCell(FSpatialHashStreamingGridLayerCell&& Other) = default;

	// Move assignment.
	FSpatialHashStreamingGridLayerCell& operator=(const FSpatialHashStreamingGridLayerCell& Other) = delete;
	FSpatialHashStreamingGridLayerCell& operator=(FSpatialHashStreamingGridLayerCell&& Other) = default;

	UPROPERTY()
	TArray<TObjectPtr<UWorldPartitionRuntimeSpatialHashCell>> GridCells;
};

// Disable copy of this USTRUCT by the autogenerated code.
template<> struct TStructOpsTypeTraits<FSpatialHashStreamingGridLayerCell> : public TStructOpsTypeTraitsBase2<FSpatialHashStreamingGridLayerCell> { enum { WithCopy = false }; };

/**
 * Represents a PIE/Game streaming grid level
 */
USTRUCT()
struct FSpatialHashStreamingGridLevel
{
	GENERATED_USTRUCT_BODY()

	FSpatialHashStreamingGridLevel() = default;

	// Move constructor.
	FSpatialHashStreamingGridLevel(const FSpatialHashStreamingGridLevel& Other) = delete;
	FSpatialHashStreamingGridLevel(FSpatialHashStreamingGridLevel&& Other) = default;

	// Move assignment.
	FSpatialHashStreamingGridLevel& operator=(const FSpatialHashStreamingGridLevel& Other) = delete;
	FSpatialHashStreamingGridLevel& operator=(FSpatialHashStreamingGridLevel&& Other) = default;

	/** 
	 * Represents the grid cells
	 */
	UPROPERTY()
	TArray<FSpatialHashStreamingGridLayerCell> LayerCells;

	/** 
	 * Represents the grid cells index mapping
	 */
	UPROPERTY()
	TMap<int64, int32> LayerCellsMapping;
};

// Disable copy of this USTRUCT by the autogenerated code.
template<> struct TStructOpsTypeTraits<FSpatialHashStreamingGridLevel> : public TStructOpsTypeTraitsBase2<FSpatialHashStreamingGridLevel> { enum { WithCopy = false }; };

struct FSquare2DGridHelper;

/**
 * Represents a PIE/Game streaming grid
 */
USTRUCT()
struct FSpatialHashStreamingGrid
{
	GENERATED_USTRUCT_BODY()

	FSpatialHashStreamingGrid();
	~FSpatialHashStreamingGrid();

	// Move constructor.
	FSpatialHashStreamingGrid(const FSpatialHashStreamingGrid& Other) = delete;
	FSpatialHashStreamingGrid(FSpatialHashStreamingGrid&& Other) = default;

	// Move assignment.
	FSpatialHashStreamingGrid& operator=(const FSpatialHashStreamingGrid& Other) = delete;
	FSpatialHashStreamingGrid& operator=(FSpatialHashStreamingGrid&& Other) = default;

	UPROPERTY()
	FName GridName;

	UPROPERTY()
	FVector Origin;

	UPROPERTY()
	int32 CellSize;

	UPROPERTY()
	float LoadingRange;

	UPROPERTY()
	bool bBlockOnSlowStreaming;

	UPROPERTY()
	FLinearColor DebugColor;

	UPROPERTY()
	TArray<FSpatialHashStreamingGridLevel> GridLevels;

	UPROPERTY()
	FBox WorldBounds;

	UPROPERTY()
	bool bClientOnlyVisible;

	UPROPERTY()
	TObjectPtr<const UHLODLayer> HLODLayer;

	float OverrideLoadingRange;

	float GetLoadingRange() const
	{
		if (OverrideLoadingRange >= 0.f)
		{
			return OverrideLoadingRange;
		}
		return LoadingRange;
	}

	// Used by PIE/Game
	int64 GetCellSize(int32 Level) const;
	void GetCells(const FWorldPartitionStreamingQuerySource& QuerySource, TSet<const UWorldPartitionRuntimeCell*>& OutCells, bool bEnableZCulling) const;
	void GetCells(const TArray<FWorldPartitionStreamingSource>& Sources, const class UDataLayerSubsystem* DataLayerSubsystem, UWorldPartitionRuntimeHash::FStreamingSourceCells& OutActivateCells, UWorldPartitionRuntimeHash::FStreamingSourceCells& OutLoadCells, bool bEnableZCulling) const;
	void GetAlwaysLoadedCells(const UDataLayerSubsystem* DataLayerSubsystem, TSet<const UWorldPartitionRuntimeCell*>& OutActivateCells, TSet<const UWorldPartitionRuntimeCell*>& OutLoadCells) const;
	void Draw2D(UCanvas* Canvas, UWorld* World, const TArray<FWorldPartitionStreamingSource>& Sources, const FBox& Region, const FBox2D& GridScreenBounds, TFunctionRef<FVector2D(const FVector2D&)> WorldToScreen) const;
	void Draw3D(UWorld* World, const TArray<FWorldPartitionStreamingSource>& Sources, const FTransform& Transform) const;

private:
	const FSpatialHashStreamingGridLayerCell* GetLayerCell(const FGridCellCoord& Coords) const;
	void DrawStreamingSource2D(UCanvas* Canvas, const FSphericalSector& Shape, TFunctionRef<FVector2D(const FVector2D&)> WorldToScreen, const FColor& Color) const;
	void DrawStreamingSource3D(UWorld* World, const FSphericalSector& Shape, const FTransform& Transform, const FColor& Color) const;
	void GetFilteredCellsForDebugDraw(const FSpatialHashStreamingGridLayerCell* LayerCell, const UDataLayerSubsystem* DataLayerSubsystem, TArray<const UWorldPartitionRuntimeCell*>& FilteredCells) const;
	const FSquare2DGridHelper& GetGridHelper() const;
	EWorldPartitionRuntimeCellVisualizeMode GetStreamingCellVisualizeMode() const;
	mutable FSquare2DGridHelper* GridHelper;
};

// Disable copy of this USTRUCT by the autogenerated code.
template<> struct TStructOpsTypeTraits<FSpatialHashStreamingGrid> : public TStructOpsTypeTraitsBase2<FSpatialHashStreamingGrid> { enum { WithCopy = false }; };

/**
 * Represents a runtime grid (editing)
 */
USTRUCT()
struct FSpatialHashRuntimeGrid
{
	GENERATED_USTRUCT_BODY()

	FSpatialHashRuntimeGrid()
#if WITH_EDITORONLY_DATA
		: CellSize(12800)
		, LoadingRange(25600)
		, bBlockOnSlowStreaming(false)
		, Priority(0)
		, DebugColor(FLinearColor::MakeRandomColor())
		, bClientOnlyVisible(false)
		, HLODLayer(nullptr)
#endif
	{}

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category=Settings)
	FName GridName;

	UPROPERTY(EditAnywhere, Category=Settings)
	int32 CellSize;

	UPROPERTY(EditAnywhere, Category=Settings)
	float LoadingRange;

	/** Should streaming block in situations where cells aren't getting loaded fast enough. */
	UPROPERTY(EditAnywhere, Category = Settings)
	bool bBlockOnSlowStreaming;

	UPROPERTY(EditAnywhere, Category=Settings)
	int32 Priority;

	UPROPERTY(EditAnywhere, Category=Settings, meta = (IgnoreForMemberInitializationTest))
	FLinearColor DebugColor;

	UPROPERTY()
	bool bClientOnlyVisible;

	UPROPERTY()
	TObjectPtr<const UHLODLayer> HLODLayer;
#endif
};

/**
 * Actor keeping information regarding a runtime grid
 */
UCLASS(NotPlaceable)
class ASpatialHashRuntimeGridInfo : public AInfo
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY()
	FSpatialHashRuntimeGrid	GridSettings;
};

UCLASS()
class URuntimeSpatialHashExternalStreamingObject : public URuntimeHashExternalStreamingObjectBase
{
	GENERATED_BODY()

public:
	//~ Begin URuntimeHashExternalStreamingObjectBase Interface
	virtual void OnStreamingObjectLoaded() override;

	virtual void ForEachStreamingCells(TFunctionRef<void(UWorldPartitionRuntimeCell&)> Func) override;

#if WITH_EDITOR
	virtual void PopulateGeneratorPackageForCook() override;
#endif
	//~ End URuntimeHashExternalStreamingObjectBase Interface

	UPROPERTY();
	TArray<FSpatialHashStreamingGrid> StreamingGrids;

private:
	UPROPERTY();
	TMap<FName, FName> CellToLevelStreamingPackage;
};

UCLASS()
class ENGINE_API UWorldPartitionRuntimeSpatialHash : public UWorldPartitionRuntimeHash
{
	GENERATED_UCLASS_BODY()

public:
	PRAGMA_DISABLE_DEPRECATION_WARNINGS // Suppress compiler warning on override of deprecated function
	UE_DEPRECATED(5.0, "Use version that takes FObjectPreSaveContext instead.")
	virtual void PreSave(const class ITargetPlatform* TargetPlatform) override;
	PRAGMA_ENABLE_DEPRECATION_WARNINGS
	virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void SetDefaultValues() override;
	virtual bool SupportsHLODs() const override { return true; }
	virtual bool PrepareGeneratorPackageForCook(TArray<UPackage*>& OutModifiedPackages) override;
	virtual bool PopulateGeneratorPackageForCook(const TArray<FWorldPartitionCookPackage*>& PackagesToCook, TArray<UPackage*>& OutModifiedPackage) override;
	virtual bool PopulateGeneratedPackageForCook(const FWorldPartitionCookPackage& PackageToCook, TArray<UPackage*>& OutModifiedPackages) override;
	virtual void FlushStreaming() override;
	virtual bool GenerateHLOD(ISourceControlHelper* SourceControlHelper, const IStreamingGenerationContext* StreamingGenerationContext, bool bCreateActorsOnly) override;
	virtual void DrawPreview() const override;

	virtual URuntimeHashExternalStreamingObjectBase* StoreToExternalStreamingObject(UObject* StreamingObjectOuter, FName StreamingObjectName) override;

	static FString GetCellNameString(FName InGridName, const FGridCellCoord& InCellGlobalCoord, const FDataLayersID& InDataLayerID, const FGuid& InContentBundleID);

	bool GetPreviewGrids() const;
	void SetPreviewGrids(bool bInPreviewGrids);
#endif

	// streaming interface
	virtual void ForEachStreamingCells(TFunctionRef<bool(const UWorldPartitionRuntimeCell*)> Func) const override;
	virtual void ForEachStreamingCellsQuery(const FWorldPartitionStreamingQuerySource& QuerySource, TFunctionRef<bool(const UWorldPartitionRuntimeCell*)> Func) const override;
	virtual void ForEachStreamingCellsSources(const TArray<FWorldPartitionStreamingSource>& Sources, TFunctionRef<bool(const UWorldPartitionRuntimeCell*, EStreamingSourceTargetState)> Func) const override;

	virtual bool InjectExternalStreamingObject(URuntimeHashExternalStreamingObjectBase* ExternalStreamingObject) override;
	virtual bool RemoveExternalStreamingObject(URuntimeHashExternalStreamingObjectBase* ExternalStreamingObject) override;

	uint32 GetNumGrids() const;

	static FString GetCellCoordString(const FGridCellCoord& InCellGlobalCoord);

protected:
	void ForEachStreamingGrid(TFunctionRef<void(FSpatialHashStreamingGrid&)> Func);
	void ForEachStreamingGridBreakable(TFunctionRef<bool(const FSpatialHashStreamingGrid&)> Func) const;
	void ForEachStreamingGrid(TFunctionRef<void(const FSpatialHashStreamingGrid&)> Func, bool bIncludeExternalStreamingObjects = true) const;

	virtual EWorldPartitionStreamingPerformance GetStreamingPerformanceForCell(const UWorldPartitionRuntimeCell* Cell) const override;

#if WITH_EDITOR
	virtual bool GenerateStreaming(class UWorldPartitionStreamingPolicy* StreamingPolicy, const IStreamingGenerationContext* StreamingGenerationContext, TArray<FString>* OutPackagesToGenerate = nullptr) override;
	virtual void DumpStateLog(FHierarchicalLogArchive& Ar) override;
#endif

private:
	/** Console command used to change loading range for a given streaming grid */
	static class FAutoConsoleCommand OverrideLoadingRangeCommand;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Config, Category = RuntimeSettings)
	TArray<FSpatialHashRuntimeGrid> Grids;

	/** Whether to preview runtime grids. */
	UPROPERTY(Transient)
	bool bPreviewGrids;

	UPROPERTY(Transient)
	mutable FWorldPartitionRuntimeSpatialHashGridPreviewer GridPreviewer;

	TMap<FString, UWorldPartitionRuntimeCell*> PackagesToGenerateForCook;
#endif

	/** Whether this hash enables Z culling. */
	UPROPERTY(EditAnywhere, Config, Category = RuntimeSettings)
	bool bEnableZCulling;

	/** 
	 * Represents the streaming grids (PIE or Game)
	 */
	UPROPERTY(NonPIEDuplicateTransient)
	TArray<FSpatialHashStreamingGrid> StreamingGrids;
	mutable TMap<FName, const FSpatialHashStreamingGrid*> NameToGridMapping;
	mutable bool bIsNameToGridMappingDirty;

	UPROPERTY(Transient)
	TArray<TWeakObjectPtr<URuntimeSpatialHashExternalStreamingObject>> ExternalStreamingObjects;
	
	virtual bool Draw2D(class UCanvas* Canvas, const TArray<FWorldPartitionStreamingSource>& Sources, const FVector2D& PartitionCanvasSize, const FVector2D& Offset, FVector2D& OutUsedCanvasSize) const override;
	virtual void Draw3D(const TArray<FWorldPartitionStreamingSource>& Sources) const override;
	virtual bool ContainsRuntimeHash(const FString& Name) const override;

private:
	void GetAlwaysLoadedStreamingCells(const FSpatialHashStreamingGrid& StreamingGrid, TSet<const UWorldPartitionRuntimeCell*>& Cells) const;
	void GetStreamingCells(const FVector& Position, const FSpatialHashStreamingGrid& StreamingGrid, TSet<const UWorldPartitionRuntimeCell*>& Cells) const;
	const TMap<FName, const FSpatialHashStreamingGrid*>& GetNameToGridMapping() const;
#if WITH_EDITOR
	TArray<UWorldPartitionRuntimeCell*> GetAlwaysLoadedCells() const;
	bool CreateStreamingGrid(const FSpatialHashRuntimeGrid& RuntimeGrid, const FSquare2DGridHelper& PartionedActors, UWorldPartitionStreamingPolicy* StreamingPolicy, TArray<FString>* OutPackagesToGenerate = nullptr);
#endif
	TArray<const FSpatialHashStreamingGrid*> GetFilteredStreamingGrids() const;

	friend class UWorldPartitionSubsystem;
};