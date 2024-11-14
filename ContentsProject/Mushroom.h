#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AMushroom : public AActor
{
public:
	// constrcuter destructer
	AMushroom();
	~AMushroom();

	// delete Function
	AMushroom(const AMushroom& _Other) = delete;
	AMushroom(AMushroom&& _Other) noexcept = delete;
	AMushroom& operator=(const AMushroom& _Other) = delete;
	AMushroom& operator=(AMushroom&& _Other) noexcept = delete;

protected:
	class USpriteRenderer* SpriteRenderer = nullptr;


private:

};
