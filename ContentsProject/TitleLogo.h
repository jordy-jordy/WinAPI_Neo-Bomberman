#pragma once
#include <EngineCore/Actor.h>


// ���� :
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

	void DestroyTitleLogo();

	class USpriteRenderer* MAINRENDERER = nullptr;
	class USpriteRenderer* BASE00 = nullptr;
	class USpriteRenderer* BASE01 = nullptr;


protected:
	void BeginPlay();
	void Tick(float _DeltaTime);

private:
	float Delay = 0.0f;
	float Wait = 3.0f;

	class AScore* COINs = nullptr;


};

