#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AEnding : public AActor
{
public:
	// constrcuter destructer
	AEnding();
	~AEnding();

	// delete Function
	AEnding(const AEnding& _Other) = delete;
	AEnding(AEnding&& _Other) noexcept = delete;
	AEnding& operator=(const AEnding& _Other) = delete;
	AEnding& operator=(AEnding&& _Other) noexcept = delete;

	class USpriteRenderer* BACKGROUND = nullptr;
	class USpriteRenderer* GIRL = nullptr;
	class USpriteRenderer* BOYS = nullptr;
	class USpriteRenderer* THANKS = nullptr;
	class USpriteRenderer* BACK = nullptr;


protected:
	void BeginPlay();
	void Tick(float _DeltaTime);


private:

};
