#pragma once
#include <EngineCore/Actor.h>
#include <EnginePlatform/EngineSound.h>


// 설명 :
class AResult : public AActor
{
public:
	// constrcuter destructer
	AResult();
	~AResult();

	// delete Function
	AResult(const AResult& _Other) = delete;
	AResult(AResult&& _Other) noexcept = delete;
	AResult& operator=(const AResult& _Other) = delete;
	AResult& operator=(AResult&& _Other) noexcept = delete;

	class USpriteRenderer* STAGECLEAR = nullptr;
	class USpriteRenderer* RESULTINFO = nullptr;
	class USpriteRenderer* RESULTBBMS = nullptr;
	class USpriteRenderer* RESULTSTAMP = nullptr;


	void SetMode(class APlayGameMode* _data);

	bool GetIsInfoMoved()
	{
		return IsInfoMoved;
	}

	bool IsBBMsActive = false;
	bool IsMovingDone = false;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	class APlayGameMode* PlayMode = nullptr;

	FVector2D BBMs_CurPos = { 1000, 204 };
	float BBMs_CurMoveSize = 0.0f;
	float BBMs_TargetDownMoveSize = 10.0f;
	float BBMs_TargetUpMoveSize = -10.0f;
	float BBMs_TargetPosX = 450.0f; // 목표 X 좌표

	bool IsMoved = false;
	bool IsInfoMoved = false;

	FVector2D INFO_CurPos = { -300, 224 };
	FVector2D INFO_CenterPos = { 0, 0 };

	float FlowedTime = 0.0f;

};
