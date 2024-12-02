#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>

#include "TitleGameMode.h"


class AEndGameMode : public AGameMode
{
public:
	// constrcuter destructer
	AEndGameMode();
	~AEndGameMode();

	// delete Function
	AEndGameMode(const AEndGameMode& _Other) = delete;
	AEndGameMode(AEndGameMode&& _Other) noexcept = delete;
	AEndGameMode& operator=(const AEndGameMode& _Other) = delete;
	AEndGameMode& operator=(AEndGameMode&& _Other) noexcept = delete;

	void BeginPlay();

	void MOVETO_TITLE();

	static void SetTITLE(ATitleGameMode* _Data)
	{
		TITLELEVEL = _Data;
	}


protected:
	void Tick(float _DeltaTime) override;


private:
	class AEnding* EndingCut = nullptr;

	class AFade* END_Fade = nullptr;

	static ATitleGameMode* TITLELEVEL; // TitleGameMode¸¦ ÀúÀåÇÒ ½ºÅÂÆ½ ¸â¹ö

	class USoundPlayer SOUND_ENDROLL;
	bool ON_SOUND_ENDROLL = false;


};

