#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>


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


protected:
	void Tick(float _DeltaTime) override;


private:
	class AEnding* EndingCut = nullptr;

	class AFade* END_Fade = nullptr;

	class ATitleGameMode* TITLE = nullptr;

};

