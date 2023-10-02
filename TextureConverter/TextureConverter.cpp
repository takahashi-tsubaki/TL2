#include "TextureConverter.h"

void TextureConverter::CovertTextureWICToDDS(const std::string& filepath)
{
	LoadWICTextureFromFile(filepath);


}

void TextureConverter::LoadWICTextureFromFile(const std::string& filepath)
{
	std::wstring wfilePath = ConvertMultiByteStringToWideString(filepath);



}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mstring)
{
	int filePathBufferSize = MultiByteToWideChar(CP_ACP,0,mstring.c_str(),-1,nullptr,0 );

	std::wstring wString;
	wString.resize(filePathBufferSize);

	MultiByteToWideChar(CP_ACP, 0, mstring.c_str(), -1, &wString[0], filePathBufferSize);

	return wString;
}
