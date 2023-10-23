#pragma once
#include <string>
#include <windows.h>
#include "DirectXTex.h"
class TextureConverter
{
public:
	///
	//ファイルパスをDDSに変換する
	void CovertTextureWICToDDS(const std::string& filepath);

	void LoadWICTextureFromFile(const std::string& filepath);

	void SeparateFilePath(const std::wstring& filepath);
	void SaveDDSTextureToFile();

private:

	static std::wstring ConvertMultiByteStringToWideString(const std::string& mstring);

	//画像の情報
	DirectX::TexMetadata metadeta_;
	//画像のイメージコンテナ
	DirectX::ScratchImage scratchImage_;

	HRESULT result;

	std::wstring directoryPath_;

	std::wstring fileName_;

	std::wstring fileExt_;
};

