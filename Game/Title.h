#pragma once
class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update() override;
	void Render(RenderContext& rc) override;

	void StartFadeIn()
	{
		m_state = enState_FadeIn;
	}
	void StartFadeOut()
	{
		m_state = enState_FadeOut;
	}

	float GetCurrentAlpha() const
	{
		return m_currentAlpha;
	}

private:
	enum EnState
	{
		enState_FadeIn, //フェードイン中
		enState_FadeOut,//フェードアウト中
	};
	FontRender m_fontRender; //フォントレンダラー
	EnState			m_state = enState_FadeIn;//状態。
	float			m_currentAlpha = 1.0f;	//現在のα値。ここを変更すると画像が透明になる。

	SpriteRender m_titleSprite;	//タイトル画面のスプライトレンダラー

	SoundSource* m_titleBGM;	//タイトルBGMのサウンドソース
	SoundSource* m_titleDecisionSE; //決定SEのサウンドソース
};

