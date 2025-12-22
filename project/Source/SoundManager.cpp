#include "SoundManager.h"
#include <assert.h>
#include <DxLib.h>

SoundManager::SoundManager()
{
	//=== ここにサウンド読み込みを追加 ===

	Load("quiz_start", "data/sound/quiz_start.wav", 100);
	Load("quiz_correct", "data/sound/quiz_correct.wav", 100);
	Load("quiz_wrong", "data/sound/quiz_wrong.wav", 100);
	Load("quiz_bgm", "data/sound/quiz_bgm.wav", 100);

	//=====================================

	for (auto& s : hSounds)
		assert(s.second > 0);
}

SoundManager::~SoundManager()
{
	for (auto& s : hSounds)
	{
		if (s.second > 0)
			DeleteSoundMem(s.second);
	}
	hSounds.clear();
}

void SoundManager::Update()
{
	for (auto& p : playSounds)
		p.second = 0;
}

void SoundManager::Play(const std::string& _name, const bool& _loop)
{
	// 再生中のサウンドがなかったら
	if (playSounds.count(_name) == 0)
	{
		// 再生中サウンドとして追加
		playSounds.insert({ _name, 0 });
	}
	else
	{
		// 再生中の数が許容外かチェック
		playSounds[_name]++;
		if (playSounds[_name] > SAME_TIME_PLAY_MAX)
			return;
	}
	// 再生
	PlaySoundMem(hSounds[_name], _loop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK);
}

void SoundManager::Stop(const std::string& _name)
{
	StopSoundMem(hSounds[_name]);
}

bool SoundManager::IsPlay(const std::string& _name)
{
	return (CheckSoundMem(hSounds[_name]) == TRUE);
}

void SoundManager::Load(const std::string& _name, const std::string& _fileName, const float& _volume)
{
	// サウンド名と読みこんだデータを登録
	hSounds.insert({ _name, LoadSoundMem(_fileName.c_str()) });
	// 音量設定(％)
	ChangeVolumeSoundMem((int)((_volume / 100) * 255), hSounds[_name]);
}
