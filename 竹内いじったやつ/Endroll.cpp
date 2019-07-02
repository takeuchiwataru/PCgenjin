//=============================================================================
//
// エンドロール処理 [Endroll.cpp]
// Author : 竹内亘
//
//=============================================================================
#include"Scene.h"
#include "manager.h"
#include "RenderDraw.h"
#include "sound.h"
#include "camera.h"
#include "Endroll.h"

//=============================================================================
// エンドロールの初期化処理
//=============================================================================
HRESULT CEndroll::Init(void)
{
	CScene2D *p2D;

	if (SceneCreate(p2D, 6))
	{// エンドロールの画像
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),	// 位置
			450,SCREEN_HEIGHT / 2,											// X,Yの長さ
			D3DX_PI,														// 向き
			0, 1, 10, 0.5f,													// UV
			CScene2D::STATE_FLOW3,											// 状態
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),								// 色
			CScene::TEX_ENDROLL);											// テクスチャ
	}

	//if (SceneCreate(p2D, 6))
	//{//プレスエニーボタン
	//	p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 8 * 7, 0.0f), SCREEN_WIDTH / 4, SCREEN_HEIGHT / 12, D3DX_PI, 0, 1, 1, 0.05f,
	//		CScene2D::STATE_FLASH, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CScene::TEX_Press);
	//}
	//if (SceneCreate(p2D, 6))
	//{
	//	p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 3, 2, 2, 0.5f,
	//		CScene2D::STATE_FLOW2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), CScene::TEX_Fog000);
	//	p2D->BindDrawType(CScene::DRAW_TYPE_SUBTRACT);
	//}
	//m_fCntState = 0.0f;	//時間初期化

	//BGMの再生
	CManager::GetSound()->Play(CSound::LABEL_TITLE000);
	return S_OK;
}
//=============================================================================
// エンドロールの更新処理
//=============================================================================
void CEndroll::Update(void)
{
	CSound *pSound = CManager::GetSound();
	CInputKeyboard *pInputKey = CManager::GetInputKey();	//キーボード情報獲得
	CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//ジョイパッド情報獲得
	CInputJoyPad	*pInputPad1 = CManager::GetInputJoyPad(1);	//ジョイパッド情報獲得

	m_nTime++;

	//if ((pInputKey->GetTrigger(DIK_RETURN)))
	//{//セレクトへ
	//	//CManager::GetSound()->Play(CSound::LABEL_RETURN);
	//	//CRenderDraw::SetFade(CManager::MODE_SELECT, CRenderDraw::FADE_CRUMBLE, CRenderDraw::STATE_FADE_IN);
	//}

	if (m_nTime == 60 * MAX_SECONDS)
	{// 設定の秒数になったら
		CRenderDraw::SetFade(CManager::MODE_SELECT, CRenderDraw::FADE_CRUMBLE, CRenderDraw::STATE_FADE_IN);
	}


	//m_fCntState += 1.0f;
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
// エンドロールの終了処理
//=============================================================================
void	CEndroll::Uninit(void)
{
	//BGMのストップ
	CManager::GetSound()->Stop(CSound::LABEL_TITLE000);

}