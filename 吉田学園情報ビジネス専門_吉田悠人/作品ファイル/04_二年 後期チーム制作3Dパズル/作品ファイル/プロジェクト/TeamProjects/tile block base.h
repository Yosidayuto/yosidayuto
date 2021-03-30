//=============================================================================
//
// タイルブロックベース [tile block base.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _TILE_BLOCK_BASE_H_
#define _TILE_BLOCK_BASE_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "model.h"
#include "block base.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TILE_HEIGHT (25.0f)	//アイテムブロックの高さ

//=============================================================================
// 前方宣言
//=============================================================================
class CModel;
//=============================================================================
// クラス定義
//=============================================================================
class CTileBlockBase : public CBlockBase
{
public:

	CTileBlockBase();
	~CTileBlockBase();
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

private:

};
#endif