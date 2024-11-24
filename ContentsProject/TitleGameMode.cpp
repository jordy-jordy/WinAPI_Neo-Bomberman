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
}


void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (ISCHANGED == true)
	{
		return;
	}

	std::string SpriteNAME = TITLE->MAINRENDERER->GetCurSpriteName();
	if (SpriteNAME == "03_OP_ANIMATION")
	{
		if (TITLE->MAINRENDERER->IsCurAnimationEnd() == true)
		{
			CHANGEDELAY += _DeltaTime;
			if (CHANGEDELAY >= 3.5f)
			{
				TITLE->DestroyTitleLogo();
				UCoinInsert* COININSERT = GetWorld()->SpawnActor<UCoinInsert>();
				ISCHANGED = true;
				CHANGEDELAY = 0.0f;
				return;
			}
		}

		if (true == UEngineInput::GetInst().IsDown('F'))
		{
			TITLE->DestroyTitleLogo();
			UCoinInsert* COININSERT = GetWorld()->SpawnActor<UCoinInsert>();
			ISCHANGED = true;
		}
		//UEngineAPICore::GetCore()->OpenLevel("STAGE01");
	}

}