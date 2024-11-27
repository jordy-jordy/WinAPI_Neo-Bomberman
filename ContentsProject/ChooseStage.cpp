#include "PreCompile.h"
#include "ChooseStage.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>

#include "ContentsEnum.h"


UChooseStage::UChooseStage()
{
	Background = CreateDefaultSubObject<USpriteRenderer>();
	Background->SetSprite("00_BASIC.png");
	Background->SetSpriteScale(1.0f);
	Background->SetComponentLocation(BG_SIZE.Half());
	Background->SetOrder(ERenderOrder::BACKGROUND0);

	Basic_UI00 = CreateDefaultSubObject<USpriteRenderer>();
	Basic_UI00->SetSprite("01_BASIC.png");
	Basic_UI00->SetSpriteScale(1.0f);
	Basic_UI00->SetComponentLocation(BG_SIZE.Half());
	Basic_UI00->SetOrder(ERenderOrder::BACKGROUND1);

	Basic_UI01 = CreateDefaultSubObject<USpriteRenderer>();
	Basic_UI01->SetSprite("02_BASIC.png");
	Basic_UI01->SetSpriteScale(1.0f);
	Basic_UI01->SetComponentLocation(BG_SIZE.Half());
	Basic_UI01->SetOrder(ERenderOrder::BACKGROUND2);

	CHOOSE_00 = CreateDefaultSubObject<USpriteRenderer>();
	CHOOSE_00->SetSprite("INFO_STAGE_01_02.png");
	CHOOSE_00->SetSpriteScale(1.0f);
	CHOOSE_00->SetPivotType(PivotType::Top);
	CHOOSE_00->SetComponentLocation({ 352, 176 });
	CHOOSE_00->SetOrder(ERenderOrder::BACKGROUND3);
	CHOOSE_00->SetActive(true);

	CHOOSE_01 = CreateDefaultSubObject<USpriteRenderer>();
	CHOOSE_01->SetSprite("INFO_STAGE_02_02.png");
	CHOOSE_01->SetSpriteScale(1.0f);
	CHOOSE_01->SetPivotType(PivotType::Top);
	CHOOSE_01->SetComponentLocation({ 352, 336 });
	CHOOSE_01->SetOrder(ERenderOrder::BACKGROUND3);
	CHOOSE_01->SetActive(false);

	BLACKMAN = CreateDefaultSubObject<USpriteRenderer>();
	BLACKMAN->SetSprite("05_CHOOSE_STAGE_01_CHA_BLK");
	BLACKMAN->SetSpriteScale(1.0f);
	BLACKMAN->SetPivotType(PivotType::Top);
	BLACKMAN->SetComponentLocation({ 379, 16 });
	BLACKMAN->SetOrder(ERenderOrder::OBJECTS);
	BLACKMAN->CreateAnimation("BLKMAN", "05_CHOOSE_STAGE_01_CHA_BLK", 0, 5, 0.15f, true);
	BLACKMAN->ChangeAnimation("BLKMAN");

	BOMB_MAN = CreateDefaultSubObject<USpriteRenderer>();
	BOMB_MAN->SetSprite("03_BASIC.png");
	BOMB_MAN->SetSpriteScale(1.0f);
	BOMB_MAN->SetPivotType(PivotType::Top);
	BOMB_MAN->SetComponentLocation({ 65, 194 });
	BOMB_MAN->SetOrder(ERenderOrder::OBJECTS);
	BOMB_MAN->CreateAnimation("DRAW", "05_CHOOSE_STAGE_02_CHA_DRAW", 0, 9, 0.1f, false);
	BOMB_MAN->CreateAnimation("MOVE", "05_CHOOSE_STAGE_03_CHA_MOVE", 0, 3, 0.15f, true);
	BOMB_MAN->CreateAnimation("BACK", "05_CHOOSE_STAGE_03_CHA_MOVE", 4, 4, 0.1f, false);

	CIRCLE = CreateDefaultSubObject<USpriteRenderer>();
	CIRCLE->SetSprite("05_CHOOSE_STAGE_03_CIRCLE");
	CIRCLE->SetSpriteScale(1.0f);
	CIRCLE->SetPivotType(PivotType::Top);
	CIRCLE->SetComponentLocation({ 378, 184 });
	CIRCLE->SetOrder(ERenderOrder::OBJECTS);
	CIRCLE->CreateAnimation("CIRCLE", "05_CHOOSE_STAGE_03_CIRCLE", 0, 6, 0.05f, false);
	CIRCLE->SetActive(false);
};

UChooseStage::~UChooseStage()
{

};

void UChooseStage::BeginPlay()
{
	Super::BeginPlay();
}

void UChooseStage::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// 이동 중이 아니어야 스페이스 키가 동작하도록 수정
	if (IsStageONE == true &&
		UEngineInput::GetInst().IsDown(VK_SPACE) == true &&
		IsDownMoving == false && IsUpMoving == false)
	{
		StopMove = true;
		BOMB_MAN->ChangeAnimation("DRAW");
		CIRCLE->SetActive(true);
		CIRCLE->ChangeAnimation("CIRCLE");
	}

	if (CIRCLE->IsActive() == true)
	{
		if (CIRCLE->IsCurAnimationEnd() == true)
		{
			CircleDrawDone = true;
		}
	}

	if (StopMove != true)
	{
		// S 키를 눌렀을 때: 아래로 이동 시작
		if (UEngineInput::GetInst().IsDown('S') == true)
		{
			IsDownMoving = true;
			IsUpMoving = false; // 위 이동 중지
		}

		// W 키를 눌렀을 때: 위로 이동 시작
		if (UEngineInput::GetInst().IsDown('W') == true)
		{
			IsUpMoving = true;
			IsDownMoving = false; // 아래 이동 중지
		}

		// 아래 이동 로직
		if (IsDownMoving == true)
		{
			float Cur_Y = BOMB_MAN->GetComponentLocation().Y;

			if (Cur_Y < StageTwoPos)
			{
				float Move_Y = Cur_Y + MoveSpeed * _DeltaTime;

				if (Move_Y > StageTwoPos)
				{
					Move_Y = StageTwoPos;
				}

				BOMB_MAN->ChangeAnimation("MOVE");
				BOMB_MAN->SetComponentLocation({ 65.0f, Move_Y });
			}
			else
			{
				BOMB_MAN->ChangeAnimation("BACK");
				IsDownMoving = false; // 아래 이동 종료
			}
		}

		// 위 이동 로직
		if (IsUpMoving == true)
		{
			float Cur_Y = BOMB_MAN->GetComponentLocation().Y;

			if (Cur_Y > StageOnePos)
			{
				float Move_Y = Cur_Y - MoveSpeed * _DeltaTime;

				if (Move_Y < StageOnePos)
				{
					Move_Y = StageOnePos;
				}

				BOMB_MAN->ChangeAnimation("MOVE");
				BOMB_MAN->SetComponentLocation({ 65.0f, Move_Y });
			}
			else
			{
				BOMB_MAN->ChangeAnimation("BACK");
				IsUpMoving = false; // 위 이동 종료
			}
		}

		float Cur_Y = BOMB_MAN->GetComponentLocation().Y;
		if (Cur_Y >= 290.0f)
		{
			IsStageONE = false;
			IsStageTWO = true;
			CHOOSE_00->SetActive(false);
			CHOOSE_01->SetActive(true);
		}
		else
		{
			IsStageONE = true;
			IsStageTWO = false;
			CHOOSE_00->SetActive(true);
			CHOOSE_01->SetActive(false);
		}
	}

}


