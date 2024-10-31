#pragma once
#include "SceneComponent.h"

// 설명 :
class USpriteRenderer : public USceneComponent
{
	// 애가 다 담당한다.
	// 클래스를 심화분류해서
public:
	class FrameAnimation
	{
		//int Start = 0;
		//int End = 0;

		std::vector<int> FrameIndex;
		std::vector<float> FrameTime;

		float Inter;
	};

public:
	// constrcuter destructer
	USpriteRenderer();
	~USpriteRenderer();

	// delete Function
	USpriteRenderer(const USpriteRenderer& _Other) = delete;
	USpriteRenderer(USpriteRenderer&& _Other) noexcept = delete;
	USpriteRenderer& operator=(const USpriteRenderer& _Other) = delete;
	USpriteRenderer& operator=(USpriteRenderer&& _Other) noexcept = delete;

	void Render();
	void BeginPlay() override;
	void ComponentTick(float _DeltaTime) override;

	// int를 주는 함수들은 일반적으로 Enum으로 대체해서 넣고 싶을때가 많다.
	// 그런데 그건 커텐츠 만드는 사람이 만드는 자신만의 enum일 것이기 때문에 
	// 템플릿을 사용하여 어떤 enum이건 받게 만드는 방식을 선호한다.
	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetOrder(int _Order);

	int GetOrder()
	{
		return Order;
	}

	FVector2D SetSpriteScale(float _Ratio = 1.0f, int _CurIndex = 0);

	void CreateAnimation(std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame);

protected:

public:
	int Order = 0;
	class UEngineSprite* Sprite = nullptr;
	int CurIndex = 0;
	void SetSprite(std::string_view _Name, int _CurIndex = 0);
};

