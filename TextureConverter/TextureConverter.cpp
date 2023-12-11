#include "TextureConverter.h"

#include <windows.h>
using namespace DirectX;

void TextureConverter::ConverterTextureWICToDDS(
    const std::string& filePath, int32_t numOptions, char* options[]) {
	// �e�N�X�`���t�@�C����ǂݍ���
	LoadWICTextureFromFile(filePath);

	SaveDDSTextureToFile(numOptions, options);
}

void TextureConverter::SeparateFilePath(const std::wstring& filePath) {
	size_t pos1;
	std::wstring exceptExt;

	// ��؂蕶��'.'���o�Ă����ԍŌ�̕���������
	pos1 = filePath.rfind('.');
	// �������q�b�g������
	if (pos1 != std::wstring::npos) {
		// ��؂蕶���̌��̃t�@�C���g���q�Ƃ��ĕۑ�
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		// ��؂蕶���̑O�܂ł𔲂��o��
		exceptExt = filePath.substr(0, pos1);
	} else {
		fileExt_ = L"";
		exceptExt = filePath;
	}
	// ��؂蕶��'\\'���o�ăN�X��ԍŌ�̕���������
	pos1 = exceptExt.rfind('\\');
	if (pos1 != std::wstring::npos) {
		// ��؂蕶���̑O�܂ł��f�B���N�g���p�X�Ƃ��ĕۑ�
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		// ��؂蕶���̌����t�@�C�����Ƃ��ĕۑ�
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}
	// ��؂蕶��'/'���o�ăN�X��ԍŌ�̕���������
	pos1 = exceptExt.rfind('/');
	if (pos1 != std::wstring::npos) {
		// ��؂蕶���̑O�܂ł��f�B���N�g���p�X�Ƃ��ĕۑ�
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		// ��؂蕶���̌����t�@�C�����Ƃ��ĕۑ�
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}
	// ��؂蕶�����Ȃ��̂Ńt�@�C�����݂̂Ƃ��Ĉ���
	fileExt_ = L"";
	fileName_ = exceptExt;
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath) {
	HRESULT result;
	std::wstring wfilePath = ConvertMultiByteStringToWideString(filePath);
	// �e�N�X�`����ǂݍ���
	// WIC�e�N�X�`���̃��[�h
	result = LoadFromWICFile(wfilePath.c_str(), WIC_FLAGS_NONE, &metadata_, scratchImage_);
	assert(SUCCEEDED(result));

	SeparateFilePath(wfilePath);
}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& String) {
	// ���C�h������ɕϊ������ۂ̕��������v�Z
	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, String.c_str(), -1, nullptr, 0);

	// ���C�h������
	std::wstring wString;
	wString.resize(filePathBufferSize);

	// ���C�h������ɕϊ�
	MultiByteToWideChar(CP_ACP, 0, String.c_str(), -1, &wString[0], filePathBufferSize);

	return wString;
}

void TextureConverter::SaveDDSTextureToFile(int32_t numOptions, char* options[]) {
	HRESULT result3;

	size_t mipLevel = 0;
	// �~�b�v�}�b�v���x���w�������
	for (int i = 0; i < numOptions; i++) {
		if (std::string(options[i]) == "-ml") {
			// �~�b�v���x���w��
			mipLevel = std::stoi(options[i + 1]);
			break;
		}
	}

	DirectX::ScratchImage mipChain;
	// �~�b�v�}�b�v����
	result3 = DirectX::GenerateMipMaps(
	    scratchImage_.GetImages(), scratchImage_.GetImageCount(), scratchImage_.GetMetadata(),
	    DirectX::TEX_FILTER_DEFAULT, mipLevel, mipChain);
	if (SUCCEEDED(result3)) {
		// �C���[�W�ƃ��^�f�[�^���A�~�b�v�}�b�v�łŒu��������
		scratchImage_ = std::move(mipChain);
		metadata_ = scratchImage_.GetMetadata();
	}

	// ���k�`���ɕϊ�
	DirectX::ScratchImage converted;
	result3 = DirectX::Compress(
	    scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_,
	    DXGI_FORMAT_BC7_UNORM_SRGB,
	    DirectX::TEX_COMPRESS_BC7_QUICK | DirectX::TEX_COMPRESS_SRGB_OUT |
	        DirectX::TEX_COMPRESS_PARALLEL,
	    1.0f, converted);
	if (SUCCEEDED(result3)) {
		scratchImage_ = std::move(converted);
		metadata_ = scratchImage_.GetMetadata();
	}

	HRESULT result2;
	// �o�̓t�@�C������ݒ肷��
	std::wstring filePath = directoryPath_ + fileName_ + L".dds";

	// DDS�t�@�C�������o��
	result2 = SaveToDDSFile(
	    scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_, DDS_FLAGS_NONE,
	    filePath.c_str());
	assert(SUCCEEDED(result2));
}

void TextureConverter::OutputUsage() {
	printf("�摜�t�@�C����WIC�`������DDS�`���ɕϊ����܂��B\n");
	printf("\n"); // �󔒍s
	printf("TextureConverter [�h���C�u:][�p�X][�t�@�C����]\n");
	printf("\n"); // �󔒍s
	printf(" [�h���C�u:][�p�X][�t�@�C����]: �ϊ�������WIC�`���̉摜�t�@�C�����w�肵�܂��B\n");
	printf("\n");
	printf(
	    "[-ml level]: "
	    "�~�b�v���x�����w�肵�܂��B0���w�肷���1x1�܂ł̃t���~�b�v�}�b�v�`�F�[���𐶐����܂��B");
}