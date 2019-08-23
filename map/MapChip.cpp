//=============================================================================
//
// �}�b�v�`�b�v���� [MapChip.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS	//Fire Wall�˔j
#include <stdio.h>				//�C���N���h�t�@�C��
#include <stdlib.h>				//�����h�p
#include <time.h>				//�����������h�p
#include <string.h>				//�X�g�����O�g�p�̂���

#include "main.h"
#include "MapChip.h"
#include "Chip.h"
#include "MapChip_BG.h"
#include "Story.h"

#include "player.h"
#include "3DPolygon.h"
#include "DebugLog.h"
#include "camera.h"
#include "enemy.h"

#include "renderer.h"
#include "RenderDraw.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_DRAW_RANGE	(12)
#define MAX_UPDATE_RANGE	(16)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//==================================================================================================//
//    *	��̃`�b�v�̏����� *
//==================================================================================================//
HRESULT COneChip::Init(void)
{
	m_nMaxChip = 0;
	m_pChip = NULL;
	m_nMaxFront = 0;
	m_pFront = NULL;
	return S_OK;
}
//==================================================================================================//
//    *	��̃`�b�v�̏I�� *
//==================================================================================================//
void	COneChip::Uninit(void)
{
	if (m_pChip != NULL)
	{//�`�b�v����������Ă���Ȃ�
		for (int nCount = 0; nCount < m_nMaxChip; nCount++)
		{//�Ǘ����̃`�b�v�̏I��
			if (m_pChip[nCount] == NULL) { continue; }
			m_pChip[nCount]->Uninit();
			m_pChip[nCount] = NULL;
		}
		delete[] m_pChip;
	}
	delete this;
}
//==================================================================================================//
//    *	��̃`�b�v�̕`�� *
//==================================================================================================//
void	COneChip::Draw(void)
{
	if (m_pChip != NULL)
	{//�`�b�v����������Ă���Ȃ�
		for (int nCount = 0; nCount < m_nMaxChip; nCount++)
		{//�Ǘ����̃`�b�v�̕`��
			if (m_pChip[nCount] == NULL) { continue; }
			if (m_pChip[nCount]->GetDType() != CManager::GetpMapChip()->GetDType()) { continue; }
			m_pChip[nCount]->Draw();
		}
	}
}
//==================================================================================================//
//    *	��̃`�b�v�̍X�V *
//==================================================================================================//
void	COneChip::Update(void)
{
	if (m_pChip != NULL)
	{//�`�b�v����������Ă���Ȃ�
		for (int nCount = 0; nCount < m_nMaxChip; nCount++)
		{//�Ǘ����̃`�b�v�̍X�V
			if (m_pChip[nCount] == NULL) { continue; }
			if (m_pChip[nCount]->Update())
			{//�폜����
				m_pChip[nCount]->Uninit();
				m_pChip[nCount] = NULL;
			}
		}
	}
}
//==================================================================================================//
//    *	��̃`�b�v�̃}�g���b�N�X�v�Z *
//==================================================================================================//
void	COneChip::SetMtx(D3DXVECTOR3 &pos)
{
	if (m_pChip != NULL)
	{//�`�b�v����������Ă���Ȃ�
		for (int nCount = 0; nCount < m_nMaxChip; nCount++)
		{//�Ǘ����̃`�b�v�̍X�V
			if (m_pChip[nCount] == NULL) { continue; }
			m_pChip[nCount]->SetMtx(pos);
		}
	}
}
//==================================================================================================//
//    *	��̃`�b�v�̓����蔻�� *
//==================================================================================================//
bool	COneChip::CollisionY(CCharacter *&pChar)
{
	bool bLand = false;

	if (m_pChip != NULL)
	{//�`�b�v����������Ă���Ȃ�
		for (int nCount = 0; nCount < m_nMaxChip; nCount++)
		{//�Ǘ����̃`�b�v�̍X�V
			if (m_pChip[nCount] == NULL) { continue; }
			if (m_pChip[nCount]->CollisionY(pChar)) { bLand = true; }
		}
	}

	return bLand;
}
//==================================================================================================//
//    *	��̃`�b�v�̓����蔻�� *
//==================================================================================================//
bool	COneChip::CollisionXZ(CCharacter *&pChar, int &nHit)
{
	bool bHit = false;

	if (m_pChip != NULL)
	{//�`�b�v����������Ă���Ȃ�
		for (int nCount = 0; nCount < m_nMaxChip; nCount++)
		{//�Ǘ����̃`�b�v�̍X�V
			if (m_pChip[nCount] == NULL) { continue; }
			if (m_pChip[nCount]->CollisionXZ(pChar, nHit)) { bHit = true; };
		}
	}
	return bHit;
}
//==================================================================================================//
//    *	��̃`�b�v�̑I���L�����Z�� *
//==================================================================================================//
void	COneChip::ResetSelect(void)
{
	if (m_pChip != NULL)
	{//�`�b�v����������Ă���Ȃ�
		for (int nCount = 0; nCount < m_nMaxChip; nCount++)
		{//�Ǘ����̃`�b�v�̍X�V
			if (m_pChip[nCount] == NULL) { continue; }
			m_pChip[nCount]->GetbSelect() = false;
		}
	}
}
//==================================================================================================//
//    *	��̃`�b�v�̏����� *
//==================================================================================================//
void	COneChip::SetChip(int nNumChip)
{
	//if (nNumChip <= 0) { return; }				//0�ȉ��Ȃ�L�����Z��
	if (m_pChip != NULL) { Uninit(); Init(); }	//���ɐ�������Ă���Ȃ�j��

	m_nMaxChip = 10;						//�`�b�v�����
	//m_nMaxChip = nNumChip;
	m_pChip = new CChip*[m_nMaxChip];			//�w�蕪����

	for (int nCount = 0; nCount < m_nMaxChip; nCount++)
	{
		m_pChip[nCount] = NULL;
	}
}
//==================================================================================================//
//    *	��̃`�b�v�̏����� *
//==================================================================================================//
CChip *&COneChip::GetChip(int nNumber)
{
	return m_pChip[nNumber];
}
//==================================================================================================//
//    *	��̃`�b�v�̏����� *
//==================================================================================================//
void	COneChip::Save(FILE *&pFile)
{
	if (m_pChip != NULL)
	{//�`�b�v����������Ă���Ȃ�
		int nCntChip = 0;
		for (int nCount = 0; nCount < m_nMaxChip; nCount++)
		{//�`�b�v�����Z�[�u
			if (m_pChip[nCount] != NULL) { nCntChip++; }
		}
		fprintf(pFile, "%d \n", nCntChip);

		for (int nCount = 0; nCount < m_nMaxChip; nCount++)
		{//�`�b�v�����Z�[�u
			if (m_pChip[nCount] == NULL) { continue; }
			fprintf(pFile, "%d \n", m_pChip[nCount]->GetType());
			m_pChip[nCount]->Save(pFile);
		}
	}
}
//==================================================================================================//
//    *	��̃`�b�v�̏����� *
//==================================================================================================//
void	COneChip::Load(FILE *&pFile)
{
	int nNumChip, nType;

	fscanf(pFile, "%d \n", &nNumChip);	//�`�b�v���ǂݍ���
	SetChip(nNumChip);				//�w�蕪�|�C���^�𐶐�

	for (int nCount = 0; nCount < nNumChip; nCount++)
	{//�������ǂݍ���
		CChip *&pChip = GetChip(nCount);
		fscanf(pFile, "%d \n", &nType);	//�`�b�v���ǂݍ���
		CreateChip(pChip, (CChip::TYPE)nType);
		pChip->Load(pFile);
	}
}
//==================================================================================================//
//    *	��̃`�b�v�̃`�b�v���� *
//==================================================================================================//
void	COneChip::CreateChip(CChip *&pChip, CChip::TYPE type)
{
	if (pChip != NULL)
	{//���ɉ�����������Ă���ꍇ
		if (pChip->GetType() == type) { return; }
		pChip->Uninit(); pChip = NULL;
	}

	switch (type)
	{
	case CChip::TYPE_NULL:		pChip = new CChip;			break;
	case CChip::TYPE_MODEL:		pChip = new CChip_Model;	break;
	case CChip::TYPE_POLYGON:	pChip = new CChip_Polygon;	break;
	}

	if (pChip != NULL)
	{
		pChip->GetType() = type;
		pChip->Init();
	}
}
//==================================================================================================//
//    *	��̃`�b�v�̏�ԕ`�� *
//==================================================================================================//
void	COneChip::StatusLog(int &nMaxSelect)
{
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�ő�`�b�v %d\n", m_nMaxChip);
	nMaxSelect = m_nMaxChip;
	for (int nCount = 0; nCount < m_nMaxChip; nCount++)
	{//�������ǂݍ���
		if (m_pChip[nCount] == NULL) { continue; }
		CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "%d�F", nCount);
		m_pChip[nCount]->StatusLog();
	}
}

//**************************************************************************************************//
//==================================================================================================//
//    * �}�b�v�`�b�v�̏����� *
//==================================================================================================//
//**************************************************************************************************//
HRESULT CMapChip::Init(void)
{
	CManager::GetpMapChip() = this;
	m_Map			= MAP_1;
	m_bMirror		= false;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nMaxX = 0;	m_nMaxZ = 0;
	m_fInitHeight	= 0;
	m_nMaxOneChip	= 0;
	m_nWKNumber		= 0;
	m_nWait			= 0;
	m_nClear		= 0;
	m_pOneChip		= NULL;
	m_pBG			= NULL;
	m_bEdit			= false;
	m_nEdit			= 0;
	m_DType			= CChip::DTYPE_MAX;
	m_Collision = CChip::COLLISION::COLLISION_NO;

	m_nMaxSelect = 1;
	m_nSelect = 0;
	m_Edit = EDIT_MODEL;
	m_ModelType = CChip_Model::TYPE_BLOCK00;
	m_ItemType = CChip_Model::TYPE_BLOCK00;
	m_PolyType = CChip_Polygon::TYPE_PFIELD;
	if (Create(m_p3D))
	{//�^�񒆂�3D��\��
		m_p3D->Set(m_pos + D3DXVECTOR3(-MAP_CHIP_SIZE * 0.5f, -0.1f, -MAP_CHIP_SIZE * 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)
			, D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, 1, 1
			, CScene::DRAW_TYPE_ADD, CScene::TEX_MAX, false);
	}
	LPDIRECT3DTEXTURE9	WKpTex;				//�摜
	CSceneModel::LoadModel(CSceneModel::MODEL_BLOC00, WKpTex);
	return S_OK;
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̏I�� *
//==================================================================================================//
void	CMapChip::Uninit(void)
{
	CManager::GetpMapChip() = NULL;
	Reset();
	CScene::Uninit();
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̍X�V *
//==================================================================================================//
void	CMapChip::Update(void)
{
	Edit();

	if (m_pBG != NULL) { m_pBG->Update(); }
	if (m_p3D != NULL) { m_p3D->Update(); }

	if (m_nClear > 0)
	{
		CRenderDraw_Meny *pReDraw;
		m_nClear++;

		//2�l�v���C�ŕЕ��S�[���Ȃ�ҋ@
		if (CPlayer::WaitGoal() && m_nWait < 180)
		{
			m_nClear = 1;
			m_nWait++;
		}

		switch (m_nClear)
		{
		case CLEAR_ADVANCE: 
			CCharacter::GetbWait() = true;
			//pReDraw = (CRenderDraw_Meny*)CRenderDraw::SetFade(CManager::MODE_GAME, CRenderDraw::FADE_MENY_SPIN, CRenderDraw::STATE_FADE_IN);
			pReDraw = (CRenderDraw_Meny*)CRenderDraw::SetFade(CManager::MODE_GAME, CRenderDraw::FADE_MOVE, CRenderDraw::STATE_FADE_IN);
			pReDraw->SetRotMove(D3DX_PI * -0.5f);
			pReDraw->GetbMode() = false;
			break;
		case CLEAR_FADE:
			Advance();
			break;

		}
	}
	if (m_pOneChip != NULL)
	{//��}�X���Ƃ̃`�b�v����������Ă���Ȃ�
		int nNumX_Min, nNumX_Max;
		float fCameraX = CManager::GetCamera()->GetPlay(0)->GetChar()->GetposR().x;
		nNumX_Min = (int)(fCameraX / MAP_CHIP_SIZE) - MAX_UPDATE_RANGE + 1;
		nNumX_Max = (int)(fCameraX / MAP_CHIP_SIZE) + MAX_UPDATE_RANGE;
		if (nNumX_Min < 0) { nNumX_Min = 0; }
		if (nNumX_Max > m_nMaxX) { nNumX_Max = m_nMaxX; }

		for (int nCntX = nNumX_Min; nCntX < nNumX_Max; nCntX++)
		{
			for (int nCntZ = 0; nCntZ < m_nMaxZ; nCntZ++)
			{//�Ǘ����̃`�b�v�̕`�� & �}�X�ڌv�Z
				m_nWKNumber = (nCntZ * m_nMaxX) + nCntX;
				if (m_pOneChip[m_nWKNumber] == NULL) { continue; }	//��������Ă��Ȃ��Ȃ疳��
				m_pOneChip[m_nWKNumber]->Update();
			}
		}
	}

}
//==================================================================================================//
//    * �}�b�v�`�b�v�̕`�� *
//==================================================================================================//
void	CMapChip::DrawMap(int nPriority)
{
	if (m_pOneChip != NULL && nPriority < CChip::DTYPE_MAX)
	{//��}�X���Ƃ̃`�b�v����������Ă���Ȃ�
		if (nPriority == CChip::DTYPE_NO) { return; }

		int nNumX_Min, nNumX_Max;
		float fCameraX = CManager::GetCamera()->GetPlay(0)->GetChar()->GetposR().x;
		nNumX_Min = (int)(fCameraX / MAP_CHIP_SIZE) - MAX_DRAW_RANGE + 1;
		nNumX_Max = (int)(fCameraX / MAP_CHIP_SIZE) + MAX_DRAW_RANGE;
		if (nNumX_Min < 0) { nNumX_Min = 0; }
		if (nNumX_Max > m_nMaxX) { nNumX_Max = m_nMaxX; }

		m_DType = (CChip::DTYPE)nPriority;

		//�`�揉�߂ɔw�i�̕`��
		if (m_DType == CChip::DTYPE_OBJECT) { if (m_pBG != NULL) { m_pBG->Draw(); } }

		for (int nCntX = nNumX_Min; nCntX < nNumX_Max; nCntX++)
		{
			for (int nCntZ = 0; nCntZ < m_nMaxZ; nCntZ++)
			{//�Ǘ����̃`�b�v�̕`�� & �}�X�ڌv�Z
				m_nWKNumber = (nCntZ * m_nMaxX) + nCntX;
				if (m_pOneChip[m_nWKNumber] == NULL) { continue; }	//��������Ă��Ȃ��Ȃ疳��
				m_pOneChip[m_nWKNumber]->Draw();
			}
		}
	}
	if (m_p3D != NULL && m_bEdit)
	{ m_p3D->Draw(); }
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̕`�� *
//==================================================================================================//
void	CMapChip::Reset(void)
{
	CCharacter::GetbWait() = false;
	if (m_pOneChip != NULL)
	{//��}�X���Ƃ̃`�b�v����������Ă���Ȃ�
		for (int nCount = 0; nCount < m_nMaxOneChip; nCount++)
		{//�Ǘ����̃`�b�v�̏I��
			if (m_pOneChip[nCount] == NULL) { continue; }	//��������Ă��Ȃ��Ȃ疳��
			m_pOneChip[nCount]->Uninit();
		}
		delete[] m_pOneChip;
		m_pOneChip = NULL;
		m_nMaxOneChip = 0;
	}
	if (m_p3D != NULL) { m_p3D->Uninit(); m_p3D = NULL; }
	if (m_pBG != NULL) { m_pBG->Uninit(); m_pBG = NULL; }
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̊Ǘ����̃}�g���b�N�X�v�Z *
//==================================================================================================//
void	CMapChip::SetMtx(void)
{
	if (m_pOneChip != NULL)
	{//��}�X���Ƃ̃`�b�v����������Ă���Ȃ�
		D3DXVECTOR3 pos = m_pos;
		int nCountX = 0;
		int nCountZ = 0;

		for (nCountX = 0; nCountX < m_nMaxX; nCountX++)
		{//�Ǘ����̃`�b�v�̍X�V
			for (nCountZ = 0; nCountZ < m_nMaxZ; nCountZ++)
			{
				if (m_pOneChip[m_nMaxX * nCountZ + nCountX] == NULL) { continue; }	//��������Ă��Ȃ��Ȃ疳��
				pos.x = nCountX * MAP_CHIP_SIZE + m_pos.x;
				pos.z = nCountZ * MAP_CHIP_SIZE + m_pos.z;
				m_pOneChip[m_nMaxX * nCountZ + nCountX]->SetMtx(pos);
			}
		}
	}
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̊Ǘ����̃`�b�v�I���L�����Z�� *
//==================================================================================================//
void	CMapChip::ResetSelect(void)
{
	if (m_pOneChip != NULL)
	{//��}�X���Ƃ̃`�b�v����������Ă���Ȃ�
		int nCountX = 0;
		int nCountZ = 0;

		for (nCountX = 0; nCountX < m_nMaxX; nCountX++)
		{//�Ǘ����̃`�b�v�̍X�V
			for (nCountZ = 0; nCountZ < m_nMaxZ; nCountZ++)
			{
				if (m_pOneChip[m_nMaxX * nCountZ + nCountX] == NULL) { continue; }	//��������Ă��Ȃ��Ȃ疳��
				m_pOneChip[m_nMaxX * nCountZ + nCountX]->ResetSelect();
			}
		}
	}
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̐i�s���� *
//==================================================================================================//
void	CMapChip::Advance(void)
{
	CPlayer::ResetMoveScale();
	CPlayer::GetnTime() = 0;
	m_Map = (MAP)(m_Map + 1);
	CPlayer::Start();

	if (m_Map == MAP_MAX) 
	{//Result�� 
		CRenderDraw::SetFade(CManager::MODE_SELECT, CRenderDraw::FADE_ZOOM, CRenderDraw::STATE_FADE_IN); 
		return;
	}

	//�}�b�v�؂�ւ�
	SetMap(m_Map);
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̐ݒ� *
//==================================================================================================//
void	CMapChip::Set(D3DXVECTOR3 pos, int nMaxX, int nMaxZ)
{
	if (nMaxX > 0 && nMaxZ > 0)
	{//X, Z�Ƃ���1�ȏ�Ȃ�
		if (m_pOneChip != NULL) { Reset(); Init(); }			//���ɐ�������Ă���Ȃ�폜
		m_pos = pos;	m_nMaxX = nMaxX;	m_nMaxZ = nMaxZ;	//�ݒ�l���
		m_nMaxOneChip = nMaxX * nMaxZ;							//�ő�`�b�v���v�Z

		m_pOneChip = new COneChip*[m_nMaxOneChip];				//�w��`�b�v��������
		for (int nCount = 0; nCount < m_nMaxOneChip; nCount++)
		{
			m_pOneChip[nCount] = NULL;
		}
	}
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̃`�b�v���� *
//==================================================================================================//
COneChip	*CMapChip::CreateChip(int nNumber)
{
	if (m_pOneChip == NULL || 0 > nNumber || m_nMaxOneChip < nNumber)
	{//�����͈͊O�Ȃ�
		MessageBox(0, "�����͈͊O�Ƀ`�b�v�𐶐����悤�Ƃ��Ă��", "MapChip.cpp/�֐�[CreateChip]", MB_OK);
		return NULL;
	}

	//��̃`�b�v�𐶐�->������
	m_pOneChip[nNumber] = NULL;
	m_pOneChip[nNumber] = new COneChip;
	if (m_pOneChip[nNumber] != NULL)
	{
		m_pOneChip[nNumber]->Init();
	}

	return m_pOneChip[nNumber];
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̍����擾 *
//==================================================================================================//
float CMapChip::GetHeight(D3DXVECTOR3 pos, int nSelect)
{
	int				nNumX, nNumZ, nNumber;

	nNumX = (int)((pos.x - m_pos.x + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumZ = (int)((pos.z - m_pos.z + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumber = (m_nMaxX * nNumZ) + nNumX;

	if (m_pOneChip[nNumber] != NULL)
	{ 
		if (m_pOneChip[nNumber]->GetChip(nSelect) != NULL)
		{
			return m_pOneChip[nNumber]->GetChip(nSelect)->GetHeight();
		}
	}
	return 0.0f;
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̃`�b�v���� *
//==================================================================================================//
void CMapChip::Collision(CCharacter *pChar)
{
	D3DXVECTOR3		&pos = pChar->Getpos();
	int				nNumX, nNumZ, nNumber;
	bool			bLand = false;

	nNumX = (int)((pos.x - m_pos.x + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumZ = (int)((pos.z - m_pos.z + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumber = (m_nMaxX * nNumZ) + nNumX;
	
	if (m_pOneChip != NULL)
	{//��}�X���Ƃ̃`�b�v����������Ă���Ȃ�
		
	 //Y����
		for (int nCntX = 0; nCntX < 3; nCntX++)
		{
			for (int nCntZ = 0; nCntZ < 3; nCntZ++)
			{
				m_nWKNumber = (m_nMaxX * (nNumZ - 1 + nCntZ)) + (nNumX - 1 + nCntX);
				if (m_nWKNumber >= m_nMaxOneChip || m_nWKNumber < 0) { continue; }
				if (m_pOneChip[m_nWKNumber] == NULL) { continue; }
				if (m_pOneChip[m_nWKNumber]->CollisionY(pChar)) { bLand = true; }
			}
		}
		if (CCharacter::CollisionAll(pChar)) { bLand = true; }//�L�������m�����蔻��

		if (bLand) { pChar->Landing(); }
		else { pChar->GetbJump() = false; }

		//X����
		int nCountX = 0;
		int nCountZ = 0;
		int nHit;

		if (!pChar->GetbCollision()) { return; }
		for (int nCntZ = 0; nCntZ < 3; nCntZ++)
		{
			nHit = 0;
			for (int nCntX = 0; nCntX < 3; nCntX++)
			{
				m_nWKNumber = (m_nMaxX * (nNumZ - 1 + nCntZ)) + (nNumX - 1 + nCntX);
				if (m_nWKNumber >= m_nMaxOneChip || m_nWKNumber < 0) { continue; }
				if (m_pOneChip[m_nWKNumber] == NULL) { continue; }
				m_pOneChip[m_nWKNumber]->CollisionXZ(pChar, nHit);
			}
			if (nHit == 2)
			{//X�˂����������
				pos.x -= 0.1f;
			}
		}
	}
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̃`�b�v���� *
//==================================================================================================//
void	CMapChip::Edit(void)
{
	if (CManager::GetPlayer(0) == NULL) { return; }
	CInputKeyboard	*pInputKey = CManager::GetInputKey();
	D3DXVECTOR3		&pos = CManager::GetPlayer(0)->Getpos();
	int				nNumX, nNumZ, nNumber;
	float			fWKValue = 0.01f;
	bool			bEdit = false;

	nNumX = (int)((pos.x - m_pos.x + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumZ = (int)((pos.z - m_pos.z + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumber = (m_nMaxX * nNumZ) + nNumX;

	ResetSelect();
	StatusLog(nNumX, nNumZ, nNumber);
	if (m_p3D != NULL)
	{
		m_p3D->GetLength() = D3DXVECTOR3(m_nMaxX * MAP_CHIP_SIZE, 0.0f, m_nMaxZ * MAP_CHIP_SIZE);
		m_p3D->SetChipSize();
	}

	if (pInputKey->GetTPress(DIK_F3)) { m_bEdit = (m_bEdit ? false : true); }

	if (!m_bEdit) { return; }
	//�}�b�v�̑傫���ύX
	if (pInputKey->GetRelease(DIK_Y)) { ChangeSize(m_nMaxX, m_nMaxZ + 1); return; }
	if (pInputKey->GetRelease(DIK_H)) { ChangeSize(m_nMaxX, m_nMaxZ - 1); return; }
	if (pInputKey->GetRelease(DIK_O)) { ChangeSize(m_nMaxX + 1, m_nMaxZ); return; }
	if (pInputKey->GetRelease(DIK_U)) { ChangeSize(m_nMaxX - 1, m_nMaxZ); return; }

	if (pInputKey->GetPress(DIK_LCONTROL))
	{
		if (pInputKey->GetRelease(DIK_J)) { ChangePosX(nNumber, 1);		bEdit = true; }
		if (pInputKey->GetRelease(DIK_L)) { ChangePosX(nNumber, -1);	bEdit = true; }
	}
	else
	{
		//�}�b�v�̈ړ�
		if (pInputKey->GetTrigger(DIK_I)) { ChangePos(0, 1);	bEdit = true; }
		if (pInputKey->GetTrigger(DIK_K)) { ChangePos(0, -1);	bEdit = true; }
		if (pInputKey->GetTrigger(DIK_J)) { ChangePos(-1, 0);	bEdit = true; }
		if (pInputKey->GetTrigger(DIK_L)) { ChangePos(1, 0);	bEdit = true; }
	}
	//�I��ԍ��ύX
	if (pInputKey->GetTPress(DIK_RIGHT)) { m_nSelect++; }
	if (pInputKey->GetTPress(DIK_LEFT)) { m_nSelect--; }
	if (m_nSelect > m_nMaxSelect) { m_nSelect = m_nMaxSelect; }
	if (m_nSelect < 0) { m_nSelect = 0; }

	//���������ύX
	if (pInputKey->GetTPress(DIK_NUMPAD7)) { m_fInitHeight += 0.5f; }
	if (pInputKey->GetTPress(DIK_NUMPAD4)) { m_fInitHeight -= 0.5f; }

	//�����^�C�v�ύX
	if (pInputKey->GetTPress(DIK_NUMPAD1)) { m_Edit = (EDIT)((m_Edit + 1) % EDIT_MAX); }

	if (m_pOneChip != NULL)
	{//��}�X���Ƃ̃`�b�v����������Ă���Ȃ�
		if (nNumX > -1 && nNumX < m_nMaxX && nNumZ > -1 && nNumZ < m_nMaxZ)
		{
			if (m_pOneChip[nNumber] != NULL)
			{//��������Ă��Ȃ��Ȃ疳��

			 //�폜
				if (pInputKey->GetTrigger(DIK_BACKSPACE)) { DeleteChip(nNumber); bEdit = true; }

				//�ύX�Ώۂ̕ύX
				if (pInputKey->GetTrigger(DIK_ADD)) { m_nEdit++; }
				if (pInputKey->GetTrigger(DIK_SUBTRACT)) { m_nEdit--; }

				if (m_nEdit < 0) { m_nEdit = 0; }
				//�ݒu�E�ύX
				switch (m_Edit)
				{
				case EDIT_MODEL:	EditModel(nNumber, bEdit);		break;
				case EDIT_POLYGON:	EditPolygon(nNumber, bEdit);	break;
				case EDIT_ITEM:		EditItem(nNumber, bEdit);		break;
				}
			}
		}
	}


	//�Z�[�u�E���[�h
	if (pInputKey->GetTrigger(DIK_F9)) { Save("data/TEXT/EDIT/Editor.txt"); }
	if (pInputKey->GetTrigger(DIK_9)) { Load("data/TEXT/EDIT/Editor.txt"); }

	if (bEdit) { EditTrue(); }
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̃��f���ݒ� *
//==================================================================================================//
void	CMapChip::EditModel(int &nNumber, bool &bEdit)
{
	CInputKeyboard	*pInputKey = CManager::GetInputKey();

	if (m_nEdit >= 2) { m_nEdit = 1; }
	if (pInputKey->GetTPress(DIK_RETURN)) { SettingModel(nNumber);			bEdit = true; }
	if (pInputKey->GetTPress(DIK_UP)) { UpHeightModel(nNumber, 0.25f);		bEdit = true; }
	if (pInputKey->GetTPress(DIK_DOWN)) { UpHeightModel(nNumber, -0.25f);	bEdit = true; }
	if (pInputKey->GetTPress(DIK_NUMPAD8)) { m_ModelType = (CChip_Model::TYPE)((m_ModelType + 1) % CChip_Model::TYPE_MAX); }
	if (pInputKey->GetTPress(DIK_NUMPAD5)) { m_ModelType = (CChip_Model::TYPE)((m_ModelType + (CChip_Model::TYPE_MAX - 1)) % CChip_Model::TYPE_MAX); }

	switch (m_nEdit)
	{
	case 0:
		if (pInputKey->GetTPress(DIK_NUMPAD9)) { UpRotationModel(nNumber, D3DX_PI * 0.5f);		bEdit = true; }
		if (pInputKey->GetTPress(DIK_NUMPAD6)) { UpRotationModel(nNumber, -D3DX_PI * 0.5f);	bEdit = true; }
		break;
	case 1:
		if (pInputKey->GetPress(DIK_LCONTROL))
		{//�����p�ݒ�
			if (pInputKey->GetTPress(DIK_NUMPAD9)) { m_Collision = (CChip::COLLISION)(((int)m_Collision + 1) % CChip::COLLISION_MAX); bEdit = true; }
			if (pInputKey->GetTPress(DIK_NUMPAD6)) { m_Collision = (CChip::COLLISION)(((int)m_Collision + 1) % CChip::COLLISION_MAX);	bEdit = true; }
		}
		else
		{//�I�����f�����f���ݒ�
			if (pInputKey->GetTPress(DIK_NUMPAD9)) { ChangeCollisionModel(nNumber);		bEdit = true; }
			if (pInputKey->GetTPress(DIK_NUMPAD6)) { ChangeCollisionModel(nNumber);		bEdit = true; }
		}
		break;
	}
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̃|���S���ݒ� *
//==================================================================================================//
void	CMapChip::EditPolygon(int &nNumber, bool &bEdit)
{
	CInputKeyboard	*pInputKey = CManager::GetInputKey();

	if (m_nEdit >= 2) { m_nEdit = 1; }
	if (pInputKey->GetTPress(DIK_RETURN)) { SettingPolygon(nNumber);			bEdit = true; }
	if (pInputKey->GetTPress(DIK_NUMPAD8)) { m_PolyType = (CChip_Polygon::TYPE)((m_PolyType + 1) % CChip_Polygon::TYPE_MAX); }
	if (pInputKey->GetTPress(DIK_NUMPAD5)) { m_PolyType = (CChip_Polygon::TYPE)((m_PolyType + (CChip_Polygon::TYPE_MAX - 1)) % CChip_Polygon::TYPE_MAX); }

	switch (m_nEdit)
	{
	case 0:
		if (pInputKey->GetTPress(DIK_NUMPAD9)) { UpRotationPolygon(nNumber, D3DX_PI * 0.5f);		bEdit = true; }
		if (pInputKey->GetTPress(DIK_NUMPAD6)) { UpRotationPolygon(nNumber, -D3DX_PI * 0.5f);	bEdit = true; }
		break;
	case 1:
		if (pInputKey->GetPress(DIK_LCONTROL))
		{//�����p�ݒ�
			if (pInputKey->GetTPress(DIK_NUMPAD9)) { m_Collision = (CChip::COLLISION)(((int)m_Collision + 1) % CChip::COLLISION_MAX); bEdit = true; }
			if (pInputKey->GetTPress(DIK_NUMPAD6)) { m_Collision = (CChip::COLLISION)(((int)m_Collision + 1) % CChip::COLLISION_MAX);	bEdit = true; }
		}
		else
		{//�I�����f�����f���ݒ�
			if (pInputKey->GetTPress(DIK_NUMPAD9)) { ChangeCollisionModel(nNumber);		bEdit = true; }
			if (pInputKey->GetTPress(DIK_NUMPAD6)) { ChangeCollisionModel(nNumber);		bEdit = true; }
		}
		break;
	}
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̃A�C�e���ݒ� *
//==================================================================================================//
void	CMapChip::EditItem(int &nNumber, bool &bEdit)
{
	CInputKeyboard	*pInputKey = CManager::GetInputKey();

	if (m_nEdit >= 1) { m_nEdit = 0; }
	if (pInputKey->GetTPress(DIK_RETURN))	{ SettingItem(nNumber);			bEdit = true; }
	if (pInputKey->GetTPress(DIK_UP))		{ UpHeightModel(nNumber, 0.25f);		bEdit = true; }
	if (pInputKey->GetTPress(DIK_DOWN))		{ UpHeightModel(nNumber, -0.25f);	bEdit = true; }
	if (pInputKey->GetTPress(DIK_NUMPAD8))	{ m_ItemType = (CChip_Model::TYPE)((m_ItemType + 1) % CChip_Model::TYPE_MAX); }
	if (pInputKey->GetTPress(DIK_NUMPAD5))	{ m_ItemType = (CChip_Model::TYPE)((m_ItemType + (CChip_Model::TYPE_MAX - 1)) % CChip_Model::TYPE_MAX); }

	switch (m_nEdit)
	{
	case 0:
		if (pInputKey->GetTPress(DIK_NUMPAD9)) { UpRotationModel(nNumber, D3DX_PI * 0.5f);		bEdit = true; }
		if (pInputKey->GetTPress(DIK_NUMPAD6)) { UpRotationModel(nNumber, -D3DX_PI * 0.5f);	bEdit = true; }
		break;
	}
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̃|���S���ݒ� *
//==================================================================================================//
void	CMapChip::EditEnemy(int &nNumber)
{
	CInputKeyboard	*pInputKey = CManager::GetInputKey();
	if (m_nEdit >= 1) { m_nEdit = 0; }

}
//==================================================================================================//
//    * �}�b�v�̑傫���ύX *
//==================================================================================================//
void	CMapChip::ChangeSize(int nNumX, int nNumZ)
{
	CMapChip *pMap;
	int nCntL, nCntS;	//L = ��芷����AS = ��芷���O
	int nMaxX, nMaxZ;
	bool bEdit = m_bEdit;
	COneChip *pOneChip;

	if (SceneCreate(pMap, MAP_PRIORYITY))
	{
		pMap->Set(m_pos, nNumX, nNumZ);
		for (int nCount = 0; nCount < nNumX * nNumZ; nCount++)
		{
			pMap->CreateChip(nCount)->SetChip(1);
		}

		if (m_nMaxX > nNumX) { nMaxX = nNumX; }
		else { nMaxX = m_nMaxX; }
		if (m_nMaxZ > nNumZ) { nMaxZ = nNumZ; }
		else { nMaxZ = m_nMaxZ; }

		for (int nCountX = 0; nCountX < nMaxX; nCountX++)
		{
			for (int nCountZ = 0; nCountZ < nMaxZ; nCountZ++)
			{
				nCntL = (nNumX * nCountZ) + nCountX;
				nCntS = (m_nMaxX * nCountZ) + nCountX;
				//if (m_pOneChip[nCntS] == NULL) { continue; }	//��������Ă��Ȃ��Ȃ疳��

				pOneChip = pMap->m_pOneChip[nCntL];
				pMap->m_pOneChip[nCntL] = m_pOneChip[nCntS];
				m_pOneChip[nCntS] = pOneChip;
			}
		}
		pMap->SetMtx();
		pMap->GetbEdit() = true;
		CManager::GetInputKey()->Skip();
	}
	Uninit();
	CManager::GetpMapChip() = pMap;
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̑S�ړ� *
//==================================================================================================//
void	CMapChip::ChangePos(int nNumX, int nNumZ)
{
	int nSNumber, nDNumber;

	if (nNumX < 0)
	{//X��-1�ȉ��̏ꍇ�FX���ɂ��炷
		for (int nCountZ = 0; nCountZ < m_nMaxZ; nCountZ++)
		{
			for (int nCountX = 1; nCountX < m_nMaxX; nCountX++)
			{
				nSNumber = (m_nMaxX * nCountZ) + nCountX;
				nDNumber = (m_nMaxX * nCountZ) + (nCountX - 1);
				if (m_pOneChip[nDNumber] != NULL) { m_pOneChip[nDNumber]->Uninit(); }
				m_pOneChip[nDNumber] = m_pOneChip[nSNumber];
				m_pOneChip[nSNumber] = NULL;
			}
		}
	}
	if (nNumX > 0)
	{//X��1�ȏ�̏ꍇ�F�E��
		for (int nCountZ = 0; nCountZ < m_nMaxZ; nCountZ++)
		{
			for (int nCountX = m_nMaxX - 2; nCountX >= 0; nCountX--)
			{
				nSNumber = (m_nMaxX * nCountZ) + nCountX;
				nDNumber = (m_nMaxX * nCountZ) + (nCountX + 1);
				if (m_pOneChip[nDNumber] != NULL) { m_pOneChip[nDNumber]->Uninit(); }
				m_pOneChip[nDNumber] = m_pOneChip[nSNumber];
				m_pOneChip[nSNumber] = NULL;
			}
		}
	}

	if (nNumZ < 0)
	{//Z��-1�ȉ��̏ꍇ�F��O�ɂ��炷
		for (int nCountX = 0; nCountX < m_nMaxX; nCountX++)
		{
			for (int nCountZ = 1; nCountZ < m_nMaxZ; nCountZ++)
			{
				nSNumber = (m_nMaxX * nCountZ) + nCountX;
				nDNumber = (m_nMaxX * (nCountZ - 1)) + nCountX;
				if (m_pOneChip[nDNumber] != NULL) { m_pOneChip[nDNumber]->Uninit(); }
				m_pOneChip[nDNumber] = m_pOneChip[nSNumber];
				m_pOneChip[nSNumber] = NULL;
			}
		}
	}
	if (nNumZ > 0)
	{//Z��1�ȏ�̏ꍇ�F���ɂ��炷
		for (int nCountX = 0; nCountX < m_nMaxX; nCountX++)
		{
			for (int nCountZ = m_nMaxZ - 2; nCountZ >= 0; nCountZ--)
			{
				nSNumber = (m_nMaxX * nCountZ) + nCountX;
				nDNumber = (m_nMaxX * (nCountZ + 1)) + nCountX;
				if (m_pOneChip[nDNumber] != NULL) { m_pOneChip[nDNumber]->Uninit(); }
				m_pOneChip[nDNumber] = m_pOneChip[nSNumber];
				m_pOneChip[nSNumber] = NULL;
			}
		}
	}

	for (int nCount = 0; nCount < m_nMaxX * m_nMaxZ; nCount++)
	{//NULL�̓z���Đ���
		if (m_pOneChip[nCount] != NULL) { continue; }
		CreateChip(nCount)->SetChip(1);
	}
}
//==================================================================================================//
//    * �}�b�v�`�b�v��X����ړ� *
//==================================================================================================//
void	CMapChip::ChangePosX(int &nNumber, int nValue)
{
	int nSNumber, nDNumber;
	int nNumX0 = nNumber % m_nMaxX;

	if (nValue > 0)
	{//�E�Ɉ�}�X���炷
		for (int nCountZ = 0; nCountZ < m_nMaxZ; nCountZ++)
		{
			for (int nCountX = 1; nCountX < nNumX0; nCountX++)
			{
				nSNumber = (m_nMaxX * nCountZ) + nCountX;
				nDNumber = (m_nMaxX * nCountZ) + (nCountX - 1);
				if (m_pOneChip[nDNumber] != NULL) { m_pOneChip[nDNumber]->Uninit(); }
				m_pOneChip[nDNumber] = m_pOneChip[nSNumber];
				m_pOneChip[nSNumber] = NULL;
			}
		}
	}
	else if (nValue < 0)
	{//���Ɉ�}�X���炷
		for (int nCountZ = 0; nCountZ < m_nMaxZ; nCountZ++)
		{
			for (int nCountX = m_nMaxX - 2; nCountX >= nNumX0 + 1; nCountX--)
			{
				nSNumber = (m_nMaxX * nCountZ) + nCountX;
				nDNumber = (m_nMaxX * nCountZ) + (nCountX + 1);
				if (m_pOneChip[nDNumber] != NULL) { m_pOneChip[nDNumber]->Uninit(); }
				m_pOneChip[nDNumber] = m_pOneChip[nSNumber];
				m_pOneChip[nSNumber] = NULL;
			}
		}
	}
	for (int nCount = 0; nCount < m_nMaxX * m_nMaxZ; nCount++)
	{//NULL�̓z���Đ���
		if (m_pOneChip[nCount] != NULL) { continue; }
		CreateChip(nCount)->SetChip(1);
	}
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̊Ǘ����̈�̃`�b�v�̍폜 *
//==================================================================================================//
void	CMapChip::DeleteChip(int &nNumber)
{
	CChip *&pChip = m_pOneChip[nNumber]->GetChip(m_nSelect);
	if (pChip != NULL) { pChip->Uninit(); pChip = NULL; }
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̊Ǘ����̈�̃`�b�v�̐����E�ύX *
//==================================================================================================//
void	CMapChip::SettingModel(int &nNumber)
{
	if (m_pOneChip[nNumber] != NULL)
	{
		CChip *&pChip = m_pOneChip[nNumber]->GetChip(m_nSelect);
		if (m_pOneChip[nNumber] != NULL)
		{
			m_pOneChip[nNumber]->CreateChip(pChip, CChip::TYPE_MODEL);
			((CChip_Model*)pChip)->Set(m_ModelType);
			((CChip_Model*)pChip)->GetfPosY() = m_fInitHeight;
			((CChip_Model*)pChip)->GetCollision() = m_Collision;

			switch (m_ModelType)
			{
			case CChip_Model::TYPE_ROCK00:	((CChip_Model*)pChip)->GetfPosY() += 0.15f; break;
			case CChip_Model::TYPE_FENCE00: ((CChip_Model*)pChip)->GetfPosY() += 0.25f;	break;
			}
		}
	}
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̊Ǘ����̈�̃`�b�v�̐����E�ύX *
//==================================================================================================//
void	CMapChip::SettingItem(int &nNumber)
{
	if (m_pOneChip[nNumber] != NULL)
	{
		CChip *&pChip = m_pOneChip[nNumber]->GetChip(m_nSelect);
		if (m_pOneChip[nNumber] != NULL)
		{
			m_pOneChip[nNumber]->CreateChip(pChip, CChip::TYPE_MODEL);
			((CChip_Model*)pChip)->Set(m_ItemType);
			((CChip_Model*)pChip)->GetfPosY() = m_fInitHeight;
			((CChip_Model*)pChip)->GetCollision() = CChip::COLLISION_NO;
			((CChip_Model*)pChip)->GetState() = CChip_Model::STATE_ITEM;
		}
	}
}
//==================================================================================================//
//    * �A�C�e���̃h���b�v *
//==================================================================================================//
void	CMapChip::DropItem(D3DXVECTOR3 pos, CChip_Model::TYPE model)
{
	CMapChip *&pMap = CManager::GetpMapChip();

	if (pMap == NULL) { return; }
	COneChip **&m_pOneChip = pMap->m_pOneChip;
	D3DXVECTOR3 &m_pos = pMap->Getpos();
	int			&m_nMaxX = pMap->GetnMaxX();
	int			nNumX, nNumZ, nNumber;

	nNumX = (int)((pos.x - m_pos.x + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumZ = (int)((pos.z - m_pos.z + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumber = (m_nMaxX * nNumZ) + nNumX;

	//�`�b�v���Ȃ��Ȃ�
	if (m_pOneChip[nNumber] == NULL) { return; }

	int			&m_nMaxChip = m_pOneChip[nNumber]->GetnMaxChip();
	for (int nCount = 0; nCount < m_nMaxChip; nCount++)
	{//�S�`�b�v�����
		CChip *&pChip = m_pOneChip[nNumber]->GetChip(nCount);
		if (pChip == NULL)
		{
			m_pOneChip[nNumber]->CreateChip(pChip, CChip::TYPE_MODEL);
			((CChip_Model*)pChip)->Set(model);
			((CChip_Model*)pChip)->GetfPosY() = pos.y / MAP_CHIP_SIZE;
			((CChip_Model*)pChip)->GetState() = CChip_Model::STATE_ITEM_MOVE;
			((CChip_Model*)pChip)->GetfCntState() = 1.0f;
			((CChip_Model*)pChip)->GetMove() = D3DXVECTOR3(0.035f, 0.075f, 0.0f);

			D3DXVECTOR3 WKpos = INIT_VECTOR;
			WKpos.x = (nNumber % m_nMaxX) * MAP_CHIP_SIZE + m_pos.x;
			WKpos.z = (nNumber / m_nMaxX) * MAP_CHIP_SIZE + m_pos.z;
			pChip->GetCollision() = CChip::COLLISION_NO;
			pChip->SetMtx(WKpos);
			break;
		}

	}

}
//==================================================================================================//
//    * ���f���_�E����0�Ԃ�NORMAL�ɕύX *
//==================================================================================================//
void	CMapChip::DownSetField(D3DXVECTOR3 pos)
{
	CMapChip *&pMap = CManager::GetpMapChip();

	if (pMap == NULL) { return; }
	COneChip **&m_pOneChip = pMap->m_pOneChip;
	D3DXVECTOR3 &m_pos = pMap->Getpos();
	int			&m_nMaxX = pMap->GetnMaxX();
	int			nNumX, nNumZ, nNumber;

	nNumX = (int)((pos.x - m_pos.x + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumZ = (int)((pos.z - m_pos.z + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumber = (m_nMaxX * nNumZ) + nNumX;

	//�`�b�v���Ȃ��Ȃ�
	if (m_pOneChip[nNumber] == NULL) { return; }

	m_pOneChip[nNumber]->GetChip(0)->GetCollision() = CChip::COLLISION_NORMAL;
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̃}�X�̈ʒu��Ԃ� *
//==================================================================================================//
D3DXVECTOR3 CMapChip::GetposChip(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 &m_pos = Getpos();
	int			&m_nMaxX = GetnMaxX();
	int			nNumX, nNumZ, nNumber;

	nNumX = (int)((pos.x - m_pos.x + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumZ = (int)((pos.z - m_pos.z + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumber = (m_nMaxX * nNumZ) + nNumX;

	pos.x = nNumX * MAP_CHIP_SIZE + m_pos.x;
	pos.z = nNumZ * MAP_CHIP_SIZE + m_pos.z;

	return D3DXVECTOR3(pos.x, 0.0f, pos.z);
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̊Ǘ����̈�̃`�b�v�̍����ύX *
//==================================================================================================//
void	CMapChip::UpHeightModel(int &nNumber, float fValue)
{
	CChip *&pChip = m_pOneChip[nNumber]->GetChip(m_nSelect);
	if (pChip == NULL) { return; }
	if (pChip->GetType() == CChip::TYPE_MODEL)
	{
		((CChip_Model*)pChip)->GetfPosY() += fValue;
	}
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̊Ǘ����̈�̃`�b�v�̍����ύX *
//==================================================================================================//
void	CMapChip::UpRotationModel(int &nNumber, float fValue)
{
	CChip *&pChip = m_pOneChip[nNumber]->GetChip(m_nSelect);
	if (pChip == NULL) { return; }
	if (pChip->GetType() == CChip::TYPE_MODEL)
	{
		float &fRot = ((CChip_Model*)pChip)->GetRot().y;
		fRot += fValue;
		if (fRot > D3DX_PI) { fRot -= D3DX_PI * 2.0f; }
		if (fRot < D3DX_PI) { fRot += D3DX_PI * 2.0f; }
	}
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̊Ǘ����̈�̃`�b�v�̓����蔻��ύX *
//==================================================================================================//
void	CMapChip::ChangeCollisionModel(int &nNumber)
{
	CChip *&pChip = m_pOneChip[nNumber]->GetChip(m_nSelect);
	if (pChip == NULL) { return; }
	pChip->GetCollision() = (CChip::COLLISION)(((int)pChip->GetCollision() + 1) % CChip::COLLISION_MAX);
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̊Ǘ����̈�̃`�b�v�̐����E�ύX *
//==================================================================================================//
void	CMapChip::SettingPolygon(int &nNumber)
{
	if (m_pOneChip[nNumber] != NULL)
	{
		CChip *&pChip = m_pOneChip[nNumber]->GetChip(m_nSelect);
		if (m_pOneChip[nNumber] != NULL)
		{
			m_pOneChip[nNumber]->CreateChip(pChip, CChip::TYPE_POLYGON);
			((CChip_Polygon*)pChip)->Set(m_PolyType, m_fInitHeight);
			((CChip_Polygon*)pChip)->GetCollision() = m_Collision;
		}
	}
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̊Ǘ����̈�̃`�b�v�̍����ύX *
//==================================================================================================//
void	CMapChip::UpRotationPolygon(int &nNumber, float fValue)
{
	CChip *&pChip = m_pOneChip[nNumber]->GetChip(m_nSelect);
	if (pChip == NULL) { return; }
	if (pChip->GetType() == CChip::TYPE_POLYGON)
	{
		float &fRot = ((CChip_Polygon*)pChip)->GetRot().y;
		fRot += fValue;
		if (fRot > D3DX_PI) { fRot -= D3DX_PI * 2.0f; }
		if (fRot < D3DX_PI) { fRot += D3DX_PI * 2.0f; }
	}
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̃G�f�B�b�g���X�V *
//==================================================================================================//
void	CMapChip::EditTrue(void)
{
	SetMtx();
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̏�ԕ`�� *
//==================================================================================================//
void	CMapChip::StatusLog(int &nNumX, int &nNumZ, int &nNumber)
{
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "X�ő�  %d,  Z�ő�  %d\n", m_nMaxX, m_nMaxZ);
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "���ݒn X %d,  Z %d\n", nNumX, nNumZ);
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�ʒu X %.1f,  Z %.1f\n\n", nNumX * MAP_CHIP_SIZE, nNumZ * MAP_CHIP_SIZE);

	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�I��� %d,  �������� %.1f\n", m_nSelect, m_fInitHeight);
	switch (m_Edit)
	{
	case EDIT_MODEL:
		CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "EDIT:MODEL  ������%d\n", m_ModelType);
		switch (m_nEdit)
		{
		case 0: CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�ύX��F�p�xd\n");		break;
		case 1: CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�ύX��F�����蔻��d\n");	break;
		}
		break;
	case EDIT_POLYGON:
		CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "EDIT:POLY   ������%d\n", m_PolyType);
		switch (m_nEdit)
		{
		case 0: CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�ύX��F�p�xd\n");		break;
		case 1: CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�ύX��F�����蔻��d\n");	break;
		}
		break;
	case EDIT_ITEM:
		CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "EDIT:ITEM  ������%d\n", m_ItemType);
		CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�ύX��F�p�xd\n");		break;
		break;
	case EDIT_ENEMY:
		CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "EDIT:ENEMY   ������%d\n", m_EnmType);
		break;
	}
	m_nMaxSelect = 1;
	if (m_pOneChip != NULL)
	{//��}�X���Ƃ̃`�b�v����������Ă���Ȃ�
		if (nNumX > -1 && nNumX < m_nMaxX && nNumZ > -1 && nNumZ < m_nMaxZ)
		{//�͈͓��Ȃ�
			if (m_pOneChip[nNumber] != NULL)
			{//��������Ă��Ȃ��Ȃ疳��
				m_pOneChip[nNumber]->StatusLog(m_nMaxSelect);
				if (m_pOneChip[nNumber]->GetnMaxChip() > 0)
				{//�`�b�v��1�ȏ゠��Ȃ�
					if (m_pOneChip[nNumber]->GetChip(m_nSelect) != NULL)
					{
						m_pOneChip[nNumber]->GetChip(m_nSelect)->GetbSelect() = true;
					}
				}
			}
		}
	}
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̃}�b�v�ݒ� *
//==================================================================================================//
void	CMapChip::SetMap(MAP Map)
{
	char aStr[32];

	m_Map = Map;

	GetMapFont(aStr);	//�}�b�v�̕�����擾
	Load(aStr);			//�}�b�v�̃��[�h
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̃}�b�v���Ƃ̕����擾 *
//==================================================================================================//
void	CMapChip::SetMapData(void)
{
	CStory *pStory;
	switch (m_Map)
	{
	case MAP_TITLE:		SetSea();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 4.5f, MAP_CHIP_SIZE * 2.0f, MAP_CHIP_SIZE * 4.5f)); break;
	case MAP_SELECT:	SetSea();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 4.5f, MAP_CHIP_SIZE * 2.0f, MAP_CHIP_SIZE * 4.5f)); break;
	case MAP_PRACTICE:	
		CPlayer::GetnTime() = 100;
		SetSea();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 2.0f, MAP_CHIP_SIZE * 0.5f, MAP_CHIP_SIZE * 3.9f)); break;
	case MAP_PRINCESS:
		if (SceneCreate(pStory, STORY_PRIORITY)) { pStory->Set(CStory::STORY_01_Departure); }
		CPlayer::GetnTime() = 100;
		SetSea();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 6.0f, MAP_CHIP_SIZE * 0.0f, MAP_CHIP_SIZE * 1.0f)); break;
	case MAP_1:			
		CPlayer::GetnTime() = 100;
		SetSea();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 8.0f, 0.0f, MAP_CHIP_SIZE * 4.0f)); break;
	case MAP_2:			SetField();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 6.0f, 0.0f, MAP_CHIP_SIZE * 4.0f)); break;
	case MAP_3:			SetField();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 6.0f, MAP_CHIP_SIZE * 0.5f, MAP_CHIP_SIZE * 11.0f)); break;
	case MAP_4:			SetField();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 5.0f, MAP_CHIP_SIZE * 1.5f, MAP_CHIP_SIZE * 4.0f)); break;
	case MAP_BOSS:		
		if (SceneCreate(pStory, STORY_PRIORITY)) { pStory->Set(CStory::STORY_02_KingBattle); }
		CPlayer::GetnTime() = 100;
		SetField();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 9.0f, MAP_CHIP_SIZE * 5.0f, MAP_CHIP_SIZE * 2.0f));  break;
	case MAP_RESULT:
		if (SceneCreate(pStory, STORY_PRIORITY)) { pStory->Set(CStory::STORY_03_EATEAT); }
		CPlayer::GetnTime() = 100;
		SetSea();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 5.0f, MAP_CHIP_SIZE * 0.0f, MAP_CHIP_SIZE * 1.0f)); break;
	}
	CManager::GetCamera()->Reset();
	if (m_nClear > 0)
	{
		CCamera_Char *pCamera = CManager::GetCamera()->GetPlay(0)->GetChar();
		pCamera->GetposV().x += MAP_CHIP_SIZE * 3.0f;
		pCamera->GetposR().x += MAP_CHIP_SIZE * 3.0f;
	}

}
//==================================================================================================//
//    * �}�b�v�`�b�v�̔w�i�i�t�B�[���h�j�̐��� *
//==================================================================================================//
void	CMapChip::SetSea(void)
{
	CMapChip_BG_SEA *pBG;
	if (Create(pBG)) { m_pBG = pBG; }
	m_bMirror = true;
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̔w�i�i�t�B�[���h�j�̐��� *
//==================================================================================================//
void	CMapChip::SetField(void)
{
	CMapChip_BG_Field *pBG;
	if (Create(pBG)) { m_pBG = pBG; }
	m_bMirror = false;
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̃}�b�v���Ƃ̕����擾 *
//==================================================================================================//
void	CMapChip::GetMapFont(char *aStr)
{
	switch (m_Map)
	{
	case MAP_TITLE:		strcpy(aStr, "Title.txt"); break;
	case MAP_SELECT:	strcpy(aStr, "Select.txt"); break;
	case MAP_PRACTICE:	strcpy(aStr, "Practice.txt"); break;
	case MAP_PRINCESS:	strcpy(aStr, "Practice.txt"); break;
	case MAP_1:			strcpy(aStr, "1-1.txt"); break;
	case MAP_2:			strcpy(aStr, "1-2.txt"); break;
	case MAP_3:			strcpy(aStr, "1-3.txt"); break;
	case MAP_4:			strcpy(aStr, "1-4.txt"); break;
	case MAP_BOSS:		strcpy(aStr, "Boss.txt"); break;
	case MAP_RESULT:	strcpy(aStr, "Practice.txt"); break;
	}
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̃`�b�v���� *
//==================================================================================================//
void	CMapChip::SampleMap(void)
{
	Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5, 10);
	for (int nCount = 0; nCount < m_nMaxOneChip; nCount++)
	{
		COneChip *pOneChip = CreateChip(nCount);
		if (pOneChip != NULL)
		{
			pOneChip->SetChip(1);

			CChip *&pChip = pOneChip->GetChip(0);

			//CChip *&pChip2 = pOneChip->GetChip(1);
			//pOneChip->CreateChip(pChip2, CChip::TYPE_MODEL);
			//((CChip_Model*)pChip2)->Set(CChip_Model::TYPE_BOX);
			//((CChip_Model*)pChip2)->GetfPosY() = 50.0f;
		}
	}
	SetMtx();
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̃`�b�v���� *
//==================================================================================================//
void	CMapChip::Load(char *aStr)
{
	FILE *pFile = NULL;
	MAP WKMap = m_Map;
	char aMap[128] = "data/TEXT/MAP/";		strcat(&aMap[0], &aStr[0]);
	char aEnm[128] = "data/TEXT/ENEMY/";	strcat(&aEnm[0], &aStr[0]);
	pFile = fopen(aMap, "r");
	int nData;

	if (pFile != NULL)
	{//Save�@����
		CScene::BreakObject(CScene::OBJTYPE_ENEMY);
		CEnemy::Load(aEnm);

		Reset(); Init();	//������
		m_Map = WKMap;
		fscanf(pFile, "%d %d %d\n", &m_nMaxX, &m_nMaxZ, &m_nMaxOneChip);
		Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_nMaxX, m_nMaxZ);	//����

		for (int nCount = 0; nCount < m_nMaxOneChip; nCount++)
		{
			fscanf(pFile, "%d \n", &nData);
			
			if (nData != 0)
			{//�`�b�v������Ȃ�ǂݍ���
				CreateChip(nCount)->Load(pFile);
			}
			else { CreateChip(nCount)->SetChip(10); }
			fscanf(pFile, "\n");
		}
		fclose(pFile);
		SetMapData();	//�}�b�v���Ƃ̏������s
		SetMtx();		//�}�g���b�N�X�v�Z
	}
}
//==================================================================================================//
//    * �}�b�v�`�b�v�̃`�b�v���� *
//==================================================================================================//
void	CMapChip::Save(char *aStr)
{
	FILE *pFile = NULL;
	pFile = fopen(&aStr[0], "w");

	if (pFile != NULL)
	{//Save�@����
		fprintf(pFile, "%d %d %d\n", m_nMaxX, m_nMaxZ, m_nMaxOneChip);
		for (int nCount = 0; nCount < m_nMaxOneChip; nCount++)
		{//�`�b�v�̕ۑ�
			if (m_pOneChip[nCount] == NULL) { fprintf(pFile, "%d \n", 0); }	//��������Ă��Ȃ��Ȃ疳��
			else
			{
				fprintf(pFile, "%d \n", 1);
				m_pOneChip[nCount]->Save(pFile);
			}
			fprintf(pFile, "\n");
		}
		CEnemy::Save();
		fclose(pFile);
	}
}