#pragma once
#include <EngineCore/Actor.h>

// 설명 :
class ATile_Destroy : public AActor
{
public:
	// constrcuter destructer
	ATile_Destroy();
	~ATile_Destroy();

	// delete Function
	ATile_Destroy(const ATile_Destroy& _Other) = delete;
	ATile_Destroy(ATile_Destroy&& _Other) noexcept = delete;
	ATile_Destroy& operator=(const ATile_Destroy& _Other) = delete;
	ATile_Destroy& operator=(ATile_Destroy&& _Other) noexcept = delete;

	void SetWallTileMap(class ATileMap* _TileMap, FIntPoint _Index);

	void Object_Destroy();
	void ClearObjectTile();

	// 겟 스프라이트

protected:
	void Tick(float _DeltaTime) override;

private:
	class ATileMap* WallTileMap = nullptr;
	class USpriteRenderer* SpriteRenderer = nullptr;

	FIntPoint ObjectTileIndex;



};
