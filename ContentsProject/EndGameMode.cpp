#include "PreCompile.h"
//#include "EndGameMode.h"
//
//#include "Result.h"
//#include "Score.h"
//#include "ContentsEnum.h"
//#include "PlayGameMode.h"
//
//AEndGameMode::AEndGameMode()
//{
//};
//
//
//AEndGameMode::~AEndGameMode()
//{
//};
//
//
//void AEndGameMode::BeginPlay()
//{
//	Super::BeginPlay();
//
//	TIME_Remain = APlayGameMode::StageTime;
//	SCORENUMBER_Gain = APlayGameMode::PlayerScore;
//
//	//AResult* ResultScene = GetWorld()->SpawnActor<AResult>();
//	//ResultScene->SetMode(this);
//
//	// 스코어(타임 - 분) 세팅
//	TIME_Minute = GetWorld()->SpawnActor<AScore>();
//	TIME_Minute->SetTextSpriteName("ResultCount.png");
//	TIME_Minute->SetActorLocation({ 216, 260 });
//	TIME_Minute->SetTextScale({ 32, 20 });
//	TIME_Minute->SetAlignment(AScore::Alignment::Right);
//	TIME_Minute->SetOrder(ERenderOrder::TEXT_UI);
//	TIME_Minute->SetDigitCount(DIGIT_Minute);
//	TIME_Minute->SetActive(true);
//
//	// 스코어(타임 - 초) 세팅
//	TIME_Second = GetWorld()->SpawnActor<AScore>();
//	TIME_Second->SetTextSpriteName("ResultCount.png");
//	TIME_Second->SetActorLocation({ 312, 260 });
//	TIME_Second->SetTextScale({ 32, 20 });
//	TIME_Second->SetAlignment(AScore::Alignment::Right);
//	TIME_Second->SetOrder(ERenderOrder::TEXT_UI);
//	TIME_Second->SetDigitCount(DIGIT_Second);
//	TIME_Second->SetActive(true);
//
//	// 스코어(보너스) 세팅
//	SCORE_Bonus = GetWorld()->SpawnActor<AScore>();
//	SCORE_Bonus->SetTextSpriteName("ResultCount.png");
//	SCORE_Bonus->SetActorLocation({ 312, 324 });
//	SCORE_Bonus->SetTextScale({ 32, 20 });
//	SCORE_Bonus->SetAlignment(AScore::Alignment::Right);
//	SCORE_Bonus->SetOrder(ERenderOrder::TEXT_UI);
//	SCORE_Bonus->SetValue(SCORENUMBER_Bonus);
//	SCORE_Bonus->SetActive(true);
//
//	// 스코어(토탈) 세팅
//	SCORE_Total = GetWorld()->SpawnActor<AScore>();
//	SCORE_Total->SetTextSpriteName("ResultCount.png");
//	SCORE_Total->SetActorLocation({ 312, 388 });
//	SCORE_Total->SetTextScale({ 32, 20 });
//	SCORE_Total->SetAlignment(AScore::Alignment::Right);
//	SCORE_Total->SetOrder(ERenderOrder::TEXT_UI);
//	SCORE_Total->SetValue(SCORENUMBER_Gain);
//	SCORE_Total->SetActive(true);
//
//}
//
//
//void AEndGameMode::Tick(float _DeltaTime)
//{
//	Super::Tick(_DeltaTime);
//
//	SCORENUMBER_Gain = APlayGameMode::PlayerScore;
//
//	if (IsZeroTime == false)
//	{
//		// DecreaseAmount를 부동소수점 오차 없이 정확히 계산
//		float DecreaseAmount = _DeltaTime * TimeDereaseSpeed;
//
//		// TIME_Remain과 TIME_Elapsed 모두 동일한 DecreaseAmount 적용
//		TIME_Remain -= DecreaseAmount;
//		TIME_Elapsed += DecreaseAmount;
//
//		// TIME_Remain이 음수로 내려가는 경우 방지
//		if (TIME_Remain < 0.0f)
//		{
//			DecreaseAmount += TIME_Remain; // 음수로 내려간 만큼 조정
//			TIME_Remain = 0.0f;
//			TIME_Elapsed += DecreaseAmount; // 남은 감소량만큼 누적
//			StopDecreaseTime();
//		}
//	}
//
//	int Remain_M = static_cast<int>(TIME_Remain) / 60;
//	int Remain_S = static_cast<int>(TIME_Remain) % 60;
//
//	// TIME_Remain이 음수가 되는 것을 방지했으므로 여기서 추가 처리 불필요
//
//	TIME_Minute->SetValue(Remain_M);
//	TIME_Second->SetValue(Remain_S);
//
//	int Bonus = static_cast<int>(TIME_Elapsed) * 10;
//	SCORE_Bonus->SetValue(Bonus);
//
//	if (IsZeroTime == true)
//	{
//		int Total = SCORENUMBER_Gain + Bonus;
//		StartTimer();
//		TimerFloat += _DeltaTime;
//		if (Timer == true && TimerFloat >= 1.3f)
//		{
//			SCORE_Total->SetValue(Total);
//			ShowedAllScore = true;
//		}
//	}
//
//
//
//
//}
//
