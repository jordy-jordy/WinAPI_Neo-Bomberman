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
	SpriteRenderer->CreateAnimation("Bomb_Up", "01_Bomb_02_Up", 0, 19, 0.2f);
	SpriteRenderer->CreateAnimation("Bomb_UpMid", "01_Bomb_03_UpMid", 0, 19, 0.2f);
	SpriteRenderer->CreateAnimation("Bomb_Down", "01_Bomb_04_Down", 0, 19, 0.2f);
	SpriteRenderer->CreateAnimation("Bomb_DownMid", "01_Bomb_05_DownMid", 0, 19, 0.2f);
	SpriteRenderer->CreateAnimation("Bomb_Left", "01_Bomb_06_Left", 0, 19, 0.2f);
	SpriteRenderer->CreateAnimation("Bomb_LeftMid", "01_Bomb_07_LeftMid", 0, 19, 0.2f);
	SpriteRenderer->CreateAnimation("Bomb_Right", "01_Bomb_08_Right", 0, 19, 0.2f);
	SpriteRenderer->CreateAnimation("Bomb_RightMid", "01_Bomb_09_RightMid", 0, 19, 0.2f);

	SpriteRenderer->SetOrder(ERenderOrder::BOMB);
}

ABomb::~ABomb()
{
	ClearBombTile(); // 소멸자에서 타일맵 업데이트
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
		SpriteRenderer->ChangeAnimation("Bomb_Center"); // 폭발 애니메이션으로 변경

		StartDestroyTimer(); // 폭탄 제거 타이머 ON
		Bomb_Destroy(_DeltaTime); // 폭탄 제거 함수 실행
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
		ClearBombTile(); // 폭탄 제거 전 타일맵 업데이트
		Destroy(); // 폭탄 제거
	}
}

void ABomb::ClearBombTile()
{
	if (WallTileMap != nullptr)
	{
		WallTileMap->SetBomb(BombTileIndex, nullptr); // 폭탄 포인터를 nullptr로 설정
	}
}