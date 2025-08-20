#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "Player.h"
#include "GameOver.h"
#include "GameClear.h"
#include "Box.h"
#include "nature/SkyCube.h"
#include "SoundManager.h"
Game::Game()
{
}
Game::~Game()
{
	DeleteGO(m_gameBGM);
	DeleteGO(m_player);
	DeleteGO(gamecamera);
	for (auto box : m_Boxs)
	{
		DeleteGO(box);
	}
}
bool Game::Start()
{
	InitSky();

	//PlayingSound()を使用するため、SoundManagerのインスタンスを取得。
	SoundManager* sound = FindGO<SoundManager>("soundManager");
	//BGMの再生。
	m_gameBGM = sound->PlayingSound(Sound::enSound_GameBGM);

	m_player = NewGO<Player>(0, "BattleCharacter");

	gamecamera = NewGO<GameCamera>(0,"gamecamera");

	m_levelRender.Init("Assets/modelData/Stage.tkl", [&](LevelObjectData& objData) 
	{
			if (objData.EqualObjectName(L"Box") == true)
			{
				auto box = NewGO<Box>(0,"Box");
				box->m_position = objData.position;
				box->m_scale = objData.scale;
				box->m_rotation = objData.rotation;

				m_Boxs.push_back(box);
				return true;
			}
			return false;
	});
	return true;
}

void Game::Update()
{
	// g_renderingEngine->DisableRaytracing();
	
	if (m_player->m_BoxCount == 5)
	{
		NewGO<GameClear>(0, "GameClear");
		DeleteGO(this);
		
	}

	if (m_player->m_position.y < -1200.0f)
	{
		NewGO<GameOver>(0, "GameOver");
		DeleteGO(this);
	}
}

void Game::InitSky()
{
	//現在の空を廃棄
	DeleteGO(m_skyCube);

	m_skyCube = NewGO<SkyCube>(0, "SkyCube");
	m_skyCube->SetType((EnSkyCubeType)m_skyCubeType); //空の種類を設定

	//環境光の計算のためのIBLテクスチャをセットする。
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 1.0);
}

void Game::Render(RenderContext& rc)
{
	m_levelRender.Draw(rc);
}