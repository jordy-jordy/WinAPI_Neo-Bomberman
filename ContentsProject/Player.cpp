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

		SpriteRenderer->CreateAnimation("Mush_Idle", "01_Mushroom_00_Idle", 0, 1, 0.1f);
		SpriteRenderer->CreateAnimation("Mush_Left", "01_Mushroom_01_Left", 0, 5, 0.1f);
		SpriteRenderer->CreateAnimation("Mush_Right", "01_Mushroom_02_Right", 0, 5, 0.1f);
		SpriteRenderer->CreateAnimation("Mush_Up", "01_Mushroom_03_Up", 0, 5, 0.1f);
		SpriteRenderer->CreateAnimation("Mush_Down", "01_Mushroom_04_Down", 0, 5, 0.1f);
		SpriteRenderer->CreateAnimation("Mush_Uniq", "01_Mushroom_05_Uniq", 0, 10, 0.1f);

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
	case PlayerState::Jump:
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

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		Vector += FVector2D::RIGHT;
		SpriteRenderer->ChangeAnimation("Mush_Right");
	}
	else if (true == UEngineInput::GetInst().IsPress('A'))
	{
		Vector += FVector2D::LEFT;
		SpriteRenderer->ChangeAnimation("Mush_Left");
	}
	else if (true == UEngineInput::GetInst().IsPress('S'))
	{
		Vector += FVector2D::DOWN;
		SpriteRenderer->ChangeAnimation("Mush_Down");
	}
	else if (true == UEngineInput::GetInst().IsPress('W'))
	{
		Vector += FVector2D::UP;
		SpriteRenderer->ChangeAnimation("Mush_Up");
	}

	if (false == UEngineInput::GetInst().IsPress('A') &&
		false == UEngineInput::GetInst().IsPress('D') &&
		false == UEngineInput::GetInst().IsPress('W') &&
		false == UEngineInput::GetInst().IsPress('S'))
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	FVector2D TileLocation = GetActorLocation() - WallTileMap->GetActorLocation();
	FVector2D NextTilePos = TileLocation + Vector * _DeltaTime* Speed;

	Tile* TileData = WallTileMap->GetTileRef(NextTilePos);

	FVector2D TileSize = WallTileMap->GetTileSize();

	FVector2D PlayerLocation = TileLocation / TileSize;
	FVector2D NextPlayerPos = PlayerLocation + Vector * _DeltaTime * Speed;

	if (NextPlayerPos.X < 0 || NextPlayerPos.Y < 0 || NextPlayerPos.X > 13 || NextPlayerPos.Y > 11)
	{
		return;
	}
	else if (TileData->SpriteIndex != 2 && TileData->SpriteIndex != 1)
	{
		AddActorLocation(Vector * _DeltaTime * Speed);
	}
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//FVector2D TileLocation = GetActorLocation() - WallTileMap->GetActorLocation();
	//FVector2D PlayerLocation = TileLocation / 32;


	//// 창의 왼쪽 위를 (0, 0)으로 두고 플레이어 위치 반환
	//UEngineDebug::CoreOutPutString("PlayerPosOrigin : " + GetActorLocation().ToString());

	//// 위 결과에서 플레이어 위치에서 타일맵 위치를 뺌s
	//UEngineDebug::CoreOutPutString("TilePos : " + TileLocation.ToString());

	//// 위 결과에서 타일 크기(32)를 나눔
	//UEngineDebug::CoreOutPutString("PlayerPos : " + PlayerLocation.ToString());

	switch (CurPlayerState)
	{
	case PlayerState::Idle:
		Idle(_DeltaTime);
		break;
	case PlayerState::Move:
		Move(_DeltaTime);
		break;
	case PlayerState::Jump:
		break;
	default:
		break;
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

