#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineBase/FSMStateManager.h>

enum class NewPlayerState
{
	Idle,
	Move,
};

// Ό³Έν :
class ANewPlayer : public AActor
{
public:
	// constrcuter destructer
	ANewPlayer();
	~ANewPlayer();

	// delete Function
	ANewPlayer(const ANewPlayer& _Other) = delete;
	ANewPlayer(ANewPlayer&& _Other) noexcept = delete;
	ANewPlayer& operator=(const ANewPlayer& _Other) = delete;
	ANewPlayer& operator=(ANewPlayer&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelChangeStart() override;

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);

	void SetColImage(std::string_view _ColImageName);
protected:

private:
	float Speed = 500.0f;
	class UEngineWinImage* ColImage = nullptr;
	class USpriteRenderer* SpriteRenderer = nullptr;
	UFSMStateManager FSM;
	int Test;

	static int Hp;
};

