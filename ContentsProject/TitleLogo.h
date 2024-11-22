#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class UTitleLogo : public AActor
{
public:
	// constrcuter destructer
	UTitleLogo();
	~UTitleLogo();

	// delete Function
	UTitleLogo(const UTitleLogo& _Other) = delete;
	UTitleLogo(UTitleLogo&& _Other) noexcept = delete;
	UTitleLogo& operator=(const UTitleLogo& _Other) = delete;
	UTitleLogo& operator=(UTitleLogo&& _Other) noexcept = delete;

	bool CurAniEND();

protected:
	void BeginPlay();
	void Tick(float _DeltaTime);

private:
	class USpriteRenderer* MAINRENDERER = nullptr;
	class USpriteRenderer* BASE00 = nullptr;
	class USpriteRenderer* BASE01 = nullptr;
	class USpriteRenderer* COIN_INSERT = nullptr;


	float Delay = 0.0f;
};

