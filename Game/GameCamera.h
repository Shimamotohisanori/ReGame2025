#pragma once
class Player;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	void Update();
	bool Start();
	Player* player;
	Vector3 m_toCameraPos;
};

