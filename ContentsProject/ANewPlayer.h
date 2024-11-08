#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>

enum class NewPlayerState
{
	Idle,
	Move,
	Attack,
};

// 설명 :
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
	void Attack(float _DeltaTime);

	void SetColImage(std::string_view _ColImageName);

	void PlayerCameraCheck();
	void PlayerGroundCheck(FVector2D MovePos);

	void Gravity(float _DeltaTime);

	// 중력은 만드는 방법이 너무 많다.


protected:

private:
	U2DCollision* CollisionComponent;
	float Speed = 500.0f;
	class UEngineWinImage* ColImage = nullptr;
	class USpriteRenderer* SpriteRenderer = nullptr;

	int IsGround = false;
	bool IsMove = false;
	FVector2D GravityForce = FVector2D::ZERO;

	UFSMStateManager FSM;
};

