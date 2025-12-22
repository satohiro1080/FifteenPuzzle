#pragma once
#include "../Library/GameObject.h"
#include <unordered_map>
#include <string>
#include "singleton.h"

// シングルトン化してアクセスするときの短縮マクロ
#define SOUND Singleton<SoundManager>::Instance()

/// <summary>
/// サウンドを管理するクラス
/// </summary>
class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	void Update();
	// 再生する
	void Play(const std::string& _name, const bool& _loop = false);
	// 停止する
	void Stop(const std::string& _name);
	// 再生中か
	bool IsPlay(const std::string& _name);

private:
	/// <summary>
	/// サウンド素材を読みこむ
	/// </summary>
	/// <param name="_name">サウンド名</param>
	/// <param name="_fileName">ファイルパス</param>
	/// <param name="_volume">音量設定 0～100(％)</param>
	void Load(const std::string& _name, const std::string& _fileName, const float& _volume);

	std::unordered_map<std::string, int> hSounds; // サウンド素材ハンドル
	std::unordered_map<std::string, int> playSounds; // 再生中のサウンド

	// 同じ音を同時に鳴らせる最大数
	static constexpr int SAME_TIME_PLAY_MAX = 2;
};
