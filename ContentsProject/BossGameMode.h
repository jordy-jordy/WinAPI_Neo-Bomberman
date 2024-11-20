#pragma once

#include <EngineCore/GameMode.h>


// Ό³Έν :
class ABossGameMode : public AGameMode
{
public:
	// constrcuter destructer
	ABossGameMode();
	~ABossGameMode();

	// delete Function
	ABossGameMode(const ABossGameMode& _Other) = delete;
	ABossGameMode(ABossGameMode&& _Other) noexcept = delete;
	ABossGameMode& operator=(const ABossGameMode& _Other) = delete;
	ABossGameMode& operator=(ABossGameMode&& _Other) noexcept = delete;

	void BeginPlay();

	FVector2D WallTileMapLocation = { 96, 64 };


protected:
	void Tick(float _DeltaTime) override;
	void PlayTileMapInit();
	void PlayerInit();

private:
	class ATileMap* WallTileMap = nullptr;
	USpriteRenderer* SpriteRendererBOSS = nullptr;



};
