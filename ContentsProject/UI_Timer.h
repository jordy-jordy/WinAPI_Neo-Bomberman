#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineTimer.h>

// 설명 :
class AUI_Timer : public AActor
{
public:
	// constrcuter destructer
	AUI_Timer();
	~AUI_Timer();

	// delete Function
	AUI_Timer(const AUI_Timer& _Other) = delete;
	AUI_Timer(AUI_Timer&& _Other) noexcept = delete;
	AUI_Timer& operator=(const AUI_Timer& _Other) = delete;
	AUI_Timer& operator=(AUI_Timer&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StartTimer(float StartTimeInSeconds); // 타이머 시작

protected:

private:
	class USpriteRenderer* TOPBAR = nullptr;
	class USpriteRenderer* TIME_MINUTE[1] = { nullptr };
	class USpriteRenderer* TIME_SECOND[2] = { nullptr, nullptr };

	class USpriteRenderer* PLAYMODE_SCORE_ALL = nullptr;
	class USpriteRenderer* PLAYMODE_SCORE_MONSTER = nullptr;

	UEngineTimer Timer; // EngineTimer 객체
	float RemainingTime = 0.0f; // 남은 시간
	bool bTimerRunning = false; // 타이머 실행 여부

	void UpdateUITimer(); // UI 업데이트

};
