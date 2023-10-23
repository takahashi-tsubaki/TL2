#include "TextureConverter.h"
#include "DirectXTex.h"
#include <cassert>

using namespace DirectX;

void TextureConverter::CovertTextureWICToDDS(const std::string& filepath)
{
	LoadWICTextureFromFile(filepath);

	SaveDDSTextureToFile();
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filepath)
{
	std::wstring wfilePath = ConvertMultiByteStringToWideString(filepath);

	result = LoadFromWICFile(wfilePath.c_str(), WIC_FLAGS_NONE, &metadeta_, scratchImage_);
	assert(SUCCEEDED(result));

	//
	SeparateFilePath(wfilePath);

}

void TextureConverter::SeparateFilePath(const std::wstring& filepath)
{
	size_t pos1;
	std::wstring excepExt;

	//区切り文字'.'が出てくる一番最後の部分を検索
	pos1 = filepath.rfind('.');
	//検索がヒットしたら
	if (pos1 != std::wstring::npos)
	{
		fileExt_ = filepath.substr(pos1 + 1, filepath.size() - pos1 - 1);
		//
		excepExt = filepath.substr(0,pos1);
	}
	else
	{
		fileExt_ = L"";
		excepExt = filepath;
	}

	pos1 = excepExt.rfind('\\');
	if (pos1 != std::wstring::npos)
	{
		directoryPath_ = excepExt.substr(0,pos1+1);
		//
		fileName_ = excepExt.substr(pos1 + 1, excepExt.size() - pos1 - 1);
		return;
	}

	pos1 = filepath.rfind('/');
	//検索がヒットしたら
	if (pos1 != std::wstring::npos)
	{
		directoryPath_ = excepExt.substr(0, pos1 + 1);
		//
		fileName_ = excepExt.substr(pos1 + 1, excepExt.size() - pos1 - 1);
		return;
	}
	fileExt_ = L"";
	excepExt = filepath;


}

void TextureConverter::SaveDDSTextureToFile()
{
	//
	metadeta_.format = MakeSRGB(metadeta_.format);

	HRESULT result;

	//
	std::wstring filePath = directoryPath_ + fileName_ + L".dds";

	//DDS書き出し
	result = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadeta_,DDS_FLAGS_NONE,filePath.c_str());

	assert(SUCCEEDED(result));

}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mstring)
{
	int filePathBufferSize = MultiByteToWideChar(CP_ACP,0,mstring.c_str(),-1,nullptr,0 );

	std::wstring wString;
	wString.resize(filePathBufferSize);

	MultiByteToWideChar(CP_ACP, 0, mstring.c_str(), -1, &wString[0], filePathBufferSize);

	return wString;
}
