//=============================================================================
//
// �^�C�g������ [Title.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MODEL (4)

//*****************************************************************************
// �N���X�̒�`
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
		//�ϐ��錾//***********************************************************************
	float m_fCntState;
	int m_nTime;
	CPlayer		*m_pPlayer;
	CScene2D	*m_p2DLogo;				// 3D(2D�|���S��ver)
	CMoveModel	*m_apModel[MAX_MODEL];	// �^�C�g���������f��
	CMoveModel	*m_pModel;				// �~�T�C��
	CScene2D	*m_p2DMoji;				// PC���l����(2D�|���S��ver)

	CScene3D	*m_p3DLogo;				// 3D(3D�|���S��ver)
	CScene3DMove	*m_p3DMoji;			// PC���l����(3D�|���S��ver)
};

#endif
