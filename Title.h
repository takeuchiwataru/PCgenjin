//=============================================================================
//
// タイトル処理 [Title.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_MODEL (4)

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CTitle
{
public:
	CTitle() { m_pPlayer = NULL; m_p2DLogo = NULL;
	for (int nCount = 0; nCount < MAX_MODEL; nCount++) { m_apModel[nCount] = NULL; }; 
	m_pModel = NULL; m_p2DMoji = NULL; m_p3DLogo = NULL; m_p3DMoji = NULL;};
	~CTitle() {};

	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);
private://*****************************************************************************
		//変数宣言//***********************************************************************
	float m_fCntState;
	int m_nTime;
	CPlayer		*m_pPlayer;
	CScene2D	*m_p2DLogo;				// 3D(2Dポリゴンver)
	CMoveModel	*m_apModel[MAX_MODEL];	// タイトル文字モデル
	CMoveModel	*m_pModel;				// ミサイル
	CScene2D	*m_p2DMoji;				// PC原人文字(2Dポリゴンver)

	CScene3D	*m_p3DLogo;				// 3D(3Dポリゴンver)
	CScene3DMove	*m_p3DMoji;			// PC原人文字(3Dポリゴンver)
};

#endif
