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

	void StopDecreaseTime()
	{
		IsZeroTime = true;
	}

	void StartTimer()
	{
		Timer = true;
	}

	void StopTimer()
	{
		Timer = false;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	class AScore* TIME_Minute = nullptr;
	class AScore* TIME_Second = nullptr;
	class AScore* SCORE_Bonus = nullptr;
	class AScore* SCORE_Total = nullptr;

	int DIGIT_Minute = 1;
	int DIGIT_Second = 2;

	float TIME_Remain = 0.0f;
	int SCORENUMBER_Gain = 0;
	int SCORENUMBER_Bonus = 0;

	float TIME_Elapsed = 0.0f;

	bool IsZeroTime = false;

	bool Timer = false;
	float TimerFloat = 0.0f;

	float TimeDereaseSpeed = 120.0f;

};
