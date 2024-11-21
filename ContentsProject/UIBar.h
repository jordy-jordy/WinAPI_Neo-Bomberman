#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AUIBar : public AActor
{
public:
	// constrcuter destructer
	AUIBar();
	~AUIBar();

	// delete Function
	AUIBar(const AUIBar& _Other) = delete;
	AUIBar(AUIBar&& _Other) noexcept = delete;
	AUIBar& operator=(const AUIBar& _Other) = delete;
	AUIBar& operator=(AUIBar&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


protected:

private:
	class USpriteRenderer* TOPBAR = nullptr;
	class USpriteRenderer* COLON = nullptr;

};
