#pragma once
#include "Monster.h"

#include "ATileMap.h"
#include <EngineBase/EngineRandom.h>


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

	void DIR_ANIM(FVector2D _Dir);

	void UNIQ_SKILL();

	float GET_RANDOM_TIME();
	FVector2D GET_RANDOM_DIR();


	bool BOMBBOMB(FVector2D _NEXTPOS);


	std::string NAME_CHECK();


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

	FVector2D TEMP_ZERO = { 0 , 0 };
	FVector2D TEMP_UP = { 0, -17 };
	FVector2D TEMP_DOWN = { 0, 17 };
	FVector2D TEMP_LEFT = { -17, 0 };
	FVector2D TEMP_RIGHT = { 17, 0 };

	std::string ANIMNAME;

	float RandomTime = 0.0f;
	float MIN_TIME = 5.0f;
	float MAX_TIME = 10.0f;

	bool UNIQUE_ON = false;

	bool BOMBCHECK;

};
