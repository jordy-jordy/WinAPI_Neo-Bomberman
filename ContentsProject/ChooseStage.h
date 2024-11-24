#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineMath.h>

// Ό³Έν :
class UChooseStage : public AActor
{
public:
	// constrcuter destructer
	UChooseStage();
	~UChooseStage();

	// delete Function
	UChooseStage(const UChooseStage& _Other) = delete;
	UChooseStage(UChooseStage&& _Other) noexcept = delete;
	UChooseStage& operator=(const UChooseStage& _Other) = delete;
	UChooseStage& operator=(UChooseStage&& _Other) noexcept = delete;

	void AddActorLocation(FVector2D _Direction)
	{
		Transform.Location += _Direction;
	}

protected:
	void BeginPlay();
	void Tick(float _DeltaTime);


private:
	class USpriteRenderer* Background = nullptr;
	class USpriteRenderer* Basic_UI00 = nullptr;
	class USpriteRenderer* Basic_UI01 = nullptr;

	class USpriteRenderer* CHOOSE_00 = nullptr;
	class USpriteRenderer* CHOOSE_01 = nullptr;

	class USpriteRenderer* BLACKMAN = nullptr;
	class USpriteRenderer* BOMB_MAN = nullptr;

	FVector2D BG_SIZE = { 608, 448 };

	class FTransform Transform;

};
