//=============================================================================
//
//	セリフNo.6[talk no6.h]
//	Author:筒井　俊稀
//
//=============================================================================

// 二重インクルード防止
#ifndef _TALK_NO6_H_
#define _TALK_NO6_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "talk_base.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CTutorial;

//=============================================================================
// クラス定義
//=============================================================================
class CTalkNo6 :public CTalkbase
{
public:

	CTalkNo6(int nPriorit = PRIORITY_UI_0);	// コンストラクタ
	static CTalkNo6* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT		Init(void);				// 初期化処理
	void		Update(void);			// 更新処理

protected:

};
#endif
