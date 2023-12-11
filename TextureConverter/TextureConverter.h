#pragma once
#include <DirectXTex.h>
#include <string>

class TextureConverter {
public:
	/// <summary>
	/// テクスチャをWICからDDSに変換する
	/// </summary>
	/// <param name = "fliePath">ファイルパス</param>
	void ConverterTextureWICToDDS(
	    const std::string& filePath, int32_t numOptions = 0, char* options[] = nullptr);

	/// <summary>
	/// パスとファイル名を分離する
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void SeparateFilePath(const std::wstring& filePath);

	/// <summary>
	/// テクスチャファイル読み込み
	/// </summary>
	/// <param name = "fliePath">ファイルパス</param>
	void LoadWICTextureFromFile(const std::string& filePath);

	static std::wstring ConvertMultiByteStringToWideString(const std::string& String);

	/// <summary>
	/// DDSテクスチャとしてファイル書き出し
	/// </summary>
	void SaveDDSTextureToFile(int32_t numOptions, char* options[]);

	/// <summary>
	/// 使用方法を出力(表示)する
	/// </summary>
	static void OutputUsage();

private:
	// 画像の情報
	DirectX::TexMetadata metadata_;
	// 画像のイメージのコンテナ
	DirectX::ScratchImage scratchImage_;

	// ディレクトリパス
	std::wstring directoryPath_;
	// ファイル名
	std::wstring fileName_;
	// ファイル拡張子
	std::wstring fileExt_;
};