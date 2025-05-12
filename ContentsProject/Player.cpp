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
			MSGASSERT("Ÿ�� ���� ���õ��� �ʾҽ��ϴ�.")
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


// ��ź ��ġ
void APlayer::PlaceBomb()
{
	FVector2D PlayerLocation = GetActorLocation(); // 112, 80 (+ 16�� ������ ����) // �������� LEFT TOP�� �������� å��
	FVector2D TileMapLocation = WallTileMap->GetActorLocation(); // 96, 64 // �������� LEFT TOP�� �������� å��
	FVector2D LocalLocation = PlayerLocation - TileMapLocation; // Ÿ�ϸ��� LEFT TOP�� �������� å���ǵ��� ���

	FIntPoint BOMB_SET_Index = WallTileMap->LocationToIndex(LocalLocation); // Ÿ�ϸ� ���� �ε���

	// ��ź ��ġ ���� ���� ��Ȯ��
	if (WallTileMap->IsBomb(BOMB_SET_Index))
	{
		return; // �̹� ��ź�� ��ġ�� ���
	}

	FVector2D TileSize = WallTileMap->GetTileSize(); // 32
	FVector2D TileHalfSize = WallTileMap->GetTileHalfSize(); // 16

	FIntPoint PLAYERINDEX = WallTileMap->LocationToIndex(PlayerLocation);
	FVector2D BOMB_SET_LOCATION = WallTileMap->IndexToTileLocation(PLAYERINDEX) + FVector2D(TileHalfSize.X, TileHalfSize.Y);

	ABomb* Bomb = GetWorld()->SpawnActor<ABomb>();

	// Ÿ�ϸʿ� ��ź ���� (����)
	WallTileMap->SetBomb(BOMB_SET_Index, Bomb);
	// ��ġ�� ��ź ��ġ
	Bomb->SetWallTileMap(WallTileMap, BOMB_SET_Index); // Ÿ�ϸ� ���� ����
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

	FVector2D PLAYER_LOCAL_LOC = GetActorLocation() - WallTileMap->GetActorLocation(); // Ÿ�ϸ� LEFT TOP ����
	//bool BombCheck = WallTileMap->IsBomb(PLAYER_LOCAL_IDX_NEXT); // ��ź üũ �Լ�

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
	// ���� ��ġ�� Ÿ�� ���� ��������
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

	// Ÿ�ϸ� ũ��
	const int POS_X_MIN = 96;
	const int POS_X_MAX = 512;
	const int POS_Y_MIN = 64;
	const int POS_Y_MAX = 416;

	// Ÿ�� �ٱ����� �������� üũ
	if (_NextPOS_Win.X < POS_X_MIN || _NextPOS_Win.X > POS_X_MAX || _NextPOS_Win.Y < POS_Y_MIN || _NextPOS_Win.Y > POS_Y_MAX)
	{
		ThereIsOutOfMap = true;
	}
	else
	{
		ThereIsOutOfMap = false;
	}

	// Ÿ�� ������ ������ �����鼭 ���� ���⿡ ��ֹ��� �ִ��� üũ
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


