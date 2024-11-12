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
		SpriteRendererHead = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRendererHead->SetSprite("MainCharater_White.png");
		SpriteRendererHead->SetComponentLocation({ 0, 0 });
		SpriteRendererHead->SetComponentScale({ 64, 64 });
		SpriteRendererHead->SetPivotType(PivotType::Bot);

		SpriteRendererHead->CreateAnimation("Idle_Up_Head", "MainCharater_White.png", 17, 17, 0.1f);
		SpriteRendererHead->CreateAnimation("Run_Up_Head", "MainCharater_White.png", 18, 22 , 0.1f);

		SpriteRendererHead->CreateAnimation("Idle_Down_Head", "MainCharater_White.png", 0, 0, 0.1f);
		SpriteRendererHead->CreateAnimation("Run_Down_Head", "MainCharater_White.png", 1, 6, 0.1f);

		SpriteRendererHead->CreateAnimation("Idle_Left_Head", "MainCharater_White.png", 8, 8, 0.1f);
		SpriteRendererHead->CreateAnimation("Run_Left_Head", "MainCharater_White.png", 9, 14, 0.1f);

		SpriteRendererHead->CreateAnimation("Idle_Right_Head", "MainCharater_White.png", 24, 24, 0.1f);
		SpriteRendererHead->CreateAnimation("Run_Right_Head", "MainCharater_White.png", 25, 30, 0.1f);

		SpriteRendererHead->CreateAnimation("Idle_Anim_Head", "MainCharater_White.png", { 580, 581 }, { 1.5f, 0.2f }, true);

		//std::string Name = SpriteRenderer->GetCurSpriteName();
	}

	{
		SpriteRendererBody = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRendererBody->SetSprite("MainCharater_White.png");
		SpriteRendererBody->SetComponentLocation({ 0, static_cast<int>(64 * 0.5f) });
		SpriteRendererBody->SetComponentScale({ 64, 64 });
		SpriteRendererBody->SetPivotType(PivotType::Bot);

		SpriteRendererBody->CreateAnimation("Idle_Up_Body", "MainCharater_White.png", 48, 48, 0.1f);
		SpriteRendererBody->CreateAnimation("Run_Up_Body", "MainCharater_White.png", 50, 54 , 0.1f);

		SpriteRendererBody->CreateAnimation("Idle_Down_Body", "MainCharater_White.png", 32, 32, 0.1f);
		SpriteRendererBody->CreateAnimation("Run_Down_Body", "MainCharater_White.png", 33, 38, 0.1f);

		SpriteRendererBody->CreateAnimation("Idle_Left_Body", "MainCharater_White.png", 40, 40, 0.1f);
		SpriteRendererBody->CreateAnimation("Run_Left_Body", "MainCharater_White.png", 41, 46, 0.1f);

		SpriteRendererBody->CreateAnimation("Idle_Right_Body", "MainCharater_White.png", 56, 56, 0.1f);
		SpriteRendererBody->CreateAnimation("Run_Right_Body", "MainCharater_White.png", 57, 62, 0.1f);

		SpriteRendererBody->CreateAnimation("Idle_Anim_Body", "MainCharater_White.png", { 612, 613 }, { 1.5f, 0.2f }, true);
	}

	SpriteRendererBody->ChangeAnimation("Idle_Down_Body");
	SpriteRendererHead->ChangeAnimation("Idle_Down_Head");

	SpriteRendererHead->SetOrder(ERenderOrder::PLAYER);
	SpriteRendererBody->SetOrder(ERenderOrder::PLAYER);

}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	// 현재 쓰지 않아서 주석 처리
	//ChangeState(PlayerState::Idle);
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
	case PlayerState::Idle_Anim:
		Idle_Anim(_DeltaTime);
		break;
	default:
		break;
	}

	if (true == UEngineInput::GetInst().IsDown('F'))
	{
		IdleAnimTimer = 0.0f;

		FVector2D LocalLocation = GetActorLocation() - WallTileMap->GetActorLocation();
		FIntPoint CurTileIndex = WallTileMap->LocationToIndex(LocalLocation);

		if (false == WallTileMap->IsBomb(CurTileIndex))
		{
			PlaceBomb(_DeltaTime);
		}
	}

	SpriteRendererHead->SetOrder(GetActorLocation().Y - WallTileMap->GetActorLocation().Y);
	SpriteRendererBody->SetOrder(GetActorLocation().Y - WallTileMap->GetActorLocation().Y);

	if (nullptr == WallTileMap)
	{
		MSGASSERT("타일 맵이 세팅되지 않았습니다.")
	}
}


FVector2D APlayer::PosToTileIndex(FVector2D _Pos)
{
	FVector2D Location = _Pos;
	FIntPoint Index = WallTileMap->LocationToIndex(Location);
	FVector2D InvertResult = {Index.X, Index.Y};
	return InvertResult;
}


// 폭탄 설치
void APlayer::PlaceBomb(float _DeltaTime)
{
	FVector2D Location = GetActorLocation() - WallTileMap->GetActorLocation();
	FVector2D WallTileMapLocation = WallTileMap->GetActorLocation();
	FVector2D TileIndex = PosToTileIndex(Location);
	FVector2D HalfTiles = WallTileMap->GetTileHalfSize();

	//FIntPoint IndexBefore =  WallTileMap->LocationToIndex(TileIndex);
	FIntPoint Index = {static_cast<int>(floorf(TileIndex.X)), static_cast<int>(floorf(TileIndex.Y))};
	FVector2D Pos = {(( WallTileMapLocation.X + HalfTiles.X ) + Index.X * WallTileMap->GetTileSize().X),(( WallTileMapLocation.Y+ HalfTiles.Y ) + Index.Y * WallTileMap->GetTileSize().Y)};

	// 폭탄 설치 가능 여부 재확인
	if (WallTileMap->IsBomb(Index))
	{
		return; // 이미 폭탄이 설치된 경우
	}

	ABomb* Bomb = GetWorld()->SpawnActor<ABomb>();

	// 타일맵에 폭탄 세팅 (연결)
	WallTileMap->SetBomb(Index, Bomb);
	// 위치에 폭탄 설치
	Bomb->SetWallTileMap(WallTileMap, Index); // 타일맵 정보 설정
	Bomb->SetActorLocation(Pos);

	Bomb->SetPower(7);

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
}

void APlayer::MoveStart()
{
}

void APlayer::Idle_Anim(float _DeltaTime)
{
	SpriteRendererBody->ChangeAnimation("Idle_Anim_Body");
	SpriteRendererHead->ChangeAnimation("Idle_Anim_Head");
	
	if (true == UEngineInput::GetInst().IsPress('A') ||
		true == UEngineInput::GetInst().IsPress('D') ||
		true == UEngineInput::GetInst().IsPress('W') ||
		true == UEngineInput::GetInst().IsPress('S'))
	{
		IdleAnimTimer = 0.0f;
		ChangeState(PlayerState::Move);
		return;
	}
}


void APlayer::Idle(float _DeltaTime)
{
	SpriteRendererBody->ChangeAnimation("Idle_Down_Body");
	SpriteRendererHead->ChangeAnimation("Idle_Down_Head");

	IdleAnimTimer += _DeltaTime;
	if (IdleAnimTimer >= IdleAnimTime)
	{
		ChangeState(PlayerState::Idle_Anim);
		return;
	}

	if (true == UEngineInput::GetInst().IsPress('A') ||
		true == UEngineInput::GetInst().IsPress('D') ||
		true == UEngineInput::GetInst().IsPress('W') ||
		true == UEngineInput::GetInst().IsPress('S'))
	{
		IdleAnimTimer = 0.0f;
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
		SpriteRendererBody->ChangeAnimation("Run_Right_Body");
		SpriteRendererHead->ChangeAnimation("Run_Right_Head");
		Temp = 1;
	}
	else if (true == UEngineInput::GetInst().IsPress('A'))
	{
		Vector = FVector2D::LEFT;
		SpriteRendererBody->ChangeAnimation("Run_Left_Body");
		SpriteRendererHead->ChangeAnimation("Run_Left_Head");
		Temp = 2;
	}
	else if (true == UEngineInput::GetInst().IsPress('S'))
	{
		Vector = FVector2D::DOWN;
		SpriteRendererBody->ChangeAnimation("Run_Down_Body");
		SpriteRendererHead->ChangeAnimation("Run_Down_Head");
		Temp = 3;
	}
	else if (true == UEngineInput::GetInst().IsPress('W'))
	{
		Vector = FVector2D::UP;
		SpriteRendererBody->ChangeAnimation("Run_Up_Body");
		SpriteRendererHead->ChangeAnimation("Run_Up_Head");
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
	case 3: PlusPos *= 6.0f; break;
	case 4: PlusPos *= 26.0f; break;
	default: break;
	}

	FVector2D LocalLocation = GetActorLocation() - WallTileMap->GetActorLocation(); // 타일맵 기준으로 변경
	FVector2D NextLocalLocation = LocalLocation + PlusPos + (Vector * _DeltaTime * Speed); // 플레이어 피봇에 더해지는 크기

	//FVector2D CurTileIndex = PosToTileIndex(LocalLocation); 
	//FVector2D NextTileIndex = PosToTileIndex(NextLocalLocation);

	// 타일 사이즈를 나눠서 타일 플레이어 위치의 타일 인덱스 도출
	FVector2D TileSize = WallTileMap->GetTileSize(); // 32
	FVector2D LocationAtIndex = LocalLocation / TileSize; // 플레이어 위치를 타일맵 인덱스로 보기 위함
	FVector2D NextLocationAtIndex = NextLocalLocation / TileSize; // 플레이어가 이동하는 방향의 타일맵 인덱스

	// 확인용
	//FVector2D Location = GetActorLocation() - WallTileMap->GetActorLocation();
	//FIntPoint TileIndex = WallTileMap->LocationToIndex(Location);
	//FVector2D TileIndexFVector = { TileIndex.X, TileIndex.Y };
	//UEngineDebug::CoreOutPutString("NextLocalLocation : " + NextLocalLocation.ToString());
	//UEngineDebug::CoreOutPutString("CurTileIndex : " + CurTileIndex.ToString());
	//UEngineDebug::CoreOutPutString("NextTileIndex : " + NextTileIndex.ToString());
	//UEngineDebug::CoreOutPutString("LocationAtIndex : " + LocationAtIndex.ToString());
	//UEngineDebug::CoreOutPutString("NextLocationAtIndex : " + NextLocationAtIndex.ToString());

	//UEngineDebug::CoreOutPutString("TileIndex : " + TileIndexFVector.ToString());

	Tile* TileData = WallTileMap->GetTileRef(NextLocalLocation);
	bool BombCheck = WallTileMap->IsBomb({ static_cast<int>(NextLocationAtIndex.X), static_cast<int>(NextLocationAtIndex.Y) });

	if (NextLocationAtIndex.X < 0 || NextLocationAtIndex.Y < 0 || NextLocationAtIndex.X > 13 || NextLocationAtIndex.Y > 11)
	{
		return;
	}
	if (TileData->SpriteIndex != 2 && 
		TileData->SpriteIndex != 1 /*&& 
		true != BombCheck*/)
	{
		AddActorLocation(Vector * _DeltaTime * Speed);
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

