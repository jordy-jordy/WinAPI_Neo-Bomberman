#pragma once
#include <EngineCore/Actor.h>

enum class MonsterDir
{
	ZERO,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

// Ό³Έν :
class AMonster : public AActor
{
public:
	// constrcuter destructer
	AMonster();
	~AMonster();

	// delete Function
	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

	virtual void SetWallTileMap(class ATileMap* _TileMap) = 0;
	virtual ATileMap* GetWallTileMap() = 0;

	FIntPoint GetMonsterPos_INDEX (FVector2D _CurPos, ATileMap* _Map);
	FVector2D GetMonsterPos_VECTOR(FVector2D _CurPos, ATileMap* _Map);

	FIntPoint GetNextIndex(FIntPoint _CurIndex, MonsterDir _TagetDir);
	FVector2D GetNextVector(FVector2D _CurPos, MonsterDir _TagetDir);

protected:
	void Tick(float _DeltaTime) override;


private:
	UEngineSprite* SpriteRenderer;
	ATileMap* WallTileMap;

	FIntPoint INDEX_ZERO = { 0, 0 };
	FIntPoint INDEX_UP     = { 0, -1 };
	FIntPoint INDEX_DOWN   = { 0, 1 };
	FIntPoint INDEX_LEFT   = { -1 , 0 };
	FIntPoint INDEX_RIGHT  = { 1, 0 };

	FVector2D VECTOR_ZERO = { 0, 0 };
	FVector2D VECTOR_UP    = { 0, -32 };
	FVector2D VECTOR_DOWN  = { 0, 32 };
	FVector2D VECTOR_LEFT  = { -32, 0 };
	FVector2D VECTOR_RIGHT = { 32, 0 };

	


};
