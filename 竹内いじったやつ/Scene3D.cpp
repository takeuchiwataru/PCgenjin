//=============================================================================
//
// �|���S������ [Scene3D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene3D.h"
#include"Renderer.h"
#include "collision.h"
#include "player.h"
#include "manager.h"
#include "camera.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// ���ёւ�����
//=============================================================================
void CScene3D::Sort(void)
{
	CScene *pScene;
	CScene **pSwap = new CScene*[CScene::GetnNumAll(S3D_PRIORITY)];
	float  *pfDistance = new float[CScene::GetnNumAll(S3D_PRIORITY)];
	int	   nCount = 0;
	pScene = CScene::GetTop(S3D_PRIORITY);
	while (pScene != NULL)
	{//NULL�ɂȂ�܂ŌJ��Ԃ�
		//��񔲏o
		nCount++;
		pScene = pScene->GetpNext();
	}



	delete[] pSwap;
	delete[] pfDistance;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CScene3D::Init(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	m_pVtxBuff = NULL;
	m_pTex = NULL;

	// ���_���̍쐬
	MakeVertex(pD3DDevice);

	m_DrawType = CScene::DRAW_TYPE_NORMAL;
	m_bBILLBoard = false;
	m_nNumCamera = -1;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene3D::Uninit(void)
{
	// ���_�o�b�t�@�̊J��;
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CScene::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene3D::Update(void)
{
	if (m_state != STATE_NORMAL)
	{
		D3DXVECTOR3 WKlength;	//�v�Z�p�̒���

		switch (m_state)
		{
		case STATE_UVFLOW_1:
			PlusUV(D3DXVECTOR2(1.0f, 2.0f) * m_fCntState);
			break;
		case STATE_UVFLOW_0:
			PlusUV(D3DXVECTOR2(1.0f, 1.0f) * m_fCntState);
			break;
		case STATE_FADESPIN:
			m_fCntState += 0.02f;
			m_rot.y += D3DX_PI * 0.03f;
			if (m_fCntState >= 1.0f) { Uninit(); return; }
			m_col.a = 1.0f - m_fCntState;//�����x�ύX
			m_length *= 1.0f + ((1.0f - m_fCntState) * 0.15f);
			SetColor(m_col);
			SetSize(m_length);
			break;
		case STATE_FADEIN:
			m_col.a += 0.05f;//�����x�ύX
			if (m_col.a > 1.0f) { m_col.a = 1.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;

		case STATE_FADEOUT:
			m_col.a -= m_fCntState;//�����x�ύX
			if (m_col.a <= 0.0f) 
			{ Uninit(); return; }
			SetColor(m_col);
			break;
		case STATE_FADEOUT2:
			m_col.a -= 0.05f;//�����x�ύX
			if (m_col.a < 0.0f) { m_col.a = 0.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_BFLOW_IN:
			if (m_col.a != 1.0f)
			{//�����x������Ȃ��I
				m_col.a += 0.01f;//�����x�ύX
				if (m_col.a >= 1.0f) { m_col.a = 1.0f; }
				SetColor(m_col);
			}
			PlusUV(D3DXVECTOR2(0.002f, 0.001f));
			break;
		case STATE_BFLOW_OUT:
			if (m_col.a != 0.0f)
			{//�����x������Ȃ��I
				m_col.a -= 0.01f;//�����x�ύX
				if (m_col.a <= 0.0f)
				{
					m_col.a = 0.0f;
					m_state = STATE_NORMAL;
					return;
				}
				SetColor(m_col);
			}
			PlusUV(D3DXVECTOR2(0.02f, 0.01f));
			break;
		case STATE_LOCK_0:	//�����g��k��
			m_fCntState += D3DX_PI * 0.0125f;
			WKlength = m_length * (1.0f + sinf(m_fCntState) * 0.25f);
			SetSize(WKlength);
			break;
		case STATE_LOCK_1:	//�M�����I�ƋÏk
			m_fCntState *= 0.75f;
			if (m_fCntState < 1.0f) { m_fCntState = 1.0f; m_state = STATE_NORMAL; }
			WKlength = m_length * m_fCntState;
			SetSize(WKlength);
			break;
		case STATE_HIT:
			m_pos.y += 0.5f;
			m_col.a -= m_fCntState;//�����x�ύX
			if (m_col.a <= 0.0f)
			{
				Uninit(); return;
			}
			SetColor(m_col);
			SetMtx();
			break;

		case STATE_FADEIN2:		// �^�C�g��3D�̃t�F�[�h�@�|���ǉ�
			m_col.a += m_fCntState;
			if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		}
	}
	if (m_state == STATE_CHECK)
	{//�`�F�b�N�|�C���g
	 //�v���C���[������
		CPlayer *&pPlayer = CManager::GetPlayer(0);
		if (pPlayer == NULL) { return; }
		//�v���C���[���߂��ɂ����
		D3DXVECTOR3 &m_pos = GetPosition();
		D3DXVECTOR3 &playerPos0 = pPlayer->Getpos();
		float fDistance0 = 50000.0f;
		float fDistance1 = 50000.0f;

		fDistance0 = powf(playerPos0.x - m_pos.x, 2) + powf(playerPos0.z - m_pos.z, 2);
		if (CManager::GetbDuo() && CManager::GetPlayer(1) != NULL)
		{
			D3DXVECTOR3 &playerPos1 = CManager::GetPlayer(1)->Getpos();
			fDistance1 = powf(playerPos1.x - m_pos.x, 2) + powf(playerPos1.z - m_pos.z, 2);
		}
		if (fDistance0 <= 120.0f * 120.0f || fDistance1 <= 120.0f * 120.0f)
		{//�߂��ɂ���Ȃ�
			CSceneAnim3D *p3DAnim;

			CManager::GetSound()->Play(CSound::LABEL_PARIS);
			if (SceneCreate(p3DAnim, S3D_PRIORITY))
			{//�G�t�F�N�g
				p3DAnim->Set(m_pos, m_rot, m_col, m_length, CScene::TEX_Disappear, false,
					CScene::DRAW_TYPE_OVERLAY, 0, 5, 2, 3, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_FADESPIN);
			}
			Uninit();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene3D::Draw(void)
{
	if (m_nNumCamera == -1 || m_nNumCamera != CCamera_Manager::GetInfo().pCamera->GetnNumCamera())
	{//�Ή����Ă���J�����Ȃ�
		LPDIRECT3DDEVICE9	pD3DDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

		if (CScene::DrawPrepare(m_DrawType, pD3DDevice)) { return; }

		// ���[���h�}�g���b�N�X�̐ݒ�
		if (m_bBILLBoard) { SetMtx(); }
		pD3DDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pD3DDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		if (m_pTex != NULL)
		{//�e�N�X�`���̐ݒ�
			pD3DDevice->SetTexture(0, m_pTex);
		}//�e�N�X�`���폜

		// �|���S���̕`��
		//�A���t�@�e�X�g����(�������ɂ��摜�̐؂��茻�ۂ�L���ɂ���)
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 30);//REF = Reference:�Q��
		pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//FUNC = Function:�@�\ //GREATER = �`���傫��

		pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);    // ���ʂ��J�����O

		pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		pD3DDevice->SetTexture(0, NULL);

		pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);    // ���ʂ��J�����O
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void CScene3D::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �ݒ�
//=============================================================================
void CScene3D::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length, TEXTURE nType, int nUV, int nUV_X, int nUV_Y, bool bBillBoard, DRAW_TYPE DrawType)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			m_pTex = Load(nType);
			m_col = col;

			m_pos = pos;
			m_rot = rot;
			m_length = length;
			m_DrawType = DrawType;
			m_bBILLBoard = bBillBoard;

			pVtx[0].pos = D3DXVECTOR3(-m_length.x, m_length.y, m_length.z);
			pVtx[1].pos = D3DXVECTOR3(m_length.x, m_length.y, m_length.z);
			pVtx[2].pos = D3DXVECTOR3(-m_length.x, -m_length.y, -m_length.z);
			pVtx[3].pos = D3DXVECTOR3(m_length.x, -m_length.y, -m_length.z);

			//pVtx[0].pos = D3DXVECTOR3(-100.0f, 100.0f, 50.0f);
			//pVtx[1].pos = D3DXVECTOR3(100.0f, 100.0f, 50.0f);
			//pVtx[2].pos = D3DXVECTOR3(-100.0f, -100.0f, -0.0f);
			//pVtx[3].pos = D3DXVECTOR3(100.0f, -100.0f, -0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
			pVtx[1].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
			pVtx[2].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
			pVtx[3].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j

			//UV�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X)				 , (nUV / nUV_X) * (1.0f / nUV_Y));
			pVtx[1].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
			pVtx[2].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X)				 , (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));
			pVtx[3].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	if (!m_bBILLBoard) { SetMtx(); }
}
//=============================================================================
// �F�̐ݒ�
//=============================================================================
void	CScene3D::SetColor(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_col = col;

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
	pVtx[1].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
	pVtx[2].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
	pVtx[3].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �F�̐ݒ�
//=============================================================================
void	CScene3D::SetSize(D3DXVECTOR3 length)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�l����
	//m_length = length;

	pVtx[0].pos = D3DXVECTOR3(-length.x, length.y, length.z);
	pVtx[1].pos = D3DXVECTOR3(length.x, length.y, length.z);
	pVtx[2].pos = D3DXVECTOR3(-length.x, -length.y, -length.z);
	pVtx[3].pos = D3DXVECTOR3(length.x, -length.y, -length.z);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//==================================================================================================//
//    * ����������UV���W�ύX *
//==================================================================================================//
void CScene3D::SetUV(int nUV, int nUV_X, int nUV_Y)
{
	//Vtx�̕ύX
	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�ݒ�
	pVtx[0].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
	pVtx[1].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
	pVtx[2].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));
	pVtx[3].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));

	//���_BUFFER���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// UV�p�^�[�����ݒ�
//=============================================================================
void	CScene3D::SetUVPattern(float fUV_X, float fUV_Y)
{
	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�ݒ�
	//pVtx[0].tex = D3DXVECTOR2((m_pos.x + m_fLengthX) * fUV_X, (m_pos.z - m_fLengthZ) * fUV_Y);
	//pVtx[1].tex = D3DXVECTOR2((m_pos.x - m_fLengthX) * fUV_X, (m_pos.z + m_fLengthZ) * fUV_Y);
	//pVtx[2].tex = D3DXVECTOR2((m_pos.x + m_fLengthX) * fUV_X, (m_pos.z - m_fLengthZ) * fUV_Y);
	//pVtx[3].tex = D3DXVECTOR2((m_pos.x - m_fLengthX) * fUV_X, (m_pos.z + m_fLengthZ) * fUV_Y);

	pVtx[0].tex = D3DXVECTOR2((m_pos.x / m_length.x) * fUV_X, (m_pos.z / m_length.z) * fUV_Y);
	pVtx[1].tex = D3DXVECTOR2(((m_pos.x + m_length.x) / m_length.x) * fUV_X, ((m_pos.z / m_length.z) * fUV_Y));
	pVtx[2].tex = D3DXVECTOR2((m_pos.x / m_length.x) * fUV_X, ((m_pos.z + m_length.z) / m_length.z) * fUV_Y);
	pVtx[3].tex = D3DXVECTOR2(((m_pos.x + m_length.x) / m_length.x) * fUV_X, ((m_pos.z + m_length.z) / m_length.z) * fUV_Y);

	//���_BUFFER���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// UV���Z����
//=============================================================================
void	CScene3D::PlusUV(D3DXVECTOR2 uv)
{
	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�ݒ�
	pVtx[0].tex += uv;
	pVtx[1].tex += uv;
	pVtx[2].tex += uv;
	pVtx[3].tex += uv;

	//���_BUFFER���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// UV�ύX����
//=============================================================================
void	CScene3D::SetUV(float fUV_X, float fUV_Y)
{
	//Vtx�̕ύX
	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / fUV_X, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / fUV_Y);
	pVtx[3].tex = D3DXVECTOR2(1.0f / fUV_X, 1.0f / fUV_Y);

	//���_BUFFER���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �}�g���b�N�X���[���h�̌v�Z����
//=============================================================================
void CScene3D::SetMtx(void)
{
	LPDIRECT3DDEVICE9	pD3DDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;	//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	if (m_bBILLBoard)
	{ //�r���{�[�h
		pD3DDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�t�s���ݒ�
		m_mtxWorld._11 = mtxView._11;
		m_mtxWorld._12 = mtxView._21;
		m_mtxWorld._13 = mtxView._31;
		m_mtxWorld._21 = mtxView._12;
		m_mtxWorld._22 = mtxView._22;
		m_mtxWorld._23 = mtxView._32;
		m_mtxWorld._31 = mtxView._13;
		m_mtxWorld._32 = mtxView._23;
		m_mtxWorld._33 = mtxView._33;
	}
	else
	{// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	}
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}
//=============================================================================
// ������ƃt�F�[�h�i�|���ǉ�)
//=============================================================================
void	CScene3D::Fade(float fCntState, STATE state)
{
	m_fCntState = fCntState;
	m_state = state;

	if (m_col.a >= 1.0f)
	{
		m_col.a += m_fCntState;

		m_col.a = 1.0f; m_state = STATE_NORMAL;
	}
	SetColor(m_col);
}
////=============================================================================
//// �|���S���̈ړ�(�|���ǉ�)
////=============================================================================
//void	CScene3D::SetMove(D3DXVECTOR3 move, STATE state)
//{
//	D3DXVECTOR3 &PolygonPos = GetPosition();
//	D3DXVECTOR3 Move;
//
//	Move = move;
//	m_state = state;
//
//	if (PolygonPos == D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 70.0f, 0.0f))
//	{// �Z���^�[�܂ł�����ړ��X�g�b�v
//		Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	}
//	else
//	{// �Z���^�[�ɗ���܂ł͈ړ�
//		Move.x += 1.0f;
//		PolygonPos.x -= Move.x;
//	}
//}

//=============================================================================
// �G�t�F�N�g�̐ݒ�
//=============================================================================
void CSceneEffect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,TEXTURE nType, 
	int nUV, int nUV_X, int nUV_Y, bool bBillBoard, DRAW_TYPE DrawType, D3DXVECTOR3 *pPos, int nCNumber)
{
	CScene3D::Set(pos, rot, col, length, nType, nUV, nUV_X, nUV_Y, bBillBoard, DrawType);
	m_pPos = pPos;
	m_nCNumber = nCNumber;
}
//=============================================================================
// �G�t�F�N�g�̍X�V
//=============================================================================
void CSceneEffect::Update(void)
{
	if (m_pPos != NULL)
	{
		GetPosition() = m_pPos[0] + D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		CScene3D::Update();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CSceneEffect::Draw(void)
{
	if (CManager::GetCamera()->GetInfo().pCamera->GetnNumCamera() != m_nCNumber || m_nCNumber < 0)
	{//�`�悵�Ă����J�����Ȃ�
		CScene3D::Draw();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CScene3DView::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 length, DRAW_TYPE DrawType)
{
	LPDIRECT3DDEVICE9	&pDevice = CManager::GetRenderer()->GetDevice();
	LPDIRECT3DSURFACE9	pRenderOrg;	//�����_���[�̕ۊǗp
	LPDIRECT3DSURFACE9	pBuffOrg;	//�o�b�t�@�̕ۊǗp

	CScene3D::Set(pos, rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), length, CScene::TEX_MAX, 0, 1, 1, true, CScene::DRAW_TYPE_NORMAL);

	pDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 1,
		D3DUSAGE_RENDERTARGET, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, &m_pTextureMT, NULL);
	m_pTextureMT->GetSurfaceLevel(0, &m_pRenderMT);

	pDevice->CreateDepthStencilSurface(SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_D16,
		D3DMULTISAMPLE_NONE, 0, TRUE, &m_pBuffMT, NULL);

	pDevice->GetRenderTarget(0, &pRenderOrg);	//�擾
	pDevice->GetDepthStencilSurface(&pBuffOrg);	//�擾
	pDevice->SetRenderTarget(0, m_pRenderMT);	//�e�N�X�`���Ɋ��蓖�Ă�
	pDevice->SetDepthStencilSurface(m_pBuffMT);	//���蓖��

	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	pDevice->SetRenderTarget(0, pRenderOrg);	//�߂�
	pDevice->SetDepthStencilSurface(pBuffOrg);	//�߂�
}
//=============================================================================
// �`�揈��
//=============================================================================
HRESULT CScene3DView::Init(void)
{
	CScene3D::Init();
	m_pBuffMT = NULL;
	m_pRenderMT = NULL;
	m_pTextureMT = NULL;

	m_viewportMT.X = 0;
	m_viewportMT.Y = 0;
	m_viewportMT.Width = 1280;
	m_viewportMT.Height = 720;
	m_viewportMT.MinZ = 0.0f;
	m_viewportMT.MaxZ = 1.0f;

	return S_OK;
}
//=============================================================================
// �`�揈��
//=============================================================================
void	CScene3DView::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
// �`�揈��
//=============================================================================
void	CScene3DView::Update(void)
{

}
//=============================================================================
// �`�揈��
//=============================================================================
void	CScene3DView::Draw(void)
{
	LPDIRECT3DDEVICE9	&pDevice = CManager::GetRenderer()->GetDevice();
	LPDIRECT3DSURFACE9	pRenderOrg;	//�����_���[�̕ۊǗp
	LPDIRECT3DSURFACE9	pBuffOrg;	//�o�b�t�@�̕ۊǗp
	D3DXMATRIX			mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX			mtxView;			//�r���[�}�g���b�N�X
	D3DVIEWPORT9		Viewport;
	CCamera *&pCamera = CCamera_Manager::GetInfo().pCamera;

	pDevice->GetRenderTarget(0, &pRenderOrg);	//�擾
	pDevice->GetDepthStencilSurface(&pBuffOrg);	//�擾
	pDevice->SetRenderTarget(0, m_pRenderMT);	//���蓖��
	pDevice->SetDepthStencilSurface(m_pBuffMT);	//���蓖��
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	Viewport = CCamera_Manager::GetInfo().pCamera->GetViewPort();
	pDevice->GetViewport(&m_viewportMT);
	mtxProjection = pCamera->GetMtxProjection();
	mtxView = pCamera->GetMtxView();

	pDevice->SetViewport(&m_viewportMT);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxProjection);
	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(45.0f), (float)Viewport.Width / (float)Viewport.Height, 10.0f, 24800.0f);
	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxView);
	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&mtxView, &pCamera->GetposV(), &pCamera->GetposR(), &pCamera->GetvecU());
	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);

	pDevice->SetTexture(0, CScene::Load(CScene::TEX_Number));
	CScene3D::Draw();

	pDevice->SetRenderTarget(0, pRenderOrg);	//�߂�
	pDevice->SetDepthStencilSurface(pBuffOrg);	//�߂�

	pDevice->SetTexture(0, m_pTextureMT);
	CScene3D::Draw();
}
//=============================================================================
// �ݒ�
//=============================================================================
void CScene3DMove::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length, TEXTURE nType, int nUV, int nUV_X, int nUV_Y, bool bBillBoard, DRAW_TYPE DrawType,STATE state)
{
	CScene3D::Set(pos, rot,col, length, nType, nUV, nUV_X, nUV_Y, bBillBoard, DrawType);
	m_state = state;
}
//=============================================================================
// �X�V����
//=============================================================================
void	CScene3DMove::Update(void)
{
	D3DXVECTOR3 &PolygonPos = GetPosition();

	if (m_state == STATE_MOVE)
	{// �ړ���������
		if (PolygonPos.x <= 100.0f)
		{// �Z���^�[�܂ł�����ړ��X�g�b�v
			m_move = INIT_VECTOR;
		}
		else
		{// �Z���^�[�ɗ���܂ł͈ړ�
			m_move.x += 0.003f;
			PolygonPos.x -= m_move.x;
		}
	}
	SetMtx();
}
