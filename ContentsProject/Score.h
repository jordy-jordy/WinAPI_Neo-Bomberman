#pragma once
#include <vector>

#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/SpriteRenderer.h>

// 설명 :
class AScore : public AActor
{
public:
	enum class Alignment
	{
		Left,
		Right
	};

	// constrcuter destructer
	AScore();
	~AScore();

	// delete Function
	AScore(const AScore& _Other) = delete;
	AScore(AScore&& _Other) noexcept = delete;
	AScore& operator=(const AScore& _Other) = delete;
	AScore& operator=(AScore&& _Other) noexcept = delete;

	void SetTextSpriteName(const std::string _Text);

	void SetTextScale(FVector2D _TextScale)
	{
		TextScale = _TextScale;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetOrder(int _Order);
	void SetValue(int _Score);

	void SetAlignment(Alignment _Alignment)
	{
		CurrentAlignment = _Alignment;
	}

	void SetDigitCount(size_t _Digits); // 자리수 설정

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::string TextSpriteName;
	FVector2D TextScale;
	std::vector<class USpriteRenderer*> Renders;

	Alignment CurrentAlignment = Alignment::Left; // 기본값: 왼쪽 정렬
	size_t DigitCount = 1; // 기본 자리수: 1

};

