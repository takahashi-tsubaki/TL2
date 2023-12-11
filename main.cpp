#include <cstdio>
#include <cstdlib>
#include <cassert>
//#include <Windows.h>

#include "TextureConverter.h"

enum Argument
{
	kApplicationPath,//�A�v���P�[�V�����p�X
	kFilePath,//�n���ꂽ�p�X

	NumArgument
};

int main(int argc,char* argv[])
{
	
	//�R�}���h���C�������w��Ȃ�
	if (argc < NumArgument)
	{
		//�g������\������
		TextureConverter::OutputUsage();
		return 0;
	}

	//COM ���C�u�����̏�����
	HRESULT hr = CoInitializeEx(nullptr,COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	//�e�N�X�`���R���o�[�^
	TextureConverter converter;

	//�I�v�V�����̐�
	int numOptions = argc - NumArgument;
	//�I�v�V�����z��
	char** options = argv + NumArgument;

	//�e�N�X�`���ϊ�
	converter.ConverterTextureWICToDDS(argv[kFilePath], numOptions, options);

	CoUninitialize();

	//system("pause");

	return 0;

}