#include "PreCompile.h"
#include "Bomb.h"

#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>

#include "ATileMap.h"


ABomb::ABomb()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("01_Bomb_00_Idle");
	SpriteRenderer->SetComponentScale({ 32, 32 });

	SpriteRenderer->CreateAnimation("Bomb_Idle", "01_Bomb_00_Idle", { 0, 1, 2, 1 }, { 0.2f, 0.2f ,0.2f ,0.2f });
	SpriteRenderer->ChangeAnimation("Bomb_Idle");

	SpriteRenderer->CreateAnimation("Bomb_Center", "01_Bomb_01_Center", 0, 19, 0.2f);

	Explode_Up = CreateDefaultSubObject<USpriteRenderer>();
	Explode_Up->SetSprite("01_Bomb_02_Up");
	Explode_Up->CreateAnimation("Bomb_Up", "01_Bomb_02_Up", 0, 19, 0.2f);
	Explode_Up->SetComponentScale({ 32, 32 });
	Explode_Up->SetComponentLocation({ 0, -32 });

	Explode_Left = CreateDefaultSubObject<USpriteRenderer>();
	Explode_Left->SetSprite("01_Bomb_06_Left");
	Explode_Left->CreateAnimation("Bomb_Left", "01_Bomb_06_Left", 0, 19, 0.2f);
	Explode_Left->SetComponentScale({ 32, 32 });
	Explode_Left->SetComponentLocation({ -32, 0 });

	Explode_Down = CreateDefaultSubObject<USpriteRenderer>();
	Explode_Down->SetSprite("01_Bomb_04_Down");
	Explode_Down->CreateAnimation("Bomb_Down", "01_Bomb_04_Down", 0, 19, 0.2f);
	Explode_Down->SetComponentScale({ 32, 32 });
	Explode_Down->SetComponentLocation({ 0, 32 });

	Explode_Right = CreateDefaultSubObject<USpriteRenderer>();
	Explode_Right->SetSprite("01_Bomb_08_Right");
	Explode_Right->CreateAnimation("Bomb_Right", "01_Bomb_08_Right", 0, 19, 0.2f);
	Explode_Right->SetComponentScale({ 32, 32 });
	Explode_Right->SetComponentLocation({ 32, 0 });


	//Explode_Up_Mid->CreateAnimation("Bomb_UpMid", "01_Bomb_03_UpMid", 0, 19, 0.2f);
	//Explode_Left_Mid->CreateAnimation("Bomb_LeftMid", "01_Bomb_07_LeftMid", 0, 19, 0.2f);
	//Explode_Down_Mid->CreateAnimation("Bomb_DownMid", "01_Bomb_05_DownMid", 0, 19, 0.2f);
	//Explode_Right_Mid->CreateAnimation("Bomb_RightMid", "01_Bomb_09_RightMid", 0, 19, 0.2f);

	SpriteRenderer->SetOrder(ERenderOrder::BOMB);
}

ABomb::~ABomb()
{
	ClearBombTile(); // ¼Ò¸êÀÚ¿¡¼­ Å¸ÀÏ¸Ê ¾÷µ¥ÀÌÆ®
}

void ABomb::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Bomb_Explode(_DeltaTime);
}

void ABomb::SetWallTileMap(ATileMap* _TileMap, FIntPoint _Index)
{
	WallTileMap = _TileMap;
	BombTileIndex = _Index;
}


void ABomb::StartExplodeTimer()
{
	ExplodeTimer_On = true;
}


void ABomb::StartDestroyTimer()
{
	DestroyTimer_On = true;
}


void ABomb::Bomb_Explode(float _DeltaTime)
{
	if (true != ExplodeTimer_On)
	{
		return;
	}

	Explodecheck_Start_Timer += _DeltaTime;
	if (Explodecheck_Start_Timer >= Explode_Start_Time)
	{
		SpriteRenderer->ChangeAnimation("Bomb_Center"); // Æø¹ß ¾Ö´Ï¸ÞÀÌ¼ÇÀ¸·Î º¯°æ
		Explode_Up->ChangeAnimation("Bomb_Up");
		Explode_Left->ChangeAnimation("Bomb_Left");
		Explode_Down->ChangeAnimation("Bomb_Down");
		Explode_Right->ChangeAnimation("Bomb_Right");

		StartDestroyTimer(); // ÆøÅº Á¦°Å Å¸ÀÌ¸Ó ON
		Bomb_Destroy(_DeltaTime); // ÆøÅº Á¦°Å ÇÔ¼ö ½ÇÇà
	}
}

void ABomb::Bomb_Destroy(float _DeltaTime)
{
	if (true != DestroyTimer_On)
	{
		return;
	}

	Bomb_DestroyTimer += _DeltaTime;

	if (Bomb_DestroyTimer >= Bomb_DestroyTime)
	{
		ClearBombTile(); // ÆøÅº Á¦°Å Àü Å¸ÀÏ¸Ê ¾÷µ¥ÀÌÆ®
		Destroy(); // ÆøÅº Á¦°Å
	}
}

void ABomb::ClearBombTile()
{
	if (WallTileMap != nullptr)
	{
		WallTileMap->SetBomb(BombTileIndex, nullptr); // ÆøÅº Æ÷ÀÎÅÍ¸¦ nullptr·Î ¼³Á¤
	}
}