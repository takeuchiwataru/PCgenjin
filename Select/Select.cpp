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
#include "SceneModel.h"
#include "mesh.h"
#include "dungeon.h"
#include "Font.h"
#include "MapChip.h"

#include "Select.h"
#include "CharSelect.h"
#include "camera.h"
#include "light.h"
#include "wind.h"
#include "sound.h"

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
	m_workState = STATE_NONE;
	m_fCntState = 0.0f;
	m_nCntWorkState = 0;

	CMotion::Load();
	CCharacter::Load();

	CLight *pLight;			Create(pLight);		//ライトの生成
	CWind_Manager *pWind;	Create(pWind);		//風の生成
	CCamera_Play	*pCamera;

	CPlayer *pPlayer;
	//CEnemy *pEnemy;

	pCamera = CCamera_Manager::Create_Play(0);
	pCamera->GetChar()->SetViewport(0, 0, 1280, 720);
	pCamera->GetObj()->SetViewport(0, 0, 1280, 720);
	pCamera->GetObj()->GetposV() = D3DXVECTOR3(1130.0f, 100.0f, 20.0f);
	pCamera->GetObj()->GetposR() = D3DXVECTOR3(1130.0f, 0.0f, 19.0f);

	if (SceneCreate(pPlayer, CHAR_PRIORITY))
	{//キャラ作成
		pPlayer->Set(D3DXVECTOR3(MAP_CHIP_SIZE * 1.0f, 0.0f, MAP_CHIP_SIZE * 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_PLAYER);
	}
	//if (SceneCreate(pEnemy, CHAR_PRIORITY))
	//{//キャラ作成
	//	pEnemy->Set(D3DXVECTOR3(MAP_CHIP_SIZE * 7.0f, 0.0f, MAP_CHIP_SIZE * 1.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CMotion::TYPE_ENEMY_0, CEnemy::TYPE_NONE, 1);
	//	pEnemy->SetAIState(TYPE_NORMAL, D3DXVECTOR3(MAP_CHIP_SIZE * 5.0f, 0.0f, MAP_CHIP_SIZE * 1.0f), D3DXVECTOR3(MAP_CHIP_SIZE * 8.0f, 0.0f, MAP_CHIP_SIZE * 1.0f));
	//}
	//if (SceneCreate(pEnemy, CHAR_PRIORITY))
	//{//キャラ作成
	//	pEnemy->Set(D3DXVECTOR3(MAP_CHIP_SIZE * 22.0f, 0.0f, MAP_CHIP_SIZE * 7.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CMotion::TYPE_ENEMY_0, CEnemy::TYPE_NONE, 1);
	//	pEnemy->SetAIState(TYPE_NORMAL, D3DXVECTOR3(MAP_CHIP_SIZE * 21.0f, 0.0f, MAP_CHIP_SIZE * 7.0f), D3DXVECTOR3(MAP_CHIP_SIZE * 23.0f, 0.0f, MAP_CHIP_SIZE * 7.0f));
	//}

	for (int nCount = 0; nCount < MAX_OPTION_SELECT; nCount++)
	{//Fontの初期化
		m_pFont[nCount] = NULL;
	}

	CMapChip *pMap;
	if (SceneCreate(pMap, MAP_PRIORYITY))
	{
		pMap->SampleMap();
		pMap->Load("data/TEXT/EDIT/Editor.txt");
	}

	return S_OK;
}

//=============================================================================
// セレクトの更新処理
//=============================================================================
void CSelect::Update(void)
{
	CInputKeyboard *pInputKey = CManager::GetInputKey();	//キーボード情報獲得
	CPlayer *pPlayer = CManager::GetPlayer(0);
	D3DXVECTOR3 Target;	// 選択時の目的地

	if (pInputKey->GetTrigger(DIK_TAB))
	{
		CRenderDraw::SetFade(CManager::MODE_SELECT, CRenderDraw::FADE_NORMAL, CRenderDraw::STATE_FADE_IN);
	}

	if (m_state == STATE_NONE)
	{
		if (pInputKey->GetTrigger(DIK_RETURN))
		{
			if ((pPlayer->Getpos().x > MAP_CHIP_SIZE * 0.5f) && (pPlayer->Getpos().x < MAP_CHIP_SIZE * 2.5f))
			{// 左2マス
				m_workState = STATE_GAME;
			}
			else if ((pPlayer->Getpos().x > MAP_CHIP_SIZE * 3.5f) && (pPlayer->Getpos().x < MAP_CHIP_SIZE * 5.5f))
			{// 中央2マス
				m_workState = STATE_CREDIT;
			}
			else if ((pPlayer->Getpos().x > MAP_CHIP_SIZE * 6.5f) && (pPlayer->Getpos().x < MAP_CHIP_SIZE * 8.5f))
			{// 右2マス
				m_workState = STATE_TITLE;
			}
		}
	}

	switch (m_workState)
	{
	case STATE_NONE:	// 通常
		break;
	case STATE_GAME:	// ゲーム
		m_nCntWorkState++;
		switch (m_nCntWorkState)
		{
		case 180:
			SetState(STATE_GAME);
			break;
		case 300:
			CRenderDraw::SetFade(CManager::MODE_GAME, CRenderDraw::FADE_NORMAL, CRenderDraw::STATE_FADE_IN);
			break;
		default:
			if (m_workState != m_state)
			{
				Target = (D3DXVECTOR3(MAP_CHIP_SIZE * 1.5f, 0.0f, MAP_CHIP_SIZE * 2.0f) - pPlayer->Getpos()) * 0.05f;
				pPlayer->Getpos() += D3DXVECTOR3(Target.x, 0.0f, Target.z);
			}
			break;
		}
		break;
	case STATE_CREDIT:	// クレジット
		m_nCntWorkState++;
		switch (m_nCntWorkState)
		{
		case 180:
			SetState(STATE_CREDIT);
			break;
		case 300:
			CRenderDraw::SetFade(CManager::MODE_SELECT, CRenderDraw::FADE_NORMAL, CRenderDraw::STATE_FADE_IN);
			break;
		default:
			if (m_workState != m_state)
			{
				Target = (D3DXVECTOR3(MAP_CHIP_SIZE * 4.5f, 0.0f, MAP_CHIP_SIZE * 2.0f) - pPlayer->Getpos()) * 0.05f;
				pPlayer->Getpos() += D3DXVECTOR3(Target.x, 0.0f, Target.z);
			}
			break;
		}
		break;
	case STATE_TITLE:	// タイトル
		m_nCntWorkState++;
		switch (m_nCntWorkState)
		{
		case 180:
			SetState(STATE_TITLE);
			break;
		case 300:
			CRenderDraw::SetFade(CManager::MODE_TITLE, CRenderDraw::FADE_NORMAL, CRenderDraw::STATE_FADE_IN);
			break;
		default:
			if (m_workState != m_state)
			{
				Target = (D3DXVECTOR3(MAP_CHIP_SIZE * 7.5f, 0.0f, MAP_CHIP_SIZE * 2.0f) - pPlayer->Getpos()) * 0.05f;
				pPlayer->Getpos() += D3DXVECTOR3(Target.x, 0.0f, Target.z);
			}
			break;
		}
		break;
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

	for (int nCount = 0; nCount < MAX_GAME_PAUSE; nCount++)
	{//全ポーズの破棄
		if (m_pScene2D[nCount] != NULL)
		{//生成されていれば削除
			m_pScene2D[nCount]->Uninit();
			m_pScene2D[nCount] = NULL;
		}
	}

	CManager::GetCamera()->Uninit();
	CManager::GetLight()->Uninit();
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
