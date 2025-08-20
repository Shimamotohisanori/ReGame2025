#pragma once
class Player;
class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender GameOverRender;
	SoundSource* m_gameOverBGM; //ゲームオーバーBGMのサウンドソース
	SoundSource* m_titleDecisionSE; //SEのサウンドソース
private:
	Player* m_player;
};

