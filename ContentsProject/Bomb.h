#pragma once
#include <EngineCore/Actor.h>


enum class BombState
{
	Idle_Bomb = 0,
	Start_Exploding = 1,
	Running_Exploding = 2,
	End_Exploding = 3,
	Over = 4

};

class ABomb : public AActor
{
public:
	// constrcuter destructer
	ABomb();
	~ABomb();

	// delete Function
	ABomb(const ABomb& _Other) = delete;
	ABomb(ABomb&& _Other) noexcept = delete;
	ABomb& operator=(const ABomb& _Other) = delete;
	ABomb& operator=(ABomb&& _Other) noexcept = delete;

	class USpriteRenderer* SpriteRenderer;

	void SetWallTileMap(class ATileMap* _TileMap)
	{
		WallTileMap = _TileMap;
	}


protected:
	void Tick(float _DeltaTime) override;

private:
	class ATileMap* WallTileMap = nullptr;

};

