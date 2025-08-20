#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"
#include "SoundManager.h"
GameOver::GameOver()
{
}

GameOver::~GameOver()
{
	DeleteGO(m_gameOverBGM);
}

bool GameOver::Start()
{
	GameOverRender.Init("Assets/sprite/GameOver.dds", 1920.0f, 1080.0f);

	//PlayingSound()を使用するため、SoundManagerのインスタンスを取得。
	SoundManager* sound = FindGO<SoundManager>("soundManager");
	//ゲームオーバーBGMの再生。
	m_gameOverBGM = sound->PlayingSound(Sound::enSound_GameOverBGM);
	return true;
}

void GameOver::Update()
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

void GameOver::Render(RenderContext& rc)
{
	GameOverRender.Draw(rc);
}