#pragma once
#include <EngineBase/Object.h>

class UActorComponent : public UObject
{
public:
	friend class AActor;

	typedef UActorComponent Super;

	UActorComponent();
	~UActorComponent();

	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

	virtual void BeginPlay() {}
	virtual void ComponentTick(float _DeltaTime) {}

	class AActor* GetActor()
	{
		return ParentActor;
	}

	bool IsActive() override
	{
		// 랜더러는 자신을 가진 액터에게 종속된다.
		// 부모도        true            true
		return UObject::IsActive() && GetActor()->IsActive();
	}


	bool IsDestroy() override
	{
		// 부모도        true            true
		return UObject::IsDestroy() || GetActor()->IsDestroy();
	}


protected:

private:
	class AActor* ParentActor;
};

