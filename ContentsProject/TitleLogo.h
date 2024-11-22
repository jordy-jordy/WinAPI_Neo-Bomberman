#pragma once
#include <EngineCore/Actor.h>

#include <string>


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

	class USpriteRenderer* MAINRENDERER = nullptr;
	class USpriteRenderer* BASE00 = nullptr;
	class USpriteRenderer* BASE01 = nullptr;
	class USpriteRenderer* LEVEL4 = nullptr;
	class USpriteRenderer* CREDIT = nullptr;


protected:
	void BeginPlay();
	void Tick(float _DeltaTime);

private:
	float Delay = 0.0f;
	float Wait = 3.0f;

};

