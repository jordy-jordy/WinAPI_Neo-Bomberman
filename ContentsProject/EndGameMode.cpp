#include "PreCompile.h"
#include "EndGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>

#include "Ending.h"
#include "Fade.h"
#include "TitleGameMode.h"

ATitleGameMode* AEndGameMode::TITLELEVEL = nullptr; // 스태틱 멤버 초기화

AEndGameMode::AEndGameMode()
{
};

AEndGameMode::~AEndGameMode()
{

};

void AEndGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 사운드 경로 로드
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Sounds//02_END");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineSound::Load(FilePath);
		}
	}

	END_Fade = GetWorld()->SpawnActor<AFade>();
	END_Fade->SetFadeSpeed(1.5f);
	END_Fade->FadeOut();

	EndingCut = GetWorld()->SpawnActor<AEnding>();
}

void AEndGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (ON_SOUND_ENDROLL == false)
	{
		SOUND_ENDROLL = UEngineSound::Play("023_StaffRoll(Normal).mp3");
		ON_SOUND_ENDROLL = true;
	}

	if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
	{
		END_Fade->FadeIn();

		// TITLE 포인터를 통해 ResetState 호출
		if (TITLELEVEL != nullptr)
		{
			TITLELEVEL->ResetState();
		}

		TimeEventer.PushEvent(1.5f, std::bind(&AEndGameMode::MOVETO_TITLE, this), false, false);
	}


}

void AEndGameMode::MOVETO_TITLE()
{
	SOUND_ENDROLL.Stop();
	UEngineAPICore::GetCore()->OpenLevel("TITLE");
}

