#pragma once
#include"sound/SoundSource.h"

//ファイルパスを追加する際は、
//cppのnamespaceと下記のenumを使用してください。
enum Sound {
	enSound_OPBGM,
	enSound_GameBGM,
	enSound_GameOverBGM, //ゲームオーバーBGM
	enSound_GameClearBGM, //ゲームクリアBGM
	enSound_SE, //効果音などのサウンド
	enSound_DecisionSE, //決定SE
	enSound_JUMPSE, //ジャンプSE
	enSound_Num //このステータスは、サウンドの総数を表しているため、この下には追加しないでください。
};
class SoundManager : public IGameObject
{
public:
	SoundManager();
	~SoundManager() {};
	///<summary>
	///指定したサウンドを再生し、再生中のサウンドソースを返します。
	/// </summary>
	/// <param name="number">再生するサウンドを指定します。</param>
	/// <param name="isLoop">サウンドをループ再生するかどうかをしていします。デフォルトは true です。</param>
	/// <param name="volume">再生音量を指定します。デフォルトは1.0fです。</param>
	/// <returns>再生中のサウンドソースへのポインタ。</returns>
	SoundSource* PlayingSound(Sound number, bool isLoop = true, float volume = 1.0f);
};

