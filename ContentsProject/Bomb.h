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

	void StartExplodeTimer();
	void StartDestroyTimer();

	void SetPower(int _Power);

protected:
	void Tick(float _DeltaTime) override;
	void Bomb_Explode(float _DeltaTime);
	void Bomb_Destroy(float _DeltaTime);

private:
	class ATileMap* WallTileMap = nullptr;
	FIntPoint BombTileIndex;

	bool ExplodeTimer_On = false;
	float Explode_Start_Time = 2.0f; // ÆøÅº ¼³Ä¡ ÈÄ 2ÃÊ µÚ¿¡ ÆøÅºÀÌ Æø¹ßÇÏµµ·Ï ¼³Á¤
	float Explodecheck_Start_Timer = 0.0f; // ÆøÅº Æø¹ß Å¸ÀÌ¸Ó

	bool DestroyTimer_On = false;
	float Bomb_DestroyTime = 3.0f; // ÆøÅºÀÌ ÅÍÁø ÈÄ 3.0ÃÊ µÚ¿¡ ÆøÅºÀÌ ¾ø¾îÁöµµ·Ï ¼³Á¤
	float Bomb_DestroyTimer = 0.0f; // ÆøÅº Á¦°Å Å¸ÀÌ¸Ó

	void ClearBombTile(); // ÆøÅº Á¦°Å ÀüÈÄ Å¸ÀÏ¸Ê ¾÷µ¥ÀÌÆ®

	int CurBombPower = 1; // ÇöÀç ÆøÅºÀÇ ÆÄ¿ö

	//// Æø¹ß ·»´õ·¯
	//class USpriteRenderer* Explode_Up = nullptr;
	//class USpriteRenderer* Explode_Left = nullptr;
	//class USpriteRenderer* Explode_Down = nullptr;
	//class USpriteRenderer* Explode_Right = nullptr;

	//class USpriteRenderer* Explode_Up_Mid = nullptr;
	//class USpriteRenderer* Explode_Left_Mid = nullptr;
	//class USpriteRenderer* Explode_Down_Mid = nullptr;
	//class USpriteRenderer* Explode_Right_Mid = nullptr;

	USpriteRenderer* Explode_Center;

	FIntPoint Explosion_Index_Up = { BombTileIndex.X, BombTileIndex.Y - 1 };
	FIntPoint Explosion_Index_Left = { BombTileIndex.X - 1, BombTileIndex.Y };
	FIntPoint Explosion_Index_Down = { BombTileIndex.X, BombTileIndex.Y + 1 };
	FIntPoint Explosion_Index_Right = { BombTileIndex.X + 1, BombTileIndex.Y };


};

