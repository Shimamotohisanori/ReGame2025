#pragma once
class GameOver;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render(RenderContext& renderContext);
	void Move();
	void Rotation();
	void ManageState();
	void PlayAnimation();
	//ココからメンバ変数
	ModelRender m_modelRender;
	Vector3 m_position;
	enum EnAnimationClip {		//アニメーション。
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];		//アニメーションクリップ。
	Quaternion rot;
	CharacterController characterController;
	Vector3 moveSpeed;
	int m_playerState = 0;
	int jumpCount = 0;
	int maxjumpcount = 2;

	int m_BoxCount = 0;
private:
	SoundSource* m_jumpSE = nullptr; //ジャンプSE
};

