#include "PreCompile.h"
#include "EndGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

#include "Ending.h"
#include "Fade.h"
#include "TitleGameMode.h"


AEndGameMode::AEndGameMode()
{
};

AEndGameMode::~AEndGameMode()
{

};

void AEndGameMode::BeginPlay()
{
	Super::BeginPlay();

	END_Fade = GetWorld()->SpawnActor<AFade>();
	END_Fade->SetFadeSpeed(1.5f);
	END_Fade->FadeOut();

	EndingCut = GetWorld()->SpawnActor<AEnding>();
}

void AEndGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
	{
		END_Fade->FadeIn();

		TimeEventer.PushEvent(2.0f, std::bind(&AEndGameMode::MOVETO_TITLE, this), false, false);

	}


}

void AEndGameMode::MOVETO_TITLE()
{
	UEngineAPICore::GetCore()->OpenLevel("TITLE");

}

