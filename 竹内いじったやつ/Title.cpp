//=============================================================================
//
// タイトル処理 [Title.cpp]
// Author : 竹内亘
//
//=============================================================================
#include"Scene.h"
#include "manager.h"
#include "RenderDraw.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "Title.h"

#include "player.h"
#include "SceneModel.h"


//=============================================================================
// タイトルの初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	CMotion::Load();
	CCharacter::Load();

	CLight *pLight;			Create(pLight);		// ライトの生成
	CCamera_Play *pCamera;						
	pCamera = CCamera_Manager::Create_Play(0);	// カメラの生成

	pCamera->GetChar()->SetViewport(0, 0, 0, 0);
	pCamera->GetObj()->SetViewport(0, 0, 1280, 720);
	pCamera->GetObj()->GetposV() = D3DXVECTOR3(85.0f, 100.0f, -450.0f);
	pCamera->GetObj()->GetposR() = D3DXVECTOR3(85.0f, 100.0f, 0.0f);

	if (SceneCreate(m_pPlayer, CHAR_PRIORITY))
	{// プレイヤーの生成
		m_pPlayer->Set(D3DXVECTOR3(MAP_CHIP_SIZE * 1.0f, 500.0f, MAP_CHIP_SIZE * 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_PLAYER);
	}

	if (SceneCreate(m_apModel[0], 3))
	{// モデルの生成
		m_apModel[0]->Set(D3DXVECTOR3(MAP_CHIP_SIZE * -0.5f, 500.0f, MAP_CHIP_SIZE * 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_TITLE000, CScene::DRAW_TYPE_NORMAL, false);
	}
	if (SceneCreate(m_apModel[1], 3))
	{// モデルの生成
		m_apModel[1]->Set(D3DXVECTOR3(MAP_CHIP_SIZE * 0.5f, 500.0f, MAP_CHIP_SIZE * 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_TITLE001, CScene::DRAW_TYPE_NORMAL, false);
	}
	if (SceneCreate(m_apModel[2], 3))
	{// モデルの生成
		m_apModel[2]->Set(D3DXVECTOR3(MAP_CHIP_SIZE * 1.5f, 500.0f, MAP_CHIP_SIZE * 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_TITLE002, CScene::DRAW_TYPE_NORMAL, false);
	}
	if (SceneCreate(m_apModel[3], 3))
	{// モデルの生成
		m_apModel[3]->Set(D3DXVECTOR3(MAP_CHIP_SIZE * 2.5f, 500.0f, MAP_CHIP_SIZE * 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_TITLE003, CScene::DRAW_TYPE_NORMAL, false);
	}

	if (SceneCreate(m_pModel, 3))
	{//ミサイルの生成
		m_pModel->Set(D3DXVECTOR3(MAP_CHIP_SIZE * 7.0f, 30.0f, MAP_CHIP_SIZE * 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_MISSILE, CScene::DRAW_TYPE_NORMAL, false);
	}

	CMapChip *pMap;
	if (SceneCreate(pMap, MAP_PRIORYITY))
	{
		pMap->SampleMap();
		pMap->Load("data/TEXT/EDIT/Editor.txt");
	}

	if (SceneCreate(m_p3DLogo, 2))
	{// タイトル3D(あとから出てくるやつ)
		m_p3DLogo->Set(D3DXVECTOR3(100.0f, 200.0f, 200.0f),					// 位置
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),									// 向き
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),								// 色
			D3DXVECTOR3(200.0f, 200.0f, 0.0f),								// 長さ
			CScene::TEX_TITLE_3D,											// テクスチャ
			0, 1, 1,														// UV
			false,															// ビルボードかどうか
			CScene::DRAW_TYPE_NORMAL);										// 描画の種類
	}

	if (SceneCreate(m_p3DMoji, 2))
	{// PC
		m_p3DMoji->Set(D3DXVECTOR3(850.0f, 45.0f, 50.0f),					// 位置
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),									// 向き
			D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f),								// 色
			D3DXVECTOR3(200.0f, 10.0f, 0.0f),								// 長さ
			CScene::TEX_TITLE_MOJI,											// テクスチャ
			0, 1, 1,														// UV
			false,															// ビルボードかどうか
			CScene::DRAW_TYPE_NORMAL,										// 描画の種類
			CScene3D::STATE_MOVE);											// 使用状態						
	}

#if 0
	if (SceneCreate(m_p2DLogo, 6))
	{// タイトル3D(あとから出てくるやつ)
		m_p2DLogo->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100.0f, 0.0f),	// 位置
			300, 300,																	// X,Yの長さ
			D3DX_PI,																	// 向き
			0, 1, 1, 0.0f,																// UV
			CScene2D::STATE_NORMAL,														// 状態
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),											// 色
			CScene::TEX_TITLE_3D);														// テクスチャ
	}

	if (SceneCreate(m_p2DMoji, 6))
	{// PC	
		m_p2DMoji->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + 1000.0f, SCREEN_HEIGHT / 2 + 70.0f, 0.0f),	// 位置
			300, 20,																				// X,Yの長さ
			D3DX_PI,																				// 向き
			0, 1, 1, 0.0f,																			// UV
			CScene2D::STATE_NORMAL,																	// 状態
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),														// 色
			CScene::TEX_TITLE_MOJI);																// テクスチャ
	}
#endif

	CScene2D *p2D;

	if (SceneCreate(p2D, 6))
	{//プレスエニーボタン
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 8 * 7, 0.0f), SCREEN_WIDTH / 4, SCREEN_HEIGHT / 12, D3DX_PI, 0, 1, 1, 0.05f,
			CScene2D::STATE_FLASH, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CScene::TEX_Press);
	}

	//if (SceneCreate(p2D, 6))
	//{
	//	p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 3, 2, 2, 0.5f,
	//		CScene2D::STATE_FLOW2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), CScene::TEX_Fog000);
	//	p2D->BindDrawType(CScene::DRAW_TYPE_SUBTRACT);
	//}
	//m_fCntState = 0.0f;	//時間初期化

	////BGMの再生
	//CManager::GetSound()->Play(CSound::LABEL_TITLE000);
	return S_OK;
}
//=============================================================================
// タイトルの更新処理
//=============================================================================
void CTitle::Update(void)
{
	CSound *pSound = CManager::GetSound();
	CInputKeyboard *pInputKey = CManager::GetInputKey();	//キーボード情報獲得
	CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//ジョイパッド情報獲得
	CInputJoyPad	*pInputPad1 = CManager::GetInputJoyPad(1);	//ジョイパッド情報獲得

	m_fCntState += 1.0f;

	if (m_pPlayer->Getpos() == D3DXVECTOR3(MAP_CHIP_SIZE * 1.0f, 0.0f, MAP_CHIP_SIZE * 1.0f))
	{// プレイヤーが落ちてきたら
		for (int nCount = 0; nCount < MAX_MODEL; nCount++)
		{// モデル落下
			m_apModel[nCount]->Move();

			if (m_apModel[nCount]->GetPosition().y <= T_MODEL_MESSYHEIGHT)
			{// モデル落下が終わったら

				// ぐちゃぐちゃにする
				m_apModel[nCount]->Messy();
	
				m_nTime++;
				if (m_nTime >= 60 * 2)
				{// 文字が浮いてくる
					m_apModel[nCount]->Floating();
				}
				if (m_nTime >= 60 * 10)
				{// タイトル3Dが出てくる
					//m_p2DLogo->Fade(0.006f, CScene2D::STATE_FADEIN);
					m_p3DLogo->Fade(0.004f, CScene3D::STATE_FADEIN2);
				}
				if (m_nTime >= 60 * 17)
				{// 並べる
					m_apModel[0]->Set(D3DXVECTOR3(MAP_CHIP_SIZE * -0.5f, T_MODEL_LINEUPHEIGHT, MAP_CHIP_SIZE * 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_TITLE000, CScene::DRAW_TYPE_NORMAL, false);
					m_apModel[1]->Set(D3DXVECTOR3(MAP_CHIP_SIZE * 0.5f, T_MODEL_LINEUPHEIGHT, MAP_CHIP_SIZE * 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_TITLE001, CScene::DRAW_TYPE_NORMAL, false);
					m_apModel[2]->Set(D3DXVECTOR3(MAP_CHIP_SIZE * 1.5f, T_MODEL_LINEUPHEIGHT, MAP_CHIP_SIZE * 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_TITLE002, CScene::DRAW_TYPE_NORMAL, false);
					m_apModel[3]->Set(D3DXVECTOR3(MAP_CHIP_SIZE * 2.5f, T_MODEL_LINEUPHEIGHT, MAP_CHIP_SIZE * 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_TITLE003, CScene::DRAW_TYPE_NORMAL, false);
				}
			}
		}
		// ミサイルの移動
		m_pModel->Move();
	}

	//if ((pInputKey->GetTrigger(DIK_RETURN)))
	//{//セレクトへ
	//	CManager::GetSound()->Play(CSound::LABEL_RETURN);
	//	CRenderDraw::SetFade(CManager::MODE_SELECT, CRenderDraw::FADE_CRUMBLE, CRenderDraw::STATE_FADE_IN);
	//}

	//if (m_fCntState > 30.0f && CManager::GetRenderer()->GetReDraw()->GetState() == CRenderDraw::STATE_NONE)
	//{
	//	if ((pInputKey->GetAllTrigger() || pInputPad0->GetAllTrigger() || pInputPad1->GetAllTrigger()))
	//	{//セレクトへ
	//		CManager::GetSound()->Play(CSound::LABEL_RETURN);
	//		CRenderDraw::SetFade(CManager::MODE_SELECT, CRenderDraw::FADE_CRUMBLE, CRenderDraw::STATE_FADE_IN);
	//	}
	//	else if (m_fCntState > 360.0f) { CRenderDraw::SetFade(CManager::MODE_WATCH, CRenderDraw::FADE_NORMAL, CRenderDraw::STATE_FADE_IN); }
	//}
}
//=============================================================================
// タイトルの終了処理
//=============================================================================
void	CTitle::Uninit(void)
{
	////BGMのストップ
	//CManager::GetSound()->Stop(CSound::LABEL_TITLE000);
}