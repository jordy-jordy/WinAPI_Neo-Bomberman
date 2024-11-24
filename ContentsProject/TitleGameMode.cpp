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
	COINs->SetActorLocation({ 586, 440 });
	COINs->SetTextScale({ 16, 16 });
	COINs->SetAlignment(AScore::Alignment::Right);
	COINs->SetOrder(ERenderOrder::TEXT_UI);
	COINs->SetDigitCount(DIGITCOUNT);
	COINs->SetValue(COIN_NUMBER);
	COINs->SetActive(false);
}


void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('P'))
	{
		UEngineAPICore::GetCore()->OpenLevel("STAGE01");
	}

	if (InitCurState() == SCENES::CHOOSE_STAGE)
	{

	}





	if (InitCurState() == SCENES::COIN_INSERT)
	{
		if (true == UEngineInput::GetInst().IsDown('F'))
		{
			COIN_NUMBER += 1;
			COINs->SetValue(COIN_NUMBER);
		}

		if (COIN_NUMBER > 0 && true == UEngineInput::GetInst().IsDown(VK_SPACE))
		{
			ISPASS_COIN_INSERT = true;
			CHOOSE->SetActive(true);
			COININSERT->Destroy();
			COININSERT = nullptr;
			COINs->SetActive(false); // 스코어 (코인) 비활성화
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
			if (CHANGEDELAY >= 3.0f)
			{
				ISPASS_ANI_OP = true;
				COININSERT->SetActive(true); // 코인 인서트 장면 활성화
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
			COININSERT->SetActive(true); // 코인 인서트 장면 활성화
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
			COININSERT->SetActive(true); // 코인 인서트 장면 활성화
			TITLE->Destroy(); // 타이틀로고 액터 삭제
			TITLE = nullptr;
			return;
		}
	}



}
