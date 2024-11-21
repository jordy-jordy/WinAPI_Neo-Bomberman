#pragma once
#include "Monster.h"

#include <EngineBase/EngineRandom.h>

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

	ATileMap* GetWallTileMap() override
	{
		return WallTileMap;
	}


	void Mush_Move(float _DeltaTime);

	FVector2D InvertLOC(FVector2D _Loc);
	bool ISMOVE(FVector2D _NEXTPOS, Tile* _NEXTTILE);

	void DIR_ANIM(FVector2D _Dir);

	void UNIQ_SKILL();

	FVector2D GET_RANDOM_DIR();

	bool BOMBBOMB(FVector2D _NEXTPOS);

	void RemoveMushroom();

	std::string NAME_CHECK();

	int getRandomValue(int _MaxDelay, UEngineRandom& _randomEngine);



protected:
	class USpriteRenderer* SpriteRenderer = nullptr;
	class USpriteRenderer* UniqueRenderer = nullptr;


private:
	class ATileMap* WallTileMap = nullptr;
	float Speed = 80.0f;

	FVector2D MoveTO = FVector2D::LEFT;
	FVector2D RANDOM_DIR;

	int TILE_INDEX_MIN_X = 0;
	int TILE_INDEX_MAX_X = 13;
	int TILE_INDEX_MIN_Y = 0;
	int TILE_INDEX_MAX_Y = 11;

	FVector2D CUSTOM_VECTOR_ZERO = { 0 , 0 };
	FVector2D CUSTOM_VECTOR_UP = { 0, -17 };
	FVector2D CUSTOM_VECTOR_DOWN = { 0, 17 };
	FVector2D CUSTOM_VECTOR_LEFT = { -17, 0 };
	FVector2D CUSTOM_VECTOR_RIGHT = { 17, 0 };

	std::string ANIMNAME;

	float MAX_TIME = 2.0f;
	int MAXDELAY = 2;


	bool UNIQUE_ON = false;

	bool BOMBCHECK;

	float elapsedTime = 0.0f;

};
