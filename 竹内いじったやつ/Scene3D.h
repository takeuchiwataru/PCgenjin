#pragma once
//=============================================================================
//
// シーン3D処理 [scene3D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define S3D_PRIORITY		(1)
#define S3DF_PRIORITY		(2)

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CScene3D : public CScene
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		/*フェード*/STATE_FADESPIN, STATE_FADE, STATE_FADEIN,  STATE_FADEOUT, STATE_FADEOUT2, STATE_FADEOUTN,
		/*UVフロー*/STATE_UVFLOW_0, STATE_UVFLOW_1,
		/*ストップ*/STATE_STOP,
		/*ロック*/	STATE_LOCK_0, STATE_LOCK_1,
		/*ヒット*/	STATE_HIT,
		/*チェックポイント*/		STATE_CHECK,
		/*ボスBG*/	STATE_BFLOW_IN, STATE_BFLOW_OUT,
		/*タイトル3D*/STATE_FADEIN2,	// 竹内追加
		/*タイトル文字*/STATE_MOVE,		// 竹内追加
		STATE_MAX
	}STATE;
	CScene3D(int nPrioryity = 3) : CScene::CScene(nPrioryity) { m_pTex = NULL; };
	~CScene3D() {};

	static void Sort(void);
	void CScene3D::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length, TEXTURE nType, int nUV, int nUV_X, int nUV_Y, bool bBillBoard, DRAW_TYPE DrawType);
	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);

	D3DXVECTOR3 &GetPosition(void)	{ return m_pos; }
	D3DXVECTOR3 &GetRotation(void)	{ return m_rot; }
	D3DXCOLOR	&GetColor(void)		{ return m_col; }
	D3DXVECTOR3	&GetLength(void)	{ return m_length; }
	float		&GetfCntState(void) { return m_fCntState; }
	STATE		&GetState(void)		{ return m_state; }
	int			&GetnNumCamera(void) { return m_nNumCamera; }

	void		SetColor(D3DXCOLOR col);
	void		SetSize(D3DXVECTOR3 length);
	void		SetUV(int nUV, int nUV_X, int nUV_Y);
	void		SetUVPattern(float fUV_X, float fUV_Y);
	void		PlusUV(D3DXVECTOR2 uv);
	void		SetUV(float fUV_X, float fUV_Y);
	void		SetMtx(void);
	void		BindDrawType(CScene::DRAW_TYPE DrawType) { m_DrawType = DrawType; }
	CScene::DRAW_TYPE		&GetDrawType(void) { return m_DrawType; }
	void		BindTexture(LPDIRECT3DTEXTURE9 pTex) { m_pTex = pTex; }

	void		Fade(float fCntState, STATE state);					// 竹内追加

protected://*****************************************************************************

	//変数用//***********************************************************************
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }
	LPDIRECT3DTEXTURE9		GetTexture(void) { return m_pTex; }
private://*****************************************************************************
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	//変数宣言//***********************************************************************
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	D3DXMATRIX			m_mtxWorld;			//ワールドマトリックス
	D3DXVECTOR3			m_pos;				//位置
	D3DXVECTOR3			m_rot;				//向き
	D3DXCOLOR			m_col;				//色
	LPDIRECT3DTEXTURE9	m_pTex;				//画像
	CScene::DRAW_TYPE	m_DrawType;			// 描画する方法(加算合成など)
	D3DXVECTOR3			m_length;			//ポリゴンの長さ
	float				m_fCntState;		//STATE管理用
	int					m_nNumCamera;		//対応カメラ番号
	STATE				m_state;			//使用方法
	bool				m_bBILLBoard;		//ビルボードかどうか
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSceneEffect : public CScene3D
{
public:

	CSceneEffect(int nPrioryity = 3) : CScene3D::CScene3D(nPrioryity) { m_pPos = NULL; };
	~CSceneEffect() {};

	void CSceneEffect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,
		TEXTURE nType, int nUV, int nUV_X, int nUV_Y, bool bBillBoard, DRAW_TYPE DrawType, D3DXVECTOR3 *pPos, int m_nCNumber);
	void Draw(void);
	void Update(void);

	D3DXVECTOR3 *&GetpPos(void) { return m_pPos; }
private://*****************************************************************************
	D3DXVECTOR3 *m_pPos;
	int			m_nCNumber;	//描画するカメラ番号
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CScene3DView : public CScene3D
{
public:

	CScene3DView(int nPrioryity = 3) : CScene3D::CScene3D(nPrioryity) {};
	~CScene3DView() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 length, DRAW_TYPE DrawType);
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

private://*****************************************************************************
	LPDIRECT3DTEXTURE9		m_pTextureMT;
	LPDIRECT3DSURFACE9		m_pRenderMT;
	LPDIRECT3DSURFACE9		m_pBuffMT;
	D3DVIEWPORT9			m_viewportMT;
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CScene3DMove : public CScene3D
{
public:
	CScene3DMove(int nPrioryity = 3) : CScene3D::CScene3D(nPrioryity) { m_move = INIT_VECTOR; };
	~CScene3DMove() {};
	void CScene3DMove::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length, TEXTURE nType, int nUV, int nUV_X, int nUV_Y, bool bBillBoard, DRAW_TYPE DrawType,STATE state);
	void	Update(void);

private://*****************************************************************************
	D3DXVECTOR3			m_move;				//移動
	STATE				m_state;			//使用方法

};
#endif
