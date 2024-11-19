#include "PreCompile.h"
#include "Bomb.h"

#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>

#include "ATileMap.h"
#include "Tile_Destroy.h"
#include "Mushroom.h"


ABomb::ABomb()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//SpriteRenderer->SetSprite("01_Bomb_00_Idle");
	SpriteRenderer->SetComponentScale({ 32, 32 });

	SpriteRenderer->CreateAnimation("Bomb_Idle", "01_Bomb_00_Idle", 0, 3, IdleFrameSpeed, true);
	SpriteRenderer->ChangeAnimation("Bomb_Idle");

	SpriteRenderer->CreateAnimation("Bomb_Gone", "01_Bomb_00_Idle", 4, 4, IdleFrameSpeed, false);

	SpriteRenderer->SetOrder(ERenderOrder::BOMB);
	TimeEventer.PushEvent(Bomb_Explode_Time, std::bind(&ABomb::Bomb_ExPlode, this), false, false);
}

ABomb::~ABomb()
{
	ClearBombTile(); // 소멸자에서 타일맵 업데이트
}

void ABomb::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Bomb_Destroy();
}

void ABomb::SetWallTileMap(ATileMap* _TileMap, FIntPoint _Index)
{
	WallTileMap = _TileMap;
	BombTileIndex = _Index;
}

void ABomb::Bomb_Destroy()
{
	if (nullptr != Explode_Center)
	{
		if (true == Explode_Center->IsCurAnimationEnd())
		{
			// 폭탄 제거
			Destroy();
		}
	}
}

void ABomb::ClearBombTile()
{
	if (WallTileMap != nullptr)
	{
		WallTileMap->SetBomb(BombTileIndex, nullptr); // 폭탄 포인터를 nullptr로 설정
	}
}

void ABomb::HandleExplosion(EDirection Direction, int Power)
{
	FVector2D DirectionVector;
	std::string MidSpriteName;
	std::string EndSpriteName;

	// 방향별 설정
	switch (Direction)
	{
	case EDirection::Left:
		DirectionVector = { -32, 0 };
		MidSpriteName = "ExplodeLeftMid.png";
		EndSpriteName = "ExplodeLeft.png";
		break;
	case EDirection::Right:
		DirectionVector = { 32, 0 };
		MidSpriteName = "ExplodeRightMid.png";
		EndSpriteName = "ExplodeRight.png";
		break;
	case EDirection::Up:
		DirectionVector = { 0, -32 };
		MidSpriteName = "ExplodeUpMid.png";
		EndSpriteName = "ExplodeUp.png";
		break;
	case EDirection::Down:
		DirectionVector = { 0, 32 };
		MidSpriteName = "ExplodeDownMid.png";
		EndSpriteName = "ExplodeDown.png";
		break;
	}

	FVector2D BombPos_Location = GetActorLocation() - WallTileMap->GetActorLocation(); // 폭발 중심 계산

	// 현재 스폰되어 있는 모든 몬스터를 가져옴
	std::list <AMonster*> AllMonsters;
	AllMonsters = GetWorld()->GetActorsFromClass<AMonster>();

	int SpreadCount = 0;
	for (int i = 1; i <= Power - 1; ++i)
	{
		FVector2D TilePos_Location = DirectionVector * static_cast<float>(i);
		FVector2D TargetPos = BombPos_Location + TilePos_Location;

		Tile* TargetTile = WallTileMap->GetTileRef(TargetPos - WallTileMap->GetTileHalfSize());
		if (TargetTile == nullptr || TargetTile->SpriteIndex == 2) // 장애물이나 끝
		{
			break;
		}

		USpriteRenderer* Explode_Mid = CreateDefaultSubObject<USpriteRenderer>();
		Explode_Mid->CreateAnimation("Bomb_Mid", MidSpriteName.c_str(), 0, 19, ExplodeFrameSpeed, false);
		Explode_Mid->ChangeAnimation("Bomb_Mid");
		Explode_Mid->SetComponentScale({ 32, 32 });
		Explode_Mid->SetComponentLocation(TilePos_Location);
		FVector2D ExplodePos = BombPos_Location + Explode_Mid->GetComponentLocation();
		FIntPoint TilePos_INDEX = WallTileMap->LocationToIndex(ExplodePos);
		FIntPoint bbb = WallTileMap->LocationToIndex(ExplodePos);


		// iterator로 순회 돌림
		std::list<AMonster*>::iterator StartIter = AllMonsters.begin();
		std::list<AMonster*>::iterator EndIter = AllMonsters.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AMonster* CurMonster = *StartIter;

			FIntPoint MonsterINDEX = CurMonster->GetMonsterPos_INDEX(CurMonster->GetActorLocation(), WallTileMap);
			FIntPoint TilePos_INDEX = WallTileMap->LocationToIndex(TargetPos);
			int a = 0;

			if (MonsterINDEX == TilePos_INDEX)
			{
				CurMonster->Destroy();
			}
		}

		if (TargetTile->SpriteIndex == 1) // 파괴 가능한 타일
		{
			HandleTileDestruction(TargetPos);
			break;
		}

		SpreadCount = i;
	}

	// 마지막 스프라이트 처리
	FVector2D TilePos_Location = DirectionVector * static_cast<float>(SpreadCount + 1);
	FVector2D TargetPos = BombPos_Location + TilePos_Location;

	Tile* FinalTile = WallTileMap->GetTileRef(TargetPos - WallTileMap->GetTileHalfSize());
	if (FinalTile && FinalTile->SpriteIndex != 2)
	{
		USpriteRenderer* Explode_End = CreateDefaultSubObject<USpriteRenderer>();
		Explode_End->CreateAnimation("Bomb_End", EndSpriteName.c_str(), 0, 19, ExplodeFrameSpeed, false);
		Explode_End->ChangeAnimation("Bomb_End");
		Explode_End->SetComponentScale({ 32, 32 });
		Explode_End->SetComponentLocation(TilePos_Location);
		FVector2D ExplodePos = BombPos_Location + Explode_End->GetComponentLocation();
		FIntPoint TilePos_INDEX = WallTileMap->LocationToIndex(ExplodePos);

		// iterator로 순회 돌림
		std::list<AMonster*>::iterator StartIter = AllMonsters.begin();
		std::list<AMonster*>::iterator EndIter = AllMonsters.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AMonster* CurMonster = *StartIter;

			FIntPoint MonsterINDEX = CurMonster->GetMonsterPos_INDEX(CurMonster->GetActorLocation(), WallTileMap);
			FIntPoint TilePos_INDEX = WallTileMap->LocationToIndex(TargetPos);

			if (MonsterINDEX == TilePos_INDEX)
			{
				CurMonster->Destroy();
			}
		}

		if (FinalTile->SpriteIndex == 1)
		{
			HandleTileDestruction(TargetPos);
		}
	}
}

void ABomb::HandleTileDestruction(const FVector2D& TargetPos)
{
	WallTileMap->RemoveTile(TargetPos);
	FIntPoint TargetIndex = WallTileMap->LocationToIndex(TargetPos);

	ATile_Destroy* Object = GetWorld()->SpawnActor<ATile_Destroy>();
	WallTileMap->SetDestroyObject(TargetIndex, Object);
	Object->SetWallTileMap(WallTileMap, TargetIndex);
	Object->SetActorLocation(GetActorLocation() + (TargetPos - (GetActorLocation() - WallTileMap->GetActorLocation())));
}


void ABomb::Bomb_ExPlode()
{
	// 폭탄 중심 애니메이션 전환
	SpriteRenderer->ChangeAnimation("Bomb_Gone");

	// 폭발 중심 스프라이트 생성
	Explode_Center = CreateDefaultSubObject<USpriteRenderer>();
	Explode_Center->CreateAnimation("Bomb_Center", "ExplodeCenter.png", 0, 19, ExplodeFrameSpeed, false);
	Explode_Center->ChangeAnimation("Bomb_Center");
	Explode_Center->SetComponentScale({ 32, 32 });
	Explode_Center->SetComponentLocation({ 0, 0 });

	// 방향별로 폭발 처리
	HandleExplosion(EDirection::Left, CurBombPower);
	HandleExplosion(EDirection::Right, CurBombPower);
	HandleExplosion(EDirection::Up, CurBombPower);
	HandleExplosion(EDirection::Down, CurBombPower);
}

