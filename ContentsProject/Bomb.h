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

	void SetWallTileMap(class ATileMap* _TileMap, FIntPoint _Index);

	void StartDestroyTimer();

protected:
	void Tick(float _DeltaTime) override;
	void ReleaseCheck(float _DeltaTime);

private:
	class ATileMap* WallTileMap = nullptr;
	FIntPoint BombTileIndex;

	bool IsDeathTimeCheck = false;
	float DeathTime = 2.0f; // 2초 후에 폭탄이 없어지도록 설정
	float CurDeathTime = 0.0f;

	void ClearBombTile(); // 폭탄 제거 후 타일맵 업데이트

};

