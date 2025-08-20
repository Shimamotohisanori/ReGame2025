#include "stdafx.h"
#include "Box.h"
#include "Game.h"
#include "Player.h"
#include "SoundManager.h"
Box::Box()
{
}

Box::~Box()
{
}

bool Box::Start()
{
	m_modelRender.Init("Assets/modelData/Box.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);

	m_modelRender.Update();

	m_player = FindGO<Player>("BattleCharacter");

	m_defPosition = m_position;

	return true;
}


void Box::Position()
{
	if (m_moveflag == false) {
		m_position.y += 1.0f;
	}
	else {
		m_position.y -= 1.0f;
	}

	if (m_position.y <= m_defPosition.y - m_move) {
		m_moveflag = false;
	}
	else if (m_position.y >= m_defPosition.y + m_move) {
		m_moveflag = true;
	}

	m_modelRender.SetPosition(m_position);
}

void Box::Rotation()
{
	m_rotation.AddRotationDegY(1.0f);
	m_modelRender.SetRotation(m_rotation);
}

void Box::Update()
{

	Vector3 diff = m_player->m_position - m_position;
	if(diff.Length() < 100.0f) {
		//PlayingSound()を使用するため、SoundManagerのインスタンスを取得。
		SoundManager* sound = FindGO<SoundManager>("soundManager");
		//BGMの再生。
		m_boxSE = sound->PlayingSound(Sound::enSound_SE,false);
		m_player->m_BoxCount++;
		DeleteGO(this);
	}
	Position();

	Rotation();

	m_modelRender.Update();
}

void Box::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
