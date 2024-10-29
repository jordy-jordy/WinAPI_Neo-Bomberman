#pragma once
#include <filesystem>

class UEnginePath
{
public:
	UEnginePath();
	UEnginePath(std::string_view _Path);
	UEnginePath(std::filesystem::path _Path);
	~UEnginePath();


	bool IsExists();
	void MoveParent();

	std::string GetPathToString();


	bool MoveParentToDirectory(std::string_view _Path);

	bool IsDirectory();

	bool IsFile();


protected:
	std::filesystem::path Path;

private:
};

