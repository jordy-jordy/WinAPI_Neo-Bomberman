#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineRandom.h>

#include "PlayMap.h"
#include "TileMapGameMode.h"
#include "ATileMap.h"
#include "Player.h"
#include "Bomb.h"
#include "Monster.h"
#include "Mushroom.h"
#include "Portal.h"
#include "Score.h"
#include "UIBar.h"
#include "Fade.h"
#include "Result.h"


float APlayGameMode::StageTime = 121.0f;
int APlayGameMode::PlayerScore = 0;


APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayGameMode::StageTime = 121.0f;
	APlayGameMode::PlayerScore = 0;

	// ���� ��� �ε�
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Sounds//01_PLAY");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineSound::Load(FilePath);
		}
	}

	Play_Fade = GetWorld()->SpawnActor<AFade>();
	Play_Fade->SetFadeSpeed(1.5f);
	Play_Fade->SetActive(false);

	Result_Fade = GetWorld()->SpawnActor<AFade>();
	Result_Fade->SetFadeSpeed(1.5f);
	Result_Fade->SetActive(false);

	ResultToEnd_Fade = GetWorld()->SpawnActor<AFade>();
	ResultToEnd_Fade->SetFadeOrder(30000);
	ResultToEnd_Fade->SetFadeSpeed(1.2f);
	ResultToEnd_Fade->SetActive(false);

	///////////////////////////////////////////////////////////////////// �÷��� ��� ����
	// ��׶��� ����
	APlayMap* STAGE1_BG = GetWorld()->SpawnActor<APlayMap>();
	SpriteRendererSTAGE = STAGE1_BG->SpriteRenderer;
	SpriteRendererSTAGE->ChangeAnimation("Stage1_BG");

	// UI�� ����
	AUIBar* UI_TOP = GetWorld()->SpawnActor<AUIBar>();

	// ���ھ�(�ð�) ����
	Minute = GetWorld()->SpawnActor<AScore>();
	Minute->SetTextSpriteName("TimeCount.png");
	Minute->SetActorLocation({ 282, 24 });
	Minute->SetTextScale({ 16, 12 });
	Minute->SetAlignment(AScore::Alignment::Left);
	Minute->SetOrder(ERenderOrder::TEXT_UI);

	Second = GetWorld()->SpawnActor<AScore>();
	Second->SetTextSpriteName("TimeCount.png");
	Second->SetActorLocation({ 314, 24 });
	Second->SetTextScale({ 16, 12 });
	Second->SetAlignment(AScore::Alignment::Left);
	Second->SetOrder(ERenderOrder::TEXT_UI);

	Zero = GetWorld()->SpawnActor<AScore>();
	Zero->SetTextSpriteName("TimeCount.png");
	Zero->SetActorLocation({ 314, 24 });
	Zero->SetTextScale({ 16, 12 });
	Zero->SetAlignment(AScore::Alignment::Left);
	Zero->SetOrder(ERenderOrder::TEXT_UI);
	Zero->SetValue(0);
	Zero->SetActive(false);

	// ���ھ�(����) ����
	Score = GetWorld()->SpawnActor<AScore>();
	Score->SetTextSpriteName("BarScoreNumber.png");
	Score->SetActorLocation({ 264, 23 });
	Score->SetTextScale({ 16, 14 });
	Score->SetAlignment(AScore::Alignment::Right);
	Score->SetOrder(ERenderOrder::TEXT_UI);

	// Ÿ�ϸ� ����
	PlayTileMapInit();

	// �÷��̾� ����
	PlayerInit();

	// ���� ����
	MonsterInit();

	// ��Ż ����
	PortalInit();

	Player->SetPortal(Portal);

	///////////////////////////////////////////////////////////////////// ��� ��� ����
	TIME_Remain = APlayGameMode::StageTime;
	SCORENUMBER_Gain = APlayGameMode::PlayerScore;

	ResultScene = GetWorld()->SpawnActor<AResult>();
	ResultScene->SetMode(this);
	ResultScene->SetActive(false);

	// ���ھ�(Ÿ�� - ��) ����
	TIME_Minute = GetWorld()->SpawnActor<AScore>();
	TIME_Minute->SetTextSpriteName("ResultCount.png");
	TIME_Minute->SetActorLocation({ 216, 260 });
	TIME_Minute->SetTextScale({ 32, 20 });
	TIME_Minute->SetAlignment(AScore::Alignment::Right);
	TIME_Minute->SetOrder(ERenderOrder::UI_OVERFADE);
	TIME_Minute->SetDigitCount(DIGIT_Minute);
	TIME_Minute->SetActive(false);

	// ���ھ�(Ÿ�� - ��) ����
	TIME_Second = GetWorld()->SpawnActor<AScore>();
	TIME_Second->SetTextSpriteName("ResultCount.png");
	TIME_Second->SetActorLocation({ 312, 260 });
	TIME_Second->SetTextScale({ 32, 20 });
	TIME_Second->SetAlignment(AScore::Alignment::Right);
	TIME_Second->SetOrder(ERenderOrder::UI_OVERFADE);
	TIME_Second->SetDigitCount(DIGIT_Second);
	TIME_Second->SetActive(false);

	// ���ھ�(���ʽ�) ����
	SCORE_Bonus = GetWorld()->SpawnActor<AScore>();
	SCORE_Bonus->SetTextSpriteName("ResultCount.png");
	SCORE_Bonus->SetActorLocation({ 312, 324 });
	SCORE_Bonus->SetTextScale({ 32, 20 });
	SCORE_Bonus->SetAlignment(AScore::Alignment::Right);
	SCORE_Bonus->SetOrder(ERenderOrder::UI_OVERFADE);
	SCORE_Bonus->SetValue(SCORENUMBER_Bonus);
	SCORE_Bonus->SetActive(false);

	// ���ھ�(��Ż) ����
	SCORE_Total = GetWorld()->SpawnActor<AScore>();
	SCORE_Total->SetTextSpriteName("ResultCount.png");
	SCORE_Total->SetActorLocation({ 312, 388 });
	SCORE_Total->SetTextScale({ 32, 20 });
	SCORE_Total->SetAlignment(AScore::Alignment::Right);
	SCORE_Total->SetOrder(ERenderOrder::UI_OVERFADE);
	SCORE_Total->SetValue(SCORENUMBER_Gain);
	SCORE_Total->SetActive(false);
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	///////////////////////////////////////////////////////////////////// �÷��� ��� ����
	if (IsPlayEnd == false)
	{
		if (ON_SOUND_PLAY == false)
		{
			SOUND_PLAY = UEngineSound::Play("01Play_00_Stage1.mp3");
			SOUND_PLAY.SetVolume(SoundVolume);
			ON_SOUND_PLAY = true;
		}

		if (IsPlayFaded == false)
		{
			Play_Fade->SetActive(true);
			Play_Fade->FadeOut();
			IsPlayFaded = true;
		}

		Score->SetValue(PlayerScore);

		IsMonsterAllDead();

		if (Portal->GET_ISCANMOVE() == true)
		{
			StopTIme();
			MOVETO_RESULT();
		}

		if (true == UEngineInput::GetInst().IsDown('L'))
		{
			UEngineAPICore::GetCore()->OpenLevel("MAPEDIT");
		}

		if (IsStopTime == false)
		{
			StageTime -= _DeltaTime;

			int M = static_cast<int>(StageTime) / 60;
			int S = static_cast<int>(StageTime) % 60;

			if (S < 0 || M < 0)
			{
				return;
			}

			Minute->SetValue(M);

			if (S >= 10)
			{
				Zero->SetActive(false);
				Second->SetActorLocation({ 314, 24 });
				Second->SetValue(S);
			}
			else if (S < 10)
			{
				Zero->SetActive(true);
				Second->SetActorLocation({ 330, 24 });
				Second->SetValue(S);
			}
		}
	}

	///////////////////////////////////////////////////////////////////// ��� ��� ����
	if (IsPlayEnd == true)
	{
		SOUND_PLAY.Stop();

		if (ON_SOUND_RESULT == false)
		{
			SOUND_RESULT = UEngineSound::Play("01Play_07_StageClear.mp3");
			SOUND_RESULT.SetVolume(SoundVolume);
			ON_SOUND_RESULT = true;
		}

		if (IsResultFaded == false)
		{
			Result_Fade->SetActive(true);
			Result_Fade->IsHalfFadeActive();
			Result_Fade->SetFadeInLimite(0.75f);
			Result_Fade->FadeIn();
			IsResultFaded = true;
		}

		ResultScene->SetActive(true);

		bool InfoMovingCheck = ResultScene->GetIsInfoMoved();
		if (InfoMovingCheck != true)
		{
			return;
		}

		TimeFlowing0 += _DeltaTime;
		if (TimeFlowing0 <= 0.3f)
		{
			return;
		}

		int CurRemain_M = static_cast<int>(StageTime) / 60;
		int CurRemain_S = static_cast<int>(StageTime) % 60;

		TIME_Minute->SetActive(true);
		TIME_Minute->SetValue(CurRemain_M);
		TIME_Second->SetActive(true);
		TIME_Second->SetValue(CurRemain_S);
		SCORE_Bonus->SetActive(true);
		SCORE_Total->SetActive(true);

		SCORENUMBER_Gain = APlayGameMode::PlayerScore;
		SCORE_Total->SetValue(SCORENUMBER_Gain);

		TimeFlowing1 += _DeltaTime;
		if (TimeFlowing1 <= 1.0f)
		{
			return;
		}

		if (IsZeroTime == false)
		{
			// DecreaseAmount�� �ε��Ҽ��� ���� ���� ��Ȯ�� ���
			float DecreaseAmount = _DeltaTime * TimeDereaseSpeed;

			// TIME_Remain�� TIME_Elapsed ��� ������ DecreaseAmount ����
			StageTime -= DecreaseAmount;
			TIME_Elapsed += DecreaseAmount;

			// ���� ���� TIME_Remain ���� ���
			int Current_TIME_Remain = static_cast<int>(StageTime);

			// TIME_Remain�� ���� �κ��� ���� ���� �ٸ� ���� �Ҹ� ���
			if (Current_TIME_Remain != Prev_TIME_Remain)
			{
				SOUND_NUMBERSDE = UEngineSound::Play("01Play_07_NumberDecrease.wav");
				Prev_TIME_Remain = Current_TIME_Remain; // ���� �� ������Ʈ
			}

			// TIME_Remain�� ������ �������� ��� ����
			if (StageTime < 0.0f)
			{
				DecreaseAmount += StageTime; // ������ ������ ��ŭ ����
				StageTime = 0.0f;
				TIME_Elapsed += DecreaseAmount; // ���� ���ҷ���ŭ ����
				StopDecreaseTime();
			}
		}

		int Remain_M = static_cast<int>(StageTime) / 60;
		int Remain_S = static_cast<int>(StageTime) % 60;

		// TIME_Remain�� ������ �Ǵ� ���� ���������Ƿ� ���⼭ �߰� ó�� ���ʿ�

		TIME_Minute->SetValue(Remain_M);
		TIME_Second->SetValue(Remain_S);

		int Bonus = static_cast<int>(TIME_Elapsed) * 10;
		SCORE_Bonus->SetValue(Bonus);

		if (IsZeroTime == true)
		{
			int Total = SCORENUMBER_Gain + Bonus;
			StartTimer();
			TimerFloat += _DeltaTime;
			if (Timer == true && TimerFloat >= 1.3f)
			{
				if (ON_SOUND_NUMBERSDE == false)
				{
					SOUND_NUMBERSDE = UEngineSound::Play("01Play_07_NumberDecrease.wav");
					ON_SOUND_NUMBERSDE = true;
				}

				SCORE_Bonus->SetDigitCount(1);
				SCORE_Bonus->SetValue(0);
				SCORE_Total->SetValue(Total);
				ShowedAllScore = true;
				StopTimer();
			}
		}

		if (ResultScene->IsBBMsActive == true)
		{
			if (ON_SOUND_GOODRESULT == false)
			{
				SOUND_GOODRESULT = UEngineSound::Play("01Play_07_ResultsGood.mp3");
				ON_SOUND_GOODRESULT = true;
			}
		}

		if (ResultScene->IsMovingDone == true && true == UEngineInput::GetInst().IsDown(VK_SPACE))
		{
			ResultToEnd_Fade->SetActive(true);
			ResultToEnd_Fade->FadeIn();

			TimeEventer.PushEvent(2.5f, std::bind(&APlayGameMode::MOVETO_END, this), false, false);
		}
	}
}

void APlayGameMode::PlayerInit()
{
	std::vector<FIntPoint> PlayerStartPOS = WallTileMap->FindSpriteIndex(AStageTiles::Player_Spawn);

	UEngineRandom StartRandom;
	FIntPoint Point = PlayerStartPOS[StartRandom.RandomInt(0, static_cast<int>(PlayerStartPOS.size()) - 1)];

	FVector2D TileLocation = WallTileMap->IndexToTileLocation(Point) + WallTileMap->GetActorLocation();
	FVector2D HalfTiles = WallTileMap->GetTileHalfSize();
	FVector2D LocalLocation = TileLocation + HalfTiles;
	GetWorld()->GetPawn()->SetActorLocation(LocalLocation);

	Player = GetWorld()->GetPawn<APlayer>();
	Player->SetWallTileMap(WallTileMap);
	Player->SetPlayMode(this);
}

void APlayGameMode::PlayTileMapInit()
{
	WallTileMap = GetWorld()->SpawnActor<ATileMap>();
	WallTileMap->SetActorLocation(WallTileMapLocation);

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

	std::vector<FIntPoint> IDXs_SPAWN = WallTileMap->FindSpriteIndex(4);
	std::vector<FIntPoint> IDXs_PORTAL = WallTileMap->FindSpriteIndex(3);

	Tile* TILEs_SPAWN = nullptr;
	Tile* TILEs_PORTAL = nullptr;

	for (unsigned __int64 i = 0; i < IDXs_SPAWN.size(); i++)
	{
		TILEs_SPAWN = WallTileMap->GetTileRef(IDXs_SPAWN[i]);
		TILEs_SPAWN->SpriteRenderer->SetActive(false);
	}

	for (unsigned __int64 i = 0; i < IDXs_PORTAL.size(); i++)
	{
		TILEs_PORTAL = WallTileMap->GetTileRef(IDXs_PORTAL[i]);
		TILEs_PORTAL->SpriteRenderer->SetActive(false);
	}

	WallTileMap->SetMode(this);
}

void APlayGameMode::MonsterInit()
{
	{
		AMonster* Mushroom = GetWorld()->SpawnActor<AMushroom>();
		Mushroom->SetWallTileMap(WallTileMap);
		FVector2D TileMapLoc = WallTileMap->GetActorLocation();
		FVector2D TileHalfSize = WallTileMap->GetTileHalfSize();
		FIntPoint Index = { 0, 0 };
		FVector2D Mush_Location = WallTileMap->IndexToTileLocation(Index);
		FVector2D LocalLoc = Mush_Location + TileMapLoc + TileHalfSize;
		Mushroom->SetActorLocation(LocalLoc);
		Mushroom->SetMode(this);
	}
	{
		AMonster* Mushroom = GetWorld()->SpawnActor<AMushroom>();
		Mushroom->SetWallTileMap(WallTileMap);
		FVector2D TileMapLoc = WallTileMap->GetActorLocation();
		FVector2D TileHalfSize = WallTileMap->GetTileHalfSize();
		FIntPoint Index = { 12, 0 };
		FVector2D Mush_Location = WallTileMap->IndexToTileLocation(Index);
		FVector2D LocalLoc = Mush_Location + TileMapLoc + TileHalfSize;
		Mushroom->SetActorLocation(LocalLoc);
		Mushroom->SetMode(this);
	}
	{
		AMonster* Mushroom = GetWorld()->SpawnActor<AMushroom>();
		Mushroom->SetWallTileMap(WallTileMap);
		FVector2D TileMapLoc = WallTileMap->GetActorLocation();
		FVector2D TileHalfSize = WallTileMap->GetTileHalfSize();
		FIntPoint Index = { 0, 11 };
		FVector2D Mush_Location = WallTileMap->IndexToTileLocation(Index);
		FVector2D LocalLoc = Mush_Location + TileMapLoc + TileHalfSize;
		Mushroom->SetActorLocation(LocalLoc);
		Mushroom->SetMode(this);
	}
}

void APlayGameMode::PortalInit()
{
	Portal = GetWorld()->SpawnActor<APortal>();
	std::vector<FIntPoint> PortalPOS = WallTileMap->FindSpriteIndex(AStageTiles::Object_Portal);
	FVector2D Location = WallTileMap->IndexToTileLocation(PortalPOS[0]);
	FVector2D TileLocation = Location + WallTileMap->GetActorLocation();
	FVector2D HalfTiles = WallTileMap->GetTileHalfSize();
	FVector2D LocalLocation = TileLocation + HalfTiles;
	Portal->SetActorLocation(LocalLocation);
	Portal->SetWallTileMap(WallTileMap);
}

bool APlayGameMode::IsMonsterAllDead()
{
	std::list<AMonster*> AllMonsters;
	AllMonsters = GetWorld()->GetActorsFromClass<AMonster>();

	if (AllMonsters.size() <= 0)
	{
		PortalON();
		return true;
	}

	return false;
}

void APlayGameMode::PortalON()
{
	if (ON_SOUND_PORTAL == false)
	{
		SOUND_PORTAL = UEngineSound::Play("01Play_04_PortalOn.wav");
		SOUND_PORTAL.SetVolume(SoundVolume * 3.5f);
		ON_SOUND_PORTAL = true;
	}

	Portal->PORTAL_SWITCH(true);
}

void APlayGameMode::MOVETO_RESULT()
{
	FVector2D PLAYER_POS = GetWorld()->GetPawn()->GetActorLocation() - WallTileMapLocation;
	FVector2D PORTAL_POS = Portal->GetActorLocation() - WallTileMapLocation;

	FIntPoint PLAYER_INDEX = WallTileMap->LocationToIndex(PLAYER_POS);
	FIntPoint PORTAL_INDEX = WallTileMap->LocationToIndex(PORTAL_POS);

	if (PLAYER_INDEX == PORTAL_INDEX)
	{
		Player->SetActorLocation(Portal->GetActorLocation());

		if (ON_PLAYER_TAKEPORTAL == false)
		{
			PLAYER_TAKEPORTAL = UEngineSound::Play("01Play_05_PortalMove.wav");
			PLAYER_TAKEPORTAL.SetVolume(SoundVolume * 1.5f);
			ON_PLAYER_TAKEPORTAL = true;
		}

		IsPlayEnd = true;
		PLAYER_MOVESOUND = Player->Get_SOUND_MOVE();
		PLAYER_MOVESOUND.Stop();
	}
}

void APlayGameMode::MOVETO_END()
{
	SOUND_GOODRESULT.Stop();
	UEngineAPICore::GetCore()->ResetLevel<APlayGameMode, APlayer>("STAGE01");
	UEngineAPICore::GetCore()->OpenLevel("END");
}




