#pragma once
#include "Monster.h"

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

	void SetWallTileMap(class ATileMap* _TileMap) override
	{
		WallTileMap = _TileMap;
	}

protected:
	class USpriteRenderer* SpriteRenderer = nullptr;


private:
	class ATileMap* WallTileMap = nullptr;

};
