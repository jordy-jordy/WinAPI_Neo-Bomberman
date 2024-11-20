#pragma once
#include <EngineCore/Actor.h>


// Ό³Έν :
class ATestMap : public AActor
{
public:
	// constrcuter destructer
	ATestMap();
	~ATestMap();

	// delete Function
	ATestMap(const ATestMap& _Other) = delete;
	ATestMap(ATestMap&& _Other) noexcept = delete;
	ATestMap& operator=(const ATestMap& _Other) = delete;
	ATestMap& operator=(ATestMap&& _Other) noexcept = delete;

	USpriteRenderer* SpriteRenderer = nullptr;

protected:

private:

};
