#pragma once
#include <string>
#include <windows.h>
class TextureConverter
{
public:
	///
	//ファイルパスをDDSに変換する
	void CovertTextureWICToDDS(const std::string& filepath);

	void LoadWICTextureFromFile(const std::string& filepath);

private:

	static std::wstring ConvertMultiByteStringToWideString(const std::string& mstring);
};

