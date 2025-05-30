#include "PreCompile.h"
#include "Player.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EnginePlatform/EngineInput.h>

#include "Bomb.h"
#include "ATileMap.h"
#include "PlayGameMode.h"
#include "Portal.h"


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

		SpriteRendererHead->CreateAnimation("Clear_Stage_Head", "MainCharater_White.png", 583, 589, 0.1f, false);
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

		SpriteRendererBody->CreateAnimation("Clear_Stage_Body", "MainCharater_White.png", 615, 621, 0.1f, false);
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
	
	if (PlayMode->GetIsPlayEnd() == true)
	{
		SpriteRendererHead->ChangeAnimation("Clear_Stage_Head");
		SpriteRendererBody->ChangeAnimation("Clear_Stage_Body");
		SpriteRendererHead->SetOrder(ERenderOrder::TEXT_UI);
		SpriteRendererBody->SetOrder(ERenderOrder::TEXT_UI);
		IsCleared = true;
	}

	if (Portal->GET_ISCANMOVE() == true)
	{
		IsPortalCanMove = true;
	}

	if (IsCleared != true)
	{
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

		if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
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
		return {0, 0};
}


// 폭탄 설치
void APlayer::PlaceBomb()
{
	FVector2D PlayerLocation = GetActorLocation(); // 112, 80 (+ 16이 더해져 있음) // 윈도우의 LEFT TOP을 기준으로 책정
	FVector2D TileMapLocation = WallTileMap->GetActorLocation(); // 96, 64 // 윈도우의 LEFT TOP을 기준으로 책정
	FVector2D LocalLocation = PlayerLocation - TileMapLocation; // 타일맵의 LEFT TOP을 기준으로 책정되도록 계산

	FIntPoint BOMB_SET_Index = WallTileMap->LocationToIndex(LocalLocation); // 타일맵 기준 인덱스

	// 폭탄 설치 가능 여부 재확인
	if (WallTileMap->IsBomb(BOMB_SET_Index))
	{
		return; // 이미 폭탄이 설치된 경우
	}

	FVector2D TileSize = WallTileMap->GetTileSize(); // 32
	FVector2D TileHalfSize = WallTileMap->GetTileHalfSize(); // 16

	FIntPoint PLAYERINDEX = WallTileMap->LocationToIndex(PlayerLocation);
	FVector2D BOMB_SET_LOCATION = WallTileMap->IndexToTileLocation(PLAYERINDEX) + FVector2D(TileHalfSize.X, TileHalfSize.Y);

	ABomb* Bomb = GetWorld()->SpawnActor<ABomb>();

	// 타일맵에 폭탄 세팅 (연결)
	WallTileMap->SetBomb(BOMB_SET_Index, Bomb);
	// 위치에 폭탄 설치
	Bomb->SetWallTileMap(WallTileMap, BOMB_SET_Index); // 타일맵 정보 설정
	Bomb->SetActorLocation(BOMB_SET_LOCATION);

	Bomb->SetPower(BOMBPOWER);
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
	SOUND_MOVE.Stop();
	ON_SOUND_MOVE = false;

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
	if (ON_SOUND_MOVE == false)
	{
		SOUND_MOVE = UEngineSound::Play("01Play_01_Walking.mp3");
		SOUND_MOVE.SetVolume(SoundVolume * 3.0);
		SOUND_MOVE.Loop();
		ON_SOUND_MOVE = true;
	}

	FVector2D Vector = FVector2D::ZERO;

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		Vector = FVector2D::RIGHT;
		SpriteRendererBody->ChangeAnimation("Run_Right_Body");
		SpriteRendererHead->ChangeAnimation("Run_Right_Head");
	}
	else if (true == UEngineInput::GetInst().IsPress('A'))
	{
		Vector = FVector2D::LEFT;
		SpriteRendererBody->ChangeAnimation("Run_Left_Body");
		SpriteRendererHead->ChangeAnimation("Run_Left_Head");
	}
	else if (true == UEngineInput::GetInst().IsPress('S'))
	{
		Vector = FVector2D::DOWN;
		SpriteRendererBody->ChangeAnimation("Run_Down_Body");
		SpriteRendererHead->ChangeAnimation("Run_Down_Head");
	}
	else if (true == UEngineInput::GetInst().IsPress('W'))
	{
		Vector = FVector2D::UP;
		SpriteRendererBody->ChangeAnimation("Run_Up_Body");
		SpriteRendererHead->ChangeAnimation("Run_Up_Head");
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

	FVector2D PLAYER_LOCAL_LOC = GetActorLocation() - WallTileMap->GetActorLocation(); // 타일맵 LEFT TOP 기준
	//bool BombCheck = WallTileMap->IsBomb(PLAYER_LOCAL_IDX_NEXT); // 폭탄 체크 함수

	FVector2D POS_LEFTTOP_NEXT = GetActorLocation() + (Vector * _DeltaTime * Speed) + SIZE_LEFTTOP;
	FVector2D POS_LEFTBOT_NEXT = GetActorLocation() + (Vector * _DeltaTime * Speed) + SIZE_LEFTBOT;
	FVector2D POS_RIGHTTOP_NEXT = GetActorLocation() + (Vector * _DeltaTime * Speed) + SIZE_RIGHTTOP;
	FVector2D POS_RIGHTBOT_NEXT = GetActorLocation() + (Vector * _DeltaTime * Speed) + SIZE_RIGHTBOT;

	FVector2D LOCAL_LEFTTOP_NEXT = PLAYER_LOCAL_LOC + (Vector * _DeltaTime * Speed) + SIZE_LEFTTOP;
	FVector2D LOCAL_LEFTBOT_NEXT = PLAYER_LOCAL_LOC + (Vector * _DeltaTime * Speed) + SIZE_LEFTBOT;
	FVector2D LOCAL_RIGHTTOP_NEXT = PLAYER_LOCAL_LOC + (Vector * _DeltaTime * Speed) + SIZE_RIGHTTOP;
	FVector2D LOCAL_RIGHTBOT_NEXT = PLAYER_LOCAL_LOC + (Vector * _DeltaTime * Speed) + SIZE_RIGHTBOT;

	bool CanMove_LT_NEXT = CanMove(POS_LEFTTOP_NEXT, LOCAL_LEFTTOP_NEXT);
	bool CanMove_LB_NEXT = CanMove(POS_LEFTBOT_NEXT, LOCAL_LEFTBOT_NEXT);
	bool CanMove_RT_NEXT = CanMove(POS_RIGHTTOP_NEXT, LOCAL_RIGHTTOP_NEXT);
	bool CanMove_RB_NEXT = CanMove(POS_RIGHTBOT_NEXT, LOCAL_RIGHTBOT_NEXT);

	if (CanMove_LT_NEXT == true && CanMove_LB_NEXT == true && CanMove_RT_NEXT == true && CanMove_RB_NEXT == true)
	{
		AddActorLocation(Vector * _DeltaTime * Speed);
	}

	if (Vector == FVector2D::UP || Vector == FVector2D::DOWN)
	{
		if (CanMove_LT_NEXT && !CanMove_RT_NEXT || CanMove_LB_NEXT && !CanMove_RB_NEXT)
		{
			AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
			return;
		}
		else if (!CanMove_LT_NEXT && CanMove_RT_NEXT || !CanMove_LB_NEXT && CanMove_RB_NEXT)
		{
			AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
			return;
		}
	}
	else
	{
		if (CanMove_RT_NEXT && !CanMove_RB_NEXT || CanMove_LT_NEXT && !CanMove_LB_NEXT)
		{
			AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
			return;
		}
		else if (!CanMove_RT_NEXT && CanMove_RB_NEXT || !CanMove_LT_NEXT && CanMove_LB_NEXT)
		{
			AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
			return;
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


bool APlayer::CanMove(FVector2D _NextPOS_Win, FVector2D _NextPOS_Local)
{
	// 다음 위치의 타일 정보 가져오기
	Tile* TileData = WallTileMap->GetTileRef(_NextPOS_Local);
	if (TileData != nullptr)
	{
		if (TileData->SpriteIndex == 2 ||
			TileData->SpriteIndex == 1 ||
			TileData->SpriteIndex == 3 &&
			IsPortalCanMove == false)
		{
			ThereIsTILE = true;
		}
		else
		{
			ThereIsTILE = false;
		}
	}

	// 타일맵 크기
	const int POS_X_MIN = 96;
	const int POS_X_MAX = 512;
	const int POS_Y_MIN = 64;
	const int POS_Y_MAX = 416;

	// 타일 바깥으로 나가는지 체크
	if (_NextPOS_Win.X < POS_X_MIN || _NextPOS_Win.X > POS_X_MAX || _NextPOS_Win.Y < POS_Y_MIN || _NextPOS_Win.Y > POS_Y_MAX)
	{
		ThereIsOutOfMap = true;
	}
	else
	{
		ThereIsOutOfMap = false;
	}

	// 타일 밖으로 나가지 않으면서 진행 방향에 장애물이 있는지 체크
	if (ThereIsOutOfMap == false && ThereIsTILE == false)
	{
		return true;
	}
	else if (ThereIsOutOfMap == true || ThereIsTILE == true)
	{
		return false;
	}

	return false;
}


