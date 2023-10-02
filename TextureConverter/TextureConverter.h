#pragma once
#include <string>
#include <windows.h>
class TextureConverter
{
public:
	///
	//�t�@�C���p�X��DDS�ɕϊ�����
	void CovertTextureWICToDDS(const std::string& filepath);

	void LoadWICTextureFromFile(const std::string& filepath);

private:

	static std::wstring ConvertMultiByteStringToWideString(const std::string& mstring);
};

