//=============================================================================
//
// セレクト処理 [Select.cpp]
// Author : 小松　啓祐
//
//=============================================================================
#include"Scene.h"
#include"Scene2D.h"
#include "manager.h"
#include "RenderDraw.h"
#include "scene.h"
#include "Effect.h"
#include "player.h"
#include "enemy.h"
#include "SceneModel.h"
#include "mesh.h"
#include "Font.h"
#include "MapChip.h"
#include "motion.h"

#include "Select.h"
#include "camera.h"
#include "light.h"
#include "wind.h"
#include "sound.h"
//*****************************************************************************
// マクロの定義
//*****************************************************************************
#define FADE_TIME		(180)

//=============================================================================
// 静的メンバ変数
//=============================================================================
bool CSelect::m_bDuo = false;	//2人プレイかどうか

//=============================================================================
// セレクトの初期化処理
//=============================================================================
HRESULT CSelect::Init(void)
{
	m_state = STATE_NONE;
	m_fCntState = 0.0f;
	m_nCntWorkState = 0;
	m_nSelect = 1;
	CMotion::Load();
	CCharacter::Load();

	CLight *pLight;			Create(pLight);		//ライトの生成
	CCamera_Play	*pCamera;

	CPlayer *pPlayer;
	CSceneModel *pModel;

	pCamera = CCamera_Manager::Create_Play(0);
	pCamera->GetChar()->SetViewport(0, 0, 0, 0);
	pCamera->GetObj()->SetViewport(0, 0, 1280, 720);
	pCamera->GetObj()->GetposR() = D3DXVECTOR3(MAP_CHIP_SIZE * 4.5f, MAP_CHIP_SIZE * 1.5f, MAP_CHIP_SIZE * 1.5f);
	pCamera->GetObj()->GetposV() = D3DXVECTOR3(MAP_CHIP_SIZE * 4.5f, MAP_CHIP_SIZE * 5.0f, MAP_CHIP_SIZE * -12.0f);

	CPlayer::GetManager() = CPlayer::MANAGER_SELECT;
	CPlayer::GetbUIDraw() = false;
	if (SceneCreate(pPlayer, CHAR_PRIORITY))
	{//キャラ作成
		pPlayer->Set(D3DXVECTOR3(MAP_CHIP_SIZE * 4.5f, MAP_CHIP_SIZE * 3.0f, MAP_CHIP_SIZE * 4.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_PLAYER);
	}

	CMapChip *pMap;
	if (SceneCreate(pMap, MAP_PRIORYITY))
	{//マップの生成
		pMap->SetMap(CMapChip::MAP_SELECT);
	}
	for (int nCount = 0; nCount < MAX_MODE_SELECT; nCount++)
	{
		if (SceneCreate(m_pEnemy[nCount], CHAR_PRIORITY))
		{//キャラ作成
			CCharParts **&Parts = m_pEnemy[nCount]->GetpParts();

			m_pEnemy[nCount]->Set(D3DXVECTOR3(MAP_CHIP_SIZE * (1.5f + 3.0f * nCount), 0.0f, MAP_CHIP_SIZE * 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_ENEMY_0);
			m_pEnemy[nCount]->SetAIState(CEnemyAIBase::TYPE_SIGNBOARD);
			Parts[0]->Set(6, &Parts[0]->GetBone()[6].GetMtx(), CCharParts::PARTS_MAX);
			Parts[0]->SetBone_Mtx();

			if (SceneCreate(pModel, MODEL_PRIORITY))
			{
				pModel->Getpmtx() = &Parts[0]->GetBone()[6].GetMtx();
				pModel->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.4f, 0.0f), INIT_COLLAR, CSceneModel::MODEL_BOARD_G, CScene::DRAW_TYPE_NORMAL, false);
				switch (nCount)
				{
				case 0:	 pModel->BindTexture(CScene::Load(CScene::TEX_Board_C)); break;
				case 1:	 pModel->BindTexture(CScene::Load(CScene::TEX_Board_G)); break;
				case 2:	 pModel->BindTexture(CScene::Load(CScene::TEX_Board_T)); break;
				}
			}
		}
	}
	//BGMの再生
	CManager::GetSound()->Play(CSound::LABEL_SELECT000);

	return S_OK;
}

//=============================================================================
// セレクトの更新処理
//=============================================================================
void CSelect::Update(void)
{
	CInputKeyboard *pInputKey = CManager::GetInputKey();	//キーボード情報獲得
	CInputJoyPad	*pInputPad = CManager::GetInputJoyPad(0);	//ジョイパッド情報獲得

	CPlayer *pPlayer = CManager::GetPlayer(0);
	D3DXVECTOR3 Target;	// 選択時の目的地

	if (pInputKey->GetTrigger(DIK_TAB))
	{
		CRenderDraw::SetFade(CManager::MODE_SELECT, CRenderDraw::FADE_NORMAL, CRenderDraw::STATE_FADE_IN);
	}

	if (m_state == STATE_NONE)
	{
		if (m_nCntWorkState < 30)
		{
			m_nCntWorkState++;
			CCharacter::GetbWait() = true;
		}
		else
		{
			CCharacter::GetbWait() = false;

			m_nSelect = -1;	//初期化
			if ((pPlayer->Getpos().x > MAP_CHIP_SIZE * 0.5f) && (pPlayer->Getpos().x < MAP_CHIP_SIZE * 2.5f))
			{// 左2マス
				m_nSelect = 0;
			}
			else if ((pPlayer->Getpos().x > MAP_CHIP_SIZE * 3.5f) && (pPlayer->Getpos().x < MAP_CHIP_SIZE * 5.5f))
			{// 中央2マス
				m_nSelect = 1;
			}
			else if ((pPlayer->Getpos().x > MAP_CHIP_SIZE * 6.5f) && (pPlayer->Getpos().x < MAP_CHIP_SIZE * 8.5f))
			{// 右2マス
				m_nSelect = 2;
			}

			if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(INPUT_B))
			{
				if (m_state != STATE_NONE)
				{//決定したなら
					m_nCntWorkState = 0;
				}
				switch (m_nSelect)
				{
				case 0: m_state = STATE_CREDIT; break;
				case 1: m_state = STATE_GAME; break;
				case 2: m_state = STATE_TITLE; break;
				}
			}
		}//else 数F立ったなら
	}

	if (m_state != STATE_NONE)
	{
		m_nCntWorkState++;
		switch (m_nCntWorkState)
		{
		case FADE_TIME:
			switch (m_nSelect)
			{
			case 0:	CRenderDraw::SetFade(CManager::MODE_END_ROLL, CRenderDraw::FADE_ZOOM, CRenderDraw::STATE_FADE_IN); break;
			case 1:	CRenderDraw::SetFade(CManager::MODE_PRACTICE, CRenderDraw::FADE_ZOOM, CRenderDraw::STATE_FADE_IN); break;
			case 2:	CRenderDraw::SetFade(CManager::MODE_TITLE, CRenderDraw::FADE_ZOOM, CRenderDraw::STATE_FADE_IN); break;
			}
			break;
		default:
			if (m_state != STATE_NONE)
			{
				Target = (D3DXVECTOR3(MAP_CHIP_SIZE * (1.5f + 3.0f * m_nSelect), 0.0f, MAP_CHIP_SIZE * 2.0f) - pPlayer->Getpos()) * 0.05f;
				pPlayer->Getpos() += D3DXVECTOR3(Target.x, 0.0f, Target.z);
			}
			break;
		}
	}

	//敵の更新
	EnemyUpdate();

	if (pInputKey->GetTrigger(DIK_BACKSPACE))
	{
			CRenderDraw::SetFade(CManager::MODE_TITLE, CRenderDraw::FADE_ZOOM, CRenderDraw::STATE_FADE_IN);
	}
}
//=============================================================================
// 敵の更新処理
//=============================================================================
void	CSelect::EnemyUpdate(void)
{
	if (m_nCntWorkState > 60) { return; }

	for (int nCount = 0; nCount < MAX_MODE_SELECT; nCount++)
	{
		if (nCount == m_nSelect)
		{
			m_pEnemy[nCount]->SetNextMotion(CMotion::CHIKKUN_APPEAL);
		}
	}
}
//=============================================================================
// セレクトの終了処理
//=============================================================================
void CSelect::Uninit(void)
{
	//BGMのストップ
	CSound *pSound = CManager::GetSound();
	pSound->StopBGM();

	if (CManager::GetCamera() != NULL) { CManager::GetCamera()->Uninit(); }
	if (CManager::GetLight() != NULL) { CManager::GetLight()->Uninit(); }
}

//=============================================================================
// セレクトの状態変更処理
//=============================================================================
void CSelect::SetState(STATE state)
{
	CScene2D *pScene2D;

	if (m_state != state)
	{//通常状態なら
		m_state = state;

		switch (m_state)
		{
		case STATE_GAME:	// ゲームへ
			m_fCntState = 0.0f;
			if (SceneCreate(pScene2D, S2D_PRIORITY))
			{//画面を暗くする
				pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
					D3DX_PI, 0, 1, 1, 0.03f, CScene2D::STATE_FADEIN5, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), CScene2D::TEX_MAX);
			}
			break;
		case STATE_CREDIT:	// クレジットへ
			m_fCntState = 0.0f;
			if (SceneCreate(pScene2D, S2D_PRIORITY))
			{//画面を暗くする
				pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
					D3DX_PI, 0, 1, 1, 0.03f, CScene2D::STATE_FADEIN5, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), CScene2D::TEX_MAX);
			}
			break;
		case STATE_TITLE:	// タイトルへ
			m_fCntState = 0.0f;
			if (SceneCreate(pScene2D, S2D_PRIORITY))
			{//画面を暗くする
				pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
					D3DX_PI, 0, 1, 1, 0.03f, CScene2D::STATE_FADEIN5, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), CScene2D::TEX_MAX);
			}
			break;
		}
	}
}
