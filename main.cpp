#include <cstdio>
#include <cstdlib>
#include <cassert>
//#include <Windows.h>

#include "TextureConverter.h"

enum Argument
{
	kApplicationPath,//アプリケーションパス
	kFilePath,//渡されたパス

	NumArgument
};

int main(int argc,char* argv[])
{
	
	//コマンドライン引数指定なし
	if (argc < NumArgument)
	{
		//使い方を表示する
		TextureConverter::OutputUsage();
		return 0;
	}

	//COM ライブラリの初期化
	HRESULT hr = CoInitializeEx(nullptr,COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	//テクスチャコンバータ
	TextureConverter converter;

	//オプションの数
	int numOptions = argc - NumArgument;
	//オプション配列
	char** options = argv + NumArgument;

	//テクスチャ変換
	converter.ConverterTextureWICToDDS(argv[kFilePath], numOptions, options);

	CoUninitialize();

	//system("pause");

	return 0;

}