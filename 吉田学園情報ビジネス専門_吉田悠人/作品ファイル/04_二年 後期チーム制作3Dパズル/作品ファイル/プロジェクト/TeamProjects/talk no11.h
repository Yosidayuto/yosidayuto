//=============================================================================
//
//	セリフNo.11[talk no11.h]
//	Author:筒井　俊稀
//
//=============================================================================

// 二重インクルード防止
#ifndef _TALK_NO11_H_
#define _TALK_NO11_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "talk_base.h"

//=============================================================================
// クラス定義
//=============================================================================
class CTalkNo11 :public CTalkbase
{
public:


	CTalkNo11(int nPriorit = PRIORITY_UI_0);	// コンストラクタ
	static CTalkNo11* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT		Init(void);				// 初期化処理
	void		Update(void);			// 更新処理
	void		Talk(void);				// トークを進める関数

protected:
};
#endif
