#include "PreCompile.h"
#include "ANewPlayer.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/2DCollision.h>
#include "ContentsEnum.h"

ANewPlayer::ANewPlayer()
{
	SetActorLocation({ 100, 100 });

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Player_Right.png");
		SpriteRenderer->SetComponentScale({ 300, 300 });
		SpriteRenderer->CreateAnimation("Run_Right", "Player_Right.png", 2, 4, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Right", "Player_Right.png", 0, 0, 0.1f);
	}

	{
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentLocation({ 200, 0 });
		CollisionComponent->SetComponentScale({ 50, 50 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::PlayerBody);
	}



	DebugOn();
}

ANewPlayer::~ANewPlayer()
{
}

void ANewPlayer::BeginPlay()
{
	Super::BeginPlay();
	// 직접 카메라 피봇을 설정해줘야 한다.
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1.0f);

	GetWorld()->SetCameraToMainPawn(false);

	// 앞으로 계속 강의할 것이다.
	// 즉석함수만들기
	// [] 람다 캡처
	// [=] 을하면 복사를 합니다.
	// [&] 을하면 참조를 합니다.
	// [this] 변수명 명시 복사 값이

	//  UFSMStateManager NewFSM = FSM;

	// int Value2;
	// int Value = Value2; // 복사라 보
	// Value = 30;

	// 지역변수죠

	// = 외부에서 끌어오는 값을 기본적으로 복사해서 내부에서 사용해라
	// & 외부에서 끌어오는 값을 기본적으로 참조형으로 내부에서 사용해라
	// this, Value => 명시 외부에 존재하는 명시한 값만 복사해서 내부에서 사용해라.

	// int Value;

	//FSM.CreateState(NewPlayerState::Idle,
	//	[this](float _DeltaTime)
	//	{
	//		// int Test = this->Test;
	//		// 외부에 존재하는 값을 가져다 쓸때 복제해서 내부에서 
	//		
	//		// 일반적인 지역변수는 여기서 사용할수 없다.
	//		// 맴버변수는 this를 기반으로 사용된다는 것을 잊으면 안된다.

	//		if (true == UEngineInput::GetInst().IsPress('A') ||
	//			true == UEngineInput::GetInst().IsPress('D') ||
	//			true == UEngineInput::GetInst().IsPress('W') ||
	//			true == UEngineInput::GetInst().IsPress('S'))
	//		{
	//			// 상태를 바꾸는 순간은 그 바로 종료하는게 좋다.
	//			// 최종적으로 상태를 바꿨다면 종료해라.
	//			this->FSM.ChangeState(NewPlayerState::Move);
	//			return;
	//		}

	//	},
	//	[this]()
	//	{
	//		SpriteRenderer->ChangeAnimation("Idle_Right");
	//	}
	//	);

	FSM.CreateState(NewPlayerState::Idle, std::bind(&ANewPlayer::Idle, this, std::placeholders::_1),
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Idle_Right");
		}
	);

	FSM.CreateState(NewPlayerState::Move, std::bind(&ANewPlayer::Move, this, std::placeholders::_1),
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Run_Right");
		}
	);

	FSM.CreateState(NewPlayerState::Attack, std::bind(&ANewPlayer::Attack, this, std::placeholders::_1),
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Run_Right");
		}
	);

	FSM.ChangeState(NewPlayerState::Idle);

}

void ANewPlayer::PlayerCameraCheck()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPos(GetActorLocation() - WindowSize.Half());

	DebugOn();
}

void ANewPlayer::PlayerGroundCheck(FVector2D _MovePos)
{
	IsMove = false;
	IsGround = false;

	if (nullptr != ColImage)
	{
		// 픽셀충돌에서 제일 중요한건 애초에 박히지 않는것이다.
		FVector2D NextPos = GetActorLocation() + _MovePos;

		UColor Color = ColImage->GetColor(NextPos, UColor::BLACK);
		if (Color == UColor::WHITE)
		{
			IsMove = true;
		}
		else if (Color == UColor::BLACK)
		{
			IsGround = true;
			// 땅에 박히지 않을때까지 올려주는 기능도 함께 만들거나 해야한다.
		}
	}
}

void ANewPlayer::Gravity(float _DeltaTime)
{
	if (false == IsGround)
	{
		GravityForce += FVector2D::DOWN * _DeltaTime * 500.0f;
	}
	else {
		GravityForce = FVector2D::ZERO;
	}

	// 상시 
	AddActorLocation(GravityForce * _DeltaTime);
}

void ANewPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


	// 세계에는 항상 0, 0이 존재한다.

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineDebug::SwitchIsDebug();
	}

	FSM.Update(_DeltaTime);
}

void ANewPlayer::Idle(float _DeltaTime)
{
	// 게임적 허용
	PlayerCameraCheck();
	PlayerGroundCheck(GravityForce * _DeltaTime);
	Gravity(_DeltaTime);

	if (true == UEngineInput::GetInst().IsPress('F'))
	{
		FSM.ChangeState(NewPlayerState::Attack);
		return;
	}

	if (true == UEngineInput::GetInst().IsPress('A') ||
		true == UEngineInput::GetInst().IsPress('D') ||
		true == UEngineInput::GetInst().IsPress('W') ||
		true == UEngineInput::GetInst().IsPress('S'))
	{
		// 상태를 바꾸는 순간은 그 바로 종료하는게 좋다.
		// 최종적으로 상태를 바꿨다면 종료해라.
		FSM.ChangeState(NewPlayerState::Move);
		return;
	}
}

void ANewPlayer::Attack(float _DeltaTime)
{
	//if (4 == SpriteRenderer->GetAniamtionFrame())
	//{
		// 최초충돌, 충돌중, 충돌후

	//if (true == CollisionComponent->IsCollision(ECollisionGroup::MonsterBody))
	//{
	//	// 충돌 했어.
	//}

		//U2DCollision* Result = CollisionComponent->CollisionOnce(ECollisionGroup::MonsterBody);

		//if (nullptr != Result)
		//{
		//	// 나랑 충돌한 애가 있다.
		//}
	//}

	// 
}


void ANewPlayer::Move(float _DeltaTime)
{
	PlayerCameraCheck();
	PlayerGroundCheck(GravityForce * _DeltaTime);
	Gravity(_DeltaTime);

	FVector2D Vector = FVector2D::ZERO;

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		Vector += FVector2D::RIGHT;
	}
	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		Vector += FVector2D::LEFT;
	}
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		Vector += FVector2D::DOWN;
	}
	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		Vector += FVector2D::UP;
		// AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	}

	if (true == UEngineInput::GetInst().IsPress('F'))
	{
		FSM.ChangeState(NewPlayerState::Attack);
		return;
	}

	Vector.Normalize();

	// 땅 체크하는 함수.
	PlayerGroundCheck(Vector * _DeltaTime * Speed);

	if (true == IsMove)
	{
		AddActorLocation(Vector * _DeltaTime * Speed);
	}


	if (false == UEngineInput::GetInst().IsPress('A') &&
		false == UEngineInput::GetInst().IsPress('D') &&
		false == UEngineInput::GetInst().IsPress('W') &&
		false == UEngineInput::GetInst().IsPress('S'))
	{
		FSM.ChangeState(NewPlayerState::Idle);
		return;
	}


}

void ANewPlayer::SetColImage(std::string_view _ColImageName)
{
	ColImage = UImageManager::GetInst().FindImage(_ColImageName);
}

void ANewPlayer::LevelChangeStart()
{
	int a = 0;
}