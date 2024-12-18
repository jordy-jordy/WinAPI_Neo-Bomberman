#pragma once
#include <EngineCore/Actor.h>
#include <EnginePlatform/EngineSound.h>

#include <list>


enum class EDirection
{
	Left,
	Right,
	Up,
	Down
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

	void HandleExplosion(EDirection Direction, int Power);
	void HandleTileDestruction(const FVector2D& TargetPosition);
	void CheckMonstersInExplosionRange(const std::list<class AMonster*>& AllMonsters, const FVector2D& TargetPos, ATileMap* WallTileMap);


protected:
	friend class APlayer;
	void Tick(float _DeltaTime) override;

	void SetPower(int _Power)
	{
		CurBombPower = _Power;
	}

	void Bomb_ExPlode();
	void Bomb_Destroy();


private:
	class USpriteRenderer* Explode_Center = nullptr;
	class ATileMap* WallTileMap = nullptr;
	class ATile_Destroy* Object = nullptr;
	FIntPoint BombTileIndex;

	void ClearBombTile(); // ÆøÅº Á¦°Å ÀüÈÄ Å¸ÀÏ¸Ê ¾÷µ¥ÀÌÆ®

	int CurBombPower = 0; // ÇöÀç ÆøÅºÀÇ ÆÄ¿ö

	float Bomb_Explode_Time = 2.0f;

	float IdleFrameSpeed = 0.15f;
	float ExplodeFrameSpeed = 0.05f;

	bool ISEXPLODING = false;

	class USoundPlayer SOUND_PLACEBOMB;
	bool ON_SOUND_PLACEBOMB = false;

	class USoundPlayer SOUND_BOMBEXPLODE;
	bool ON_SOUND_SOUND_BOMBEXPLODE = false;

	float SoundVolume = 1.0f;

};

