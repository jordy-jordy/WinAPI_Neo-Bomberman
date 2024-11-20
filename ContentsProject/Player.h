#pragma once
#include <EngineCore/Actor.h>

enum class PlayerState
{
	Idle,
	Move,
	Idle_Anim
};

// 설명 :
class APlayer : public AActor
{
public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RunSoundPlay();

	void LevelChangeStart();
	void LevelChangeEnd();

	void SetWallTileMap(class ATileMap* _TileMap)
	{
		WallTileMap = _TileMap;
	}

	void SetBomb(class ABomb* _Bomb)
	{
		Bomb = _Bomb;
	}

	FVector2D PosToTileIndex(FVector2D _Pos);

	FVector2D InvertLOC(FVector2D _Dir);

protected:

private:
	float Speed = 300.0f;
	int MySpriteIndex = 0;
	int BOMBPOWER = 7;

	class USpriteRenderer* SpriteRendererHead = nullptr;
	class USpriteRenderer* SpriteRendererBody = nullptr;

	float IdleAnimTime = 2.0f; // 2초 동안 입력이 없으면 실행되는 Idle 애니메이션
	float IdleAnimTimer = 0.0f; // Idle 애니메이션 타이머

	PlayerState CurPlayerState = PlayerState::Idle;
	void ChangeState(PlayerState CurPlayerState);

	void Idle_Anim(float _DeltaTime);

	void IdleStart();
	void Idle(float _DeltaTime);
	void MoveStart();
	void Move(float _DeltaTime);
	void PlaceBomb(float _DeltaTime);

	class ATileMap* WallTileMap = nullptr;

	class ABomb* Bomb = nullptr;

	FVector2D CUSTOM_VECTOR_ZERO  = { 0, 0 };
	FVector2D CUSTOM_VECTOR_UP    = { 0, -32 };
	FVector2D CUSTOM_VECTOR_DOWN  = { 0, 32 };
	FVector2D CUSTOM_VECTOR_LEFT  = { -32, 0 };
	FVector2D CUSTOM_VECTOR_RIGHT = { 32, 0 };

	FIntPoint CUSTOM_INDEX_ZERO  = { 0, 0 };
	FIntPoint CUSTOM_INDEX_UP    = { 0, -1 };
	FIntPoint CUSTOM_INDEX_DOWN  = { 0, 1 };
	FIntPoint CUSTOM_INDEX_LEFT  = { -1, 0 };
	FIntPoint CUSTOM_INDEX_RIGHT = { 1, 0 };

};

