#include "PreCompile.h"
#include "TileMapGameMode.h"
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineRandom.h>



ATileMapGameMode::ATileMapGameMode()
{
}

ATileMapGameMode::~ATileMapGameMode()
{
}

void ATileMapGameMode::BeginPlay()
{
	Super::BeginPlay();

	{
		GroundTileMap = GetWorld()->SpawnActor<ATileMap>();
	}

	{
		WallTileMap = GetWorld()->SpawnActor<ATileMap>();
		WallTileMap->Create("00_Tiles", { 13, 11 }, { 32, 32 });

		for (int y = 0; y < 13; y++)
		{
			for (int x = 0; x < 11; x++)
			{
				WallTileMap->SetTileIndex({ y,x }, { 0, 0 }, { 32, 32 }, 0);
			}
		}
	}
}

void ATileMapGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsPress(VK_LBUTTON))
	{
		//FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
		//int CurTileType = static_cast<int>(CurrentTileType);
		//WallTileMap->SetTileLocation(MousePos, static_cast<int>(CurrentTileType));

		FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
		FIntPoint TileIndex = WallTileMap->LocationToIndex(MousePos);

		FVector2D Pivot = FVector2D::ZERO;
		FVector2D SpriteScale = FVector2D(32, 32); 

		if (CurrentTileType == ATiles::Object_Unbroken)
		{
			Pivot = FVector2D(0, -6);
			SpriteScale = FVector2D(32, 44);
		}

		int SpriteIndex = static_cast<int>(CurrentTileType);

		// SetTileIndex�� ����Ͽ� ���� Ÿ�� Ÿ�Կ� �´� �ε��� ����
		WallTileMap->SetTileIndex(TileIndex, Pivot, SpriteScale, SpriteIndex);
	}

	if (true == UEngineInput::GetInst().IsPress(VK_RBUTTON))
	{
		FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
		Tile* Tile = WallTileMap->GetTileRef(MousePos);
		if (nullptr != Tile->SpriteRenderer)
		{
			Tile->SpriteRenderer->Destroy(0.0f);
			Tile->SpriteRenderer = nullptr;
		}
	}

	if (UEngineInput::GetInst().IsDown('Q'))
	{
		// ATiles enum�� ��ȯ�ϸ� ������Ʈ
		CurrentTileType = static_cast<ATiles>((static_cast<int>(CurrentTileType) + 1) % static_cast<int>(ATiles::Max));
	}



	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineSerializer _Ser;
		WallTileMap->Serialize(_Ser);
		UEngineDirectory Dir;

		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}

		Dir.Append("Data");

		std::string SaveFilePath = Dir.GetPathToString() + "\\MapData.Data";
		UEngineFile NewFile = SaveFilePath;
		NewFile.FileOpen("wb");
		NewFile.Write(_Ser);
	}

	if (true == UEngineInput::GetInst().IsPress('P'))
	{
		UEngineRandom Random;
		for (size_t i = 0; i < 10; i++)
		{
			int Value = Random.RandomInt(0, 100);
			UEngineDebug::OutPutString(std::to_string(Value));
		}
	}

	if (true == UEngineInput::GetInst().IsDown('T'))
	{
		UEngineDirectory Dir;

		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}

		Dir.Append("Data");

		std::string SaveFilePath = Dir.GetPathToString() + "\\MapData.Data";
		UEngineFile NewFile = SaveFilePath;
		NewFile.FileOpen("rb");

		UEngineSerializer Ser;
		NewFile.Read(Ser);


		WallTileMap->DeSerialize(Ser);

	}

}