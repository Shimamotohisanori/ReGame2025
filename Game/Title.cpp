#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "SoundManager.h"

Title::Title()
{
	
}
Title::~Title()
{

}

bool Title::Start()
{
	m_titleSprite.Init("Assets/sprite/title1.dds", 1920.0f, 1080.0f);

	m_fontRender.SetText(L"Enter to Start");
	m_fontRender.SetPosition(-475.0f, -300.0f,-10.0f);
	m_fontRender.SetScale(3.0f);
	//PlayingSound()を使用するため、SoundManagerのインスタンスを取得。
	SoundManager* sound = FindGO<SoundManager>("soundManager");
	//BGMの再生。
	m_titleBGM = sound->PlayingSound(Sound::enSound_OPBGM);
	

	return true;
}
void Title::Update()
{
	switch (m_state) {
	case enState_FadeIn:
		m_currentAlpha -= 0.5f * g_gameTime->GetFrameDeltaTime();
		if (m_currentAlpha <= 0.0f) {
			m_currentAlpha = 0.0f;
			m_state = enState_FadeOut; // フェードアウト状態に遷移
		}
		break;
	case enState_FadeOut:
		m_currentAlpha += 0.5f * g_gameTime->GetFrameDeltaTime();
		if (m_currentAlpha >= 1.0f) {
			m_currentAlpha = 1.0f;
			m_state = enState_FadeIn; // フェードイン状態に遷移
		}
		break;
	}

	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		//PlayingSound()を使用するため、SoundManagerのインスタンスを取得。
		SoundManager* sound = FindGO<SoundManager>("soundManager");
		//BGMの再生。
		m_titleDecisionSE = sound->PlayingSound(Sound::enSound_DecisionSE, false);

		DeleteGO(m_titleBGM);

		NewGO<Game>(0, "Game");
		DeleteGO(this);
	}
}
void Title::Render(RenderContext& rc)
{
	m_titleSprite.Draw(rc);
	if( m_currentAlpha > 0.0f) {
		m_fontRender.SetColor(0.0f, 0.0f ,0.0f, m_currentAlpha);
		m_fontRender.Draw(rc);
	}
}