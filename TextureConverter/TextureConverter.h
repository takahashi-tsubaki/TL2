#pragma once
#include <string>
#include <windows.h>
#include "DirectXTex.h"
class TextureConverter
{
public:
	///
	//�t�@�C���p�X��DDS�ɕϊ�����
	void CovertTextureWICToDDS(const std::string& filepath);

	void LoadWICTextureFromFile(const std::string& filepath);

	void SeparateFilePath(const std::wstring& filepath);
	void SaveDDSTextureToFile();

private:

	static std::wstring ConvertMultiByteStringToWideString(const std::string& mstring);

	//�摜�̏��
	DirectX::TexMetadata metadeta_;
	//�摜�̃C���[�W�R���e�i
	DirectX::ScratchImage scratchImage_;

	HRESULT result;

	std::wstring directoryPath_;

	std::wstring fileName_;

	std::wstring fileExt_;
};

