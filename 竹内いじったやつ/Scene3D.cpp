//=============================================================================
//
// ポリゴン処理 [Scene3D.cpp]
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
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
// 並び替え処理
//=============================================================================
void CScene3D::Sort(void)
{
	CScene *pScene;
	CScene **pSwap = new CScene*[CScene::GetnNumAll(S3D_PRIORITY)];
	float  *pfDistance = new float[CScene::GetnNumAll(S3D_PRIORITY)];
	int	   nCount = 0;
	pScene = CScene::GetTop(S3D_PRIORITY);
	while (pScene != NULL)
	{//NULLになるまで繰り返す
		//情報抜出
		nCount++;
		pScene = pScene->GetpNext();
	}



	delete[] pSwap;
	delete[] pfDistance;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene3D::Init(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	m_pVtxBuff = NULL;
	m_pTex = NULL;

	// 頂点情報の作成
	MakeVertex(pD3DDevice);

	m_DrawType = CScene::DRAW_TYPE_NORMAL;
	m_bBILLBoard = false;
	m_nNumCamera = -1;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene3D::Uninit(void)
{
	// 頂点バッファの開放;
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CScene::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene3D::Update(void)
{
	if (m_state != STATE_NORMAL)
	{
		D3DXVECTOR3 WKlength;	//計算用の長さ

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
			m_col.a = 1.0f - m_fCntState;//透明度変更
			m_length *= 1.0f + ((1.0f - m_fCntState) * 0.15f);
			SetColor(m_col);
			SetSize(m_length);
			break;
		case STATE_FADEIN:
			m_col.a += 0.05f;//透明度変更
			if (m_col.a > 1.0f) { m_col.a = 1.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;

		case STATE_FADEOUT:
			m_col.a -= m_fCntState;//透明度変更
			if (m_col.a <= 0.0f) 
			{ Uninit(); return; }
			SetColor(m_col);
			break;
		case STATE_FADEOUT2:
			m_col.a -= 0.05f;//透明度変更
			if (m_col.a < 0.0f) { m_col.a = 0.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_BFLOW_IN:
			if (m_col.a != 1.0f)
			{//透明度が足りない！
				m_col.a += 0.01f;//透明度変更
				if (m_col.a >= 1.0f) { m_col.a = 1.0f; }
				SetColor(m_col);
			}
			PlusUV(D3DXVECTOR2(0.002f, 0.001f));
			break;
		case STATE_BFLOW_OUT:
			if (m_col.a != 0.0f)
			{//透明度が足りない！
				m_col.a -= 0.01f;//透明度変更
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
		case STATE_LOCK_0:	//ゆらゆら拡大縮小
			m_fCntState += D3DX_PI * 0.0125f;
			WKlength = m_length * (1.0f + sinf(m_fCntState) * 0.25f);
			SetSize(WKlength);
			break;
		case STATE_LOCK_1:	//ギュン！と凝縮
			m_fCntState *= 0.75f;
			if (m_fCntState < 1.0f) { m_fCntState = 1.0f; m_state = STATE_NORMAL; }
			WKlength = m_length * m_fCntState;
			SetSize(WKlength);
			break;
		case STATE_HIT:
			m_pos.y += 0.5f;
			m_col.a -= m_fCntState;//透明度変更
			if (m_col.a <= 0.0f)
			{
				Uninit(); return;
			}
			SetColor(m_col);
			SetMtx();
			break;

		case STATE_FADEIN2:		// タイトル3Dのフェード　竹内追加
			m_col.a += m_fCntState;
			if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		}
	}
	if (m_state == STATE_CHECK)
	{//チェックポイント
	 //プレイヤーが存在
		CPlayer *&pPlayer = CManager::GetPlayer(0);
		if (pPlayer == NULL) { return; }
		//プレイヤーが近くにいれば
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
		{//近くにいるなら
			CSceneAnim3D *p3DAnim;

			CManager::GetSound()->Play(CSound::LABEL_PARIS);
			if (SceneCreate(p3DAnim, S3D_PRIORITY))
			{//エフェクト
				p3DAnim->Set(m_pos, m_rot, m_col, m_length, CScene::TEX_Disappear, false,
					CScene::DRAW_TYPE_OVERLAY, 0, 5, 2, 3, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_FADESPIN);
			}
			Uninit();
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CScene3D::Draw(void)
{
	if (m_nNumCamera == -1 || m_nNumCamera != CCamera_Manager::GetInfo().pCamera->GetnNumCamera())
	{//対応しているカメラなら
		LPDIRECT3DDEVICE9	pD3DDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得

		if (CScene::DrawPrepare(m_DrawType, pD3DDevice)) { return; }

		// ワールドマトリックスの設定
		if (m_bBILLBoard) { SetMtx(); }
		pD3DDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// 頂点バッファをデータストリームに設定
		pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pD3DDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		if (m_pTex != NULL)
		{//テクスチャの設定
			pD3DDevice->SetTexture(0, m_pTex);
		}//テクスチャ削除

		// ポリゴンの描画
		//アルファテスト処理(透明化による画像の切り取り現象を有効にする)
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 30);//REF = Reference:参照
		pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//FUNC = Function:機能 //GREATER = ～より大きい

		pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);    // 裏面をカリング

		pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		pD3DDevice->SetTexture(0, NULL);

		pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);    // 裏面をカリング
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void CScene3D::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 設定
//=============================================================================
void CScene3D::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length, TEXTURE nType, int nUV, int nUV_X, int nUV_Y, bool bBillBoard, DRAW_TYPE DrawType)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
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

			//頂点カラーの設定
			pVtx[0].col = m_col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
			pVtx[1].col = m_col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
			pVtx[2].col = m_col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
			pVtx[3].col = m_col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）

			//UVの設定
			pVtx[0].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X)				 , (nUV / nUV_X) * (1.0f / nUV_Y));
			pVtx[1].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
			pVtx[2].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X)				 , (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));
			pVtx[3].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	if (!m_bBILLBoard) { SetMtx(); }
}
//=============================================================================
// 色の設定
//=============================================================================
void	CScene3D::SetColor(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_col = col;

	//頂点カラーの設定
	pVtx[0].col = m_col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
	pVtx[1].col = m_col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
	pVtx[2].col = m_col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
	pVtx[3].col = m_col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 色の設定
//=============================================================================
void	CScene3D::SetSize(D3DXVECTOR3 length)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//値を代入
	//m_length = length;

	pVtx[0].pos = D3DXVECTOR3(-length.x, length.y, length.z);
	pVtx[1].pos = D3DXVECTOR3(length.x, length.y, length.z);
	pVtx[2].pos = D3DXVECTOR3(-length.x, -length.y, -length.z);
	pVtx[3].pos = D3DXVECTOR3(length.x, -length.y, -length.z);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
//==================================================================================================//
//    * 分割数からUV座標変更 *
//==================================================================================================//
void CScene3D::SetUV(int nUV, int nUV_X, int nUV_Y)
{
	//Vtxの変更
	VERTEX_3D *pVtx;		//頂点情報へのポインタ

							//頂点BUFFERをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標設定
	pVtx[0].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
	pVtx[1].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
	pVtx[2].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));
	pVtx[3].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));

	//頂点BUFFERをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// UVパターン化設定
//=============================================================================
void	CScene3D::SetUVPattern(float fUV_X, float fUV_Y)
{
	VERTEX_3D *pVtx;		//頂点情報へのポインタ

	//頂点BUFFERをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標設定
	//pVtx[0].tex = D3DXVECTOR2((m_pos.x + m_fLengthX) * fUV_X, (m_pos.z - m_fLengthZ) * fUV_Y);
	//pVtx[1].tex = D3DXVECTOR2((m_pos.x - m_fLengthX) * fUV_X, (m_pos.z + m_fLengthZ) * fUV_Y);
	//pVtx[2].tex = D3DXVECTOR2((m_pos.x + m_fLengthX) * fUV_X, (m_pos.z - m_fLengthZ) * fUV_Y);
	//pVtx[3].tex = D3DXVECTOR2((m_pos.x - m_fLengthX) * fUV_X, (m_pos.z + m_fLengthZ) * fUV_Y);

	pVtx[0].tex = D3DXVECTOR2((m_pos.x / m_length.x) * fUV_X, (m_pos.z / m_length.z) * fUV_Y);
	pVtx[1].tex = D3DXVECTOR2(((m_pos.x + m_length.x) / m_length.x) * fUV_X, ((m_pos.z / m_length.z) * fUV_Y));
	pVtx[2].tex = D3DXVECTOR2((m_pos.x / m_length.x) * fUV_X, ((m_pos.z + m_length.z) / m_length.z) * fUV_Y);
	pVtx[3].tex = D3DXVECTOR2(((m_pos.x + m_length.x) / m_length.x) * fUV_X, ((m_pos.z + m_length.z) / m_length.z) * fUV_Y);

	//頂点BUFFERをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// UV加算処理
//=============================================================================
void	CScene3D::PlusUV(D3DXVECTOR2 uv)
{
	VERTEX_3D *pVtx;		//頂点情報へのポインタ

							//頂点BUFFERをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標設定
	pVtx[0].tex += uv;
	pVtx[1].tex += uv;
	pVtx[2].tex += uv;
	pVtx[3].tex += uv;

	//頂点BUFFERをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// UV変更処理
//=============================================================================
void	CScene3D::SetUV(float fUV_X, float fUV_Y)
{
	//Vtxの変更
	VERTEX_3D *pVtx;		//頂点情報へのポインタ

							//頂点BUFFERをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / fUV_X, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / fUV_Y);
	pVtx[3].tex = D3DXVECTOR2(1.0f / fUV_X, 1.0f / fUV_Y);

	//頂点BUFFERをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// マトリックスワールドの計算処理
//=============================================================================
void CScene3D::SetMtx(void)
{
	LPDIRECT3DDEVICE9	pD3DDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxView;	//計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	if (m_bBILLBoard)
	{ //ビルボード
		pD3DDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//逆行列を設定
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
	{// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	}
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}
//=============================================================================
// じわっとフェード（竹内追加)
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
//// ポリゴンの移動(竹内追加)
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
//	{// センターまできたら移動ストップ
//		Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	}
//	else
//	{// センターに来るまでは移動
//		Move.x += 1.0f;
//		PolygonPos.x -= Move.x;
//	}
//}

//=============================================================================
// エフェクトの設定
//=============================================================================
void CSceneEffect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,TEXTURE nType, 
	int nUV, int nUV_X, int nUV_Y, bool bBillBoard, DRAW_TYPE DrawType, D3DXVECTOR3 *pPos, int nCNumber)
{
	CScene3D::Set(pos, rot, col, length, nType, nUV, nUV_X, nUV_Y, bBillBoard, DrawType);
	m_pPos = pPos;
	m_nCNumber = nCNumber;
}
//=============================================================================
// エフェクトの更新
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
// 描画処理
//=============================================================================
void CSceneEffect::Draw(void)
{
	if (CManager::GetCamera()->GetInfo().pCamera->GetnNumCamera() != m_nCNumber || m_nCNumber < 0)
	{//描画していいカメラなら
		CScene3D::Draw();
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CScene3DView::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 length, DRAW_TYPE DrawType)
{
	LPDIRECT3DDEVICE9	&pDevice = CManager::GetRenderer()->GetDevice();
	LPDIRECT3DSURFACE9	pRenderOrg;	//レンダラーの保管用
	LPDIRECT3DSURFACE9	pBuffOrg;	//バッファの保管用

	CScene3D::Set(pos, rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), length, CScene::TEX_MAX, 0, 1, 1, true, CScene::DRAW_TYPE_NORMAL);

	pDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 1,
		D3DUSAGE_RENDERTARGET, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, &m_pTextureMT, NULL);
	m_pTextureMT->GetSurfaceLevel(0, &m_pRenderMT);

	pDevice->CreateDepthStencilSurface(SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_D16,
		D3DMULTISAMPLE_NONE, 0, TRUE, &m_pBuffMT, NULL);

	pDevice->GetRenderTarget(0, &pRenderOrg);	//取得
	pDevice->GetDepthStencilSurface(&pBuffOrg);	//取得
	pDevice->SetRenderTarget(0, m_pRenderMT);	//テクスチャに割り当てる
	pDevice->SetDepthStencilSurface(m_pBuffMT);	//割り当て

	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	pDevice->SetRenderTarget(0, pRenderOrg);	//戻す
	pDevice->SetDepthStencilSurface(pBuffOrg);	//戻す
}
//=============================================================================
// 描画処理
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
// 描画処理
//=============================================================================
void	CScene3DView::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
// 描画処理
//=============================================================================
void	CScene3DView::Update(void)
{

}
//=============================================================================
// 描画処理
//=============================================================================
void	CScene3DView::Draw(void)
{
	LPDIRECT3DDEVICE9	&pDevice = CManager::GetRenderer()->GetDevice();
	LPDIRECT3DSURFACE9	pRenderOrg;	//レンダラーの保管用
	LPDIRECT3DSURFACE9	pBuffOrg;	//バッファの保管用
	D3DXMATRIX			mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX			mtxView;			//ビューマトリックス
	D3DVIEWPORT9		Viewport;
	CCamera *&pCamera = CCamera_Manager::GetInfo().pCamera;

	pDevice->GetRenderTarget(0, &pRenderOrg);	//取得
	pDevice->GetDepthStencilSurface(&pBuffOrg);	//取得
	pDevice->SetRenderTarget(0, m_pRenderMT);	//割り当て
	pDevice->SetDepthStencilSurface(m_pBuffMT);	//割り当て
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	Viewport = CCamera_Manager::GetInfo().pCamera->GetViewPort();
	pDevice->GetViewport(&m_viewportMT);
	mtxProjection = pCamera->GetMtxProjection();
	mtxView = pCamera->GetMtxView();

	pDevice->SetViewport(&m_viewportMT);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&mtxProjection);
	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(45.0f), (float)Viewport.Width / (float)Viewport.Height, 10.0f, 24800.0f);
	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&mtxView);
	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&mtxView, &pCamera->GetposV(), &pCamera->GetposR(), &pCamera->GetvecU());
	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);

	pDevice->SetTexture(0, CScene::Load(CScene::TEX_Number));
	CScene3D::Draw();

	pDevice->SetRenderTarget(0, pRenderOrg);	//戻す
	pDevice->SetDepthStencilSurface(pBuffOrg);	//戻す

	pDevice->SetTexture(0, m_pTextureMT);
	CScene3D::Draw();
}
//=============================================================================
// 設定
//=============================================================================
void CScene3DMove::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length, TEXTURE nType, int nUV, int nUV_X, int nUV_Y, bool bBillBoard, DRAW_TYPE DrawType,STATE state)
{
	CScene3D::Set(pos, rot,col, length, nType, nUV, nUV_X, nUV_Y, bBillBoard, DrawType);
	m_state = state;
}
//=============================================================================
// 更新処理
//=============================================================================
void	CScene3DMove::Update(void)
{
	D3DXVECTOR3 &PolygonPos = GetPosition();

	if (m_state == STATE_MOVE)
	{// 移動だったら
		if (PolygonPos.x <= 100.0f)
		{// センターまできたら移動ストップ
			m_move = INIT_VECTOR;
		}
		else
		{// センターに来るまでは移動
			m_move.x += 0.003f;
			PolygonPos.x -= m_move.x;
		}
	}
	SetMtx();
}
