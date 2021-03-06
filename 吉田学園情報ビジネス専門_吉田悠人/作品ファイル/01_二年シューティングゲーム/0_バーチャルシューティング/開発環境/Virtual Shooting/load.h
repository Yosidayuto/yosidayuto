//=============================================================================
//
// ロード画面処理 [load.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _LOAD_H_
#define _LOAD_H_


//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include <mutex>

//=============================================================================
// 前方宣言
//=============================================================================
class CLoadBg;

//=============================================================================
// クラス定義
//=============================================================================
class CLoad
{
public:
	CLoad();     //コンストラクタ
	~CLoad();    //デストラクタ

	static HRESULT	Load(void);		// テクスチャ読み込み
	static void		Unload(void);	// テクスチャの破棄

	HRESULT Init(void);		// 初期化関数
	void	Uninit(void);	// 終了関数
	bool	GetLoad(void);	// ロードゲッター
	void	FileLoad(void); // ファイルロード
	void	File(void);		// ファイル
private:
	CLoadBg*	m_pLoadBg;	// ロード画面の背景ポインタ
	bool		m_bLoad;	// ロードが終えたか
	int			nLoad;		// ロード用変数
	std::thread m_stLoad;
};

#endif