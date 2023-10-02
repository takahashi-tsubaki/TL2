#include <cstdio>
#include <cstdlib>
#include <cassert>
//#include <Windows.h>
#include "DirectXTex.h"
#include "TextureConverter.h"

enum Argument
{
	kApplicationPath,//アプリケーションパス
	kFilePath,//渡されたパス

	NumArgument
};

int main(int argc,char* argv[])
{
	
	assert(argc >= NumArgument);

	//COM ライブラリの初期化
	HRESULT hr = CoInitializeEx(nullptr,COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	//テクスチャコンバータ
	TextureConverter converter;

	//テクスチャ変換
	converter.CovertTextureWICToDDS(argv[kFilePath]);

	CoUninitialize();

	system("pause");

	return 0;

}