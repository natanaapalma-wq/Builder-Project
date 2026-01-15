#pragma once

namespace grid_data {
  struct GridTile;
  struct GridEdge;
  struct GridCorner;
}

class BaseGridCalculator;

/**
 * GridTileData acts as the mathematical backbone of the grid system.
 *
 * Think of it as "grid space FMath" - providing both data storage
 * and computational utilities for all grid operations.
 *
 * This centralized approach ensures:
 * 1. Consistent grid mathematics across all subsystems
 * 2. Single source of truth for grid state
 * 3. Optimized performance through precomputed data
 * 4. Easier debugging and testing
 */
class GAMEBUILDMODE_API StorageGridData {
public:
  GridTileData(
    BaseGridCalculator* calculator,
    float floor_height,
    FIntPoint grid_size,
    FVector world_position,
    FRotator world_rotation
  );

  // ====================
  //       TILES
  // ====================
  grid_data::GridTile* Tile(const FIntPoint& tile_coord);

  bool IsValidTile(const FIntPoint& tile_coord);

  bool IsTileOccupied(const FIntPoint& tile_coord);

  void OccupyTile(const FIntPoint& tile_coord);

  int32 GetDiagonalWallType(const FIntPoint& tile_coord);

  void SetDiagonalWall(const FIntPoint& tile_coord, int32 wall_type);

  FIntPoint NeighborTile(const FIntPoint& tile_coord, int32 direction);

  int32 DirectionToDiagonalType(FIntPoint direction);

  // ====================
  //     TILE EDGES
  // ====================

  grid_data::GridEdge* Edge(const FIntPoint& edge_coord);

  TArray<FIntPoint> EdgeBetweenCorners(const FIntPoint& corner_a, const FIntPoint& corner_b);

  bool IsEdgeBlocked(const FIntPoint& edge_coord);

  bool EdgeHasWall(const FIntPoint& edge_coord);

  FIntPoint NeighborEdge(const FIntPoint& edge_coord, const FIntPoint& direction);

  void SetEdgeWallOccupation(const FIntPoint& edge_coord, bool has_wall);

  void SetEdgeObjectOccupation(const FIntPoint& edge_coord, bool has_object);

  // Gets a straight line with conected edges occupied by wall
  TArray<FIntPoint> LineWall(FIntPoint edgeID);

  TArray<FIntPoint> DiagonalLineWall(FIntPoint tileID);

  // ====================
  //     TILE CORNERS
  // ====================

  grid_data::GridCorner* Corner(const FIntPoint& corner_coord);

  bool IsValidCorner(const FIntPoint& corner_coord);

  FIntPoint NeighborCorner(const FIntPoint& corner_coord, const FIntPoint& direction);

  TArray<FIntPoint> EdgeCorners(const FIntPoint& edge_coord);


private:
  void InitializeTiles();
  void InitializeTileEdges();
  void InitializeTileCorners();

  //     --- GRID DEFINITIONS ---
  const BaseGridCalculator* kCalculate;
  const float kTileSize = 50.f;
  const float kHalfTileSize = 25.f;
  const FIntPoint kSize;
  const float kFloorHeight;
  const FVector kGridOffset;
  const FRotator kGridRotation;

  //           --- DATA ---
  TMap<FIntPoint, grid_data::GridTile> tiles_;
  TMap<FIntPoint, grid_data::GridEdge> edges_;
  TMap<FIntPoint, grid_data::GridCorner> corners_;
};



