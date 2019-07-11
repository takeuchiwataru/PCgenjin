//=============================================================================
//
// ���Ώ��� [FallingStone.h]
// Author : �����@�[�S
//
//=============================================================================
#ifndef _FALLINGSTONE_H_
#define _FALLINGSTONE_H_

#include "main.h"
#include "sceneModel.h"

//*****************************************************************************
// �}�N���̒�`
//*****************************************************************************


//*****************************************************************************
// �N���X�̒�`
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
		//�ϐ��錾//***********************************************************************
	D3DXVECTOR3 m_move;		// �ړ���
	float m_fSpeed;			// �ړ����x
	int m_nLife;			// �̗�
};

#endif
