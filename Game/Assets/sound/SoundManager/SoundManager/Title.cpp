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

	//PlayingSound()を使用するため、SoundManagerのインスタンスを取得。
	SoundManager* sound = FindGO<SoundManager>("soundManager");
	//BGMの再生。
	m_titleBGM = sound->PlayingSound(Sound::enSound_TitleBGM);

	return true;
}

void Title::Update()
{

}

void Title::Render(RenderContext& rc)
{

}
