#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class APlayer : public AActor
{
public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MoveFunction(FVector2D _Dir);

	void RunSoundPlay();

	void LevelChangeStart();
	void LevelChangeEnd();


protected:

private:
	float Speed = 300.0f;
	int MySpriteIndex = 0;

	class USpriteRenderer* SpriteRenderer;

};

