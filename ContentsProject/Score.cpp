#include "PreCompile.h"
#include "Score.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineTimer.h>

#include "ContentsEnum.h"

AScore::AScore()
{

	for (size_t i = 0; i < 10; i++)
	{
		// 카메라가 움직여도 이녀석은 움직이지 않는다.
		USpriteRenderer* Sprite = CreateDefaultSubObject<USpriteRenderer>();
		Sprite->SetCameraEffect(false);
		Renders.push_back(Sprite);
	}
}


AScore::~AScore()
{
}

void AScore::SetTextSpriteName(const std::string _Text)
{
	TextSpriteName = _Text;

	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetSprite(TextSpriteName);
	}
}

void AScore::BeginPlay()
{
	Super::BeginPlay();


}

void AScore::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AScore::SetOrder(int _Order)
{
	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetOrder(_Order);
	}

}

void AScore::SetValue(int _Score)
{
	std::string Number = std::to_string(_Score);

	if (Renders.size() <= Number.size())
	{
		MSGASSERT("자리수를 넘겼습니다.");
		return;
	}


	FVector2D Pos = FVector2D::ZERO;
	float TotalWidth = Number.size() * TextScale.X;

	// 정렬 방식에 따라 시작 위치 설정
	if (CurrentAlignment == Alignment::Right)
	{
		Pos.X -= TotalWidth; // 오른쪽 정렬
	}

	for (size_t i = 0; i < Number.size(); i++)
	{
		char Value = Number[i] - '0';
		Renders[i]->SetSprite(TextSpriteName, Value);
		Renders[i]->SetComponentScale(TextScale);
		Renders[i]->SetComponentLocation(Pos);
		Pos.X += TextScale.X;
		Renders[i]->SetActive(true);
	}

	for (size_t i = Number.size(); i < Renders.size(); i++)
	{
		Renders[i]->SetActive(false);
	}
}

