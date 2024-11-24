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


ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}


void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	TITLE = GetWorld()->SpawnActor<UTitleLogo>();

	COININSERT = GetWorld()->SpawnActor<UCoinInsert>();
	COININSERT->SetActive(false);
	COININSERT->SetScore_Coin(COINs);

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
	TITLE->SetScore_Coin(COINs);
}


void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('P'))
	{
		UEngineAPICore::GetCore()->OpenLevel("STAGE01");
	}


	if (true == UEngineInput::GetInst().IsDown('F'))
	{
		COIN_NUMBER += 1;
		COINs->SetValue(COIN_NUMBER);
	}


	if (TITLE != nullptr)
	{
		std::string SpriteNAME = TITLE->MAINRENDERER->GetCurSpriteName();
		if (SpriteNAME == "03_OP_ANIMATION")
		{
			if (TITLE->MAINRENDERER->IsCurAnimationEnd() == true)
			{
				CHANGEDELAY += _DeltaTime;
				if (CHANGEDELAY >= 3.0f)
				{
					TITLE->DestroyTitleLogo();
					TITLE = nullptr;
					ISCHANGED = true;
					COININSERT->SetActive(true);
					CHANGEDELAY = 0.0f;
					return;
				}
			}

			if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
			{
				TITLE->DestroyTitleLogo();
				TITLE = nullptr;
				ISCHANGED = true;
				COININSERT->SetActive(true);
				return;
			}
		}
	}

	std::string name = GetWorld()->GetName();
	int a = 0;
}
