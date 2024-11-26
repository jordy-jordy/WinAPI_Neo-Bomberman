#include "PreCompile.h"
#include "EndGameMode.h"

#include "Result.h"
#include "Score.h"
#include "ContentsEnum.h"
#include "PlayGameMode.h"

AEndGameMode::AEndGameMode()
{
};


AEndGameMode::~AEndGameMode()
{
};

void AEndGameMode::SetPlayMode(APlayGameMode* _data)
{
	PlayMode = _data;
}

void AEndGameMode::BeginPlay()
{
	Super::BeginPlay();

	AResult* ResultScene = GetWorld()->SpawnActor<AResult>();

	// 스코어(타임 - 분) 세팅
	TIME_Minute = GetWorld()->SpawnActor<AScore>();
	TIME_Minute->SetTextSpriteName("ResultCount.png");
	TIME_Minute->SetActorLocation({ 216, 260 });
	TIME_Minute->SetTextScale({ 32, 20 });
	TIME_Minute->SetAlignment(AScore::Alignment::Right);
	TIME_Minute->SetOrder(ERenderOrder::TEXT_UI);
	TIME_Minute->SetDigitCount(DIGIT_Minute);
	TIME_Minute->SetActive(true);

	// 스코어(타임 - 초) 세팅
	TIME_Second = GetWorld()->SpawnActor<AScore>();
	TIME_Second->SetTextSpriteName("ResultCount.png");
	TIME_Second->SetActorLocation({ 312, 260 });
	TIME_Second->SetTextScale({ 32, 20 });
	TIME_Second->SetAlignment(AScore::Alignment::Right);
	TIME_Second->SetOrder(ERenderOrder::TEXT_UI);
	TIME_Second->SetDigitCount(DIGIT_Second);
	TIME_Second->SetActive(true);

	// 스코어(보너스) 세팅
	SCORE_Bonus = GetWorld()->SpawnActor<AScore>();
	SCORE_Bonus->SetTextSpriteName("ResultCount.png");
	SCORE_Bonus->SetActorLocation({ 312, 324 });
	SCORE_Bonus->SetTextScale({ 32, 20 });
	SCORE_Bonus->SetAlignment(AScore::Alignment::Right);
	SCORE_Bonus->SetOrder(ERenderOrder::TEXT_UI);
	SCORE_Bonus->SetValue(100);
	SCORE_Bonus->SetActive(true);

	// 스코어(토탈) 세팅
	SCORE_Total = GetWorld()->SpawnActor<AScore>();
	SCORE_Total->SetTextSpriteName("ResultCount.png");
	SCORE_Total->SetActorLocation({ 312, 388 });
	SCORE_Total->SetTextScale({ 32, 20 });
	SCORE_Total->SetAlignment(AScore::Alignment::Right);
	SCORE_Total->SetOrder(ERenderOrder::TEXT_UI);
	SCORE_Total->SetValue(100);
	SCORE_Total->SetActive(true);

}


void AEndGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	TIME_Remain -= _DeltaTime;
	
	int Remain_M = static_cast<int>(TIME_Remain) / 60;
	int Remain_S = static_cast<int>(TIME_Remain) % 60;

	TIME_Minute->SetValue(Remain_M);
	TIME_Second->SetValue(Remain_S);



}

