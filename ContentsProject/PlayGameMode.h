#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>


// ���� :
class APlayGameMode : public AGameMode
{
public:
	// constrcuter destructer
	APlayGameMode();
	~APlayGameMode();

	// delete Function
	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

	FVector2D WindowSize = { 608, 448 };
	FVector2D WallTileMapLocation = { 96, 64 };

	static float StageTime;
	static int PlayerScore;

	void BeginPlay();

	// �÷��� ��� ���� �Լ���
	bool IsMonsterAllDead();

	void PlusScore(int _Score)
	{
		PlayerScore += _Score;
	}

	int GetScore()
	{
		return PlayerScore;
	}

	void StartTIme()
	{
		IsStopTime = false;
	}

	void StopTIme()
	{
		IsStopTime = true;
	}

	// ��� ��� ���� �Լ���
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

	bool GetShowedAllScore()
	{
		return ShowedAllScore;
	}

	bool GetIsPlayEnd()
	{
		return IsPlayEnd;
	}

	void MOVETO_END();



protected:
	void Tick(float _DeltaTime) override;
	void PlayerInit();
	void PlayTileMapInit();
	void MonsterInit();
	void PortalInit();
	void PortalON();
	void MOVETO_RESULT();

private:
	// ���� �÷��� ���  ����
	class ATileMap* WallTileMap = nullptr;
	class APortal* Portal = nullptr;
	class APlayer* Player = nullptr;

	class USpriteRenderer* SpriteRendererSTAGE = nullptr;
	class USpriteRenderer* SpriteRendererSPAWN = nullptr;
	class USpriteRenderer* SpriteRendererPORTAL = nullptr;
	
	class AScore* Minute = nullptr;
	class AScore* Second = nullptr;
	class AScore* Zero = nullptr;
	class AScore* Score = nullptr;

	class AFade* Play_Fade = nullptr;

	bool IsStopTime = false;

	bool IsPlayEnd = false;

	bool IsPlayFaded = false;

	// ��� ��� ����
	class AResult* ResultScene = nullptr;
	class AScore* TIME_Minute = nullptr;
	class AScore* TIME_Second = nullptr;
	class AScore* SCORE_Bonus = nullptr;
	class AScore* SCORE_Total = nullptr;

	class AFade* Result_Fade = nullptr;
	class AFade* ResultToEnd_Fade = nullptr;

	int DIGIT_Minute = 1;
	int DIGIT_Second = 2;

	float TIME_Remain = 0.0f;
	int Prev_TIME_Remain = static_cast<int>(TIME_Remain);
	int SCORENUMBER_Gain = 0;
	int SCORENUMBER_Bonus = 0;

	float TIME_Elapsed = 0.0f;

	bool IsZeroTime = false;

	bool Timer = false;
	float TimerFloat = 0.0f;

	float TimeDereaseSpeed = 120.0f;

	bool ShowedAllScore = false;

	bool IsResultFaded = false;

	float SoundVolume = 1.0f;

	class USoundPlayer SOUND_PLAY;
	bool ON_SOUND_PLAY = false;

	class USoundPlayer PLAYER_MOVESOUND;
	class USoundPlayer PLAYER_TAKEPORTAL;
	bool ON_PLAYER_TAKEPORTAL = false;

	class USoundPlayer SOUND_PORTAL;
	bool ON_SOUND_PORTAL = false;

	class USoundPlayer SOUND_RESULT;
	bool ON_SOUND_RESULT = false;

	class USoundPlayer SOUND_NUMBERSDE;
	bool ON_SOUND_NUMBERSDE = false;

	class USoundPlayer SOUND_GOODRESULT;
	bool ON_SOUND_GOODRESULT = false;

	float TimeFlowing0 = 0.0f;
	float TimeFlowing1 = 0.0f;

	bool IsResultDonefForFade = false;
};

