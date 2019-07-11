//=============================================================================
//
// ���Ώ��� [FallingStone.cpp]
// Author : �����@�[�S
//
//=============================================================================
#include "FallingStone.h"
#include "manager.h"
#include "player.h"

//*****************************************************************************
// �}�N���̒�`
//*****************************************************************************

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================

//=============================================================================
// ���΂̏���������
//=============================================================================
HRESULT CFallingStone::Init(void)
{
	CSceneModel::Init();

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSpeed = 0.0f;

	return S_OK;
}

//=============================================================================
// ���΂̏I������
//=============================================================================
void CFallingStone::Uninit(void)
{
	CSceneModel::Uninit();
}

//=============================================================================
// ���΂̍X�V����
//=============================================================================
void CFallingStone::Update(void)
{
	D3DXVECTOR3 &pos = CSceneModel::GetPosition();
	D3DXVECTOR3 &rot = CSceneModel::GetRotation();
	CPlayer *pPlayer;

	//CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "���Α̗� : %d\n", m_nLife);

	m_move += D3DXVECTOR3(sinf(rot.y) * -m_fSpeed, 0.0f, cosf(rot.y) * -m_fSpeed);	// �ړ�
	m_move.x *= 0.95f;
	m_move.z *= 0.95f;
	rot += D3DXVECTOR3(-(m_fSpeed * 0.3f), 0.0f, 0.0f);	// ��]

	// �p�x�̃��Z�b�g
	if (rot.x < -D3DX_PI)
	{
		rot.x += D3DX_PI * 2.0f;
	}
	if (rot.x > D3DX_PI)
	{
		rot.x -= D3DX_PI * 2.0f;
	}

	// �����J�n
	m_nLife--;
	if (m_nLife <= 0)
	{
		m_move.y -= 0.3f;
	}

	// ����
	if (m_nLife < -120)
	{
		Uninit();
		return;
	}

	pos += m_move;	// �ʒu�̍X�V
	CSceneModel::SetMtx();

	//�@�v���C���[�Ƃ̓����蔻��
	pPlayer = CSceneModel::HitPlayer();
	if (pPlayer != NULL)
	{
		CCharacter *pChar;
		pPlayer->Damage(1.0f, pChar);
	}
}