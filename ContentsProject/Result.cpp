#include "PreCompile.h"
#include "Result.h"

#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"
#include "PlayGameMode.h"


AResult::AResult()
{
	STAGECLEAR = CreateDefaultSubObject<USpriteRenderer>();
	STAGECLEAR->SetSprite("01_StageClear");
	STAGECLEAR->SetOrder(ERenderOrder::UI_OVERFADE);
	STAGECLEAR->SetSpriteScale(1.0f);
	STAGECLEAR->SetPivotType(PivotType::Top);
	STAGECLEAR->SetComponentLocation({ 303, 55 });
	STAGECLEAR->CreateAnimation("StageClear", "01_StageClear", 0, 5, 0.15f, true);
	STAGECLEAR->ChangeAnimation("StageClear");

	RESULTINFO = CreateDefaultSubObject<USpriteRenderer>();
	RESULTINFO->SetSprite("STAGECLEAR_INFO.png");
	RESULTINFO->SetOrder(ERenderOrder::UI_OVERFADE);
	RESULTINFO->SetSpriteScale(1.0f);
	RESULTINFO->SetPivotType(PivotType::Center);
	RESULTINFO->SetComponentLocation(INFO_CurPos);

	RESULTBBMS = CreateDefaultSubObject<USpriteRenderer>();
	RESULTBBMS->SetSprite("STAGECLEAR_BBMs.png");
	RESULTBBMS->SetOrder(ERenderOrder::UI_OVERFADE);
	RESULTBBMS->SetSpriteScale(1.0f);
	RESULTBBMS->SetPivotType(PivotType::Top);
	RESULTBBMS->SetComponentLocation(BBMs_CurPos);
	RESULTBBMS->SetActive(false);

	RESULTSTAMP = CreateDefaultSubObject<USpriteRenderer>();
	RESULTSTAMP->SetSprite("STAGECLEAR_STAMP.png");
	RESULTSTAMP->SetOrder(23000);
	RESULTSTAMP->SetSpriteScale(1.0f);
	RESULTSTAMP->SetPivotType(PivotType::Top);
	RESULTSTAMP->SetComponentLocation({ 209, 218 });
	RESULTSTAMP->SetActive(false);
};


AResult::~AResult()
{

};


void AResult::BeginPlay()
{
	Super::BeginPlay();
}


void AResult::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (IsInfoMoved == false)
	{
		INFO_CenterPos = RESULTINFO->GetComponentScale() * 0.5;

		// 이동 속도 설정
		float MoveSpeed = 600.0f * _DeltaTime; // 이동 속도

		// X축 이동 처리
		if (INFO_CurPos.X < INFO_CenterPos.X)
		{
			INFO_CurPos.X += MoveSpeed;

			if (INFO_CurPos.X >= INFO_CenterPos.X)
			{
				INFO_CurPos.X = INFO_CenterPos.X; // 목표 위치에 도달
			}
		}
		else if (INFO_CurPos.X > INFO_CenterPos.X)
		{
			INFO_CurPos.X -= MoveSpeed;

			if (INFO_CurPos.X <= INFO_CenterPos.X)
			{
				INFO_CurPos.X = INFO_CenterPos.X; // 목표 위치에 도달
			}
		}

		// Y축 이동 처리
		if (INFO_CurPos.Y < INFO_CenterPos.Y)
		{
			INFO_CurPos.Y += MoveSpeed;

			if (INFO_CurPos.Y >= INFO_CenterPos.Y)
			{
				INFO_CurPos.Y = INFO_CenterPos.Y; // 목표 위치에 도달
			}
		}
		else if (INFO_CurPos.Y > INFO_CenterPos.Y)
		{
			INFO_CurPos.Y -= MoveSpeed;

			if (INFO_CurPos.Y <= INFO_CenterPos.Y)
			{
				INFO_CurPos.Y = INFO_CenterPos.Y; // 목표 위치에 도달
			}
		}

		// 최종 위치 설정
		RESULTINFO->SetComponentLocation(INFO_CurPos);

		// 목표 위치에 도달하면 이동 완료 플래그 설정
		if (INFO_CurPos.X == INFO_CenterPos.X && INFO_CurPos.Y == INFO_CenterPos.Y)
		{
			IsInfoMoved = true;
		}
	}


	if (PlayMode->GetShowedAllScore() == true)
	{
		FlowedTime += _DeltaTime;

		if (FlowedTime >= 1.5f)
		{
			STAGECLEAR->SetActive(false);
			RESULTBBMS->SetActive(true);

			// 이동 속도 설정
			float MoveSpeed = 30.0f * _DeltaTime;
			float XMoveSpeed = 680.0f * _DeltaTime; // X축 이동 속도

			// Y축 애니메이션 처리
			if (IsMoved == false) // 아래로 이동 중
			{
				BBMs_CurMoveSize += MoveSpeed;

				if (BBMs_CurMoveSize >= BBMs_TargetDownMoveSize)
				{
					BBMs_CurMoveSize = BBMs_TargetDownMoveSize;
					IsMoved = true; // 방향 전환
				}
			}
			else // 위로 이동 중
			{
				BBMs_CurMoveSize -= MoveSpeed;

				if (BBMs_CurMoveSize <= BBMs_TargetUpMoveSize)
				{
					BBMs_CurMoveSize = BBMs_TargetUpMoveSize;
					IsMoved = false; // 방향 전환
				}
			}

			// X축 애니메이션 처리
			if (BBMs_CurPos.X > BBMs_TargetPosX)
			{
				BBMs_CurPos.X -= XMoveSpeed;

				if (BBMs_CurPos.X < BBMs_TargetPosX)
				{
					BBMs_CurPos.X = BBMs_TargetPosX; // 목표 위치에 도달하면 고정
					RESULTSTAMP->SetActive(true);

				}
			}

			// 최종 위치 업데이트
			RESULTBBMS->SetComponentLocation({ BBMs_CurPos.X, BBMs_CurPos.Y + BBMs_CurMoveSize });

		}
	}
}


void AResult::SetMode(APlayGameMode* _data)
{
	PlayMode = _data;
}

