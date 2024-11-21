#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
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


protected:

private:
	class USpriteRenderer* TOPBAR = nullptr;
	class USpriteRenderer* COLON = nullptr;

};
