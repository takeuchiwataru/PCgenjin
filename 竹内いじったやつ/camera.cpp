//=============================================================================
//
// �J�������� [camera.cpp]
// Author : ���{��
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS	//Fire Wall�˔j
#include <stdio.h>				//�Z�[�u���[�h�̈�
#include "camera.h"
#include "mesh.h"
#include "SceneModel.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "light.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define		DISTANCE		(500.0f)			//�����_�Ǝ��_�̋���
#define		CAMERA_MOVE		(0.8f)			//�J�����̈ړ����x
#define		ROTPOOR_RY		(0)			//�����_�㉺ +��, -��
#define		ROTPOOR_VY		(80)				//�J�����{�� +��, -��

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CCamera_Manager::Info CCamera_Manager::m_info;			//�J�������

//=============================================================================
// �J�����̏���������
//=============================================================================
void CCamera::Init(void)
{
	m_Type = CCamera::CAMERA_TYPE_OBJ;

	m_posV = D3DXVECTOR3(0.0f, 200.0f, 200.0f);				//���_
	m_posR = D3DXVECTOR3(0.0f, 100.0f, 0.1f);				//�����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					//�i�j�R��(��)
	m_rot = D3DXVECTOR3(D3DX_PI * 0.065f, D3DX_PI, 0.0f);	//�p�x
	m_targetpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�Ǐ]����J�����̏ꏊ
	m_fDistance = DISTANCE;									//���_�ƒ����_�̋���
	m_nNumCamera = 0;

	m_viewport.MinZ = 0.0f;
	m_viewport.MaxZ = 1.0f;
	SetViewport(0, 0, 0, 0);
}
//=============================================================================
// �J�����̕`�揈��
//=============================================================================
void CCamera::Draw(void)
{
	SetCamera(m_posV);
	//CManager::GetRenderer()->GetDevice()->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(100, 0, 0, 0), 1.0f, 0);
	CManager::GetRenderer()->GetDevice()->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 150, 250, 0), 1.0f, 0);
	CScene::Draw3D(CManager::GetRenderer()->GetDevice());
}
//=============================================================================
// �J�����̃Z�b�g����
//=============================================================================
void CCamera::SetCamera(D3DXVECTOR3 WKposV)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	// �r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&m_viewport);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),	//��p
		(float)m_viewport.Width /
		(float)m_viewport.Height,
		10.0f,
		24800.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_mtxView, &WKposV, &m_posR, &m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(100, 0, 0, 0), 1.0f, 0);

	CCamera_Manager::GetInfo().pCamera = this;
}
//=============================================================================
// 3D�̕`�揈�������΍􏈗�
//=============================================================================
bool CCamera::DrawCheck(D3DXVECTOR3 &pos, float fLength)
{//�����_���猩�Ĉ��͈͓��Ȃ�`��
	D3DXVECTOR3 WKpos = m_posV + D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * fLength;
	float fAngle = atan2f(WKpos.x - pos.x, WKpos.z - pos.z) - m_rot.y;

	if (fAngle > D3DX_PI) { fAngle -= D3DX_PI * 2.0f; }
	if (fAngle < -D3DX_PI) { fAngle += D3DX_PI * 2.0f; }

	if (fAngle >= -D3DX_PI * (DRAW_ANGLEP / 180) && fAngle <= +D3DX_PI * (DRAW_ANGLEP / 180))
	{//�J�����̌����ʂ�Ȃ�
		float fDistance = powf(m_posR.x - pos.x, 2) + powf(m_posR.z - pos.z, 2);
		if (fDistance < fLength + DRAW_DISTANCE) { return true; }
	}

	return false;
}
//=============================================================================
// 3D�̕`�揈�������΍􏈗�
//=============================================================================
void CCamera::SetViewport(int left, int up, int right, int bottom)
{
	m_viewport.X = (DWORD)left;
	m_viewport.Y = (DWORD)up;
	m_viewport.Width = (DWORD)right;
	m_viewport.Height = (DWORD)bottom;
}

//=============================================================================
// �J�����̏���������
//=============================================================================
void CCamera_Char::Init(void)
{
	CCamera::Init();
	m_bOperation		= true;
	m_pChar				= NULL;
	m_nQuake			= 0;
	m_nMaxQuake			= 0;
	m_nQuakeAngle		= 0;
	m_fQuake			= 0.0f;
	m_fGMagnification	= 0.5f;
	m_addpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	GetType()			= CCamera::CAMERA_TYPE_CHAR;
}
//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera_Char::Update(void)
{
	if (m_pChar != NULL && m_bOperation)
	{//�Ǐ]�̏ꏊ�̍X�V
		D3DXVECTOR3		&m_posV = GetposV();
		D3DXVECTOR3		&m_posR = GetposR();
		D3DXVECTOR3		&m_rot = GetRot();
		D3DXVECTOR3		&m_targetpos = Gettargetpos();
		D3DXVECTOR3		targetpos;
		float			&m_fDistance = GetfDistance();
		bool			bEnd = false;

		if (GetnNumCamera() >= 1)
		{//�J����ID��0�ȏ�Ȃ�
			int nNumCamera = GetnNumCamera() - 1;
			CInputKeyboard	*pInputKey = CManager::GetInputKey();
			CInputJoyPad	*pInputPad = CManager::GetInputJoyPad(nNumCamera);	//�W���C�p�b�h���l��
			CCamera_Manager::Info &info = CCamera_Manager::GetInfo();
			if (pInputPad->GetStickDefeat(1))
			{//�W���C�p�b�h��R�X�e�B�b�N���|��Ă���Ȃ����
				m_rot.y += D3DX_PI * 0.01f * (pInputPad->GetnStickX(1) *  0.000015f) * info.nSpeedY[nNumCamera] * (info.bReturnY[nNumCamera] ? -1.0f : 1.0f);
				m_rot.x += D3DX_PI * 0.01f * (pInputPad->GetnStickY(1) * -0.0000075f) * info.nSpeedX[nNumCamera] * (info.bReturnX[nNumCamera] ? -1.0f : 1.0f);
			}
			else
			{//�R���g���[���[��R�X�e�B�b�N���|����Ă��Ȃ��Ȃ�
				if (pInputKey->GetPress(DIK_R)) { m_rot.y = D3DX_PI; }
				if (pInputKey->GetPress(DIK_Q)) { m_rot.y += D3DX_PI * 0.004f * info.nSpeedY[nNumCamera] * (info.bReturnY[nNumCamera] ? 1.0f : -1.0f); }
				if (pInputKey->GetPress(DIK_E)) { m_rot.y -= D3DX_PI * 0.004f * info.nSpeedY[nNumCamera] * (info.bReturnY[nNumCamera] ? 1.0f : -1.0f); }
				if (pInputKey->GetPress(DIK_1)) { m_rot.x += D3DX_PI * 0.002f * info.nSpeedX[nNumCamera] * (info.bReturnX[nNumCamera] ? 1.0f : -1.0f); }
				if (pInputKey->GetPress(DIK_2)) { m_rot.x -= D3DX_PI * 0.002f * info.nSpeedX[nNumCamera] * (info.bReturnX[nNumCamera] ? 1.0f : -1.0f); }
			}

			if (m_rot.x > D3DX_PI * 0.3f) { m_rot.x = D3DX_PI * 0.3f; bEnd = true; }
			if (m_rot.x < -D3DX_PI * 0.3f) { m_rot.x = -D3DX_PI * 0.3f; bEnd = true; }
			do
			{//Y��1�T�΍􏈗�
				bEnd = false;
				if (m_rot.y > D3DX_PI)			{ m_rot.y -= D3DX_PI * 2; bEnd = true; }
				if (m_rot.y < -D3DX_PI)			{ m_rot.y += D3DX_PI * 2; bEnd = true; }
			} while (bEnd);

			if (CManager::GetPlayer(nNumCamera) == NULL)
			{//�J�����ԍ��Ƀv���C���[�����Ȃ� = �ϐ풆
				if (pInputKey->GetPress(DIK_UP)) { m_fDistance -= 2.0f; }
				if (pInputKey->GetPress(DIK_DOWN)) { m_fDistance += 2.0f; }
				if (m_fDistance < MIN_DISTANCE) { m_fDistance = MIN_DISTANCE; }
				if (m_fDistance > MAX_DISTANCE) { m_fDistance = MAX_DISTANCE; }
			}
		}
		if (m_pDistance != NULL) { m_fDistance += (m_pDistance[0] - m_fDistance) * 0.3f; }
		m_targetpos += (m_pChar[0] - m_targetpos) * 0.08f;
		targetpos = m_targetpos + m_addpos;

		m_posR = D3DXVECTOR3(0.0f, 0.0f + ROTPOOR_RY, 0.0f) + targetpos;	//����ꏊ + �����ړ���
		//m_posR +=D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * -50.0f;

		//m_rot.x = 1.0f;
		//���_�@���� + (�p�x * ����) + �����ړ���
		m_goal = D3DXVECTOR3(
			targetpos.x + (sinf(m_rot.y) * m_fDistance) * cosf(m_rot.x),	//X��
			targetpos.y + sinf(m_rot.x) * m_fDistance + ROTPOOR_VY,			//Y��
			targetpos.z + (cosf(m_rot.y) * m_fDistance) * cosf(m_rot.x));	//Z��
		m_posV += (m_goal - m_posV) * m_fGMagnification;
		//m_posV.y = fY;
	}
}
//=============================================================================
// �J�����̕`�揈��
//=============================================================================
void CCamera_Char::Draw(void)
{
	SetCamera();
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	CManager::GetRenderer()->GetDevice()->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 150, 250, 0), 1.0f, 0);
	CScene::Draw3D(CManager::GetRenderer()->GetDevice());
}
//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera_Char::Reset(void)
{
	if (m_pChar != NULL)
	{//�Ǐ]�̏ꏊ�̍X�V
		D3DXVECTOR3		&m_posV = GetposV();
		D3DXVECTOR3		&m_posR = GetposR();
		D3DXVECTOR3		&m_rot = GetRot();
		D3DXVECTOR3		&m_targetpos = Gettargetpos();
		D3DXVECTOR3		targetpos;
		float			&m_fDistance = GetfDistance();

		if (m_pDistance != NULL) { m_fDistance += (m_pDistance[0] - m_fDistance) * 0.3f; }
		m_targetpos = m_pChar[0];
		targetpos = m_targetpos + m_addpos;

		m_posR = D3DXVECTOR3(0.0f, 0.0f + ROTPOOR_RY, 0.0f) + targetpos;	//����ꏊ + �����ړ���
		//m_posR +=D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * -50.0f;

		//���_�@���� + (�p�x * ����) + �����ړ���
		m_goal = D3DXVECTOR3(
			targetpos.x + (sinf(m_rot.y) * m_fDistance) * cosf(m_rot.x),	//X��
			targetpos.y + sinf(m_rot.x) * m_fDistance + ROTPOOR_VY,		//Y��
			targetpos.z + (cosf(m_rot.y) * m_fDistance) * cosf(m_rot.x));	//Z��
		m_posV += (m_goal - m_posV) * 1.0f;
	}

}
//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void CCamera_Char::SetCamera(void)
{
	D3DXVECTOR3		&m_posV = GetposV();
	D3DXVECTOR3		&m_posR = GetposR();
	D3DXVECTOR3		&m_vecU = GetvecU();
	D3DXVECTOR3		&m_rot = GetRot();
	D3DXVECTOR3		&m_targetpos = Gettargetpos();
	D3DXVECTOR3		targetpos;
	float			&m_fDistance = GetfDistance();

	D3DXVECTOR3 WKValue, WKmove;
	D3DXVECTOR3	WKlength = D3DXVECTOR3(1.0f, 10.0f, 1.0f);
	D3DXVECTOR3	WKnor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	WKposV;
	float		fDistance0, fDistance1;
	bool bWKJump = false;

	WKposV = m_posV;
	if (m_nQuake > 0)
	{//�h�ꂪ����Ȃ�
		targetpos = m_targetpos + m_addpos;
		m_nQuakeAngle = (m_nQuakeAngle + 1) % 3;
		WKValue = m_rot;
		switch (m_nQuakeAngle)
		{
		case 1: WKValue.x += m_fQuake * ((float)m_nQuake / (float)m_nMaxQuake); break;
		case 3: WKValue.x += cosf(D3DX_PI / 1.5f) * m_fQuake * ((float)m_nQuake / (float)m_nMaxQuake);
				WKValue.y += sinf(D3DX_PI / 1.5f) * m_fQuake * ((float)m_nQuake / (float)m_nMaxQuake); break;
		case 2: WKValue.x += cosf(D3DX_PI / 1.5f) * m_fQuake * ((float)m_nQuake / (float)m_nMaxQuake);
				WKValue.y -= sinf(D3DX_PI / 1.5f) * m_fQuake * ((float)m_nQuake / (float)m_nMaxQuake); break;
		}
		WKposV = D3DXVECTOR3(
			targetpos.x + (sinf(WKValue.y) * m_fDistance) * cosf(WKValue.x),	//X��
			targetpos.y + sinf(WKValue.x) * m_fDistance + ROTPOOR_VY,		//Y��
			targetpos.z + (cosf(WKValue.y) * m_fDistance) * cosf(WKValue.x));	//Z��
		//WKposV = m_posV + (WKposV - m_posV) * 0.1f;
		m_nQuake--;
	}

	fDistance0 = powf(m_posV.x - m_posR.x, 2) + powf(m_posV.z - m_posR.z, 2);
	WKValue = m_posR + D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * -30.0f;
	WKmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int		nCount = 0;
	//CMesh::MeshCollisionCeiling(WKposV, WKValue, WKlength);
	CMesh::MeshCollisionWall(WKposV, WKValue, WKmove, WKlength, WKnor, nCount, bWKJump, false);
	CMesh::MeshCollisionField(WKposV, WKValue, WKmove, WKlength, WKnor, bWKJump);
	WKValue = m_posR + D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * 1.0f;
	CSceneObjct::CollisionAll(WKposV, WKValue, WKmove, WKlength, WKnor, nCount, bWKJump, false);
	fDistance1 = powf(WKposV.x - m_posR.x, 2) + powf(WKposV.z - m_posR.z, 2);
	WKposV.y = m_posR.y + (WKposV.y - m_posR.y) * ((fDistance1) / fDistance0);
	CCamera::SetCamera(WKposV);
}
//=============================================================================
// �h��̐ݒ菈��
//=============================================================================
void CCamera_Char::SetQuake(float fQuake, int nQuake)
{
	m_fQuake = fQuake;
	m_nQuake = nQuake;
	m_nMaxQuake = nQuake;
}
//=============================================================================
// �X�}�b�V���V�[������
//=============================================================================
void CCamera_Char::SceneSmash(void)
{
	CCamera_Manager::Info &info = CCamera_Manager::GetInfo();

	switch (info.nCntState)
	{
	case 0:
		CScene::GetnCntStart() = PAUSE_PRIORITY;
		if (info.p2DAnim == NULL)
		{
			if (SceneCreate(info.p2DAnim, S2D_PRIORITY))
			{//�W��������
				info.p2DAnim->Set(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.75f
					, D3DX_PI, 0, 2, 2, 3, 0.0f, CScene2D::STATE_NORMAL, CSceneAnim3D::ANIMATION_LOOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), CScene::TEX_BG_EVENT);
				info.p2DAnim->BindDrawType(CScene::DRAW_TYPE_SUBTRACT);
			}
		}
		info.nCntState = 1;
	case 1:
		GetRot().y += D3DX_PI * 0.005f;
		if (info.nCntTime > 90) 
		{//�C�x���g�̏I��
			SceneEnd();
		}
		break;
	}
	info.nCntTime++;
}
//=============================================================================
// ���r�����X�J�n�V�[������
//=============================================================================
void CCamera_Char::SceneLabyrinth(void)
{
	CCamera_Manager::Info &info = CCamera_Manager::GetInfo();
	CScene2D *p2D;

	switch (info.nCntState)
	{
	case 0:
		if (SceneCreate(p2D, S2D_PRIORITY))
		{
			p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.15f, D3DX_PI,
				0, 1, 1, 0.005f, CScene2D::STATE_FADE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CScene::TEX_TitleLogo);
		}
		CCharacter::GetbWait() = true;
		m_pChar = CManager::GetCamera()->Create_Play(0)->GetChar()->GetpChare();
		info.m_fDistance = DISTANCE * 0.2f;
		m_addpos.y = -50.0f;
		m_pDistance = &info.m_fDistance;
		m_fGMagnification = 1.0f;
		GetRot().y = 0.0f;
		Reset();
		info.nCntState = 1;
	case 1:
		info.move.y -= 0.1f;
		if (info.nCntTime > 15) { info.nCntTime = 0; info.nCntState++; }
		break;
	case 2:
		info.move.y += 0.2f;
		info.m_fDistance += (DISTANCE * 0.5f -info.m_fDistance) * 0.01f;
		GetRot().x -= D3DX_PI * 0.001f;
		if (info.nCntTime > 30) { info.nCntTime = 0; info.nCntState++; }
		break;
	case 3:
		info.m_fDistance += (DISTANCE * 0.5f - info.m_fDistance) * 0.01f;
		if (info.nCntTime > 240)
		{//�C�x���g�̏I��
			CCharacter::GetbWait() = false;
			SceneEnd();
			if (SceneCreate(p2D, S2D_PRIORITY))
			{
				p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI,
					0, 1, 1, 0.02f, CScene2D::STATE_FADEOUT, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), CScene::TEX_MAX);
			}
		}
		break;
	}
	info.nCntTime++;
	m_addpos += info.move;
	info.move *= 0.95f;
}
//=============================================================================
// ���r�����X�J�n�V�[������
//=============================================================================
void CCamera_Char::SceneBoss(void)
{
	CCamera_Manager::Info &info = CCamera_Manager::GetInfo();

	switch (info.nCntState)
	{
	case 0:
		CCharacter::GetbWait() = true;
		m_pChar = CManager::GetCamera()->Create_Play(0)->GetChar()->GetpChare();
		info.m_fDistance = DISTANCE * 0.065f;
		m_addpos = D3DXVECTOR3(0.0f, -50.0f, 0.0f);
		m_pDistance = &info.m_fDistance;
		m_fGMagnification = 1.0f;
		GetRot() = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		Reset();
		info.nCntState++;
	case 1:
		info.move.y -= 0.1f;
		if (info.nCntTime > 15) { info.nCntTime = 0; info.nCntState++; }
		break;
	case 2:
		info.move.y += 0.1f;
		if (info.nCntTime > 30) { info.nCntTime = 0; info.nCntState++; }
		break;
	case 3:
		if (info.nCntTime > 60) { info.nCntTime = 0; info.nCntState++; }
		break;
	case 4://���肮�邮��
		info.m_fDistance = DISTANCE * 1.5f;
		info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_addpos = D3DXVECTOR3(0.0f, 50.0f, -500.0f);
		GetRot() = D3DXVECTOR3(D3DX_PI * 0.1f, D3DX_PI * 0.75f, 0.0f);
		Reset();
		info.nCntState++;
	case 5:
		GetRot().y += D3DX_PI * 0.0025f;

		if (info.nCntTime > 480)
		{//�C�x���g�̏I��
			CCharacter::GetbWait() = false;
			SceneEnd();
		}
		break;
	}
	info.nCntTime++;
	m_addpos += info.move;
	info.move *= 0.95f;
}
//=============================================================================
// �J�����̃C�x���g�I������
//=============================================================================
void CCamera_Char::SceneEnd(void)
{
	CCamera_Manager::Info &info = CCamera_Manager::GetInfo();

	info.nCntTime = 0;
	CManager::GetCamera()->GetEvent() = NULL;
	CScene::GetnCntStart() = 0;
	CPlayer::GetbUIDraw() = true;
	info.state = CCamera_Manager::STATE_NONE;
	info.scene = CCamera_Manager::SCENE_TYPE_NO;
	if (info.p2DAnim != NULL)
	{//���o�p�w�i�̍폜
		info.p2DAnim->Uninit();
		info.p2DAnim = NULL;
	}
	Uninit();
}

//=============================================================================
// �v���C���[�J�����̏���������
//=============================================================================
void CCamera_Play::Init(void)
{
	Create(m_pCamera_Obj);
	Create(m_pCamera_Char);
}
//=============================================================================
// �v���C���[�J�����̏I������
//=============================================================================
void CCamera_Play::Uninit(void)
{
	if (m_pCamera_Char != NULL) { delete m_pCamera_Char; }
	if (m_pCamera_Obj != NULL) { delete m_pCamera_Obj; }
}
//=============================================================================
// �v���C���[�J�����̍X�V����
//=============================================================================
void CCamera_Play::Update(void)
{
	if (m_pCamera_Char != NULL) { m_pCamera_Char->Update(); }
}
//=============================================================================
// �v���C���[�J�����̕`�揈��
//=============================================================================
void CCamera_Play::Draw(void)
{
	if (m_pCamera_Char != NULL) { m_pCamera_Char->Draw(); }
	if (m_pCamera_Obj != NULL)	{ m_pCamera_Obj->Draw(); }
}
//=============================================================================
// �v���C���[�J�����̃��Z�b�g����
//=============================================================================
void CCamera_Play::Reset(void)
{
	if (m_pCamera_Char != NULL)	{ m_pCamera_Char->Reset(); }
}
//=============================================================================
// �J�����̏���������
//=============================================================================
void CCamera_Manager::Init(void)
{
	m_pEvent = NULL;
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{//�J�������v��������
		m_pPlay[nCount] = NULL;
	}
	m_info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_info.m_fDistance = DISTANCE;
	m_info.nCntState = 0;
	m_info.nCntTime = 0;
	m_info.pCamera = NULL;
	m_info.p2DAnim = NULL;
	m_info.scene = SCENE_TYPE_NO;
	m_info.state = STATE_NONE;

	Load();	//�ݒ�̓ǂݍ���
	CManager::GetCamera() = this;
}
//=============================================================================
// �J�����Ǘ��@�S�X�V����
//=============================================================================
void CCamera_Manager::Update(void)
{
	if (m_pEvent != NULL) { m_pEvent->Update(); UpdateScene(); }
	else
	{//�C�x���g���X�V���łȂ��Ȃ�
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			if (m_pPlay[nCount] != NULL) { m_pPlay[nCount]->Update(); }
		}
	}
}
//=============================================================================
// �J�����Ǘ�(�C�x���g)�̏I������
//=============================================================================
void CCamera_Manager::Uninit_Event(void)
{
	if (m_pEvent != NULL) { m_pEvent->Uninit(); m_pEvent = NULL; }
}
//=============================================================================
// �J�����Ǘ��̏I������
//=============================================================================
void CCamera_Manager::Uninit(void)
{
	Uninit_Event();
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		if (m_pPlay[nCount] != NULL) 
		{ 
			//m_pPlay[nCount]->Uninit();
			delete m_pPlay[nCount];
			m_pPlay[nCount] = NULL;
		}
	}

	delete this;
	CManager::GetCamera() = NULL;
}
//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera_Manager::Draw(void)
{
	if (m_pEvent != NULL) 
	{ 
		if (CManager::GetLight() != NULL) { CManager::GetLight()->Set(0); }
		m_pEvent->Draw(); 
	}
	else
	{//�C�x���g���X�V���łȂ��Ȃ�
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			if (CManager::GetLight() != NULL) { CManager::GetLight()->Set(nCount + 1); }
			if (m_pPlay[nCount] != NULL) { m_pPlay[nCount]->Draw(); }
		}
	}
}
//=============================================================================
// �J�����̕`��`�F�b�N����
//=============================================================================
bool CCamera_Manager::DrawCheck(D3DXVECTOR3 &pos, float fLength)
{
	switch (m_info.pCamera->GetType())
	{
	case CCamera::CAMERA_TYPE_CHAR:
	case CCamera::CAMERA_TYPE_EVENT:
		if (!m_info.pCamera->DrawCheck(pos, fLength)) { return false; };
		break;
	case CCamera::CAMERA_TYPE_OBJ: break;
	}
	return true;
}
//=============================================================================
// �J�����̃��Z�b�g����
//=============================================================================
void CCamera_Manager::Reset(void)
{
	if (m_pEvent != NULL) { m_pEvent->Reset(); }
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{//�v���C���[�J�����̃��Z�b�g
		if (m_pPlay[nCount] != NULL) { m_pPlay[nCount]->Reset(); }
	}
}
//=============================================================================
// �v���C���[�J������������
//=============================================================================
CCamera_Play *&CCamera_Manager::Create_Play(int nCount)
{
	CCamera_Play *pPlay;
	CCamera_Manager *&pManager = CManager::GetCamera();

	if (pManager == NULL)
	{
		Create(pManager);
	}

	if (pManager->GetPlay(nCount) != NULL) { return pManager->GetPlay(nCount); }

	if (Create(pPlay))
	{//�����ŗ�����|�C���^���g�ɑ��
		pPlay->GetChar()->GetType() = CCamera::CAMERA_TYPE_CHAR;
		pPlay->GetChar()->GetnNumCamera() = nCount + 1;
		pManager->GetPlay(nCount) = pPlay;
	}
	return pManager->GetPlay(nCount);
}
//=============================================================================
// �v���C���[�J������������
//=============================================================================
CCamera_Char *&CCamera_Manager::Create_Event(void)
{
	CCamera_Char *pChar;
	CCamera_Manager *&pManager = CManager::GetCamera();

	if (pManager == NULL)
	{
		Create(pManager);
	}

	if (pManager->GetEvent() != NULL) { return pManager->GetEvent(); }

	if (Create(pChar))
	{//�����ŗ�����|�C���^���g�ɑ��
		pChar->GetType() = CCamera::CAMERA_TYPE_EVENT;
		pManager->GetEvent() = pChar;
		pChar->SetViewport(0, 0, 1280, 720);

	}
	return pManager->GetEvent();
}
//=============================================================================
// �J�����̐ݒ�ۑ�����
//=============================================================================
void CCamera_Manager::Save(void)
{
	FILE *pFile;

	pFile = fopen("data/TEXT/Camera.bin", "wb");

	if (pFile != NULL)
	{//Save�@����
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			fwrite(&m_info.nSpeedX[nCount], sizeof(int), 1, pFile);
			fwrite(&m_info.nSpeedY[nCount], sizeof(int), 1, pFile);
			fwrite(&m_info.bReturnX[nCount], sizeof(bool), 1, pFile);
			fwrite(&m_info.bReturnY[nCount], sizeof(bool), 1, pFile);
		}
		fclose(pFile);
	}
}
//=============================================================================
// �J�����̐ݒ�ǂݍ��ݏ���
//=============================================================================
void CCamera_Manager::Load(void)
{
	FILE *pFile;

	pFile = fopen("data/TEXT/Camera.bin", "rb");

	if (pFile != NULL)
	{//Save�@����
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			fread(&m_info.nSpeedX[nCount], sizeof(int), 1, pFile);
			fread(&m_info.nSpeedY[nCount], sizeof(int), 1, pFile);
			fread(&m_info.bReturnX[nCount], sizeof(bool), 1, pFile);
			fread(&m_info.bReturnY[nCount], sizeof(bool), 1, pFile);
		}
		fclose(pFile);
	}
	else
	{//�t�@�C��������
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			m_info.nSpeedX[nCount] = 50;
			m_info.nSpeedY[nCount] = 50;
			m_info.bReturnX[nCount] = false;
			m_info.bReturnY[nCount] = false;
		}
	}
}
//=============================================================================
// �J�����̍X�V����
//=============================================================================
CCamera_Char *&CCamera_Manager::SetScene(CCamera_Manager::SCENE_TYPE type)
{
	m_info.nCntState = 0;
	m_info.nCntTime = 0;
	m_info.state = STATE_MOVIE;
	m_info.scene = type;
	m_info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CPlayer::GetbUIDraw() = false;
	CBlood2D::Hide();	//���̃G�t�F�N�g���B��

	return Create_Event();
}
//=============================================================================
// �V�[���Đ�����
//=============================================================================
void CCamera_Manager::UpdateScene(void)
{
	if (m_info.state == STATE_MOVIE)
	{//�V�[���Đ�
		if (m_info.p2DAnim != NULL) { m_info.p2DAnim->Update(); }
		switch (m_info.scene)
		{
		case SCENE_TYPE_NO:	//�G���[�����p
			//Init();
			break;

		case SCENE_TYPE_SMASH:
			m_pEvent->SceneSmash();
			break;
		case SCENE_TYPE_LABYRINTH:
			m_pEvent->SceneLabyrinth();
			break;
		case SCENE_TYPE_BOSS:	//�{�X�O
			m_pEvent->SceneBoss();
			break;
		}
	}
}
