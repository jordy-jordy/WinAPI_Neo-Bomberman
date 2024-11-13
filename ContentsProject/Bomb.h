#pragma once
#include <EngineCore/Actor.h>


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

	float FrameSpeed = 0.12f;


};

