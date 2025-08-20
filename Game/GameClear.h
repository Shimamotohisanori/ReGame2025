#pragma once
class GameClear : public IGameObject
{
public:
	GameClear();
	~GameClear();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	SpriteRender m_gameClearRender;
	SoundSource* m_gameClearBGM; //ゲームクリアBGMのサウンドソース
	SoundSource* m_titleDecisionSE; //決定SEのサウンドソース
};

