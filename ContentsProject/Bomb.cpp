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
}

void ABomb::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}