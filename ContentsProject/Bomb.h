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

	void SetPower(int _Power);
	void Bomb_Destroy();

private:
	class ATileMap* WallTileMap = nullptr;
	FIntPoint BombTileIndex;

	void ClearBombTile(); // ÆøÅº Á¦°Å ÀüÈÄ Å¸ÀÏ¸Ê ¾÷µ¥ÀÌÆ®

	int CurBombPower = 0; // ÇöÀç ÆøÅºÀÇ ÆÄ¿ö

	float Bomb_Explode_Time = 2.0f;
	float Bomb_Explode_Timer = 0.0f;


	class USpriteRenderer* Explode_Center = nullptr;

	class FIntPoint Explosion_Index_Up = { BombTileIndex.X, BombTileIndex.Y - 1 };
	class FIntPoint Explosion_Index_Left = { BombTileIndex.X - 1, BombTileIndex.Y };
	class FIntPoint Explosion_Index_Down = { BombTileIndex.X, BombTileIndex.Y + 1 };
	class FIntPoint Explosion_Index_Right = { BombTileIndex.X + 1, BombTileIndex.Y };


};

