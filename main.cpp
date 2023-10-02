#include <cstdio>
#include <cstdlib>
#include <cassert>
//#include <Windows.h>
#include "DirectXTex.h"
#include "TextureConverter.h"

enum Argument
{
	kApplicationPath,//�A�v���P�[�V�����p�X
	kFilePath,//�n���ꂽ�p�X

	NumArgument
};

int main(int argc,char* argv[])
{
	
	assert(argc >= NumArgument);

	//COM ���C�u�����̏�����
	HRESULT hr = CoInitializeEx(nullptr,COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	//�e�N�X�`���R���o�[�^
	TextureConverter converter;

	//�e�N�X�`���ϊ�
	converter.CovertTextureWICToDDS(argv[kFilePath]);

	CoUninitialize();

	system("pause");

	return 0;

}