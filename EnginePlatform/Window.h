#pragma once

// Ό³Έν :
class UWindow
{
public:
	// constrcuter destructer
	UWindow();
	~UWindow();

	// delete Function
	UWindow(const UWindow& _Other) = delete;
	UWindow(UWindow&& _Other) noexcept = delete;
	UWindow& operator=(const UWindow& _Other) = delete;
	UWindow& operator=(UWindow&& _Other) noexcept = delete;

protected:

private:

};
