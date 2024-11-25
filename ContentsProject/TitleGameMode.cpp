#include "PreCompile.h"
#include "TitleGameMode.h"

#include <string>

#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineRandom.h>
#include <EngineCore/SpriteRenderer.h>

#include "TitleLogo.h"
#include "CoinInsert.h"
#include "ChooseStage.h"
#include "Score.h"
#include "ContentsEnum.h"
#include "ChooseStage.h"
#include "Fade.h"


ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}


void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 네오지오 로고 장면 세팅
	TITLE = GetWorld()->SpawnActor<UTitleLogo>();

	// 코인 충전 장면 세팅
	COININSERT = GetWorld()->SpawnActor<UCoinInsert>();
	COININSERT->SetActive(false);
	COININSERT->SetScore_Coin(COINs);

	// 스테이지 선택 장면 세팅
	CHOOSE = GetWorld()->SpawnActor<UChooseStage>();
	CHOOSE->SetActive(false);


	// 스코어(코인) 세팅
	COINs = GetWorld()->SpawnActor<AScore>();
	COINs->SetTextSpriteName("Title_countdown_24x24.png");
	COINs->SetActorLocation({ 600, 440 });
	COINs->SetTextScale({ 16, 16 });
	COINs->SetAlignment(AScore::Alignment::Right);
	COINs->SetOrder(ERenderOrder::TEXT_UI);
	COINs->SetDigitCount(DIGITCOUNT_Coins);
	COINs->SetValue(COIN_NUMBER);
	COINs->SetActive(false);

	// 스코어(남은 시간) 세팅 < 스테이지 선택 장면 >
	TIMEs_StageChoose = GetWorld()->SpawnActor<AScore>();
	TIMEs_StageChoose->SetTextSpriteName("BlueCount.png");
	TIMEs_StageChoose->SetActorLocation({ 502, 104 });
	TIMEs_StageChoose->SetTextScale({ 32, 32 });
	TIMEs_StageChoose->SetAlignment(AScore::Alignment::Left);
	TIMEs_StageChoose->SetOrder(ERenderOrder::TEXT_UI);
	TIMEs_StageChoose->SetDigitCount(DIGITCOUNT_StageChooseTime);
	TIMEs_StageChoose->SetActive(true);

	Actor_Fade = GetWorld()->SpawnActor<AFade>();
	Actor_Fade->SetFadeSpeed(1.5f);
	Actor_Fade->SetActive(false);
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (InitCurState() == SCENES::NONE)
	{
		return;
	}

	if (InitCurState() == SCENES::ANI_TRANSIT)
	{
		return;
	}

	if (InitCurState() == SCENES::CHOOSE_STAGE)
	{
		if (Actor_Fade->IsFadeOut == false && Actor_Fade->IsFadeIn == false)
		{
			Actor_Fade->SetActive(true);
			Actor_Fade->FadeOut();
		}

		CHOOSE->SetActive(true);
		TIMEs_StageChoose->SetActive(true);
		TIMEs_StageChoose->SetValue(static_cast<int>(StageChooseTime_NUMBER));

		StageChooseTime_NUMBER -= _DeltaTime;

		if (CHOOSE->GetIsStageONE() == true && UEngineInput::GetInst().IsDown(VK_SPACE))
		{
			TimeEventer.PushEvent(1.5f, std::bind(&AFade::FadeIn, Actor_Fade), false, false);
			TimeEventer.PushEvent(3.0f, std::bind(&ATitleGameMode::OpenPlayLevel, this), false, false);
			//ISPASS_CHOOSE_STAGE = true;
			//CHOOSE->Destroy();
			//CHOOSE = nullptr;
			return;
		}
	}

	if (InitCurState() == SCENES::COIN_INSERT)
	{
		COININSERT->SetActive(true); // 코인 인서트 장면 활성화

		if (true == UEngineInput::GetInst().IsDown('F'))
		{
			COIN_NUMBER += 1;
			COINs->SetValue(COIN_NUMBER);
		}

		// 코인을 넣고 스테이지 선택 화면으로 전환
		if (COIN_NUMBER > 0 && true == UEngineInput::GetInst().IsDown(VK_SPACE))
		{
			ISPASS_COIN_INSERT = true;
			COININSERT->Destroy();
			COININSERT = nullptr;
			return;
		}
	}

	if (InitCurState() == SCENES::ANI_OP)
	{
		COINs->SetActive(true); // 스코어 (코인) 활성화

		// 오프닝 애니메이션이 끝났을 때
		if (TITLE->MAINRENDERER->IsCurAnimationEnd() == true)
		{
			CHANGEDELAY += _DeltaTime;
			if (CHANGEDELAY >= 4.0f)
			{
				ISPASS_ANI_OP = true;
				TITLE->Destroy(); // 타이틀로고 액터 삭제
				TITLE = nullptr;
				CHANGEDELAY = 0.0f;
				return;
			}
		}

		// 애니메이션 도중 키를 눌렀을 때 (인서트 코인 장면으로 전환)
		if (true == UEngineInput::GetInst().IsDown(VK_SPACE) || true == UEngineInput::GetInst().IsDown('F'))
		{
			ISPASS_ANI_OP = true;
			TITLE->Destroy(); // 타이틀로고 액터 삭제
			TITLE = nullptr;
			return;
		}
	}

	if (InitCurState() == SCENES::TITLELOGO)
	{
		// 타이틀 로고를 끝까지 봤을때
		if (TITLE->MAINRENDERER->IsCurAnimationEnd() == true)
		{
			CHANGEDELAY += _DeltaTime;
			if (CHANGEDELAY >= 3.0f)
			{
				ISPASS_TITLELOGO = true;
				TITLE->MAINRENDERER->ChangeAnimation("OP_Animation");
				TITLE->BASE00->SetActive(true);
				TITLE->BASE01->SetActive(true);
				TITLE->LEVEL4->SetActive(true);
				TITLE->CREDIT->SetActive(true);
				return;
			}
		}

		// 오프닝 애니메이션으로 넘어갈 때
		if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
		{
			ISPASS_TITLELOGO = true;
			TITLE->MAINRENDERER->ChangeAnimation("OP_Animation");
			TITLE->BASE00->SetActive(true);
			TITLE->BASE01->SetActive(true);
			TITLE->LEVEL4->SetActive(true);
			TITLE->CREDIT->SetActive(true);
			return;
		}

		// 바로 인서트 코인 장면으로 넘어갈 때
		if (true == UEngineInput::GetInst().IsDown('F'))
		{
			ISPASS_TITLELOGO = true;
			ISPASS_ANI_OP = true;
			COINs->SetActive(true); // 스코어 (코인) 활성화
			TITLE->Destroy(); // 타이틀로고 액터 삭제
			TITLE = nullptr;
			return;
		}
	}

}

void ATitleGameMode::OpenPlayLevel()
{
	UEngineAPICore::GetCore()->OpenLevel("STAGE01");
}
