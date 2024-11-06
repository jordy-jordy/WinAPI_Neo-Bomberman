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

	SetActorLocation({ 108, 80 });
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("01_Mushroom_00_Idle");
		SpriteRenderer->SetComponentScale({ 32, 32 });
		SpriteRenderer->SetPivotType(PivotType::Center);

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

	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1.0f);

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
	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		Vector += FVector2D::LEFT;
		SpriteRenderer->ChangeAnimation("Mush_Left");
	}
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		Vector += FVector2D::DOWN;
		SpriteRenderer->ChangeAnimation("Mush_Down");
	}
	if (true == UEngineInput::GetInst().IsPress('W'))
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

	AddActorLocation(Vector * _DeltaTime * Speed);
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

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

	WallTileMap = GetWorld()->SpawnActor<ATileMap>();
	WallTileMap->SetActorLocation({ 96, 64 });

	SpriteRenderer->SetOrder(GetActorLocation().Y - WallTileMap->GetActorLocation().Y);
}

void APlayer::LevelChangeStart()
{
	Super::LevelChangeStart();
}

void APlayer::LevelChangeEnd()
{
	Super::LevelChangeEnd();
}

