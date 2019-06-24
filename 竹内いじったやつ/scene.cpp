//=============================================================================
//
// �����_�����O���� [renderer.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "SceneModel.h"
#include "Font.h"
#include "motion.h"

#include "2DPolygon.h"
#include "2DGage.h"
#include "3DPolygon.h"

#include "collision.h"
#include "renderer.h"
#include "camera.h"
#include "light.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CScene	*CScene::m_pTop[MAX_SCENE] = {};					// ���݂̕`����
CScene	*CScene::m_pCur[MAX_SCENE] = {};					// ���݂̕`����
int		CScene::m_nNumAll[MAX_SCENE] = { 0, 0, 0, 0, 0, 0, 0, 0 };	// ������
CScene::DRAW_TYPE		CScene::m_nDraw = CScene::DRAW_TYPE_NORMAL;					// ���݂̕`����
int		CScene::m_nCntStart = 0;				// ���݂̕`����
bool	CScene::m_bPause = false;				//�|�[�Y�̗L��
LPDIRECT3DTEXTURE9	CScene::m_pTexture[TEX_MAX] = {};		// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPrioryity)
{
	//�O�ɍ��̃I�u�W�F������
	if (m_pCur[nPrioryity] != NULL) { m_pCur[nPrioryity]->GetpNext() = this; }	//�O������
	else { m_pTop[nPrioryity] = this; }				//�����擪

													//���ɑO�̃I�u�W�F������
	m_pPrev = m_pCur[nPrioryity];
	m_pNext = NULL;

	//���ɂ��̃I�u�W�F������
	m_pCur[nPrioryity] = this;
	m_nPriority = nPrioryity;
	m_nNumAll[nPrioryity]++;

	//���ɂ����ނ���Ȃ��I�u�W�F�^�C�v��
	SetObjType(OBJTYPE_NONE);
	m_bDeath = false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene(void) {}

//=============================================================================
// �摜�̓ǂݍ���
//=============================================================================
LPDIRECT3DTEXTURE9	&CScene::Load(TEXTURE tex)
{
	if (tex < TEX_MAX)
	{//�͈͊m�F
		if (m_pTexture[tex] == NULL)
		{//�ǂݍ���łȂ��Ȃ�
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			switch (tex)
			{//�ǂݍ��� 
			case TEX_Title:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/Title000.jpg", &m_pTexture[tex]);				break;
			case TEX_Select:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/Select001.jpg", &m_pTexture[tex]);				break;
			case TEX_Select0:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SELECT/Select000.png", &m_pTexture[tex]);			break;
			case TEX_G_EXPLOSION:D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/Game_BG2.jpg", &m_pTexture[tex]);				break;
			case TEX_BG_EVENT:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/Smash000.jpg", &m_pTexture[tex]);				break;
			case TEX_BG_BLOOD:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/blood_BG.jpg", &m_pTexture[tex]);				break;
			case TEX_Sea:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/sea000.jpg", &m_pTexture[tex]);				break;
			case TEX_UnderSea:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/river000.jpg", &m_pTexture[tex]);				break;

			case TEX_RANKING0:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SURVIVAL/RANKING000.jpg", &m_pTexture[tex]);		break;
			case TEX_RANKING1:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SURVIVAL/RANKING001.png", &m_pTexture[tex]);		break;
			case TEX_RANKING2:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SURVIVAL/kaenbeam.jpg", &m_pTexture[tex]);			break;
			case TEX_RANKING_TYPE:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SURVIVAL/RANKING002.png", &m_pTexture[tex]);	break;

			case TEX_Pause_BG:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/pause100.png", &m_pTexture[tex]);				break;
			case TEX_Pause_Logo:D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/LOGO/Pause_Logo.png", &m_pTexture[tex]);			break;
			case TEX_ResultLogo:D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/LOGO/Result_Logo.png", &m_pTexture[tex]);			break;

			case TEX_Tutorial000:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SELECT/Weapon_Tutorial.jpg", &m_pTexture[tex]);					break;
			case TEX_PIcon:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/PIcon.png", &m_pTexture[tex]);					break;
			case TEX_Weapon:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/LOGO/WEAPON_LOGO.png", &m_pTexture[tex]);			break;
			case TEX_CLEAR:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/congratulations.jpg", &m_pTexture[tex]);			break;
			case TEX_Objective:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/ObjectiveUI.png", &m_pTexture[tex]);				break;
			case TEX_PUSH000:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Push000.jpg", &m_pTexture[tex]);					break;
			case TEX_PUSH001:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Push001.jpg", &m_pTexture[tex]);					break;
			case TEX_Chat_Button:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Chat_Button000.png", &m_pTexture[tex]);		break;

			case TEX_Fog000:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Fog000.jpg", &m_pTexture[tex]);				break;
			case TEX_Fog001:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Fog001.jpg", &m_pTexture[tex]);				break;
			case TEX_GateE:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Gate000.jpg", &m_pTexture[tex]);				break;
			case TEX_Disappear:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Disappear.jpg", &m_pTexture[tex]);			break;

			case TEX_TitleLogo:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/LOGO/LABYRINTH_OF_BRAVE.png", &m_pTexture[tex]);				break;
			case TEX_Press:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/LOGO/Press_Any_Button.png", &m_pTexture[tex]);		break;
			case TEX_HitLogo:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/LOGO/Hit_Logo.png", &m_pTexture[tex]);				break;
			case TEX_Versus_Logo:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/LOGO/Versus_Logo.png", &m_pTexture[tex]);			break;

			case TEX_Dead:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Dead.jpg", &m_pTexture[tex]);				break;
			case TEX_Omen:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/OverOmen.jpg", &m_pTexture[tex]);			break;
			case TEX_Over:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/explosion.jpg", &m_pTexture[tex]);			break;

			case TEX_Arrow:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SELECT/Arrow.png", &m_pTexture[tex]);				break;
			case TEX_S_Move:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SELECT/Select_Move.jpg", &m_pTexture[tex]);			break;

			case TEX_BSword:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/BoxChar_100.jpg", &m_pTexture[tex]);			break;
			case TEX_BGoburin:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/goburinn_000.jpg", &m_pTexture[tex]);			break;

			case TEX_Potion_L:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Potion000.jpg", &m_pTexture[tex]);			break;
			case TEX_Potion_E:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Potion001.jpg", &m_pTexture[tex]);			break;
			case TEX_SelectMap:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/CharSelectMap0.jpg", &m_pTexture[tex]);		break;
			case TEX_Dungeon:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/DUNGEON/Dungeon000.jpg", &m_pTexture[tex]);			break;
			case TEX_Fence:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/fence.jpg", &m_pTexture[tex]);				break;
			case TEX_Stone:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/998_stone_.jpg", &m_pTexture[tex]);			break;
			case TEX_Stone_M:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/stone100.jpg", &m_pTexture[tex]);				break;
			case TEX_Steel:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Steel000.jpg", &m_pTexture[tex]);				break;
			case TEX_Satellite:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/satellite.jpg", &m_pTexture[tex]);			break;
			case TEX_Orbit:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Orbit000.jpg", &m_pTexture[tex]);			break;
			case TEX_Circle:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Effect_Circle000.jpg", &m_pTexture[tex]);	break;
			case TEX_GageDeco:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Gage_Decoration00.png", &m_pTexture[tex]);		break;
			case TEX_UI_Wood:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/UI_Wood000.jpg", &m_pTexture[tex]);			break;
			case TEX_Pos_Mag:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Position_Magnetic000.jpg", &m_pTexture[tex]);	break;
			case TEX_Pos_Nee:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Position_Needle000.jpg", &m_pTexture[tex]);	break;

			case TEX_Number:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/number000.png", &m_pTexture[tex]);				break;
			case TEX_Lock_On:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Lock_On000.jpg", &m_pTexture[tex]);				break;
			case TEX_Button_UI:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Button_UI001.jpg", &m_pTexture[tex]);			break;
			case TEX_Help:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Help.jpg", &m_pTexture[tex]);					break;
			case TEX_HIT0:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Hit000.jpg", &m_pTexture[tex]);				break;
			case TEX_HIT1:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Effect_DASH000.jpg", &m_pTexture[tex]);		break;
			case TEX_HIT_BLOOD:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Hit_Blood000.jpg", &m_pTexture[tex]);		break;
			case TEX_Fire:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Fire000.png", &m_pTexture[tex]);				break;

			case TEX_BLOCK00:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/CHIP/TEXTURE/Field_000.jpg", &m_pTexture[tex]);		break;
			case TEX_BLOCK01:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/CHIP/TEXTURE/Field_001.jpg", &m_pTexture[tex]);		break;
			
			case TEX_PLAYER_000:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/CHARACTER/Player/PCgenjin_player_uv.jpg", &m_pTexture[tex]);		break;
			case TEX_ENEMY_000:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/CHARACTER/Enemy_0/PCgenjin_enemy_uv.jpg", &m_pTexture[tex]);		break;

			case TEX_Cloak:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Cloak000.jpg", &m_pTexture[tex]);				break;
			case TEX_AXE:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/axe_uv.jpg", &m_pTexture[tex]);				break;
			case TEX_Spear:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Spear000.jpg", &m_pTexture[tex]);				break;
			case TEX_Stick:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Sticks.jpg", &m_pTexture[tex]);				break;
			case TEX_S_Face:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Face000.jpg", &m_pTexture[tex]);				break;
			case TEX_G_Face:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/goburin000.jpg", &m_pTexture[tex]);			break;

			// �|���ǉ�
			case TEX_TITLE_MODEL:D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/title.jpg", &m_pTexture[tex]);				break;
			case TEX_ENDROLL:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/Endroll.jpg", &m_pTexture[tex]);					break;
			case TEX_TITLE_3D:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/3D.png", &m_pTexture[tex]);						break;
			case TEX_TITLE_MOJI:D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/pc.png", &m_pTexture[tex]);						break;
			case TEX_MISSILE:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/missile.jpg", &m_pTexture[tex]);				break;

			}
		}
		return m_pTexture[tex];
	}
	return m_pTexture[0];
}
//=============================================================================
// �摜�̉��
//=============================================================================
void	CScene::UnLoad(void)
{
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{//�S�摜�j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//==================================================================================================//
//    * �S����֐� *
//==================================================================================================//
void CScene::ReleaseAll(void)
{
	CSceneModel::UnLoadModel();	//Model�̍폜
	CCharacter::UnLoad();		//�L�����p�[�c�̍폜
	CMotion::UnLoad();			//���[�V�����̍폜
	CFont::UnLoad();			//�����̏I��
	UnLoad();

	if (CManager::GetCamera() != NULL) { CManager::GetCamera()->Uninit(); }
	if (CManager::GetLight() != NULL) { CManager::GetLight()->Uninit(); }

	BreakObject();
}
//=============================================================================
// �X�V����
//=============================================================================
void  CScene::UpdateAll(void)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;

	//�������\��
	CManager::GetDLog()->Update();
	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "������\n ��F%d,  ��F%d,  ��F%d,  �Q�F%d,  �l�F%d,  �ށF%d,  �Z�F%d,  ���F%d\n"
	//	, m_nNumAll[0], m_nNumAll[1], m_nNumAll[2], m_nNumAll[3], m_nNumAll[4], m_nNumAll[5], m_nNumAll[6], m_nNumAll[7]);

	for (int nCntScene = (m_bPause ? MAX_SCENE - 1 : m_nCntStart); nCntScene < MAX_SCENE; nCntScene++)
	{//�D�揇�ʕ����
		pScene = m_pTop[nCntScene];
		while (pScene != NULL)
		{//NULL�ɂȂ�܂ŌJ��Ԃ�
			pNext = pScene->GetpNext();	//Update���ɏ�����\�������邩��
			if (!pScene->m_bDeath) { pScene->Update(); }
			pScene = pNext;
		}
	}
	CCollision::CollisionAll();
}
//=============================================================================
// �`�揈��
//=============================================================================
void  CScene::DrawAll(LPDIRECT3DDEVICE9 &pDevice)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{//�D�揇�ʕ����
		pScene = m_pTop[nCntScene];
		while (pScene != NULL)
		{//NULL�ɂȂ�܂ŌJ��Ԃ�
			pNext = pScene->GetpNext();	//Draw���ɏ����邩������Ȃ�����
			if (!pScene->m_bDeath) { pScene->Draw(); }
			pScene = pNext;
		}
	}
}
//==================================================================================================//
//    * 3D�`�揈�� *
//==================================================================================================//
void	CScene::Draw3D(LPDIRECT3DDEVICE9 &pDevice)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;
	for (int nCntScene = 0; nCntScene < MAX_3DSCENE; nCntScene++)
	{//�D�揇�ʕ����
		pScene = m_pTop[nCntScene];
		while (pScene != NULL)
		{//NULL�ɂȂ�܂ŌJ��Ԃ�
			pNext = pScene->GetpNext();	//Draw���ɏ����邩������Ȃ�����
			if (!pScene->m_bDeath) { pScene->Draw(); }
			pScene = pNext;
		}
	}
}
//==================================================================================================//
//    * 3D�I�u�W�F�`�揈�� *
//==================================================================================================//
void	CScene::DrawObj(LPDIRECT3DDEVICE9 &pDevice)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;
	pScene = m_pTop[OBJ_PRIORITY];
	while (pScene != NULL)
	{//NULL�ɂȂ�܂ŌJ��Ԃ�
		pNext = pScene->GetpNext();	//Draw���ɏ����邩������Ȃ�����
		if (!pScene->m_bDeath) { pScene->Draw(); }
		pScene = pNext;
	}
}
//==================================================================================================//
//    * 2D�`�揈�� *
//==================================================================================================//
void	CScene::Draw2D(LPDIRECT3DDEVICE9 &pDevice)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;
	for (int nCntScene = START_2DSCENE; nCntScene < MAX_SCENE; nCntScene++)
	{//�D�揇�ʕ����
		pScene = m_pTop[nCntScene];
		while (pScene != NULL)
		{//NULL�ɂȂ�܂ŌJ��Ԃ�
			pNext = pScene->GetpNext();	//Draw���ɏ����邩������Ȃ�����
			if (!pScene->m_bDeath) { pScene->Draw(); }
			pScene = pNext;
		}
	}
}
//==================================================================================================//
//    * ���]�`�揈�� *
//==================================================================================================//
void	CScene::DrawMirror(LPDIRECT3DDEVICE9 &pD3DDevice)
{
	D3DXMATRIX	WKmtx;			//���[���h�}�g���b�N�X
	CScene		*pScene = NULL;
	CScene		*pNext = NULL;
	D3DXPLANE	planeField;
	D3DXVECTOR3	pos, normal;
	D3DXVECTOR4	vecLight;
	D3DLIGHT9 &light = CManager::GetLight()->Getlight(0);

	pD3DDevice->GetTransform(D3DTS_WORLD, &WKmtx);

	//���ʍ쐬

	vecLight = D3DXVECTOR4(-light.Direction.x, -light.Direction.y, -light.Direction.z, 0.0f);
	pos = D3DXVECTOR3(WKmtx._41, -WKmtx._42, WKmtx._43);
	normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	D3DXMatrixShadow(&WKmtx, &vecLight, &planeField);

	for (int nCntScene = 0; nCntScene < MAX_3DSCENE; nCntScene++)
	{//�D�揇�ʕ����
		pScene = m_pTop[nCntScene];
		while (pScene != NULL)
		{//NULL�ɂȂ�܂ŌJ��Ԃ�
			pNext = pScene->GetpNext();	//Draw���ɏ����邩������Ȃ�����
			if (!pScene->m_bDeath) { pScene->DrawMirror(pD3DDevice, planeField); }
			pScene = pNext;
		}
	}
}
//==================================================================================================//
//    * ���]�`��p���ʎ擾���� *
//==================================================================================================//
D3DXPLANE CScene::GetPlane(void)
{
	D3DXVECTOR3	pos, normal;
	D3DXPLANE	planeField;

	pos = INIT_VECTOR;
	normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	return planeField;
}
//==================================================================================================//
//    * �I���֐� *
//==================================================================================================//
void	CScene::UninitAll(void)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{//�D�揇�ʕ����
		pScene = m_pTop[nCntScene];
		while (pScene != NULL)
		{//NULL�ɂȂ�܂ŌJ��Ԃ�
			pNext = pScene->GetpNext();	//�ی�
			if (pScene->m_bDeath) { pScene->Release(); }
			pScene = pNext;
		}
	}
}
//==================================================================================================//
//    * �`�揀���֐� *
//==================================================================================================//
bool CScene::DrawPrepare(CScene::DRAW_TYPE DrawType, LPDIRECT3DDEVICE9 &pD3DDevice)
{
	if (DrawType == DRAW_TYPE_NO) { return true; }

	if (DrawType < DRAW_TYPE_NO)
	{
		if (m_nDraw / 10 != DrawType / 10)
		{//���݂�Z�e�X�g�ƕ`����@���Ⴄ�Ȃ�
			if (DrawType >= CScene::DRAW_TYPE_ZNORMAL)
			{// Z�e�X�g����
				pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
			}
			else
			{// Z�e�X�g�n��
				pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
			}
		}
		if (m_nDraw % 10 != DrawType % 10)
		{//���݂̍������@���Ⴄ�Ȃ�
			switch (DrawType % 10)
			{//�ق�Ƃ�3�s���邱�Ƃ�Y��Ă͂����Ȃ�...
			case CScene::DRAW_TYPE_NORMAL:// �ʏ�
				pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				break;
			case CScene::DRAW_TYPE_ADD:// ���u�����f�B���O�����Z�����ɐݒ�
				pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				break;
			case CScene::DRAW_TYPE_SUBTRACT:// ���Z
				pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
				pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				break;
			case CScene::DRAW_TYPE_MULTIPLY:
				pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO | D3DBLEND_ONE);
				pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);
				break;
			case CScene::DRAW_TYPE_OVERLAY:
				pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO | D3DBLEND_ONE);
				pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				break;
			case CScene::DRAW_TYPE_AER:
				pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				break;
			}
		}
		m_nDraw = DrawType;	//�`����@�̑��
	}
	else
	{
		switch (DrawType)
		{
		case DRAW_TYPE_MIRROR:
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO | D3DBLEND_ONE);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);
			m_nDraw = DRAW_TYPE_MULTIPLY;

			//CManager::GetRenderer()->SetRenderer(false);
			//pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			// �[�x�o�b�t�@�ɏ������݂͂��Ȃ�
			pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);			// ���]�ʕ`��

			pD3DDevice->Clear(0, NULL, (D3DCLEAR_STENCIL), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

			// �X�e���V���e�X�g���g�p����
			pD3DDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
			pD3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

			// �X�e���V���o�b�t�@�̑�����1�ɐݒ肷��
			pD3DDevice->SetRenderState(D3DRS_STENCILREF, 0x1);
			pD3DDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
			pD3DDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);

			DrawMirror(pD3DDevice);
			pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			// �\�ʕ`��

			pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0x0000000F);
			pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
			pD3DDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
			//return true;

			break;
		}
	}

	return false;
}
//==================================================================================================//
//    * �`��I�������� *
//==================================================================================================//
bool CScene::EndDraw(CScene::DRAW_TYPE DrawType, LPDIRECT3DDEVICE9 &pD3DDevice)
{
	switch (DrawType)
	{
	case DRAW_TYPE_MIRROR:
		CManager::GetRenderer()->SetRenderer(true);

		//// ��Ԃ����ɖ߂�
		//pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		//pD3DDevice->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, FALSE);
		////pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		//// �[�x�e�X�g�͂���
		//pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		//// �X�e���V���e�X�g�͂���
		//pD3DDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		//// �X�e���V���o�b�t�@�̒l��==1�̂Ƃ��ɏ�������
		//pD3DDevice->SetRenderState(D3DRS_STENCILREF, 1);
		//pD3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		//pD3DDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
		//pD3DDevice->SetRenderState(D3DRS_CCW_STENCILZFAIL, D3DSTENCILOP_KEEP);
		//pD3DDevice->SetRenderState(D3DRS_CCW_STENCILFAIL, D3DSTENCILOP_KEEP);
		//pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);			// ���ʕ`��


		//pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		return true;
	}
	return false;
}
//==================================================================================================//
//    * �����폜�֐� *
//==================================================================================================//
void CScene::Release()
{
	//�O�̂�Ɏ����̎������
	if (m_pPrev != NULL) { m_pPrev->GetpNext() = m_pNext; }	//�⌾��
	else { m_pTop[m_nPriority] = m_pNext; }	//�擪���

											//���̂�Ɏ��������������Ƃ�`����
	if (m_pNext != NULL) { m_pNext->GetpPrev() = m_pPrev; }	//���ƑO���Ȃ���
	else { m_pCur[m_nPriority] = m_pPrev; } //�Ō�����

											//�����̍폜
	m_nNumAll[m_nPriority]--;
	delete this;
}
//=============================================================================
//	�S�I�u�W�F�N�g��j��
//=============================================================================
void CScene::BreakObject(void)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{//�D�揇�ʕ����
		pScene = m_pTop[nCntScene];
		while (pScene != NULL)
		{//NULL�ɂȂ�܂ŌJ��Ԃ�
			pNext = pScene->GetpNext();	//�ی�
			if (!pScene->m_bDeath) { pScene->Uninit(); }
			pScene = pNext;
		}
	}
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{//�D�揇�ʕ����
		while (m_pTop[nCntScene] != NULL)
		{//NULL�ɂȂ�܂ŌJ��Ԃ�
			if (m_pTop[nCntScene]->m_bDeath) { m_pTop[nCntScene]->Release(); }
		}
	}
}
//=============================================================================
//	�w�肵���I�u�W�F�N�g��j��
//=============================================================================
void CScene::BreakObject(OBJTYPE obj)
{
	CScene *pNext = NULL;
	CScene *pTarget = NULL;
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{//�D�揇�ʕ����
		pNext = m_pTop[nCntScene];
		while (pNext != NULL)
		{//NULL�ɂȂ�܂ŌJ��Ԃ�
			pTarget = pNext;
			pNext = pNext->GetpNext();

			if (pTarget->GetObjType() == obj)
			{//�I�u�W�F�^�C�v�����Ԃ��Ă���Ȃ�폜
				pTarget->Uninit();
				pTarget->SetObjType(OBJTYPE_NONE);
			}
		}
	}
}
//=============================================================================
// �ʒu��Ԃ�
//=============================================================================
D3DXVECTOR3	*CScene::Getpos(void)
{
	switch (m_ObjType)
	{
	case OBJTYPE_PLAYER:
	case OBJTYPE_ENEMY:
	case OBJTYPE_BOSS:
		return &((CCharacter*)this)->Getpos();
		break;
	}

	return NULL;
}
