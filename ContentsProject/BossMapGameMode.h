#pragma once
#include <EngineCore/GameMode.h>

#include "ATileMap.h"
#include "ContentsEnum.h"


// Ό³Έν :
class ABossMapGameMode : public AGameMode
{
public:

	// constrcuter destructer
	ABossMapGameMode();
	~ABossMapGameMode();

	// delete Function
	ABossMapGameMode(const ABossMapGameMode& _Other) = delete;
	ABossMapGameMode(ABossMapGameMode&& _Other) noexcept = delete;
	ABossMapGameMode& operator=(const ABossMapGameMode& _Other) = delete;
	ABossMapGameMode& operator=(ABossMapGameMode&& _Other) noexcept = delete;

	ABossTiles CurrentTileType = ABossTiles::Wall;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	ATileMap* WallTileMap = nullptr;

	USpriteRenderer* SpriteRendererBOSS = nullptr;

};
