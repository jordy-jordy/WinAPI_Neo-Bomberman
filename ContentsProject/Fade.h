#pragma once
#include <EngineCore/Actor.h>

// ���� :
class AFade : public AActor
{
public:
	static AFade* MainFade;

public:
	// constrcuter destructer
	AFade();
	~AFade();

	// delete Function
	AFade(const AFade& _Other) = delete;
	AFade(AFade&& _Other) noexcept = delete;
	AFade& operator=(const AFade& _Other) = delete;
	AFade& operator=(AFade&& _Other) noexcept = delete;

	// 0 => 1
	void FadeIn();

	// 1 => 0
	void FadeOut();

	void SetFadeSpeed(float _DATA)
	{
		FadeSpeed = _DATA;
	}

	void SetFadeValue(float _DATA)
	{
		FadeValue = _DATA;
	}

	void SetFadeDir(float _DATA)
	{
		FadeDir = _DATA;
	}

	USpriteRenderer* GetRenderer()
	{
		return BackSpriteRenderer;
	}

	bool IsFadeOut = false;
	bool IsFadeIn = false;


protected:

private:
	USpriteRenderer* BackSpriteRenderer;
	void LevelChangeStart() override;
	void FadeChange();
	float FadeValue = 0.0f;
	float FadeDir = 1.0f;
	float FadeSpeed = 1.0f;
	

};
