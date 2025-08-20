#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "SoundManager.h"
GameClear::GameClear()
{
}

GameClear::~GameClear()
{
	DeleteGO(m_gameClearBGM);
}

bool GameClear::Start()
{
	m_gameClearRender.Init("Assets/sprite/GameClear.dds", 1920.0f, 1080.0f);

	//PlayingSound()を使用するため、SoundManagerのインスタンスを取得。
	SoundManager* sound = FindGO<SoundManager>("soundManager");
	//ゲームクリアBGMの再生。
	m_gameClearBGM = sound->PlayingSound(Sound::enSound_GameClearBGM);
	return true;
}

void GameClear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonY))
	{
		//PlayingSound()を使用するため、SoundManagerのインスタンスを取得。
		SoundManager* sound = FindGO<SoundManager>("soundManager");
		//BGMの再生。
		m_titleDecisionSE = sound->PlayingSound(Sound::enSound_DecisionSE, false);
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	m_gameClearRender.Draw(rc);
}
