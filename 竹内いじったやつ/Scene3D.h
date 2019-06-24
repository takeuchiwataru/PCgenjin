#pragma once
//=============================================================================
//
// �V�[��3D���� [scene3D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define S3D_PRIORITY		(1)
#define S3DF_PRIORITY		(2)

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CScene3D : public CScene
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		/*�t�F�[�h*/STATE_FADESPIN, STATE_FADE, STATE_FADEIN,  STATE_FADEOUT, STATE_FADEOUT2, STATE_FADEOUTN,
		/*UV�t���[*/STATE_UVFLOW_0, STATE_UVFLOW_1,
		/*�X�g�b�v*/STATE_STOP,
		/*���b�N*/	STATE_LOCK_0, STATE_LOCK_1,
		/*�q�b�g*/	STATE_HIT,
		/*�`�F�b�N�|�C���g*/		STATE_CHECK,
		/*�{�XBG*/	STATE_BFLOW_IN, STATE_BFLOW_OUT,
		/*�^�C�g��3D*/STATE_FADEIN2,	// �|���ǉ�
		/*�^�C�g������*/STATE_MOVE,		// �|���ǉ�
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

	void		Fade(float fCntState, STATE state);					// �|���ǉ�

protected://*****************************************************************************

	//�ϐ��p//***********************************************************************
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }
	LPDIRECT3DTEXTURE9		GetTexture(void) { return m_pTex; }
private://*****************************************************************************
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	//�ϐ��錾//***********************************************************************
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX			m_mtxWorld;			//���[���h�}�g���b�N�X
	D3DXVECTOR3			m_pos;				//�ʒu
	D3DXVECTOR3			m_rot;				//����
	D3DXCOLOR			m_col;				//�F
	LPDIRECT3DTEXTURE9	m_pTex;				//�摜
	CScene::DRAW_TYPE	m_DrawType;			// �`�悷����@(���Z�����Ȃ�)
	D3DXVECTOR3			m_length;			//�|���S���̒���
	float				m_fCntState;		//STATE�Ǘ��p
	int					m_nNumCamera;		//�Ή��J�����ԍ�
	STATE				m_state;			//�g�p���@
	bool				m_bBILLBoard;		//�r���{�[�h���ǂ���
};
//*****************************************************************************
// �N���X�̒�`
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
	int			m_nCNumber;	//�`�悷��J�����ԍ�
};
//*****************************************************************************
// �N���X�̒�`
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
// �N���X�̒�`
//*****************************************************************************
class CScene3DMove : public CScene3D
{
public:
	CScene3DMove(int nPrioryity = 3) : CScene3D::CScene3D(nPrioryity) { m_move = INIT_VECTOR; };
	~CScene3DMove() {};
	void CScene3DMove::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length, TEXTURE nType, int nUV, int nUV_X, int nUV_Y, bool bBillBoard, DRAW_TYPE DrawType,STATE state);
	void	Update(void);

private://*****************************************************************************
	D3DXVECTOR3			m_move;				//�ړ�
	STATE				m_state;			//�g�p���@

};
#endif
