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



protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	class AScore* TIME_Minute = nullptr;
	class AScore* TIME_Second = nullptr;
	class AScore* SCORE_Bonus = nullptr;
	class AScore* SCORE_Total = nullptr;

	class APlayGameMode* PlayMode = nullptr;

	int DIGIT_Minute = 1;
	int DIGIT_Second = 2;
	float TIME_Remain = 300.0f;

	float TIME_Local = 0.0f;


};
