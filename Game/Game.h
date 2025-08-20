#pragma once
#include "Level3DRender/LevelRender.h"

class Player;
class GameCamera;
class Box;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	LevelRender m_levelRender;

	std::vector<Box*> m_Boxs;
private:
	Vector3 m_pos;
	Player* m_player;
	//BackGround* m_ground;
	GameCamera* gamecamera;
	

	void InitSky();
	SkyCube* m_skyCube = nullptr;//スカイキューブ(空の実装)
	int m_skyCubeType = enSkyCubeType_DayToon; //ここで空の種類を変更する。

	SoundSource* m_gameBGM = nullptr; //ゲームBGMのサウンドソース
};

