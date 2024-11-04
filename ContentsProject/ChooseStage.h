#pragma once
#include <EngineCore/Actor.h>

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

protected:

private:

};
