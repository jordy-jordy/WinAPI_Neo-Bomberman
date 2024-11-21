#include "PreCompile.h"
#include "BombmanCore.h"
#include <EngineCore/EngineAPICore.h>

#include <EngineBase/EngineDirectory.h>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/ImageManager.h>

#include "TitleGameMode.h"
#include "PlayGameMode.h"
#include "BossGameMode.h"
#include "TileMapGameMode.h"
#include "BossMapGameMode.h"
#include "Player.h"


BombmanCore::BombmanCore()
{
}

BombmanCore::~BombmanCore()
{
}

void BombmanCore::BeginPlay()
{

	UEngineDirectory Dir;

	if (false == Dir.MoveParentToDirectory("Resources//Imgs"))
	{
		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
		return;
	}

	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
		UImageManager::GetInst().Load(FilePath);
	}

	// 타이틀 레벨 리소스 로드
	{
		UEngineDirectory Title_Basic_Dir;
		Title_Basic_Dir.MoveParentToDirectory("Resources//Imgs");
		Title_Basic_Dir.Append("01_TITLE//00_00_BASIC");
		UImageManager::GetInst().LoadFolder(Title_Basic_Dir.GetPathToString());

		UEngineDirectory Title_NeoGeo_Dir;
		Title_NeoGeo_Dir.MoveParentToDirectory("Resources//Imgs");
		Title_NeoGeo_Dir.Append("01_TITLE//00_Neo-Geo_LOGO");
		UImageManager::GetInst().LoadFolder(Title_NeoGeo_Dir.GetPathToString());

		UEngineDirectory Title_Warning_Dir;
		Title_Warning_Dir.MoveParentToDirectory("Resources//Imgs");
		Title_Warning_Dir.Append("01_TITLE//01_WARNING");
		UImageManager::GetInst().LoadFolder(Title_Warning_Dir.GetPathToString());

		UEngineDirectory Title_Hudson_Dir;
		Title_Hudson_Dir.MoveParentToDirectory("Resources//Imgs");
		Title_Hudson_Dir.Append("01_TITLE//02_HUDSON_LOGO");
		UImageManager::GetInst().LoadFolder(Title_Hudson_Dir.GetPathToString());

		UEngineDirectory Title_OP_Animation_Dir;
		Title_OP_Animation_Dir.MoveParentToDirectory("Resources//Imgs");
		Title_OP_Animation_Dir.Append("01_TITLE//03_OP_ANIMATION");
		UImageManager::GetInst().LoadFolder(Title_OP_Animation_Dir.GetPathToString());

		UEngineDirectory Title_CoinInsert_Dir;
		Title_CoinInsert_Dir.MoveParentToDirectory("Resources//Imgs");
		Title_CoinInsert_Dir.Append("01_TITLE//04_COIN_INSERT");
		UImageManager::GetInst().LoadFolder(Title_CoinInsert_Dir.GetPathToString());

		UEngineDirectory Title_ChooseStage_Dir;
		Title_ChooseStage_Dir.MoveParentToDirectory("Resources//Imgs");
		Title_ChooseStage_Dir.Append("01_TITLE//05_CHOOSE_STAGE");
		UImageManager::GetInst().LoadFolder(Title_ChooseStage_Dir.GetPathToString());
	}


	// 플레이어 관련 스프라이트
	{
		UEngineDirectory Play_Player_Dir;
		Play_Player_Dir.MoveParentToDirectory("Resources//Imgs");
		Play_Player_Dir.Append("02_PLAY//04_Player");
		UImageManager::GetInst().LoadFolder(Play_Player_Dir.GetPathToString());

		UImageManager& imgManager = UImageManager::GetInst();
		imgManager.CuttingSprite("MainCharater_White.png", { 64, 64 });
	}

	// 파괴되는 오브젝트 관련 스프라이트
	{
		UEngineDirectory Play_Object_Destroy_Anim_Dir;
		Play_Object_Destroy_Anim_Dir.MoveParentToDirectory("Resources//Imgs");
		Play_Object_Destroy_Anim_Dir.Append("02_PLAY//02_Objects//02_Object//Destroy_Anim");
		UImageManager::GetInst().LoadFolder(Play_Object_Destroy_Anim_Dir.GetPathToString());
	}

	// 타일 관련 스프라이트
	{
		UEngineDirectory Play_TILE_STAGE1_Dir;
		Play_TILE_STAGE1_Dir.MoveParentToDirectory("Resources//Imgs");
		Play_TILE_STAGE1_Dir.Append("02_PLAY//00_Tiles//00_Tiles_00_STAGE");
		UImageManager::GetInst().LoadFolder(Play_TILE_STAGE1_Dir.GetPathToString());

		UEngineDirectory Play_TILE_BOSS_Dir;
		Play_TILE_BOSS_Dir.MoveParentToDirectory("Resources//Imgs");
		Play_TILE_BOSS_Dir.Append("02_PLAY//00_Tiles//00_Tiles_01_BOSS");
		UImageManager::GetInst().LoadFolder(Play_TILE_BOSS_Dir.GetPathToString());

		UEngineDirectory Play_BG_Dir;
		Play_BG_Dir.MoveParentToDirectory("Resources//Imgs");
		Play_BG_Dir.Append("02_PLAY//01_Background");
		UImageManager::GetInst().LoadFolder(Play_BG_Dir.GetPathToString());

		UEngineDirectory Play_Bomb00_Dir;
		Play_Bomb00_Dir.MoveParentToDirectory("Resources//Imgs");
		Play_Bomb00_Dir.Append("02_PLAY//02_Objects//01_Bomb//01_Bomb_00_Idle");
		UImageManager::GetInst().LoadFolder(Play_Bomb00_Dir.GetPathToString());
	}

	// 폭탄 폭발 관련 스프라이트
	{
		UEngineDirectory Play_BombExplode_Dir;
		Play_BombExplode_Dir.MoveParentToDirectory("Resources//Imgs");
		Play_BombExplode_Dir.Append("02_PLAY//02_Objects//01_Bomb//01_Bomb_01_Explode");
		UImageManager::GetInst().LoadFolder(Play_BombExplode_Dir.GetPathToString());

		UImageManager& imgManager = UImageManager::GetInst();
		imgManager.CuttingSprite("ExplodeCenter.png", { 32, 32 });
		imgManager.CuttingSprite("ExplodeDown.png", { 32, 32 });
		imgManager.CuttingSprite("ExplodeDownMid.png", { 32, 32 });
		imgManager.CuttingSprite("ExplodeLeft.png", { 32, 32 });
		imgManager.CuttingSprite("ExplodeLeftMid.png", { 32, 32 });
		imgManager.CuttingSprite("ExplodeRight.png", { 32, 32 });
		imgManager.CuttingSprite("ExplodeRightMid.png", { 32, 32 });
		imgManager.CuttingSprite("ExplodeUp.png", { 32, 32 });
		imgManager.CuttingSprite("ExplodeUpMid.png", { 32, 32 });
	}

	// 몬스터 관련 스프라이트
	// None == 투명 이미지
	{
		UEngineDirectory Play_Monster_None_Dir;
		Play_Monster_None_Dir.MoveParentToDirectory("Resources//Imgs");
		Play_Monster_None_Dir.Append("02_PLAY//03_Monster");
		UImageManager::GetInst().LoadFolder(Play_Monster_None_Dir.GetPathToString());

		UEngineDirectory Play_Mushroom;
		Play_Mushroom.MoveParentToDirectory("Resources//Imgs");
		Play_Mushroom.Append("02_PLAY//03_Monster//01_Mushroom");
		UImageManager::GetInst().LoadFolder(Play_Mushroom.GetPathToString());

		UImageManager& imgManager = UImageManager::GetInst();
		imgManager.CuttingSprite("Mushroom.png", { 64, 64 });

		UEngineDirectory Play_Mushroom_Idle_Dir;
		Play_Mushroom_Idle_Dir.MoveParentToDirectory("Resources//Imgs");
		Play_Mushroom_Idle_Dir.Append("02_PLAY//03_Monster//01_Mushroom_00_Idle");
		UImageManager::GetInst().LoadFolder(Play_Mushroom_Idle_Dir.GetPathToString());

		UEngineDirectory Play_Mushroom_Left_Dir;
		Play_Mushroom_Left_Dir.MoveParentToDirectory("Resources//Imgs");
		Play_Mushroom_Left_Dir.Append("02_PLAY//03_Monster//01_Mushroom_01_Left");
		UImageManager::GetInst().LoadFolder(Play_Mushroom_Left_Dir.GetPathToString());

		UEngineDirectory Play_Mushroom_Right_Dir;
		Play_Mushroom_Right_Dir.MoveParentToDirectory("Resources//Imgs");
		Play_Mushroom_Right_Dir.Append("02_PLAY//03_Monster//01_Mushroom_02_Right");
		UImageManager::GetInst().LoadFolder(Play_Mushroom_Right_Dir.GetPathToString());

		UEngineDirectory Play_Mushroom_Up_Dir;
		Play_Mushroom_Up_Dir.MoveParentToDirectory("Resources//Imgs");
		Play_Mushroom_Up_Dir.Append("02_PLAY//03_Monster//01_Mushroom_03_Up");
		UImageManager::GetInst().LoadFolder(Play_Mushroom_Up_Dir.GetPathToString());

		UEngineDirectory Play_Mushroom_Down_Dir;
		Play_Mushroom_Down_Dir.MoveParentToDirectory("Resources//Imgs");
		Play_Mushroom_Down_Dir.Append("02_PLAY//03_Monster//01_Mushroom_04_Down");
		UImageManager::GetInst().LoadFolder(Play_Mushroom_Down_Dir.GetPathToString());
	}

	// 포탈 관련 스프라이트
	{
		UEngineDirectory Play_PortalOFF_Dir;
		Play_PortalOFF_Dir.MoveParentToDirectory("Resources//Imgs");
		Play_PortalOFF_Dir.Append("02_PLAY//02_Objects//03_Portal//OFF");
		UImageManager::GetInst().LoadFolder(Play_PortalOFF_Dir.GetPathToString());

		UEngineDirectory Play_PortalON0_Dir;
		Play_PortalON0_Dir.MoveParentToDirectory("Resources//Imgs");
		Play_PortalON0_Dir.Append("02_PLAY//02_Objects//03_Portal//ON_00");
		UImageManager::GetInst().LoadFolder(Play_PortalON0_Dir.GetPathToString());

		UEngineDirectory Play_PortalON1_Dir;
		Play_PortalON1_Dir.MoveParentToDirectory("Resources//Imgs");
		Play_PortalON1_Dir.Append("02_PLAY//02_Objects//03_Portal//ON_01");
		UImageManager::GetInst().LoadFolder(Play_PortalON1_Dir.GetPathToString());
	}

	// UI 관련 스프라이트
	{
		UEngineDirectory Play_UI_TOP;
		Play_UI_TOP.MoveParentToDirectory("Resources//Imgs");
		Play_UI_TOP.Append("04_UI//Score");
		UImageManager::GetInst().LoadFolder(Play_UI_TOP.GetPathToString());

		UEngineDirectory Global_UI_SelectCount;
		Global_UI_SelectCount.MoveParentToDirectory("Resources//Imgs");
		Global_UI_SelectCount.Append("04_UI//SelectCount");
		UImageManager::GetInst().LoadFolder(Global_UI_SelectCount.GetPathToString());

		UEngineDirectory Title_UI;
		Title_UI.MoveParentToDirectory("Resources//Imgs");
		Title_UI.Append("04_UI//Title");
		UImageManager::GetInst().LoadFolder(Title_UI.GetPathToString());

		UImageManager& imgManager = UImageManager::GetInst();
		imgManager.CuttingSprite("TimeCount.png", { 12, 12 });
	}

	// 타일 맵 제작용 BG
	{
		UEngineDirectory Play_TestBG_Dir;
		Play_TestBG_Dir.MoveParentToDirectory("Resources//Imgs");
		Play_TestBG_Dir.Append("02_PLAY//EX_BG");
		UImageManager::GetInst().LoadFolder(Play_TestBG_Dir.GetPathToString());
	}

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle(":: LHJ :: Neo-Bomberman ::");

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 200,200 }, { 608, 448 });

	UEngineAPICore::GetCore()->CreateLevel<ATileMapGameMode, AActor>("MAPEDIT");
	UEngineAPICore::GetCore()->CreateLevel<ABossMapGameMode, AActor>("BOSSMAPEDIT");

	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("TITLE");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("STAGE01");
	UEngineAPICore::GetCore()->CreateLevel<ABossGameMode, APlayer>("BOSS");

	UEngineAPICore::GetCore()->OpenLevel("STAGE01");
}

void BombmanCore::Tick()
{
}