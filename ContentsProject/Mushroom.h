#pragma once
#include "Monster.h"

#include "ATileMap.h"

// Ό³Έν :
class AMushroom : public AMonster
{
public:
	// constrcuter destructer
	AMushroom();
	~AMushroom();

	// delete Function
	AMushroom(const AMushroom& _Other) = delete;
	AMushroom(AMushroom&& _Other) noexcept = delete;
	AMushroom& operator=(const AMushroom& _Other) = delete;
	AMushroom& operator=(AMushroom&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void Mush_Order();

	void SetWallTileMap(class ATileMap* _TileMap) override
	{
		WallTileMap = _TileMap;
	}

	void Mush_Move(float _DeltaTime);

	FVector2D InvertLOC(FVector2D _Loc);
	bool ISMOVE(FVector2D _NEXTPOS, Tile* _NEXTTILE);


protected:
	class USpriteRenderer* SpriteRenderer = nullptr;


private:
	class ATileMap* WallTileMap = nullptr;
	float Speed = 300.0f;

	FVector2D MoveTO = FVector2D::LEFT;

	int TILE_INDEX_MIN_X = 0;
	int TILE_INDEX_MAX_X = 13;
	int TILE_INDEX_MIN_Y = 0;
	int TILE_INDEX_MAX_Y = 11;

	FVector2D ZERO = { 0 , 0 };
	FVector2D UP = { 0, -17 };
	FVector2D DOWN = { 0, 17 };
	FVector2D LEFT = { -17, 0 };
	FVector2D RIGHT = { 17, 0 };

};
