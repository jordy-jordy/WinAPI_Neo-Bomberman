#pragma once

#include <EngineCore/Actor.h>

// Ό³Έν :
class AResult : public AActor
{
public:
	// constrcuter destructer
	AResult();
	~AResult();

	// delete Function
	AResult(const AResult& _Other) = delete;
	AResult(AResult&& _Other) noexcept = delete;
	AResult& operator=(const AResult& _Other) = delete;
	AResult& operator=(AResult&& _Other) noexcept = delete;

	class USpriteRenderer* STAGECLEAR = nullptr;
	class USpriteRenderer* RESULTINFO = nullptr;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:

};
