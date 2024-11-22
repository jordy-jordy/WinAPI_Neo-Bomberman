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
}

APlayer::APlayer()
{
	{
		SpriteRendererHead = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRendererHead->SetSprite("MainCharater_White.png");
		SpriteRendererHead->SetComponentLocation({ 0, 0 });
		SpriteRendererHead->SetComponentScale({ 64, 64 });
		SpriteRendererHead->SetPivot({0.0f, -28.0f});
		SpriteRendererHead->SetPivot({ 0.0f, -28.0f });


		SpriteRendererHead->CreateAnimation("Idle_Up_Head", "MainCharater_White.png", 17, 17, 0.1f);
		SpriteRendererHead->CreateAnimation("Run_Up_Head", "MainCharater_White.png", 18, 22 , 0.1f);

		SpriteRendererHead->CreateAnimation("Idle_Down_Head", "MainCharater_White.png", 0, 0, 0.1f);
		SpriteRendererHead->CreateAnimation("Run_Down_Head", "MainCharater_White.png", 1, 6, 0.1f);

		SpriteRendererHead->CreateAnimation("Idle_Left_Head", "MainCharater_White.png", 8, 8, 0.1f);
		SpriteRendererHead->CreateAnimation("Run_Left_Head", "MainCharater_White.png", 9, 14, 0.1f);

		SpriteRendererHead->CreateAnimation("Idle_Right_Head", "MainCharater_White.png", 24, 24, 0.1f);
		SpriteRendererHead->CreateAnimation("Run_Right_Head", "MainCharater_White.png", 25, 30, 0.1f);

		SpriteRendererHead->CreateAnimation("Idle_Anim_Head", "MainCharater_White.png", { 580, 581 }, { 1.5f, 0.2f }, true);

	}

	{
		SpriteRendererBody = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRendererBody->SetSprite("MainCharater_White.png");
		SpriteRendererBody->SetComponentLocation({ 0, static_cast<int>(64 * 0.5f) });
		SpriteRendererBody->SetComponentScale({ 64, 64 });
		SpriteRendererBody->SetPivot({ 0.0f, -28.0f });

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

	SpriteRendererBody->SetOrder(ERenderOrder::PLAYER);
	SpriteRendererHead->SetOrder(ERenderOrder::PLAYER);
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();
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
			PlaceBomb();
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

FVector2D APlayer::InvertLOC(FVector2D _Dir)
{
	if (_Dir == FVector2D::ZERO)
	{
		return CUSTOM_VECTOR_ZERO;
	}

	if (_Dir == FVector2D::LEFT)
	{
		return CUSTOM_VECTOR_LEFT;
	}

	if (_Dir == FVector2D::RIGHT)
	{
		return CUSTOM_VECTOR_RIGHT;
	}

	if (_Dir == FVector2D::UP)
	{
		return CUSTOM_VECTOR_UP;
	}

	if (_Dir == FVector2D::DOWN)
	{
		return CUSTOM_VECTOR_DOWN;
	}

}


// 폭탄 설치
void APlayer::PlaceBomb()
{
	FVector2D TileSize = WallTileMap->GetTileSize(); // 32
	FVector2D TileHalfSize = WallTileMap->GetTileHalfSize(); // 16

	FVector2D PlayerLocation = GetActorLocation(); // 112, 80 (+ 16이 더해져 있음) // 윈도우의 LEFT TOP을 기준으로 책정
	FIntPoint PLAYERINDEX = WallTileMap->LocationToIndex(PlayerLocation);
	FVector2D TileMapLocation = WallTileMap->GetActorLocation(); // 96, 64 // 윈도우의 LEFT TOP을 기준으로 책정
	FVector2D LocalLocation = PlayerLocation - TileMapLocation; // 타일맵의 LEFT TOP을 기준으로 책정되도록 계산

	FIntPoint BOMB_SET_Index = WallTileMap->LocationToIndex(LocalLocation); // 타일맵 기준 인덱스
	FVector2D BOMB_SET_LOCATION = WallTileMap->IndexToTileLocation(PLAYERINDEX) + FVector2D(TileHalfSize.X, TileHalfSize.Y);

	// 폭탄 설치 가능 여부 재확인
	if (WallTileMap->IsBomb(BOMB_SET_Index))
	{
		return; // 이미 폭탄이 설치된 경우
	}

	ABomb* Bomb = GetWorld()->SpawnActor<ABomb>();

	// 타일맵에 폭탄 세팅 (연결)
	WallTileMap->SetBomb(BOMB_SET_Index, Bomb);
	// 위치에 폭탄 설치
	Bomb->SetWallTileMap(WallTileMap, BOMB_SET_Index); // 타일맵 정보 설정
	Bomb->SetActorLocation(BOMB_SET_LOCATION);

	Bomb->SetPower(BOMBPOWER);

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
	int DIR = 0;

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		Vector = FVector2D::RIGHT;
		SpriteRendererBody->ChangeAnimation("Run_Right_Body");
		SpriteRendererHead->ChangeAnimation("Run_Right_Head");
		DIR = 1;
	}
	else if (true == UEngineInput::GetInst().IsPress('A'))
	{
		Vector = FVector2D::LEFT;
		SpriteRendererBody->ChangeAnimation("Run_Left_Body");
		SpriteRendererHead->ChangeAnimation("Run_Left_Head");
		DIR = 2;
	}
	else if (true == UEngineInput::GetInst().IsPress('S'))
	{
		Vector = FVector2D::DOWN;
		SpriteRendererBody->ChangeAnimation("Run_Down_Body");
		SpriteRendererHead->ChangeAnimation("Run_Down_Head");
		DIR = 3;
	}
	else if (true == UEngineInput::GetInst().IsPress('W'))
	{
		Vector = FVector2D::UP;
		SpriteRendererBody->ChangeAnimation("Run_Up_Body");
		SpriteRendererHead->ChangeAnimation("Run_Up_Head");
		DIR = 4;
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
	switch (DIR)
	{
	case 1: PlusPos *= 16.0f; break; // RIGHT
	case 2: PlusPos *= 16.0f; break; // LEFT
	case 3: PlusPos *= 16.0f; break; // DOWN
	case 4: PlusPos *= 16.0f; break; // UP
	default: break;
	}

	// 타일맵 크기
	const int POS_X_MIN = 96;
	const int POS_X_MAX = 512;
	const int POS_Y_MIN = 64;
	const int POS_Y_MAX = 416;
	
	FVector2D PLAYER_POS_NEXT = GetActorLocation() + (Vector * _DeltaTime * Speed) + PlusPos; // 윈도우 LEFT TOP 기준
	//UEngineDebug::CoreOutPutString("PLAYER_POS_NEXT : " + PLAYER_POS_NEXT.ToString());

	FVector2D PLAYER_LOCAL_LOC = GetActorLocation() - WallTileMap->GetActorLocation(); // 타일맵 LEFT TOP 기준
	FVector2D PLAYER_LOCAL_LOC_NEXT = PLAYER_LOCAL_LOC + (Vector * _DeltaTime * Speed) + PlusPos;

	FIntPoint PLAYER_LOCAL_IDX_NEXT = WallTileMap->LocationToIndex(PLAYER_LOCAL_LOC_NEXT);

	Tile* TileData = WallTileMap->GetTileRef(PLAYER_LOCAL_LOC_NEXT);
	bool BombCheck = WallTileMap->IsBomb(PLAYER_LOCAL_IDX_NEXT);

	if (PLAYER_POS_NEXT.X < POS_X_MIN || PLAYER_POS_NEXT.X > POS_X_MAX || PLAYER_POS_NEXT.Y < POS_Y_MIN || PLAYER_POS_NEXT.Y > POS_Y_MAX)
	{
		return;
	}

	if (TileData != nullptr)
	{
		if (TileData->SpriteIndex != 2 &&
			TileData->SpriteIndex != 1 /*&&
			true != BombCheck*/)
		{
			AddActorLocation(Vector * _DeltaTime * Speed);
		}
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

