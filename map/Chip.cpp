//=============================================================================
//
// �`�b�v���� [Chip.cpp]
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
#include "motion.h"
#include "Chip.h"
#include "camera.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "3DPolygon.h"
#include "player.h"
#include "FallingStone.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//==================================================================================================//
//    *	��b�`�b�v�̕ۑ� *
//==================================================================================================//
void CChip::Save(FILE *&pFile)
{
	fprintf(pFile, "%d \n", m_type);
	fprintf(pFile, "%d \n", m_collision);
}
//==================================================================================================//
//    *	��b�`�b�v�̓ǂݍ��� *
//==================================================================================================//
void CChip::Load(FILE *&pFile)
{
	fscanf(pFile, "%d \n", &m_type);
	fscanf(pFile, "%d \n", &m_collision);
}
//==================================================================================================//
//    *	��b�`�b�v�̓ǂݍ��� *
//==================================================================================================//
void	CChip::StatusLog(void)
{
	char aStr[2][64];
	switch (m_type)
	{
	case TYPE_NULL:		strcpy(&aStr[0][0], "TYPE�FNULL"); break;
	case TYPE_MODEL:	strcpy(&aStr[0][0], "TYPE�FMODEL"); break;
	case TYPE_POLYGON:	strcpy(&aStr[0][0], "TYPE�FPOLYGON"); break;
	}
	int n = GetCollision();
	switch (GetCollision())
	{
	case COLLISION_NO:		strcpy(&aStr[1][0], "COLLISION�FNO"); break;
	case COLLISION_NORMAL:	strcpy(&aStr[1][0], "COLLISION�FNORMAL"); break;
	case COLLISION_WALL:	strcpy(&aStr[1][0], "COLLISION�FWALL"); break;
	}
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "%s, %s\n", &aStr[0][0], &aStr[1][0]);
}
//==================================================================================================//
//    *		���f���`�b�v��Y�����蔻�� *
//==================================================================================================//
bool	CChip::CollisionY_Base(CCharacter *&pChar, D3DXVECTOR3 length)
{
	if (GetCollision() != COLLISION_NORMAL) { return false; }

	D3DXMATRIX	&m_mtx = GetMtx();
	D3DXVECTOR3 &m_pos = D3DXVECTOR3(m_mtx._41, m_mtx._42, m_mtx._43);
	D3DXVECTOR3 playLength = pChar->Getlength();
	D3DXVECTOR3 &pos = pChar->Getpos();
	D3DXVECTOR3 &posold = pChar->Getposold();
	bool bLand = false;

												//Y���̂����蔻��
	if (m_pos.x + length.x + playLength.x >= pos.x && m_pos.x - length.x - playLength.x <= pos.x &&
		m_pos.z + length.z + playLength.z >= pos.z && m_pos.z - length.z - playLength.z <= pos.z)
	{//XZ�͈͓��Ȃ�
		if (m_pos.y + length.y <= posold.y && m_pos.y + length.y >= pos.y)
		{//�������蔻��
			pos.y = m_pos.y + length.y;
			bLand = true;
		}
		else if (m_pos.y - length.y - playLength.y >= posold.y && m_pos.y - length.y - playLength.y < pos.y && length.y != 0.0f)
		{//�゠���蔻��
			pos.y = m_pos.y - length.y - playLength.y;
		}
	}
	return bLand;
}
//==================================================================================================//
//    *		���f���`�b�v��XZ�����蔻�� *
//==================================================================================================//
bool	CChip::CollisionXZ_Base(CCharacter *&pChar, D3DXVECTOR3 length, bool bYModel, int &nHit)
{
	if (GetCollision() == COLLISION_NO) { return false; }

	D3DXMATRIX	&m_mtx = GetMtx();
	D3DXVECTOR3 &m_pos = D3DXVECTOR3(m_mtx._41, m_mtx._42, m_mtx._43);
	D3DXVECTOR3 &playLength = pChar->Getlength();
	D3DXVECTOR3 &pos = pChar->Getpos();
	D3DXVECTOR3 &posold = pChar->Getposold();
	bool		bHit = false;				//�q�b�g�̗L��
	float		fHitAngle = -1.0f;				//Z�q�b�g�̗L��

	//XZ�̂����蔻��
	if (m_pos.y + length.y > pos.y && (m_pos.y - length.y - playLength.y < pos.y || bYModel) || GetCollision() == COLLISION_WALL)
	{//Y�͈͓��Ȃ�
		if (m_pos.z - length.z - playLength.z <= pos.z && m_pos.z + length.z + playLength.z >= pos.z)
		{//Z�͈͓��Ȃ�
			if (m_pos.x + length.x + playLength.x <= posold.x && m_pos.x + length.x + playLength.x > pos.x)
			{//X(�E)�̂����蔻��
				pos.x = m_pos.x + length.x + playLength.x + 0.1f;
				nHit++;
				fHitAngle = 0.0f;
				bHit = true;
			}
			else if (m_pos.x - length.x - playLength.x >= posold.x && m_pos.x - length.x - playLength.x < pos.x)
			{//X(��)�̂����蔻��
				pos.x = m_pos.x - length.x - playLength.x - 0.1f;
				fHitAngle = 1.0f;
				bHit = true;
			}
		}
		if (m_pos.x - length.x - playLength.x < pos.x && m_pos.x + length.x + playLength.x > pos.x)
		{//X�͈͓��Ȃ�
			if (m_pos.z - length.z - playLength.z >= posold.z)
			{//Z(�O)�̂����蔻��
				if (m_pos.z - length.z - playLength.z < pos.z)
				{
					pos.z = m_pos.z - length.z - playLength.z - 0.1f;
					nHit++;
					fHitAngle = 2.0f;
					bHit = true;
				}
				else if (m_pos.z - length.z - playLength.z < pos.z + 0.15f)
				{
					bHit = true;
				}
			}
			else if (m_pos.z + length.z + playLength.z <= posold.z && m_pos.z + length.z + playLength.z > pos.z)
			{//Z(���)�̂����蔻��
				pos.z = m_pos.z + length.z + playLength.z + 0.1f;
				nHit++;
				fHitAngle = 3.0f;
				bHit = true;
			}
		}

		if (fHitAngle >= 0.0f && nHit >= 0)
		{//�ǉ���
			MoveCorrection(pChar, fHitAngle, length);
		}
	}

	return bHit;
}
//==================================================================================================//
//    *		�ǃq�b�g���̈ړ��␳ *
//==================================================================================================//
void	CChip::MoveCorrection(CCharacter *&pChar, float &fAngle, D3DXVECTOR3 length)
{
	D3DXMATRIX	&m_mtx = GetMtx();
	D3DXVECTOR3 &m_pos = D3DXVECTOR3(m_mtx._41, m_mtx._42, m_mtx._43);
	D3DXVECTOR3 &playLength = pChar->Getlength();
	D3DXVECTOR3 &pos = pChar->Getpos();
	D3DXVECTOR3 &posold = pChar->Getposold();

	CMapChip *&pMap = CManager::GetpMapChip();
	float	fAngleX = 0.0f;
	float	fAngleZ = 0.0f;

	if (fAngle < 2.0f) { fAngleZ = 1.0f; }
	else { fAngleX = 1.0f; }
	if (pos.x < m_pos.x) { fAngleX *= -1.0f; }
	if (pos.z < m_pos.z) { fAngleZ *= -1.0f; }

	D3DXVECTOR3 WKpos = pos;
	D3DXVECTOR3 WKold = posold;
	int nNumber = pMap->GetnWKNumber();
	int nNumX = nNumber % pMap->GetnMaxX() + (int)fAngleX;
	int nNumZ = nNumber / pMap->GetnMaxX() + (int)fAngleZ;
	bool bCollision = true;

	if (nNumX >= 0 && nNumX < pMap->GetnMaxX() &&
		nNumZ >= 0 && nNumZ < pMap->GetnMaxZ())
	{//�`�b�v�̈�m�F
		int nWKHit = -99;
		nNumber = pMap->GetnMaxX() * nNumZ + nNumX;

		//�w�肵���`�b�v���ʂ�邩�m�F
		pos = D3DXVECTOR3(m_pos.x + MAP_CHIP_SIZE * fAngleX, WKpos.y, m_pos.z + MAP_CHIP_SIZE * fAngleZ);
		posold = D3DXVECTOR3(m_pos.x, WKpos.y, m_pos.z);
		if (pMap->GetOneChip(nNumber)->CollisionXZ(pChar, nWKHit)) { bCollision = false; }
		pos = WKpos;
		posold = WKold;

		if (bCollision)
		{//�w�肵���`�b�v���ʂ��Ȃ牡�␳
			if (fAngle < 2.0f)
			{//Z�␳
				float	fLength = length.z + playLength.z;
				pos.z += ((m_pos.z + fLength * fAngleZ) - m_pos.z) * 0.035f;
				if ((fAngleZ == 1.0f ? pos.z > m_pos.z + fLength : pos.z < m_pos.z - fLength))
				{//X�̃s�b�^���␳
					pos.z = m_pos.z + (fLength + 0.25f) * fAngleZ;
					pChar->Getmove().z = 0.0f;
				}
			}
			else
			{//X�␳
				float	fLength = length.x + playLength.x;
				pos.x += ((m_pos.x + fLength * fAngleX) - m_pos.x) * 0.035f;
				if ((fAngleX == 1.0f ? pos.x > m_pos.x + fLength : pos.x < m_pos.x - fLength))
				{//X�̃s�b�^���␳
					pos.x = m_pos.x + (fLength + 0.25f) * fAngleX;
					pChar->Getmove().x = 0.0f;
				}
			}
		}
	}//if(�`�b�v�̈�m�F)
}
//==================================================================================================//
//    *		���f���`�b�v�̏����� *
//==================================================================================================//
HRESULT CChip_Model::Init(void)
{
	CChip::Init();
	CChip::GetType() = CChip::TYPE_MODEL;
	m_state = STATE_NONE;
	m_addpos = INIT_VECTOR;
	m_rot = INIT_VECTOR;
	m_move = INIT_VECTOR;
	m_type = TYPE_BLOCK00;
	m_fCntState = 0.0f;
	return S_OK;
}
//==================================================================================================//
//    *		���f���`�b�v�̍X�V *
//==================================================================================================//
bool	CChip_Model::Update(void)
{
	D3DXMATRIX &m_Mtx = GetMtx();
	D3DXVECTOR3 pos;

	switch (m_type)
	{
	case TYPE_GOAL1:
	case TYPE_GOAL2:
		GoalUpdate();
		break;
	}
	switch (m_state)
	{
	case STATE_BREAK:	BreakUpdate(); break;
	case STATE_DOWN:	
		m_rot.x += m_rot.x * 0.03f;
		if (m_rot.x > D3DX_PI * 0.5f)
		{ 
			m_rot.x = D3DX_PI * 0.5f; m_state = STATE_NONE;
			GetCollision() = COLLISION_NO;
		}
		pos = D3DXVECTOR3(m_Mtx._41, 0.0f, m_Mtx._43) - (m_addpos * MAP_CHIP_SIZE);
		SetMtx(pos);
		break;
	case STATE_ITEM_MOVE:
		m_fCntState += 1.0f;

		if (m_fCntState > 300.0f) { return true; }
		if ((int)(300 - m_fCntState) / 5 > 0)
		{
			if ((int)m_fCntState % (int)(300 - m_fCntState) / 5 == 0) { GetDType() = DTYPE_MAX; }
			else { GetDType() = DTYPE_OBJECT; }
		}
		else { GetDType() = DTYPE_OBJECT; }

		pos = D3DXVECTOR3(m_Mtx._41, m_addpos.y * MAP_CHIP_SIZE, m_Mtx._43) - (m_addpos * MAP_CHIP_SIZE);
		m_move.y -= 0.0035f;
		m_addpos += m_move;
		m_move.x *= 0.99f; m_move.z *= 0.99f;
		SetMtx(pos);
		pos = D3DXVECTOR3(m_Mtx._41, m_Mtx._42, m_Mtx._43);
		//���݂̈ʒu��Y���擾
		if (CManager::GetpMapChip()->GetHeight(pos, 0) + MAP_CHIP_SIZE * 0.35f > pos.y)
		{//�n�ʂ�艺�Ȃ�
			m_move.y = 0.075f;
		}
	case STATE_ITEM: return ItemUpdate();
	case STATE_OVER: 
		m_fCntState += 1.0f;
		if (m_fCntState > 80.0f) { return true; }
		break;
	}
	return false;
}
//==================================================================================================//
//    *		�A�C�e���`�b�v�̍X�V *
//==================================================================================================//
bool	CChip_Model::ItemUpdate(void)
{
	if (CManager::GetpMapChip()->GetbEdit()) { return false; }

	D3DXMATRIX &m_Mtx = GetMtx();
	CPlayer *pPlayer = CPlayer::HitPlayer(D3DXVECTOR3(m_Mtx._41, m_Mtx._42, m_Mtx._43), MAP_CHIP_SIZE * 0.7f);
	if (pPlayer != NULL)
	{
		switch (m_type)
		{
		case TYPE_MEAT_S: m_state = STATE_OVER;		pPlayer->SetEat(1);		m_fCntState = 0.0f; break;
		case TYPE_MEAT_M: m_state = STATE_OVER;		pPlayer->SetEat(2);		m_fCntState = 0.0f; break;
		case TYPE_BANANA:		CCommon_UI::ScoreAdd(777);	return true;
		case TYPE_STRAWBERRY:	CCommon_UI::ScoreAdd(300);	return true;
		case TYPE_WATERMELON:	CCommon_UI::ScoreAdd(3000);	return true;
		case TYPE_GRAPE:		CCommon_UI::ScoreAdd(800);	return true;
		case TYPE_SPECIES:		pPlayer->SetFlower(true);	return true;
		}
	}

	m_rot.y += D3DX_PI * 0.01f;
	D3DXVECTOR3 pos = D3DXVECTOR3(m_Mtx._41, m_Mtx._42, m_Mtx._43) - (m_addpos * MAP_CHIP_SIZE);
	SetMtx(pos);
	return false;
}
//==================================================================================================//
//    *		�S�[���`�b�v�̍X�V *
//==================================================================================================//
void	CChip_Model::GoalUpdate(void)
{
	D3DXMATRIX &m_Mtx = GetMtx();
	D3DXVECTOR3 pos = D3DXVECTOR3(m_Mtx._41, m_Mtx._42, m_Mtx._43);
	CMapChip *&MapChip = CManager::GetpMapChip();
	D3DXVECTOR3 &Mappos = MapChip->Getpos();
	int &nWKNumber = MapChip->GetnWKNumber();
	int &nMaxX = MapChip->GetnMaxX();
	int nCntX = nWKNumber % nMaxX, nCntZ = nWKNumber / nMaxX;
	pos.x = nCntX * MAP_CHIP_SIZE + Mappos.x;
	pos.z = nCntZ * MAP_CHIP_SIZE + Mappos.z;
	pos.y = Mappos.y;

	float fValue = 1.0f;
	float fPosX = CManager::GetCamera()->GetPlay(0)->GetChar()->GetposR().x;

	if (fPosX > pos.x - MAP_CHIP_SIZE * 0.0f)
	{//���͈͓��Ȃ�
		if (MapChip->GetnClear() > 0) { fValue *= -1; }
		switch (m_type)
		{
		case TYPE_GOAL1:
			m_addpos.x -= 0.5f / 100.0f * fValue;
			if (m_addpos.x < -0.5f) { m_addpos.x = -0.5f; }
			if (m_addpos.x > 0.0f && fValue < 0.0f) { m_addpos.x = 0.0f; }
			break;
		case TYPE_GOAL2:
			m_addpos.x += 0.5f / 100.0f * fValue;
			if (m_addpos.x > 0.5f) { m_addpos.x = 0.5f; }
			if (m_addpos.x < 0.0f && fValue < 0.0f) { m_addpos.x = 0.0f; }
			break;
		}
		SetMtx(pos);
	}
}
//==================================================================================================//
//    *		���f���`�b�v�̍U�������蔻�� *
//==================================================================================================//
void	CChip_Model::BreakUpdate(void)
{
	D3DXMATRIX &m_Mtx = GetMtx();
	D3DXVECTOR3 pos = D3DXVECTOR3(m_Mtx._41, m_Mtx._42, m_Mtx._43);

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		CPlayer *&pPlyaer = CManager::GetPlayer(nCount);
		if (pPlyaer != NULL)
		{
			CCharacter *pAtk = (CCharacter*)pPlyaer;
			COneMotion	*pOneMotion = &CMotion::GetMotion(pAtk->GetType())->GetOneMotion()[pAtk->GetnNumMotion(0)];
			if (pOneMotion->GetType()[pAtk->GetnNumMotion(2)] == CKey::TYPE_ATTACK)
			{//�U���̃L�[�ł���
				CAtkKey		*pKey = (CAtkKey*)pOneMotion->GetKey()[pAtk->GetnNumMotion(2)];

				if (CCharacter::HitAtkCheck(pAtk, pos, D3DXVECTOR3(MAP_CHIP_SIZE, MAP_CHIP_SIZE * 2.0f, MAP_CHIP_SIZE) * 1.0f, pAtk->GetpParts()[0]->GetmtxWorld(pKey->GetnAtkParts()), pKey->GetfRange(), pKey->GetnCntAtk()))
				{
					m_state = STATE_DOWN;
					m_rot.x = D3DX_PI * 0.03f;
				}
			}
		}
	}
}
//==================================================================================================//
//    *		���f���`�b�v�̕`�� *
//==================================================================================================//
void	CChip_Model::Draw(void)
{
	bool &bMirror = CManager::GetpMapChip()->GetbMirror();
	if (bMirror && m_state != STATE_ITEM)
	{
		LPDIRECT3DDEVICE9 &pDevice = CManager::GetRenderer()->GetDevice();
		pDevice->Clear(0, NULL, (D3DCLEAR_STENCIL), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
		D3DXMATRIX &m_Mtx = GetMtx();
		CSceneModel::MODEL model = CSceneModel::MODEL_BLOC00;
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		D3DXMATRIX	WKmtx, SMtx, SMtx2, mtxTrans;		//�ۊǗp���[���h�}�g���b�N�X
		WKmtx = m_Mtx;

		//���]�v�Z
		D3DXMatrixReflect(&SMtx, &CScene::GetPlane());
		D3DXMatrixMultiply(&SMtx, &SMtx, &WKmtx);
		SMtx2 = SMtx;
		//���f���𐅖ʂƓ���������
		//m_Mtx._44 = OUT_LINE;
		//m_Mtx._41 = m_Mtx._41 * m_Mtx._44;
		//m_Mtx._42 = MAP_CHIP_SIZE * 0.25f + MAP_CHIP_SIZE * 10.0f * m_Mtx._44;
		//m_Mtx._43 = m_Mtx._43 * m_Mtx._44;

		D3DXMatrixTranslation(&mtxTrans, 0.0f, -GetPosY() * MAP_CHIP_SIZE - MAP_CHIP_SIZE * 10.25f, 0.0f);
		D3DXMatrixMultiply(&SMtx2, &SMtx2, &mtxTrans);

		//���]�}�g���b�N�X���f���𐅖ʂ���o�Ă��镪����
		D3DXMatrixTranslation(&mtxTrans, 0.0f, -GetPosY() * MAP_CHIP_SIZE * 2.0f - MAP_CHIP_SIZE * 0.5f, 0.0f);
		D3DXMatrixMultiply(&SMtx, &SMtx, &mtxTrans);

		//���ʂɃu���b�N���f���ŃX�e���V��	Z�e�X�g�L�A�L�^���A�`�斳	Z������+1
		//CManager::GetRenderer()->SetRenderer(true);				//�`�悷��

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);			// ���]�ʕ`��
		CManager::GetRenderer()->SetRenderer(false);			//�`�悵�Ȃ�
		CManager::GetRenderer()->SetStencil(true);				//�X�e���V���̎g�p
		pDevice->SetTransform(D3DTS_WORLD, &SMtx2);
		CSceneModel::DrawModelOne(model, col);

		//�w��l�Ń��f���`��EZ�L�^�L
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		CManager::GetRenderer()->SetRenderer(true);				//�`�悷��

		//1�ɔ��]���f��
		pDevice->SetRenderState(D3DRS_STENCILREF, 1);
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);			// ���]�ʕ`��
		m_Mtx = SMtx;
		ModelDraw();

		//0�ɒʏ탂�f��
		pDevice->SetRenderState(D3DRS_STENCILREF, 0);
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			// �ʏ�ʕ`��
		m_Mtx = WKmtx;
	}

	ModelDraw();

	if (bMirror) { CManager::GetRenderer()->SetStencil(false); }				//�X�e���V���̎g�p
}
//==================================================================================================//
//    *		���f���`�b�v�̃��f���`�� *
//==================================================================================================//
void	CChip_Model::ModelDraw(void)
{
	LPDIRECT3DDEVICE9	pD3DDevice = CManager::GetRenderer()->GetDevice();
	CSceneModel::MODEL	model = GetModel();
	CScene::DRAW_TYPE	DrawType;
	LPDIRECT3DTEXTURE9	Tex;
	D3DXCOLOR			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	GetDraw(Tex, DrawType);
	if (CScene::DrawPrepare(DrawType, pD3DDevice)) { return; }

	//// ���[���h�}�g���b�N�X�̐ݒ�
	pD3DDevice->SetTransform(D3DTS_WORLD, &GetMtx());

	//�e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, Tex);

	if (GetbSelect() && CManager::GetpMapChip()->GetbEdit()) { col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f); }
	CSceneModel::DrawModel(model, col);
	pD3DDevice->SetTexture(0, NULL);
}
//==================================================================================================//
//    *		���f���`�b�v�̕`��p�ݒ�擾 *
//==================================================================================================//
void	CChip_Model::GetDraw(LPDIRECT3DTEXTURE9 &pTex, CScene::DRAW_TYPE &DrawType)
{
	DrawType = CScene::DRAW_TYPE_NORMAL;
	pTex = NULL;
	switch (m_type)
	{
	case TYPE_BLOCK10:
	case TYPE_BLOCK00:	
	case TYPE_BRIDGE00:	
	case TYPE_STAIRS00:		pTex = CScene::Load(CScene::TEX_BLOCK00);		break;

	case TYPE_BLOCK11:
	case TYPE_BLOCK01:	
	case TYPE_BRIDGE01:	
	case TYPE_STAIRS01:		pTex = CScene::Load(CScene::TEX_BLOCK01);		break;

	case TYPE_GAJIGAJI:	
	case TYPE_WOOD:			pTex = CScene::Load(CScene::TEX_GAJIGAJI);		break;

	case TYPE_GOAL:
	case TYPE_GOAL1:
	case TYPE_GOAL2:		pTex = CScene::Load(CScene::TEX_BLOCK01);		break;

	case TYPE_MEAT_S:		pTex = CScene::Load(CScene::TEX_Meat);			break;
	case TYPE_MEAT_M:		pTex = CScene::Load(CScene::TEX_Meat);			break;
	case TYPE_STRAWBERRY:	pTex = CScene::Load(CScene::TEX_STRAWBERRY);	break;
	case TYPE_WATERMELON:	pTex = CScene::Load(CScene::TEX_WATERMELON);	break;
	case TYPE_GRAPE:		pTex = CScene::Load(CScene::TEX_GRAPE);			break;
	case TYPE_BANANA:		pTex = CScene::Load(CScene::TEX_BANANA);		break;

	case TYPE_SPECIES:		pTex = CScene::Load(CScene::TEX_Species);		break;
	}
}
//==================================================================================================//
//    *		���f���`�b�v�̃��f���擾 *
//==================================================================================================//
CSceneModel::MODEL	CChip_Model::GetModel(void)
{
	switch (m_type)
	{
	case TYPE_BLOCK00:	
	case TYPE_BLOCK01:	return CSceneModel::MODEL_BLOC00;

	case TYPE_BRIDGE00:
	case TYPE_BRIDGE01:	return CSceneModel::MODEL_BRIDGE00;

	case TYPE_STAIRS00:
	case TYPE_STAIRS01:	return CSceneModel::MODEL_STAIRS00;
	
	case TYPE_WOOD:
	case TYPE_GAJIGAJI:	return CSceneModel::MODEL_GAJIGAJI;

	case TYPE_GOAL:		return CSceneModel::MODEL_BOX;
	case TYPE_GOAL1:	return CSceneModel::MODEL_COLUMN;
	case TYPE_GOAL2:	return CSceneModel::MODEL_COLUMN;

	case TYPE_BLOCK10:
	case TYPE_BLOCK11:	return CSceneModel::MODEL_BLOC10;

	case TYPE_MEAT_S:		return CSceneModel::MODEL_Meat_S;
	case TYPE_MEAT_M:		return CSceneModel::MODEL_Meat_M;
	case TYPE_STRAWBERRY:	return CSceneModel::MODEL_STRAWBERRY;
	case TYPE_WATERMELON:	return CSceneModel::MODEL_WATERMELON;
	case TYPE_GRAPE:		return CSceneModel::MODEL_GRAPE;
	case TYPE_BANANA:		return CSceneModel::MODEL_BANANA;

	case TYPE_SPECIES:		return CSceneModel::MODEL_SPECIES;

	}
	return CSceneModel::MODEL_MAX;
}
//==================================================================================================//
//    *		���f���`�b�v��Y�����蔻�� *
//==================================================================================================//
bool	CChip_Model::CollisionY(CCharacter *&pChar)
{
	if (GetCollision() == COLLISION_NO || GetCollision() == COLLISION_WALL) { return false; }

	D3DXVECTOR3	length;									//���f���̒���
	CSceneModel::GetLength(GetModel(), length);			//���f���̒����擾
	bool		bHit = CollisionY_Base(pChar, length);	//�����蔻��

	if (bHit)
	{
		switch (m_type)
		{
		case TYPE_GOAL:
			//if (CManager::GetpMapChip()->GetnClear() < 1)
			//{ 
			//	CManager::GetpMapChip()->GetnClear() = 1; 
			//	CCharacter::GetbWait() = true;
			//}
			break;
		}
	}

	return bHit;
}
//==================================================================================================//
//    *		���f���`�b�v��XZ�����蔻�� *
//==================================================================================================//
bool	CChip_Model::CollisionXZ(CCharacter *&pChar, int &nHit)
{
	if (GetCollision() == COLLISION_NO) { return false; }

	D3DXVECTOR3 &pos = pChar->Getpos();
	D3DXVECTOR3	length;				//���f���̒���
	D3DXMATRIX	&m_mtx		= GetMtx();
	bool		bHit		= false;				//�q�b�g�̗L��
	bool		bYModel		= false;				//Y�������f���̗L��

	CSceneModel::GetLength(GetModel(), length);	//���f���̒����擾
	if (GetModel() == CSceneModel::MODEL_BLOC00 || 
		GetModel() == CSceneModel::MODEL_STAIRS00 || 
		GetModel() == CSceneModel::MODEL_GAJIGAJI) { bYModel = true; }

	bHit = CollisionXZ_Base(pChar, length, bYModel, nHit);

	if (pChar->GetObjType() == CScene::OBJTYPE_PLAYER && bHit)
	{
		switch (m_type)
		{
		case TYPE_GAJIGAJI:
			if (GetCollision() == COLLISION_WALL) { break; }
			((CPlayer*)pChar)->SetState(CPlayer::STATE_CLIFF, D3DXVECTOR3(m_mtx._41, m_mtx._42, m_mtx._43));
			break;
		}
		if (GetCollision() != COLLISION_WALL)
		{//�ʏ�ǂȂ�
			((CPlayer*)pChar)->TriJump(atan2f(m_mtx._41 - pos.x, m_mtx._43 - pos.z));
		}
	}

	return bHit;
}

//==================================================================================================//
//    *		���f���`�b�v�̃��[���h�}�g���b�N�X�v�Z *
//==================================================================================================//
void	CChip_Model::SetMtx(D3DXVECTOR3 &pos)
{
	D3DXMATRIX			mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DXMATRIX &m_mtx = GetMtx();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtx);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtx, &m_mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x + m_addpos.x * MAP_CHIP_SIZE, pos.y + m_addpos.y * MAP_CHIP_SIZE, pos.z + m_addpos.z * MAP_CHIP_SIZE);
	D3DXMatrixMultiply(&m_mtx, &m_mtx, &mtxTrans);
}
//==================================================================================================//
//    *		���f���`�b�v�̐ݒ� *
//==================================================================================================//
void	CChip_Model::Set(TYPE type)
{
	LPDIRECT3DTEXTURE9 WKtex;	//�֐��Ăяo���p�ϐ�

	Init();
	m_type = type;

	switch (type)
	{
	case TYPE_WOOD: m_state = STATE_BREAK; break;
	}
	CSceneModel::LoadModel(GetModel(), WKtex);
}
//==================================================================================================//
//    *		���f���`�b�v�̕ۑ� *
//==================================================================================================//
void	CChip_Model::Save(FILE *&pFile)
{
	CChip::Save(pFile);

	fprintf(pFile, "%f %f %f \n", m_rot.x, m_rot.y, m_rot.z);
	fprintf(pFile, "%f %f %f %d %d \n", m_addpos.x, m_addpos.y, m_addpos.z, m_type, m_state);
}
//==================================================================================================//
//    *		���f���`�b�v�̓ǂݍ��� *
//==================================================================================================//
void	CChip_Model::Load(FILE *&pFile)
{
	LPDIRECT3DTEXTURE9 WKtex;	//�֐��Ăяo���p�ϐ�

	Init();

	CChip::Load(pFile);
	fscanf(pFile, "%f %f %f \n", &m_rot.x, &m_rot.y, &m_rot.z);
	fscanf(pFile, "%f %f %f %d %d \n", &m_addpos.x, &m_addpos.y, &m_addpos.z, &m_type, &m_state);

	CSceneModel::LoadModel(GetModel(), WKtex);
}

//==================================================================================================//
//    *		�|���S���`�b�v�̏����� *
//==================================================================================================//
HRESULT CChip_Polygon::Init(void)
{
	CChip::Init();
	CChip::GetType() = CChip::TYPE_POLYGON;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_PFIELD;
	m_p3D = NULL;
	return S_OK;
}
//==================================================================================================//
//    *		�|���S���`�b�v�̏I�� *
//==================================================================================================//
void	CChip_Polygon::Uninit(void)
{
	if (m_p3D != NULL) { m_p3D->Uninit(); }
	CChip::Uninit();
}
//==================================================================================================//
//    *		�|���S���`�b�v�̏I�� *
//==================================================================================================//
bool	CChip_Polygon::Update(void)
{
	switch (m_type)
	{
	case TYPE_WATERFALL:
	case TYPE_HALFWATER:
	case TYPE_WATER:
		m_p3D->PlusUV(D3DXVECTOR2(0.0f, -0.01f));
		break;
	case TYPE_Stone:
	case TYPE_StoneRand:
		UpdateSetStone();
		break;
	}

	if (m_type == TYPE_GOAL && !CManager::GetpMapChip()->GetbEdit())
	{
		D3DXMATRIX &m_Mtx = GetMtx();
		CPlayer::GoalCheck(D3DXVECTOR3(m_Mtx._41, m_Mtx._42, m_Mtx._43));
	}
	return false;
}
//==================================================================================================//
//    *		�|���S���`�b�v�̕`�� *
//==================================================================================================//
void	CChip_Polygon::Draw(void)
{
	if (m_p3D != NULL) { m_p3D->Draw(); }
}
//==================================================================================================//
//    *		�|���S���`�b�v��Y�������蔻�� *
//==================================================================================================//
bool	CChip_Polygon::CollisionY(CCharacter *&pChar)
{
	return CollisionY_Base(pChar, D3DXVECTOR3(MAP_CHIP_SIZE * 0.75f, 0.1f, MAP_CHIP_SIZE * 0.75f));
}
//==================================================================================================//
//    *		�|���S���`�b�v��XZ�������蔻�� *
//==================================================================================================//
bool	CChip_Polygon::CollisionXZ(CCharacter *&pChar, int &nHit)
{
	D3DXVECTOR3 &pos = pChar->Getpos();
	D3DXMATRIX	&m_mtx = GetMtx();
	D3DXVECTOR3 *WKpos[4];
	bool bHit = false;

	bHit = CollisionXZ_Base(pChar, D3DXVECTOR3(MAP_CHIP_SIZE * 0.75f, 0.0f, MAP_CHIP_SIZE * 0.75f), true, nHit);

	if (pChar->GetObjType() == CScene::OBJTYPE_PLAYER && bHit && nHit >= 0)
	{
		switch (m_type)
		{
		case TYPE_WATERFALL:
			m_p3D->GetVtxPos(WKpos[0], WKpos[1], WKpos[2], WKpos[3]);
			if (pos.x > m_mtx._41 + WKpos[0]->x && pos.x < m_mtx._41 + WKpos[1]->x)
			{//X�͈͓��Ȃ�
				((CPlayer*)pChar)->SetState(CPlayer::STATE_WATERFALL, D3DXVECTOR3(m_mtx._41, WKpos[0][0].z, m_mtx._43));
			}
			break;
		}
	}
	return bHit;
}
//==================================================================================================//
//    *		�|���S���`�b�v��Y���v�Z *
//==================================================================================================//
float	CChip_Polygon::GetHeight(D3DXVECTOR3 &Target)
{
	return 0.0f;
}
//==================================================================================================//
//    *		�|���S���`�b�v�̊␶������ *
//==================================================================================================//
void	CChip_Polygon::UpdateSetStone(void)
{
	float fValue = 1.0f;

	switch (CManager::GetpMapChip()->GetMap())
	{
	case CMapChip::MAP_3:	fValue = 0.5f; break;
	case CMapChip::MAP_4:	fValue = 0.6f; break;
	}
	m_rot.x += fValue;	//�|���S���͑��݂��Ȃ����ߏ�ԊǗ��Ƃ��Ĉ���

	if ((int)m_rot.x % 180 == 0)
	{//���킟
		CFallingStone *pStone;
		D3DXMATRIX &m_Mtx = GetMtx();
		D3DXVECTOR3 pos = D3DXVECTOR3(m_Mtx._41, m_rot.z, m_Mtx._43);
		pos.x += (MAP_CHIP_SIZE * -0.5f);
		if (m_type == TYPE_StoneRand)
		{//���낲��
			if ((int)m_rot.x % 360 == 0) { pos.x += MAP_CHIP_SIZE; }
		}
		//����
		if (SceneCreate(pStone, MODEL_PRIORITY))
		{
			pStone->Set(pos, m_rot.y);
		}
	}
}
//==================================================================================================//
//    *		�|���S���`�b�v�̃|���S���X�L�b�v���� *
//==================================================================================================//
bool	CChip_Polygon::PolySkip(void)
{
	switch (m_type)
	{
	case TYPE_NO:
	case TYPE_GOAL:
	case TYPE_StoneRand:
	case TYPE_Stone:
		return true;
	}
	return false;
}
//==================================================================================================//
//    *		�|���S���`�b�v�̐ݒ� *
//==================================================================================================//
void	CChip_Polygon::Set(TYPE type, float fHeight)
{
	CScene::TEXTURE tex = CScene::TEX_MAX;
	bool bWall = false;

	Init();
	m_type = type;

	switch (type)
	{
	case TYPE_WATERFALL:
	case TYPE_WATER:
	case TYPE_HALFWATER:tex = CScene::TEX_Sea;	break;
	case TYPE_HOLE:
	case TYPE_M_HOLE:
	case TYPE_BIG_HOLE:	tex = CScene::TEX_HOLE; break;
	case TYPE_Stone:
	case TYPE_StoneRand:m_rot.z = fHeight * MAP_CHIP_SIZE;	break;
	case TYPE_Mural01:
	case TYPE_Mural02:
	case TYPE_Mural03:
	case TYPE_Mural04:
	case TYPE_Mural05:
	case TYPE_Mural06:	tex = CScene::TEX_MURAL; break;
	}

	if (PolySkip()) { return; }

	if (Create(m_p3D))
	{//3D�̍쐬
		m_p3D->Set(INIT_VECTOR, INIT_VECTOR, INIT_COLLAR, D3DXVECTOR3(MAP_CHIP_SIZE * 0.5f, 0.0f, MAP_CHIP_SIZE * 0.5f), 
			0, 1, 1, CScene::DRAW_TYPE_NORMAL, tex, false);
	}

	switch (type)
	{
	case TYPE_PFIELD:
		m_p3D->BindDrawType(CScene::DRAW_TYPE_NO);
		break;
	case TYPE_WATERFALL:
		GetDType() = DTYPE_EFFECT;
		bWall = true;
		m_rot.x = D3DX_PI * -0.5f;
		m_p3D->SetWall(D3DXVECTOR3(MAP_CHIP_SIZE * 0.5f, 0.0f, MAP_CHIP_SIZE * 8.0f));
		m_p3D->BindDrawType(CScene::DRAW_TYPE_ADD);
		break;
	case TYPE_WATER:
		GetDType() = DTYPE_EFFECT;
		m_p3D->BindDrawType(CScene::DRAW_TYPE_ADD);
		break;
	case TYPE_HALFWATER:
		GetDType() = DTYPE_EFFECT;
		m_p3D->SetHalfSize(D3DXVECTOR3(MAP_CHIP_SIZE * 0.5f, 0.0f, MAP_CHIP_SIZE * 0.5f));
		m_p3D->BindDrawType(CScene::DRAW_TYPE_ADD);
		break;
	case TYPE_HOLE:
		GetDType() = DTYPE_EFFECT;
		m_p3D->SetUV(0, 1, 2);
		m_p3D->SetWall2(D3DXVECTOR3(MAP_CHIP_SIZE * 0.6f, MAP_CHIP_SIZE * 0.6f, 0.0f));
		break;
	case TYPE_M_HOLE:
		GetDType() = DTYPE_EFFECT;
		m_p3D->SetUV(0, 1, 2);
		m_p3D->GetPosition().x += -MAP_CHIP_SIZE * 0.5f;
		m_p3D->SetWall2(D3DXVECTOR3(MAP_CHIP_SIZE * 1.2f, MAP_CHIP_SIZE * 1.2f, 0.0f));
		break;
	case TYPE_BIG_HOLE:
		GetDType() = DTYPE_EFFECT;
		m_p3D->SetUV(0, 1, 2);
		m_p3D->SetWall2(D3DXVECTOR3(MAP_CHIP_SIZE * 2.0f, MAP_CHIP_SIZE * 1.5f, 0.0f));
		break;
	case TYPE_Mural01:
	case TYPE_Mural02:	
	case TYPE_Mural03:	
	case TYPE_Mural04:	
	case TYPE_Mural05:	
	case TYPE_Mural06:
		GetDType() = DTYPE_EFFECT;
		m_p3D->SetUV(type - TYPE_Mural01, 6, 1);
		m_p3D->SetWall2(D3DXVECTOR3(MAP_CHIP_SIZE * 1.5f, MAP_CHIP_SIZE * 1.5f, 0.0f));
		break;
	}
	PlusHeight(fHeight, bWall);
}
//==================================================================================================//
//    *		�|���S���`�b�v�̃}�g���b�N�X�v�Z *
//==================================================================================================//
void	CChip_Polygon::SetMtx(D3DXVECTOR3 &pos)
{
	GetMtx()._41 = pos.x;
	GetMtx()._43 = pos.z;

	if (m_p3D != NULL)
	{
		m_p3D->GetPosition() = pos;
		m_p3D->GetRotation() = m_rot;
		m_p3D->SetMtx();

		D3DXVECTOR3 *pPos[4];
		m_p3D->GetVtxPos(pPos[0], pPos[1], pPos[2], pPos[3]);
		GetMtx()._42 = pPos[0]->y;
	}
}
//==================================================================================================//
//    *		�|���S���`�b�v�̃}�g���b�N�X�v�Z *
//==================================================================================================//
void	CChip_Polygon::PlusHeight(float fHeight, bool bWall)
{
	if (m_p3D != NULL)
	{
		D3DXVECTOR3 *pPos[4];
		D3DXVECTOR3 pos[4];
		m_p3D->GetVtxPos(pPos[0], pPos[1], pPos[2], pPos[3]);
		for (int nCount = 0; nCount < 4; nCount++)
		{
			pos[nCount] = pPos[nCount][0];
			(bWall ? pos[nCount].z : pos[nCount].y) += fHeight * MAP_CHIP_SIZE;
		}
		m_p3D->SetVtxPos(pos[0], pos[1], pos[2], pos[3]);
	}
	GetMtx()._42 = fHeight * MAP_CHIP_SIZE;
}
//==================================================================================================//
//    *		�|���S���`�b�v�̕ۑ� *
//==================================================================================================//
void	CChip_Polygon::Save(FILE *&pFile)
{
	D3DXVECTOR3 *pos[4];

	CChip::Save(pFile);
	fprintf(pFile, "%f %f %f \n", m_rot.x, m_rot.y, m_rot.z);
	fprintf(pFile, "%d \n", m_type);

	if (PolySkip()) { return; }

	m_p3D->GetVtxPos(pos[0], pos[1], pos[2], pos[3]);
	for (int nCount = 0; nCount < 4; nCount++)
	{
		fprintf(pFile, "%f %f %f\n", pos[nCount][0].x, pos[nCount][0].y, pos[nCount][0].z);
	}
}
//==================================================================================================//
//    *		�|���S���`�b�v�̓ǂݍ��� *
//==================================================================================================//
void	CChip_Polygon::Load(FILE *&pFile)
{
	D3DXVECTOR3 pos[4];
	COLLISION &m_collision = GetCollision();
	COLLISION collision;
	D3DXVECTOR3 WKrot;
	Init();

	CChip::Load(pFile);
	collision = m_collision;

	fscanf(pFile, "%f %f %f \n", &WKrot.x, &WKrot.y, &WKrot.z);
	fscanf(pFile, "%d \n", &m_type);

	Set(m_type, 0.0f);
	m_collision = collision;
	m_rot = WKrot;

	if (PolySkip()) { return; }

	for (int nCount = 0; nCount < 4; nCount++)
	{
		fscanf(pFile, "%f %f %f\n", &pos[nCount].x, &pos[nCount].y, &pos[nCount].z);
	}
	m_p3D->SetVtxPos(pos[0], pos[1], pos[2], pos[3]);
}