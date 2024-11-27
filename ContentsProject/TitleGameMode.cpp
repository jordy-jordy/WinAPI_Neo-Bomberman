#include "PreCompile.h"
#include "TitleGameMode.h"

#include <string>

#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineRandom.h>
#include <EngineCore/SpriteRenderer.h>

#include "TitleLogo.h"
#include "CoinInsert.h"
#include "ChooseStage.h"
#include "Score.h"
#include "ContentsEnum.h"
#include "ChooseStage.h"
#include "Transit_Ani.h"
#include "Fade.h"


ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}


void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	UEngineDirectory Dir;

	if (false == Dir.MoveParentToDirectory("Resources//01_TITLE"))
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
		Title_Basic_Dir.MoveParentToDirectory("Resources");
		Title_Basic_Dir.Append("01_TITLE//00_00_BASIC");
		UImageManager::GetInst().LoadFolder(Title_Basic_Dir.GetPathToString());

		UEngineDirectory Title_NeoGeo_Dir;
		Title_NeoGeo_Dir.MoveParentToDirectory("Resources");
		Title_NeoGeo_Dir.Append("01_TITLE//00_Neo-Geo_LOGO");
		UImageManager::GetInst().LoadFolder(Title_NeoGeo_Dir.GetPathToString());

		UEngineDirectory Title_Hudson_Dir;
		Title_Hudson_Dir.MoveParentToDirectory("Resources");
		Title_Hudson_Dir.Append("01_TITLE//02_HUDSON_LOGO");
		UImageManager::GetInst().LoadFolder(Title_Hudson_Dir.GetPathToString());

		UEngineDirectory Title_OP_Animation_Dir;
		Title_OP_Animation_Dir.MoveParentToDirectory("Resources");
		Title_OP_Animation_Dir.Append("01_TITLE//03_OP_ANIMATION");
		UImageManager::GetInst().LoadFolder(Title_OP_Animation_Dir.GetPathToString());

		UEngineDirectory Title_CoinInsert_Dir;
		Title_CoinInsert_Dir.MoveParentToDirectory("Resources");
		Title_CoinInsert_Dir.Append("01_TITLE//04_COIN_INSERT");
		UImageManager::GetInst().LoadFolder(Title_CoinInsert_Dir.GetPathToString());

		UEngineDirectory Title_ChooseStage_Dir;
		Title_ChooseStage_Dir.MoveParentToDirectory("Resources");
		Title_ChooseStage_Dir.Append("01_TITLE//05_CHOOSE_STAGE");
		UImageManager::GetInst().LoadFolder(Title_ChooseStage_Dir.GetPathToString());

		UEngineDirectory Title_ChooseStage_BLK_Dir;
		Title_ChooseStage_BLK_Dir.MoveParentToDirectory("Resources");
		Title_ChooseStage_BLK_Dir.Append("01_TITLE//05_CHOOSE_STAGE//05_CHOOSE_STAGE_01_CHA_BLK");
		UImageManager::GetInst().LoadFolder(Title_ChooseStage_BLK_Dir.GetPathToString());

		UEngineDirectory Title_ChooseStage_MOVE_Dir;
		Title_ChooseStage_MOVE_Dir.MoveParentToDirectory("Resources");
		Title_ChooseStage_MOVE_Dir.Append("01_TITLE//05_CHOOSE_STAGE//05_CHOOSE_STAGE_03_CHA_MOVE");
		UImageManager::GetInst().LoadFolder(Title_ChooseStage_MOVE_Dir.GetPathToString());

		UEngineDirectory Title_ChooseStage_DRAW_Dir;
		Title_ChooseStage_DRAW_Dir.MoveParentToDirectory("Resources");
		Title_ChooseStage_DRAW_Dir.Append("01_TITLE//05_CHOOSE_STAGE//05_CHOOSE_STAGE_02_CHA_DRAW");
		UImageManager::GetInst().LoadFolder(Title_ChooseStage_DRAW_Dir.GetPathToString());

		UEngineDirectory Title_ChooseStage_CIRCLE_Dir;
		Title_ChooseStage_CIRCLE_Dir.MoveParentToDirectory("Resources");
		Title_ChooseStage_CIRCLE_Dir.Append("01_TITLE//05_CHOOSE_STAGE//05_CHOOSE_STAGE_03_CIRCLE");
		UImageManager::GetInst().LoadFolder(Title_ChooseStage_CIRCLE_Dir.GetPathToString());

		UImageManager& BlueCount = UImageManager::GetInst();
		BlueCount.CuttingSprite("BlueCount.png", { 34, 32 });

		UImageManager& PinkCount = UImageManager::GetInst();
		PinkCount.CuttingSprite("PinkCount.png", { 34, 32 });

		UImageManager& YellowCount = UImageManager::GetInst();
		YellowCount.CuttingSprite("YellowCount.png", { 34, 32 });

		UEngineDirectory Title_Transit_Animation_Dir;
		Title_Transit_Animation_Dir.MoveParentToDirectory("Resources");
		Title_Transit_Animation_Dir.Append("01_TITLE//06_TRASIT_ANIMATION");
		UImageManager::GetInst().LoadFolder(Title_Transit_Animation_Dir.GetPathToString());
	}


	// 네오지오 로고 장면 세팅
	TITLE = GetWorld()->SpawnActor<UTitleLogo>();

	// 코인 충전 장면 세팅
	COININSERT = GetWorld()->SpawnActor<UCoinInsert>();
	COININSERT->SetActive(false);
	COININSERT->SetScore_Coin(COINs);

	// 스테이지 선택 장면 세팅
	CHOOSE = GetWorld()->SpawnActor<UChooseStage>();
	CHOOSE->SetActive(false);

	// 전환 애니메이션 장면 세팅
	TRANSIT = GetWorld()->SpawnActor<ATransit_Ani>();
	TRANSIT->SetActive(false);

	// 스코어(코인) 세팅
	COINs = GetWorld()->SpawnActor<AScore>();
	COINs->SetTextSpriteName("Title_countdown_24x24.png");
	COINs->SetActorLocation({ 600, 440 });
	COINs->SetTextScale({ 16, 16 });
	COINs->SetAlignment(AScore::Alignment::Right);
	COINs->SetOrder(ERenderOrder::TEXT_UI);
	COINs->SetDigitCount(DIGITCOUNT_Coins);
	COINs->SetValue(COIN_NUMBER);
	COINs->SetActive(false);

	// 스코어(남은 시간) 세팅 < 스테이지 선택 장면 >
	TIMEs_StageChoose = GetWorld()->SpawnActor<AScore>();
	TIMEs_StageChoose->SetTextSpriteName("BlueCount.png");
	TIMEs_StageChoose->SetActorLocation({ 502, 104 });
	TIMEs_StageChoose->SetTextScale({ 32, 32 });
	TIMEs_StageChoose->SetAlignment(AScore::Alignment::Left);
	TIMEs_StageChoose->SetOrder(ERenderOrder::TEXT_UI);
	TIMEs_StageChoose->SetDigitCount(DIGITCOUNT_StageChooseTime);
	TIMEs_StageChoose->SetActive(true);

	// 페이드 세팅
	Actor_Fade = GetWorld()->SpawnActor<AFade>();
	Actor_Fade->SetFadeSpeed(1.5f);
	Actor_Fade->SetActive(false);

	// 고정 이미지 (레벨4, 크레딧) 세팅
	LEVEL4 = CreateDefaultSubObject<USpriteRenderer>();
	LEVEL4->SetSprite("Level-4_112x16.png");
	LEVEL4->SetOrder(ERenderOrder::BACKGROUND1);
	LEVEL4->SetSpriteScale(1.0f);
	LEVEL4->SetPivotType(PivotType::Top);
	LEVEL4->SetComponentLocation({ 312, 432 });
	LEVEL4->SetActive(false);

	CREDIT = CreateDefaultSubObject<USpriteRenderer>();
	CREDIT->SetSprite("Credits_112x16.png");
	CREDIT->SetOrder(ERenderOrder::BACKGROUND1);
	CREDIT->SetSpriteScale(1.0f);
	CREDIT->SetPivotType(PivotType::Top);
	CREDIT->SetComponentLocation({ 488, 432 });
	CREDIT->SetActive(false);

}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (InitCurState() == SCENES::NONE)
	{
		return;
	}

	if (InitCurState() == SCENES::ANI_TRANSIT)
	{
		if (ISFIRSTFADE_ANI_TRANSIT == false)
		{
			Actor_Fade->SetActive(false);
			ISFIRSTFADE_ANI_TRANSIT = true;
		}

		if (TRANSIT != nullptr)
		{
			TRANSIT->SetActive(true);

			if (TRANSIT->MAINRENDERER->IsCurAnimationEnd() == true)
			{
				Actor_Fade->SetActive(true);
				if (ISFADING_ANI_TRANSIT == false)
				{
					Actor_Fade->FadeIn();
					ISFADING_ANI_TRANSIT = true;
				}

				TimeEventer.PushEvent(2.0f, std::bind(&ATitleGameMode::OpenPlayLevel, this), false, false);
				TimeEventer.PushEvent(2.0f, std::bind(&ATransit_Ani::DestroyChoose, TRANSIT), false, false);
			}

			if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
			{
				Actor_Fade->SetActive(true);
				if (ISFADING_ANI_TRANSIT == false)
				{
					Actor_Fade->FadeIn();
					ISFADING_ANI_TRANSIT = true;
				}

				TimeEventer.PushEvent(2.0f, std::bind(&ATitleGameMode::OpenPlayLevel, this), false, false);
				TimeEventer.PushEvent(2.0f, std::bind(&ATransit_Ani::DestroyChoose, TRANSIT), false, false);
			}
		}

		if (TRANSIT->IsDestroy() == true)
		{
			TRANSIT = nullptr;
		}

	}

	if (InitCurState() == SCENES::CHOOSE_STAGE)
	{
		if (IsStopTime == false)
		{
			TIMEs_StageChoose->SetActive(true);
			StageChooseTime_NUMBER -= _DeltaTime;
			TIMEs_StageChoose->SetValue(static_cast<int>(StageChooseTime_NUMBER));
		}

		if (StageChooseTime_NUMBER < 0)
		{
			StageChooseTime_NUMBER = 0.0f;
		}

		if (ISFIRSTFADE_CHOOSE_STAGE == false)
		{
			// 페이드 아웃 효과 실행
			Actor_Fade->SetActive(true);
			Actor_Fade->FadeOut();
			ISFIRSTFADE_CHOOSE_STAGE = true;
		}

		if (CHOOSE != nullptr)
		{
			// 스테이지 선택 화면 활성화
			CHOOSE->SetActive(true);

			if (CHOOSE->GetIsStageONE() == true && UEngineInput::GetInst().IsDown(VK_SPACE))
			{
				StopTIme();

				// 1.5초 뒤에 페이드 인 실행
				TimeEventer.PushEvent(1.5f, std::bind(&AFade::FadeIn, Actor_Fade), false, false);

				// 3초 뒤에 스테이지 선택 삭제
				TimeEventer.PushEvent(3.0f, std::bind(&UChooseStage::DestroyChoose, CHOOSE), false, false);

				return;
			}
		}

		// CHOOSE 가 삭제 되었으면 포인터도 null 로 초기화
		if (CHOOSE->IsDestroy() == true)
		{
			TIMEs_StageChoose->SetActive(false);
			CHOOSE = nullptr;
			ISPASS_CHOOSE_STAGE = true;
		}
	}

	if (InitCurState() == SCENES::COIN_INSERT)
	{
		if (COININSERT != nullptr)
		{
			COININSERT->SetActive(true); // 코인 인서트 장면 활성화
			
			if (true == UEngineInput::GetInst().IsDown('F'))
			{
				COIN_NUMBER += 1;
				COINs->SetValue(COIN_NUMBER);
			}

			// 코인을 넣고 스테이지 선택 화면으로 전환
			if (COIN_NUMBER > 0 && true == UEngineInput::GetInst().IsDown(VK_SPACE))
			{
				COININSERT->Destroy();
				COININSERT = nullptr;
				return;
			}
		}

		if (COININSERT == nullptr)
		{
			ISPASS_COIN_INSERT = true;
		}
	}

	if (InitCurState() == SCENES::ANI_OP)
	{
		if (COINs != nullptr)
		{
			COINs->SetActive(true); // 스코어 (코인) 활성화
		}

		if (TITLE != nullptr)
		{
			// 오프닝 애니메이션이 끝났을 때
			if (TITLE->MAINRENDERER->IsCurAnimationEnd() == true)
			{
				CHANGEDELAY += _DeltaTime;
				if (CHANGEDELAY >= 3.5f)
				{
					TITLE->Destroy(); // 타이틀로고 액터 삭제
					TITLE = nullptr;
					CHANGEDELAY = 0.0f;
					return;
				}
			}

			// 애니메이션 도중 키를 눌렀을 때 (인서트 코인 장면으로 전환)
			if (true == UEngineInput::GetInst().IsDown(VK_SPACE) || true == UEngineInput::GetInst().IsDown('F'))
			{
				TITLE->Destroy(); // 타이틀로고 액터 삭제
				TITLE = nullptr;
				return;
			}
		}

		if (TITLE == nullptr)
		{
			ISPASS_ANI_OP = true;
		}
	}

	if (InitCurState() == SCENES::TITLELOGO)
	{
		// 타이틀 로고를 끝까지 봤을때
		if (TITLE->MAINRENDERER->IsCurAnimationEnd() == true)
		{
			CHANGEDELAY += _DeltaTime;
			if (CHANGEDELAY >= 3.0f)
			{
				ISPASS_TITLELOGO = true;
				TITLE->MAINRENDERER->ChangeAnimation("OP_Animation");
				TITLE->BASE00->SetActive(true);
				TITLE->BASE01->SetActive(true);
				LEVEL4->SetActive(true);
				CREDIT->SetActive(true);
				return;
			}
		}

		// 오프닝 애니메이션으로 넘어갈 때
		if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
		{
			ISPASS_TITLELOGO = true;
			TITLE->MAINRENDERER->ChangeAnimation("OP_Animation");
			TITLE->BASE00->SetActive(true);
			TITLE->BASE01->SetActive(true);
			LEVEL4->SetActive(true);
			CREDIT->SetActive(true);
			return;
		}

		// 바로 인서트 코인 장면으로 넘어갈 때
		if (true == UEngineInput::GetInst().IsDown('F'))
		{
			ISPASS_TITLELOGO = true;
			ISPASS_ANI_OP = true;
			COINs->SetActive(true); // 스코어 (코인) 활성화
			TITLE->Destroy(); // 타이틀로고 액터 삭제
			TITLE = nullptr;
			LEVEL4->SetActive(true);
			CREDIT->SetActive(true);
			return;
		}
	}

}

void ATitleGameMode::OpenPlayLevel()
{
	UEngineAPICore::GetCore()->OpenLevel("STAGE01");
}
