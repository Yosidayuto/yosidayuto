//=============================================================================
//
//	セリフ親クラス [talk_bass.cpp]
//	Author:筒井 俊稀
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "talk_base.h"
#include "inputkeyboard.h"
#include "inputcontroller.h"
#include "renderer.h"
#include "manager.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_PATH_TALK_1 "Data/Texture/talk_bass/serifu1.png"
#define TEXTURE_PATH_TALK_2 "Data/Texture/talk_bass/serifu2.png"
#define TEXTURE_PATH_TALK_3 "Data/Texture/talk_bass/serifu3.png"
#define TEXTURE_PATH_TALK_4 "Data/Texture/talk_bass/serifu4.png"
#define TEXTURE_PATH_TALK_5 "Data/Texture/talk_bass/serifu5.png"
#define TEXTURE_PATH_TALK_6 "Data/Texture/talk_bass/serifu6.png"
#define TEXTURE_PATH_TALK_7 "Data/Texture/talk_bass/serifu7.png"
#define TEXTURE_PATH_TALK_8 "Data/Texture/talk_bass/serifu8.png"
#define TEXTURE_PATH_TALK_9 "Data/Texture/talk_bass/serifu9.png"
#define TEXTURE_PATH_TALK_10 "Data/Texture/talk_bass/serifu10.png"
#define TEXTURE_PATH_TALK_11 "Data/Texture/talk_bass/serifu11.png"
#define TEXTURE_PATH_TALK_12 "Data/Texture/talk_bass/serifu12.png"

#define FADE_RATE 0.03f

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CTalkbase::m_apTexture[TALK_MAX] = {};
CTalkbase::TALK CTalkbase::m_Talk = CTalkbase::TALK_NONE;

//=============================================================================
// コンストラクタ
//=============================================================================
CTalkbase::CTalkbase(int nPriorit) :CUi(nPriorit)
{
	m_Fade		 = FADE_NONE;
	m_bTalkEnd	 = false;
	m_col		 = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_nAppear	 = 0;
	m_nTalkCount = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CTalkbase::~CTalkbase()
{
}

//=============================================================================
// ロード処理
//=============================================================================
HRESULT CTalkbase::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_TALK_1, &m_apTexture[TALK_1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_TALK_2, &m_apTexture[TALK_2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_TALK_3, &m_apTexture[TALK_3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_TALK_4, &m_apTexture[TALK_4]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_TALK_5, &m_apTexture[TALK_5]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_TALK_6, &m_apTexture[TALK_6]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_TALK_7, &m_apTexture[TALK_7]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_TALK_8, &m_apTexture[TALK_8]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_TALK_9, &m_apTexture[TALK_9]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_TALK_10, &m_apTexture[TALK_10]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_TALK_11, &m_apTexture[TALK_11]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_TALK_12, &m_apTexture[TALK_12]);
	return S_OK;
}

//=============================================================================
// アンロード処理
//=============================================================================
void CTalkbase::Unload(void)
{
	for (int nCount = 0; nCount < TALK_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTalkbase::Init(void)
{

	//カラーセット
	SetCol(m_col);
	//初期化処理
	CUi::Init();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTalkbase::Uninit(void)
{
	CUi::Uninit();

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTalkbase::Update(void)
{
	CUi::Update();
	//トーク処理
	Talk();
	//フェードイン・アウトの処理
	Blackout();
}

//=============================================================================
// トークを次に進める関数
//=============================================================================
void CTalkbase::Talk(void)
{
	//キーボード入力取得
	CInputKeyboard* pKeyInput = (CInputKeyboard*)CManager::GetInputKey();
	//コントローラー入力取得
	CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
	//入力確認スイッチ
	bool bJoyStick = false;
	//コントローラー入力確認
	if (pJoyInput != NULL)
	{
		if (pJoyInput->GetJoyStickTrigger(CInputJoyStick::JOY_BUTTON_A)) bJoyStick = true;
	}

	//カウントアップ
	m_nTalkCount++;

	//カウントが一定に達したら || キーを押したら||ボタンを押したら
	if (m_nTalkCount >= m_nAppear || pKeyInput->GetKeyTrigger(DIK_SPACE)|| bJoyStick)
	{
		//フェード状況設定
		m_Fade = FADE_OUT;
	
		//カウント初期化
		m_nTalkCount = 0;
	}

}

//=============================================================================
// 暗転の設定
//=============================================================================
void CTalkbase::Blackout(void)
{
	//フェードアウト時
	if (m_Fade == FADE_OUT)
	{
		//透過
		m_col.a -= FADE_RATE;

		//消えたら
		if (m_col.a <= 0.0f)
		{
			//初期化
			m_col.a = 0.0f;
			m_Fade = FADE_NONE;
			m_bTalkEnd = true;
		}
	}
	// フェードイン時
	else if (m_Fade == FADE_IN)
	{
		//不透明化
		m_col.a += FADE_RATE;

		//出現仕切ったら
		if (m_col.a >= 1.0f)
		{
			m_col.a = 1.0f;
		}

	}

	//カラーセット
	SetCol(m_col);

}

//=============================================================================
// 出現時間セッター
//=============================================================================
void CTalkbase::SetAppear(int nAppear)
{
	m_nAppear = nAppear;
}

//=============================================================================
// 出現時間ゲッター
//=============================================================================
int CTalkbase::GetAppear(void)
{
	return m_nAppear;
}

//=============================================================================
// フェード状態セッター
//=============================================================================
void CTalkbase::SetFade(TALK_FADE FadeStatus)
{
	m_Fade = FadeStatus;
}

//=============================================================================
// フェード状態ゲッター
//=============================================================================
CTalkbase::TALK_FADE CTalkbase::GetFade(void)
{
	return m_Fade;
}

//=============================================================================
// 終了フラグゲッター
//=============================================================================
bool CTalkbase::GetTalkEnd(void)
{
	return m_bTalkEnd;
}


//=============================================================================
// トークの設定
//=============================================================================
void CTalkbase::SetTalk(TALK talk)
{
	m_Talk = talk;
}

//=============================================================================
// トークのゲッター処理
//=============================================================================
CTalkbase::TALK CTalkbase::GetTalk(void)
{
	return m_Talk;
}

//=============================================================================
// テクスチャの更新
//=============================================================================
void CTalkbase::BindTalkTexture(TALK talk)
{
	BindTexture(m_apTexture[talk]);
	SetTalk(talk);
	//BGMの再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_MESSAGE);
}

//=============================================================================
// テクスチャの切り替え
//=============================================================================
void CTalkbase::SetFlagTex(TALK talk)
{
	// アルファ値がゼロになるまで更新しない
	if (m_col.a <= 0.0f)
	{
		BindTexture(m_apTexture[talk]);
		SetTalk(talk);
	}
}
