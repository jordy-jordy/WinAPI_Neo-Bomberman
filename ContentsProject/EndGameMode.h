#pragma once
#include <EngineCore/GameMode.h>

class AEndGameMode : public AGameMode
{
public:
	AEndGameMode();
	~AEndGameMode();

	AEndGameMode(const AEndGameMode& _Other) = delete;
	AEndGameMode(AEndGameMode&& _Other) noexcept = delete;
	AEndGameMode& operator=(const AEndGameMode& _Other) = delete;
	AEndGameMode& operator=(AEndGameMode&& _Other) noexcept = delete;

	void BeginPlay();

protected:

private:

};
