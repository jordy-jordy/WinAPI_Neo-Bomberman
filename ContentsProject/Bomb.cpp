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

	SpriteRenderer->CreateAnimation("Bomb_Center",   "01_Bomb_01_Center",     0, 19, 0.2f);
	SpriteRenderer->CreateAnimation("Bomb_Up",       "01_Bomb_02_Up",         0, 19, 0.2f);
	SpriteRenderer->CreateAnimation("Bomb_UpMid",    "01_Bomb_03_UpMid",      0, 19, 0.2f);
	SpriteRenderer->CreateAnimation("Bomb_Down",     "01_Bomb_04_Down",       0, 19, 0.2f);
	SpriteRenderer->CreateAnimation("Bomb_DownMid",  "01_Bomb_05_DownMid",    0, 19, 0.2f);
	SpriteRenderer->CreateAnimation("Bomb_Left",     "01_Bomb_06_Left",       0, 19, 0.2f);
	SpriteRenderer->CreateAnimation("Bomb_LeftMid",  "01_Bomb_07_LeftMid",    0, 19, 0.2f);
	SpriteRenderer->CreateAnimation("Bomb_Right",    "01_Bomb_08_Right",      0, 19, 0.2f);
	SpriteRenderer->CreateAnimation("Bomb_RightMid", "01_Bomb_09_RightMid",   0, 19, 0.2f);

}

ABomb::~ABomb()
{
	ClearBombTile(); // 소멸자에서 타일맵 업데이트
}

void ABomb::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);
    ReleaseCheck(_DeltaTime);
}

void ABomb::SetWallTileMap(ATileMap* _TileMap, FIntPoint _Index)
{
    WallTileMap = _TileMap;
    BombTileIndex = _Index;
}

void ABomb::StartDestroyTimer()
{
    IsDeathTimeCheck = true;
}

void ABomb::ReleaseCheck(float _DeltaTime)
{
    if (!IsDeathTimeCheck)
    {
        return;
    }

    CurDeathTime += _DeltaTime;

    if (CurDeathTime >= DeathTime)
    {
        ClearBombTile(); // 폭탄 제거 전 타일맵 업데이트
        Destroy();
    }
}

void ABomb::ClearBombTile()
{
    if (WallTileMap != nullptr)
    {
        WallTileMap->SetBomb(BombTileIndex, nullptr); // 폭탄 포인터를 nullptr로 설정
    }
}