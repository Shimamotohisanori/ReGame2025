#include "stdafx.h"
#include "Player.h"
#include "SoundManager.h"
Player::Player()
{
	//アニメーションクリップをロードする。
	animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Run].Load("Assets/animData/Run.tka");
	animationClips[enAnimationClip_Run].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	//ユニティちゃんのモデルを読み込む。
	m_modelRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);

	//キャラコンを初期化する。
	characterController.Init(25.0f, 75.0f, m_position);
}

Player::~Player()
{
	
}

void Player::Update()
{
	Rotation();

	Move();

	ManageState();


	PlayAnimation();

	m_modelRender.Update();
}

void Player::Move()
{

	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	Vector3 stickLeft;
	stickLeft.x = g_pad[0]->GetLStickXF();
	stickLeft.y = g_pad[0]->GetLStickYF();

	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	forward.y = 0.0f;
	right.y = 0.0f;

	float SpeedPower = 370.0f;
	
	if (characterController.IsOnGround() == true)
	{		
		moveSpeed.y = 0.0f;
		
		jumpCount = 0;
		
	}

	if (g_pad[0]->IsPress(enButtonB))
	{
		SpeedPower = 730.0f;
	}

	right *= stickLeft.x * SpeedPower;
	forward *= stickLeft.y * SpeedPower;



	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//PlayingSound()を使用するため、SoundManagerのインスタンスを取得。
		SoundManager* sound = FindGO<SoundManager>("soundManager");
		//BGMの再生。
		m_jumpSE = sound->PlayingSound(Sound::enSound_JUMPSE, false);
		if (jumpCount < maxjumpcount)
		{
			moveSpeed.y = 600.0f;
			jumpCount++;
		}
	}

	else
	{
		moveSpeed.y -= 9.8f * 2.0f;

	}

	moveSpeed += right + forward;

	m_position = characterController.Execute(moveSpeed, 1.0f / 60.0f);

	
	m_modelRender.SetPosition(m_position);

}

void Player::Rotation()
{
	
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		rot.SetRotationYFromDirectionXZ(moveSpeed);
		m_modelRender.SetRotation(rot);
	}
}

void Player::ManageState()
{
	if (characterController.IsOnGround() == false)
	{
		
		m_playerState = 1;
		return;
	}

	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		m_playerState = 2;

		if (g_pad[0]->IsPress(enButtonB))
		{
			m_playerState = 3;
		}
	}

	else
	{
		m_playerState = 0;
	}
}

void Player::PlayAnimation()
{
	switch (m_playerState)
	{
	case 0:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1:
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
	case 2:
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	case 3:
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	}
}

void Player::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}