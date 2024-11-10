#include "PreCompile.h"
#include "Player.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EnginePlatform/EngineInput.h>

#include "Bomb.h"
#include "ATileMap.h"

void APlayer::RunSoundPlay()
{
	// UEngineDebug::OutPutString("SoundPlay");
}

APlayer::APlayer()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("01_Mushroom_00_Idle");
		SpriteRenderer->SetComponentScale({ 38, 42 });
		SpriteRenderer->SetPivotType(PivotType::MidBot);

		SpriteRenderer->CreateAnimation("Mush_Idle",  "01_Mushroom_00_Idle",  0,  1, 0.1f);
		SpriteRenderer->CreateAnimation("Mush_Left",  "01_Mushroom_01_Left",  0,  5, 0.1f);
		SpriteRenderer->CreateAnimation("Mush_Right", "01_Mushroom_02_Right", 0,  5, 0.1f);
		SpriteRenderer->CreateAnimation("Mush_Up",    "01_Mushroom_03_Up",    0,  5, 0.1f);
		SpriteRenderer->CreateAnimation("Mush_Down",  "01_Mushroom_04_Down",  0,  5, 0.1f);
		SpriteRenderer->CreateAnimation("Mush_Uniq",  "01_Mushroom_05_Uniq",  0, 10, 0.1f);

		std::string Name = SpriteRenderer->GetCurSpriteName();
	}
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	ChangeState(PlayerState::Idle);
}

FVector2D APlayer::PosToTileIndex(FVector2D _Pos)
{
	FVector2D Location = _Pos;
	FIntPoint Index = WallTileMap->LocationToIndex(Location);
	FVector2D InvertResult = {Index.X, Index.Y};
	return InvertResult;
}

FVector2D APlayer::IndexToTilePos(FVector2D _Index)
{
	FIntPoint Index = { static_cast<int>(_Index.X), static_cast<int>(_Index.Y) };
	FVector2D Location = WallTileMap->IndexToTileLocation(Index);
	return Location;
}

// 폭탄 설치
void APlayer::PlaceBomb(float _DeltaTime)
{
	FVector2D Location = GetActorLocation();
	FVector2D index = PosToTileIndex(Location);
	FVector2D Pos = IndexToTilePos(index);
	FVector2D HalfTiles = WallTileMap->GetTileHalfSize();

	FIntPoint TileIndex =  WallTileMap->LocationToIndex(Location);

	// 폭탄 설치 가능 여부 재확인
	if (WallTileMap->IsBomb(TileIndex))
	{
		return; // 이미 폭탄이 설치된 경우
	}

	ABomb* Bomb = GetWorld()->SpawnActor<ABomb>();

	// 타일맵에 폭탄 세팅 (연결)
	WallTileMap->SetBomb(TileIndex, Bomb);
	// 위치에 폭탄 설치
	Bomb->SetActorLocation(Pos + HalfTiles);

	Bomb->SetWallTileMap(WallTileMap, TileIndex); // 타일맵 정보 설정
	Bomb->StartExplodeTimer(); // 폭발 타이머 시작

	ChangeState(PlayerState::Idle);

}


void APlayer::ChangeState(PlayerState _CurPlayerState)
{
	switch (_CurPlayerState)
	{
	case PlayerState::Idle:
		IdleStart();
		break;
	case PlayerState::Move:
		MoveStart();
		break;
	default:
		break;
	}
	CurPlayerState = _CurPlayerState;
}

void APlayer::IdleStart()
{
	SpriteRenderer->ChangeAnimation("Mush_Idle");
}

void APlayer::MoveStart()
{
}

void APlayer::Idle(float _DeltaTime)
{
	SpriteRenderer->ChangeAnimation("Mush_Idle");

	if (true == UEngineInput::GetInst().IsPress('A') ||
		true == UEngineInput::GetInst().IsPress('D') ||
		true == UEngineInput::GetInst().IsPress('W') ||
		true == UEngineInput::GetInst().IsPress('S'))
	{
		ChangeState(PlayerState::Move);
		return;
	}

}

void APlayer::Move(float _DeltaTime)
{
	FVector2D Vector = FVector2D::ZERO;
	int Temp = 0;

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		Vector = FVector2D::RIGHT;
		SpriteRenderer->ChangeAnimation("Mush_Right");
		Temp = 1;
	}
	else if (true == UEngineInput::GetInst().IsPress('A'))
	{
		Vector = FVector2D::LEFT;
		SpriteRenderer->ChangeAnimation("Mush_Left");
		Temp = 2;
	}
	else if (true == UEngineInput::GetInst().IsPress('S'))
	{
		Vector = FVector2D::DOWN;
		SpriteRenderer->ChangeAnimation("Mush_Down");
		Temp = 3;
	}
	else if (true == UEngineInput::GetInst().IsPress('W'))
	{
		Vector = FVector2D::UP;
		SpriteRenderer->ChangeAnimation("Mush_Up");
		Temp = 4;
	}


	if (false == UEngineInput::GetInst().IsPress('A') &&
		false == UEngineInput::GetInst().IsPress('D') &&
		false == UEngineInput::GetInst().IsPress('W') &&
		false == UEngineInput::GetInst().IsPress('S'))
	{
		ChangeState(PlayerState::Idle);
		Vector = FVector2D::ZERO;
		return;
	}

	FVector2D PlusPos = Vector;
	switch (Temp)
	{
	case 1: PlusPos *= 16.0f; break;
	case 2: PlusPos *= 16.0f; break;
	case 3: PlusPos *= 12.0f; break;
	case 4: PlusPos *= 19.0f; break;
	default: break;
	}

	FVector2D TileSize = WallTileMap->GetTileSize(); // 32
	FVector2D LocalLocation = GetActorLocation() - WallTileMap->GetActorLocation(); // 타일맵 기준으로 변경
	FVector2D NextLocalLocation = LocalLocation + PlusPos + (Vector * _DeltaTime* Speed); // 플레이어 피봇에 더해지는 크기
	UEngineDebug::CoreOutPutString("NextLocalLocation : " + NextLocalLocation.ToString());


	FVector2D CurTileIndex = PosToTileIndex(LocalLocation); 
	UEngineDebug::CoreOutPutString("CurTileIndex : " + CurTileIndex.ToString());

	FVector2D NextTileIndex = PosToTileIndex(NextLocalLocation);
	UEngineDebug::CoreOutPutString("NextTileIndex : " + NextTileIndex.ToString());


	// 타일 사이즈를 나눠서 타일 인덱스 도출
	FVector2D LocationAtIndex = LocalLocation / TileSize; // 플레이어 위치를 타일맵 인덱스로 보기 위함
	UEngineDebug::CoreOutPutString("LocationAtIndex : " + LocationAtIndex.ToString());
	FVector2D NextLocationAtIndex = NextLocalLocation / TileSize; // 플레이어가 이동하는 방향의 타일맵 인덱스
	UEngineDebug::CoreOutPutString("NextLocationAtIndex : " + NextLocationAtIndex.ToString());

	Tile* TileData = WallTileMap->GetTileRef(NextLocalLocation);

	if (NextLocationAtIndex.X < 0 || NextLocationAtIndex.Y < 0 || NextLocationAtIndex.X > 13 || NextLocationAtIndex.Y > 11)
	{
		return;
	}
	if (TileData->SpriteIndex != 2 && TileData->SpriteIndex != 1)
	{
		AddActorLocation(Vector * _DeltaTime * Speed);
	}
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
	//FVector2D LocalLocation = GetActorLocation() - WallTileMap->GetActorLocation();

	//UEngineDebug::CoreOutPutString("GetActorLocation() : " + GetActorLocation().ToString());

	//UEngineDebug::CoreOutPutString("LocalLocation : " + LocalLocation.ToString());


	switch (CurPlayerState)
	{
	case PlayerState::Idle:
		Idle(_DeltaTime);
		break;
	case PlayerState::Move:
		Move(_DeltaTime);
		break;
	default:
		break;
	}
	
	if (true == UEngineInput::GetInst().IsDown('F'))
	{
		FVector2D LocalLocation = GetActorLocation() - WallTileMap->GetActorLocation();
		FIntPoint CurTileIndex = WallTileMap->LocationToIndex(LocalLocation);

		if (false == WallTileMap->IsBomb(CurTileIndex))
		{
			PlaceBomb(_DeltaTime);
		}
	}


	SpriteRenderer->SetOrder(GetActorLocation().Y - WallTileMap->GetActorLocation().Y);

	if (nullptr == WallTileMap)
	{
		MSGASSERT("타일 맵이 세팅되지 않았습니다.")
	}
}

void APlayer::LevelChangeStart()
{
	Super::LevelChangeStart();
}

void APlayer::LevelChangeEnd()
{
	Super::LevelChangeEnd();
}

