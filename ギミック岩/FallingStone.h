//=============================================================================
//
// 落石処理 [FallingStone.h]
// Author : 小松　啓祐
//
//=============================================================================
#ifndef _FALLINGSTONE_H_
#define _FALLINGSTONE_H_

#include "main.h"
#include "sceneModel.h"

//*****************************************************************************
// マクロの定義
//*****************************************************************************


//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CFallingStone : public CSceneModel
{
public:

	CFallingStone(int nPrioryity = MODEL_PRIORITY) : CSceneModel::CSceneModel(nPrioryity) {};
	~CFallingStone() {};

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);

	void	SetState(int life, float speed) { m_nLife = life; m_fSpeed = speed; };

private://*****************************************************************************
		//変数宣言//***********************************************************************
	D3DXVECTOR3 m_move;		// 移動量
	float m_fSpeed;			// 移動速度
	int m_nLife;			// 体力
};

#endif
