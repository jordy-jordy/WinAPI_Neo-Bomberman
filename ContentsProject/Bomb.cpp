#include "PreCompile.h"
#include "Bomb.h"

#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>

#include "ATileMap.h"
#include "Tile_Destroy.h"
#include "Mushroom.h"


// 방향 벡터와 스프라이트 이름을 static 변수로 정의
static std::vector<FVector2D> DirectionVectors = 
{
	{ -32, 0 },  // Left
	{ 32, 0 },   // Right
	{ 0, -32 },  // Up
	{ 0, 32 }    // Down
};

static std::vector<std::pair<std::string, std::string>> ExplosionSprites = 
{
	{"ExplodeLeftMid.png", "ExplodeLeft.png"},   // Left
	{"ExplodeRightMid.png", "ExplodeRight.png"}, // Right
	{"ExplodeUpMid.png", "ExplodeUp.png"},       // Up
	{"ExplodeDownMid.png", "ExplodeDown.png"}    // Down
};

ABomb::ABomb()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//SpriteRenderer->SetSprite("01_Bomb_00_Idle");
	SpriteRenderer->SetComponentScale({ 32, 32 });

	SpriteRenderer->CreateAnimation("Bomb_Idle", "01_Bomb_00_Idle", 0, 3, IdleFrameSpeed, true);
	SpriteRenderer->ChangeAnimation("Bomb_Idle");

	SpriteRenderer->CreateAnimation("Bomb_Gone", "01_Bomb_00_Idle", 4, 4, IdleFrameSpeed, false);

	TimeEventer.PushEvent(Bomb_Explode_Time, std::bind(&ABomb::Bomb_ExPlode, this), false, false);

	SOUND_PLACEBOMB = UEngineSound::Play("01Play_02_PlaceBomb.wav");
	SOUND_PLACEBOMB.SetVolume(SoundVolume * 3.0);
}

ABomb::~ABomb()
{
	ClearBombTile(); // 소멸자에서 타일맵 업데이트
}

void ABomb::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Bomb_Destroy();
	SpriteRenderer->SetOrder(GetActorLocation().Y - WallTileMap->GetActorLocation().Y);
}

void ABomb::CheckMonstersInExplosionRange(const std::list<AMonster*>& AllMonsters, const FVector2D& TargetPos, ATileMap* WallTileMap) 
{
	FIntPoint TilePos_INDEX = WallTileMap->LocationToIndex(TargetPos);

	for (auto StartIter = AllMonsters.begin(); StartIter != AllMonsters.end(); ++StartIter)
	{
		AMonster* CurMonster = *StartIter;
		if (!CurMonster)
			continue;

		FIntPoint MonsterINDEX = CurMonster->GetMonsterPos_INDEX(CurMonster->GetActorLocation(), WallTileMap);

		if (MonsterINDEX == TilePos_INDEX)
		{
			CurMonster->SWITCHDEAD(true);
		}
	}
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
	// Direction 처리 코드
	FVector2D DirectionVector = DirectionVectors[static_cast<int>(Direction)];
	std::string MidSpriteName = ExplosionSprites[static_cast<int>(Direction)].first;
	std::string EndSpriteName = ExplosionSprites[static_cast<int>(Direction)].second;

	// 스프라이트를 저장하는 벡터
	std::vector<USpriteRenderer*> ExplosionEffects;

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
		if (TargetTile == nullptr || TargetTile->SpriteIndex == 2 || TargetTile->SpriteIndex == 3)
		{
			break;
		}

		USpriteRenderer* Explode_Mid = CreateDefaultSubObject<USpriteRenderer>();
		Explode_Mid->CreateAnimation("Bomb_Mid", MidSpriteName.c_str(), 0, 19, ExplodeFrameSpeed, false);
		Explode_Mid->ChangeAnimation("Bomb_Mid");
		Explode_Mid->SetComponentScale({ 32, 32 });
		Explode_Mid->SetComponentLocation(TilePos_Location);
		Explode_Mid->SetOrder(ERenderOrder::BOMB);

		ExplosionEffects.push_back(Explode_Mid);

		// 몬스터 체크. iterator로 순회 돌림
		CheckMonstersInExplosionRange(AllMonsters, TargetPos, WallTileMap);

		if (TargetTile->Bomb != nullptr)
		{
			TargetTile->Bomb->Bomb_ExPlode();
		}

		SpreadCount = i;

		if (TargetTile->SpriteIndex == 1) // 파괴 가능한 타일
		{
			HandleTileDestruction(TargetPos);
			break;
		}
	}

	// 마지막 스프라이트 처리
	FVector2D TilePos_Location = DirectionVector * static_cast<float>(SpreadCount + 1);
	FVector2D TargetPos = BombPos_Location + TilePos_Location;

	Tile* FinalTile = WallTileMap->GetTileRef(TargetPos - WallTileMap->GetTileHalfSize());
	if (FinalTile && FinalTile->SpriteIndex != 2 && FinalTile->SpriteIndex != 3)
	{
		USpriteRenderer* Explode_End = CreateDefaultSubObject<USpriteRenderer>();
		Explode_End->CreateAnimation("Bomb_End", EndSpriteName.c_str(), 0, 19, ExplodeFrameSpeed, false);
		Explode_End->ChangeAnimation("Bomb_End");
		Explode_End->SetComponentScale({ 32, 32 });
		Explode_End->SetComponentLocation(TilePos_Location);
		Explode_End->SetOrder(ERenderOrder::BOMB);

		ExplosionEffects.push_back(Explode_End);

		// 몬스터 체크. iterator로 순회 돌림
		CheckMonstersInExplosionRange(AllMonsters, TargetPos, WallTileMap);

		if (FinalTile->Bomb != nullptr)
		{
			FinalTile->Bomb->Bomb_ExPlode();
		}

		if (FinalTile->SpriteIndex == 1)
		{
			HandleTileDestruction(TargetPos);
		}
	}

	//// 스프라이트 정리 (for 루프 사용)
	//for (size_t i = 0; i < ExplosionEffects.size(); ++i)
	//{
	//	if (ExplosionEffects[i] != nullptr)
	//	{
	//		ExplosionEffects[i]->Destroy();
	//	}
	//}

	//ExplosionEffects.clear();
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
	if (ISEXPLODING == true)
	{
		return; // 이미 폭발한 경우 실행하지 않음
	}
	ISEXPLODING = true;

	SOUND_BOMBEXPLODE = UEngineSound::Play("01Play_03_BombExplode.wav");
	SOUND_BOMBEXPLODE.SetVolume(SoundVolume + 3.0);


	// 폭탄 중심 애니메이션 전환
	SpriteRenderer->ChangeAnimation("Bomb_Gone");

	// 폭발 중심 스프라이트 생성
	Explode_Center = CreateDefaultSubObject<USpriteRenderer>();
	Explode_Center->CreateAnimation("Bomb_Center", "ExplodeCenter.png", 0, 19, ExplodeFrameSpeed, false);
	Explode_Center->ChangeAnimation("Bomb_Center");
	Explode_Center->SetComponentScale({ 32, 32 });
	Explode_Center->SetComponentLocation({ 0, 0 });
	Explode_Center->SetOrder(GetActorLocation().Y - WallTileMap->GetActorLocation().Y);

	// 방향별로 폭발 처리
	HandleExplosion(EDirection::Left, CurBombPower);
	HandleExplosion(EDirection::Right, CurBombPower);
	HandleExplosion(EDirection::Up, CurBombPower);
	HandleExplosion(EDirection::Down, CurBombPower);
}

