#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ATransit_Ani : public AActor
{
public:
	// constrcuter destructer
	ATransit_Ani();
	~ATransit_Ani();

	// delete Function
	ATransit_Ani(const ATransit_Ani& _Other) = delete;
	ATransit_Ani(ATransit_Ani&& _Other) noexcept = delete;
	ATransit_Ani& operator=(const ATransit_Ani& _Other) = delete;
	ATransit_Ani& operator=(ATransit_Ani&& _Other) noexcept = delete;
	
	class USpriteRenderer* MAINRENDERER = nullptr;

	void DestroyChoose()
	{
		Destroy();
	}


protected:
	void BeginPlay();
	void Tick(float _DeltaTime);


private:

};
