#pragma once
class Player;
class Box : public IGameObject
{
	public:
	Box();
	~Box();
	bool Start() override;
	void Position();
	void Rotation();
	void Update() override;
	void Render(RenderContext& rc) override;

	ModelRender				m_modelRender;				
	Vector3					m_position;					
	Vector3					m_scale;					
	Quaternion				m_rotation;					
	SoundSource* m_boxSE = nullptr;

	Vector3					m_defPosition;				
	const float				m_move = 70.0f;				
	bool					m_moveflag = false;

private:
	Player* m_player;
};

