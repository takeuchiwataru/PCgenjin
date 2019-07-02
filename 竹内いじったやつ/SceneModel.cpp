//=============================================================================
//
// ポリゴン処理 [Scene3D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include"Scene.h"
#include"SceneModel.h"
#include "SceneAnim3D.h"
#include "player.h"
#include "dungeon.h"
#include "MapChip.h"
#include "Game.h"
#include"mesh.h"
#include"Renderer.h"
#include "manager.h"
#include "camera.h"
#include "light.h"
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
CSceneModel::MODEL_DRAW *CSceneModel::m_Model_Draw[MODEL_MAX] = {};	//モデルへのポインタ

//==================================================================================================//
//    * モデル生成関数 *
//==================================================================================================//
void	CSceneModel::LoadModel(MODEL model, LPDIRECT3DTEXTURE9 &tex)
{
	if (model < MODEL_MAX)
	{//範囲確認
		switch (model)
		{
		case MODEL_FENCE:		tex = Load(TEX_Fence);		break;
		case MODEL_BOX:			tex = Load(TEX_Fence);		break;
		case MODEL_STONE:		tex = Load(TEX_Stone);		break;
		case MODEL_STONE_S:		tex = Load(TEX_Stone);		break;
		case MODEL_STEEL:		tex = Load(TEX_Steel);		break;
		case MODEL_STEEL_B:		tex = Load(TEX_Steel);		break; 
		case MODEL_STONE_M:		tex = Load(TEX_Stone_M);	break;
		case MODEL_COLUMN:		tex = Load(TEX_Fence);		break;
		case MODEL_SATELLITE:	tex = Load(TEX_Satellite);	break;
		case MODEL_Gate:		tex = Load(TEX_Steel);		break; 
		case MODEL_Potion:		tex = Load(TEX_Steel);		break;
		case MODEL_UI_WOOD:		tex = Load(TEX_UI_Wood);	break;
		case MODEL_POS_MAG:		tex = Load(TEX_Pos_Mag);	break; 
		case MODEL_POS_NEE:		tex = Load(TEX_Pos_Nee);	break;
		//case MODEL_Earth:		tex = Load(TEX_Pos_Nee);	break;
		case MODEL_SELECTMAP0:	tex = Load(TEX_SelectMap);	break;
		//case Axe_000:		tex = Load(TEX_Sword);		break;
		case MODEL_SPEAR:		tex = Load(TEX_Spear);		break;

		case MODEL_TITLE000:	tex = Load(TEX_TITLE_MODEL);		break;	//追加
		case MODEL_TITLE001:	tex = Load(TEX_TITLE_MODEL);		break;	//追加
		case MODEL_TITLE002:	tex = Load(TEX_TITLE_MODEL);		break;	//追加
		case MODEL_TITLE003:	tex = Load(TEX_TITLE_MODEL);		break;	//追加
		case MODEL_MISSILE:		tex = Load(TEX_MISSILE);			break;	//追加
		}

		if (m_Model_Draw[model] == NULL)
		{//読み込んでないなら
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			char	aStr[64];
			m_Model_Draw[model] = new MODEL_DRAW;
			switch (model)
			{//読み込み
			case MODEL_FENCE:		strcpy(&aStr[0], "data/MODEL/OBJECT/Fence.x");			break;
			case MODEL_BOX:			strcpy(&aStr[0], "data/MODEL/OBJECT/Box.x");			break; 
			case MODEL_STONE:		strcpy(&aStr[0], "data/MODEL/OBJECT/stone.x");			break;
			case MODEL_STONE_S:		strcpy(&aStr[0], "data/MODEL/OBJECT/stone_S.x");		break;
			case MODEL_STEEL:		strcpy(&aStr[0], "data/MODEL/OBJECT/steel.x");			break;
			case MODEL_STEEL_B:		strcpy(&aStr[0], "data/MODEL/OBJECT/steel_block.x");	break;
			case MODEL_COLUMN:		strcpy(&aStr[0], "data/MODEL/OBJECT/Column.x");			break;
			case MODEL_STONE_M:		strcpy(&aStr[0], "data/MODEL/OBJECT/stone_M.x");		break;
			case MODEL_Gate:		strcpy(&aStr[0], "data/MODEL/OBJECT/Portal.x");			break;
			case MODEL_Potion:		strcpy(&aStr[0], "data/MODEL/ITEM/Potion000.x");		break;
			case MODEL_SATELLITE:	strcpy(&aStr[0], "data/MODEL/EFFECT/Satellite.x");		break; 
			case MODEL_UI_WOOD:		strcpy(&aStr[0], "data/MODEL/EFFECT/UI_Wood.x");		break;
			case MODEL_POS_MAG:		strcpy(&aStr[0], "data/MODEL/EFFECT/Position_Magnetic000.x");	break; 
			case MODEL_POS_NEE:		strcpy(&aStr[0], "data/MODEL/EFFECT/Position_Needle000.x");		break; 
			case MODEL_Earth:		strcpy(&aStr[0], "data/MODEL/shadow000.x");		break; 
			case MODEL_SELECTMAP0:	strcpy(&aStr[0], "data/MODEL/OBJECT/CharSelect_Map.x");	break;
			case MODEL_AXE:			strcpy(&aStr[0], "data/MODEL/WEAPON/axe.x");		break; 
			case MODEL_SPEAR:		strcpy(&aStr[0], "data/MODEL/WEAPON/Spear000.x");		break;
			case MODEL_TITLE000:	strcpy(&aStr[0], "data/MODEL/OBJECT/TITLE/title000.x");		break;	// 竹内追加
			case MODEL_TITLE001:	strcpy(&aStr[0], "data/MODEL/OBJECT/TITLE/title001.x");		break;	// 竹内追加
			case MODEL_TITLE002:	strcpy(&aStr[0], "data/MODEL/OBJECT/TITLE/title002.x");		break;	// 竹内追加
			case MODEL_TITLE003:	strcpy(&aStr[0], "data/MODEL/OBJECT/TITLE/title003.x");		break;	// 竹内追加
			case MODEL_MISSILE:		strcpy(&aStr[0], "data/MODEL/OBJECT/TITLE/missile.x");		break;	// 竹内追加
			case MODEL_BLOC00:		strcpy(&aStr[0], "data/MODEL/CHIP/Block000.x");		break;
			case MODEL_BRIDGE00:	strcpy(&aStr[0], "data/MODEL/CHIP/Bridge000.x");	break;
			case MODEL_STAIRS00:	strcpy(&aStr[0], "data/MODEL/CHIP/Stairs000.x");	break;
			}
			D3DXLoadMeshFromX(&aStr[0], D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
		}
	}
}
//==================================================================================================//
//    * モデル生成関数 *
//==================================================================================================//
void	CSceneModel::UnLoadModel(void)
{
	for (int nCount = 0; nCount < MODEL_MAX; nCount++)
	{
		if (m_Model_Draw[nCount] != NULL)
		{
			// メッシュの開放
			if (m_Model_Draw[nCount]->MeshModel != NULL)
			{
				m_Model_Draw[nCount]->MeshModel->Release();
				m_Model_Draw[nCount]->MeshModel = NULL;
			}

			// マテリアルの開放
			if (m_Model_Draw[nCount]->pBuffMatModel != NULL)
			{
				m_Model_Draw[nCount]->pBuffMatModel->Release();
				m_Model_Draw[nCount]->pBuffMatModel = NULL;
			}
			delete m_Model_Draw[nCount]; m_Model_Draw[nCount] = NULL;
		}
	}
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT	CSceneModel::Init(void)
{
	m_DrawType = CScene::DRAW_TYPE_NORMAL;
	m_pTex = NULL;
	m_fCntState = 0.0f;
	m_Model = MODEL_MAX;

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void	CSceneModel::Update(void)
{
	switch (m_state)
	{
	case STATE_FADEIN:	//だんだん明るく
		m_col.a += 0.03f;
		if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_NORMAL; }
		break;
	case STATE_FADEOUT:	//だんだん暗く
		m_col.a -= 0.03f;
		if (m_col.a <= 0.0f) { Uninit(); return; }
		break;
	case STATE_FADE:	//だんだん明るく->暗くなり消える
		m_col.a += 0.03f;
		if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_FADEOUT; }
		break;	
	}
}

//=============================================================================
// マトリックス設定処理
//=============================================================================
void	CSceneModel::SetMtx(void)
{
	D3DXMATRIX			mtxRot, mtxTrans;		//計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}
//=============================================================================
// 描画処理
//=============================================================================
void	CSceneModel::Draw(void)
{
	if (m_Model != MODEL_MAX)
	{
		D3DXVECTOR3 length;
		GetLength(m_Model, length);
		if (CManager::GetCamera()->DrawCheck(m_pos, powf(length.x, 2) + powf(length.z, 2)) || length.x == 0.0f)
		{
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();

			if (CScene::DrawPrepare(m_DrawType, pD3DDevice)) { return; }

			// ワールドマトリックスの設定
			pD3DDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

			if (m_pTex != NULL)
			{//テクスチャの設定
				pD3DDevice->SetTexture(0, m_pTex);
			}
			DrawModel(m_Model, m_col);

			//CSceneModel::SetShadow();
			//CScene::DrawPrepare(CScene::DRAW_TYPE_SUBTRACT, pD3DDevice);
			//pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			//DrawModel();
			//pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}
}
//=============================================================================
// モデル描画処理
//=============================================================================
void	CSceneModel::DrawModel(CSceneModel::MODEL &model, D3DXCOLOR &col)
{
	LPDIRECT3DDEVICE9		pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX WKmtx;
	D3DXMATRIX m_Mtx;
	D3DXCOLOR WKcol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//モデルの拡大
	pDevice->GetTransform(D3DTS_WORLD, &m_Mtx);
	WKmtx = m_Mtx;

	WKmtx._44 = OUT_LINE;
	WKmtx._41 = WKmtx._41 * WKmtx._44;
	WKmtx._42 = WKmtx._42 * WKmtx._44;
	WKmtx._43 = WKmtx._43 * WKmtx._44;

	//アウトラインの描画
	pDevice->SetTransform(D3DTS_WORLD, &WKmtx);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//DrawModelOne(model, WKcol);

	//通常描画
	pDevice->SetTransform(D3DTS_WORLD, &m_Mtx);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0x0000000F);
	DrawModelOne(model, col);
}
//=============================================================================
// モデル描画処理
//=============================================================================
void	CSceneModel::DrawModelOne(CSceneModel::MODEL &model, D3DXCOLOR &col)
{
	LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
	D3DMATERIAL9		matDef;					//現在のマテリアル保存用
	D3DXMATERIAL		*pMat;					//マテリアルデータへのポインタ

												// 現在のマテリアルを取得
	pD3DDevice->GetMaterial(&matDef);
	pMat = (D3DXMATERIAL*)m_Model_Draw[model]->pBuffMatModel->GetBufferPointer();

	// マテリアルの設定
	pMat = (D3DXMATERIAL*)m_Model_Draw[model]->pBuffMatModel->GetBufferPointer();

	// マテリアルデータへのポインタを取得
	for (int nCountData = 0; nCountData < (int)m_Model_Draw[model]->nNumMatModel; nCountData++)
	{
		pMat[nCountData].MatD3D.Diffuse = col; //透明度設定
		pD3DDevice->SetMaterial(&pMat[nCountData].MatD3D);
		// モデル(パーツ)の描画
		m_Model_Draw[model]->MeshModel->DrawSubset(nCountData);
	}

	// マテリアルをデフォルトに戻す
	pD3DDevice->SetMaterial(&matDef);
	pD3DDevice->SetTexture(0, NULL);
}
//=============================================================================
// 設定処理
//=============================================================================
void	CSceneModel::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL model, DRAW_TYPE DrawType, bool bHit)
{
	m_pos = pos;
	m_rot = rot;
	m_col = col;
	m_Model = model;
	m_DrawType = DrawType;
	
	//モデルのあたり判定の有無
	if(!bHit){ CScene::SetObjType(OBJTYPE_OBJ_NO); }

	//モデルと画像生成
	LoadModel(m_Model, m_pTex);
	SetMtx();
}
//=============================================================================
// モデルの大きさを獲得
//=============================================================================
void	CSceneModel::GetLength(MODEL model, D3DXVECTOR3 &length)
{
	switch (model)
	{
	case MODEL_FENCE:	length = D3DXVECTOR3(10.0f, 50.0f, 50.0f);		return;
	case MODEL_BOX:		length = D3DXVECTOR3(40.0f, 40.0f, 40.0f);		return;
	case MODEL_STONE:	length = D3DXVECTOR3(100.0f, 400.0f, 100.0f);	return;
	case MODEL_STONE_S:	length = D3DXVECTOR3(35.0f, 35.0f, 25.0f);		return;
	case MODEL_STEEL:	length = D3DXVECTOR3(35.0f, 20.0f, 65.0f);		return;
	case MODEL_STEEL_B:	length = D3DXVECTOR3(100.0f, 100.0f, 100.0f);	return;
	case MODEL_STONE_M:	length = D3DXVECTOR3(210.0f, 75.0f, 210.0f);	return;
	case MODEL_COLUMN:	length = D3DXVECTOR3(20.0f, 150.0f, 20.0f);		return;
	case MODEL_BLOC00:	
	case MODEL_BRIDGE00:
	case MODEL_STAIRS00:

		length = D3DXVECTOR3(MAP_CHIP_SIZE, 0.0f, MAP_CHIP_SIZE) * 0.5f;		return;

	}
	length = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// セット時の高さを獲得
//=============================================================================
float	CSceneModel::GetHeight(MODEL model)
{
	switch (model)
	{
	case MODEL_FENCE:
	case MODEL_BOX:
	case MODEL_STONE:
	case MODEL_STONE_S:
	case MODEL_STEEL:
	case MODEL_STEEL_B:
		return 0.0f;
	case MODEL_Gate:	return 300.0f;
	case MODEL_Earth:	return 50.0f;
	}
	return 0.0f;
}
//=============================================================================
//影の描画
//=============================================================================
void CSceneModel::SetShadow(void)
{
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	//デバイスの取得

																		// ワールドマトリックスの設定
	D3DXMATRIX	mtxShadow;
	D3DXMATRIX	WKmtx;
	D3DXPLANE	planeField;
	D3DXVECTOR4	vecLight;
	D3DXVECTOR3	pos, posold, WKpos, normal;
	bool		WKbJump = false;
	int			nWKCount = 0;
	D3DLIGHT9 &light = CManager::GetLight()->Getlight(0);

	// シャドウマトリックスの初期化
	D3DXMatrixIdentity(&mtxShadow);

	pDevice->GetTransform(D3DTS_WORLD, &WKmtx);
	vecLight = D3DXVECTOR4(-light.Direction.x, -light.Direction.y, -light.Direction.z, 0.0f);
	pos = D3DXVECTOR3(WKmtx._41, -99999.0f, WKmtx._43);
	posold = D3DXVECTOR3(0.0f, WKmtx._42, 0.0f);
	WKpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	//起伏に合わせる
	CMesh::MeshCollisionField(pos, posold, WKpos, WKpos, WKpos, WKbJump);
	//CSceneObjct::CollisionAll(pos, posold, WKpos, WKpos, WKpos, nWKCount, WKbJump, false);	//オブジェクト
	pos = D3DXVECTOR3(0.0f, pos.y + 1.0f, 0.0f);
	//pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//影板生成
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	//影を目的の物体にくっ付ける
	D3DXMatrixMultiply(&WKmtx, &WKmtx, &mtxShadow);
	pDevice->SetTransform(D3DTS_WORLD, &WKmtx);
}
//=============================================================================
// 設定処理
//=============================================================================
void	CSceneObjct::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL model, bool bHit, USE use)
{
	CMesh_Cylinder *pCylinder;

	CScene::SetObjType(OBJTYPE_OBJ);
	CSceneModel::Set(pos, rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), model, CScene::DRAW_TYPE_NORMAL, bHit);
	m_use = use;
	m_fLife = -1.0f;
	switch (model)
	{
	case MODEL_STONE:	m_fLife = 5.0f;		break;
	case MODEL_BOX:		m_fLife = 1.5f;		break;
	case MODEL_Potion:	
		if (SceneCreate(pCylinder, CYLINDER_PRIORITY))
		{//武器シリンダー生成
			pCylinder->Set(pos - D3DXVECTOR3(0.0f, 200.0f, 0.0f), 8, 400.0f, 40.0f, 0.0f
				, 0.0f, CMesh_Cylinder::STATE_NORSPIN, 0, CIRCLE_HEIGHT, CScene::TEX_Circle, NULL, &GetbDeath());
			pCylinder->GetDrawType() = CScene::DRAW_TYPE_ADD;
			pCylinder->GetCol().a = 0.25f;
		}
		break;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void	CSceneObjct::Update(void)
{
	D3DXCOLOR &col = GetColor();
	CSceneModel::STATE &state = GetState();
	D3DXVECTOR3 WKpos;

	switch (state)
	{
	case STATE_FADEIN:	//だんだん明るく
		col.a += 0.03f;
		if (col.a >= 1.0f) { col.a = 1.0f; state = STATE_NORMAL; }
		break;
	case STATE_FADEOUT:	//だんだん暗く
		col.a -= 0.03f;
		if (col.a <= 0.0f) { Uninit(); return; }
		break;
	case STATE_FADE:	//だんだん明るく->暗くなり消える
		col.a += 0.03f;
		if (col.a >= 1.0f) { col.a = 1.0f; state = STATE_FADEOUT; }
		break;
	case STATE_DAMAGE:
		col += D3DXCOLOR(0.0f, 0.03f, 0.03f, 0.0f);
		if (col.g >= 1.0f)
		{//演出終了
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (m_fLife <= 0.0f)
			{
				state = STATE_DESTROY;
				CManager::GetSound()->Play(CSound::LABEL_OVER);
			}
			else { state = STATE_NORMAL; }
		}
		WKpos = GetPosition();
		GetPosition() += D3DXVECTOR3((float)(rand() % 100), 0.0f, (float)(rand() % 100)) * (col.g - 1.0f) - D3DXVECTOR3(50.0f, 0.0f, 50.0f) * (col.g - 1.0f);
		SetMtx();
		GetPosition() = WKpos;
		break;
	case STATE_DESTROY:
		col.a -= 0.03f;
		if (col.a <= 0.0f) { DropUninit(); return; }
		WKpos = GetPosition();
		GetPosition() += D3DXVECTOR3((float)(rand() % 100), 0.0f, (float)(rand() % 100)) * (col.g - 1.0f) - D3DXVECTOR3(50.0f, 0.0f, 50.0f) * (col.g - 1.0f);
		SetMtx();
		GetPosition() = WKpos;
		break;
	}
	if (m_use != USE_NORMAL)
	{
		float fDistance[MAX_PLAYER] = { 5000.0f, 5000.0f };
		bool bHit = false;
		D3DXVECTOR3 &m_pos = GetPosition();
		CMesh_Cylinder *pCylinder;
		CPlayer *pPlayer0 = CManager::GetPlayer(0);
		CPlayer *pPlayer1 = CManager::GetPlayer(1);
		if (pPlayer0 != NULL) { fDistance[0] = powf(pPlayer0->Getpos().x - m_pos.x, 2) + powf(pPlayer0->Getpos().z - m_pos.z, 2); }
		if (pPlayer1 != NULL) { fDistance[1] = powf(pPlayer1->Getpos().x - m_pos.x, 2) + powf(pPlayer1->Getpos().z - m_pos.z, 2); }

		switch (m_use)
		{
		case USE_GATE:
			if (fDistance[0] <= 40.0f * 40.0f || fDistance[1] <= 40.0f * 40.0f)
			{//マップ切り替え
				m_use = USE_NORMAL;
				CManager::GetGame()->GetTime()->GetpNumber()->AddNumber(60);
				CManager::GetpDungeon()->ChangeMap(CDungeon::TYPE_BOSS);
			}
			break;
		case USE_LIFE_HEEL:
			GetRotation().y += D3DX_PI * 0.01f;
			SetMtx();
			if (fDistance[0] <= 40.0f * 40.0f) { bHit = true; }
			else if (fDistance[1] <= 40.0f * 40.0f) { pPlayer0 = pPlayer1; bHit = true; }

			if (bHit)
			{//当たった！
				CManager::GetSound()->Play(CSound::LABEL_LHeel);
				pPlayer0->Heel(pPlayer0->GetfMaxLife() * 0.7f);
				CManager::GetGame()->GetTime()->GetpNumber()->AddNumber(10);

				if (SceneCreate(pCylinder, CYLINDER_PRIORITY))
				{//武器シリンダー生成
					pCylinder->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 100.0f, -40.0f, 0.0f
						, 0.01f, CMesh_Cylinder::STATE_NORSPIN, 0, CIRCLE_HEIGHT, CScene::TEX_Circle, &pPlayer0->GetMtx(), NULL);
					pCylinder->GetDrawType() = CScene::DRAW_TYPE_ADD;
					pCylinder->GetCol().a = 1.0f;
				}
				Uninit();
				CMeshOrbit::Delete();
			}
			break;
		case USE_EXP_HEEL:
			GetRotation().y += D3DX_PI * 0.01f;
			SetMtx();
			if (fDistance[0] <= 40.0f * 40.0f) { bHit = true; }
			else if (fDistance[1] <= 40.0f * 40.0f) { pPlayer0 = pPlayer1; bHit = true; }

			if (bHit)
			{//当たった！
				CManager::GetSound()->Play(CSound::LABEL_EHeel);
				CManager::GetGame()->GetTime()->GetpNumber()->AddNumber(10);
				pPlayer0->Heel(pPlayer0->GetfMaxLife() * 0.25f); 
				pPlayer0->GetfExp() += 3000.0f;
				if (SceneCreate(pCylinder, CYLINDER_PRIORITY))
				{//武器シリンダー生成
					pCylinder->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 100.0f, -40.0f, 0.0f
						, 0.01f, CMesh_Cylinder::STATE_NORSPIN, 3, CIRCLE_HEIGHT, CScene::TEX_Circle, &pPlayer0->GetMtx(), NULL);
					pCylinder->GetDrawType() = CScene::DRAW_TYPE_ADD;
					pCylinder->GetCol().a = 1.0f;
				}
				Uninit();
				CMeshOrbit::Delete();
			}
			break;
		}
	}
}
//=============================================================================
// オブジェごとの終了処理
//=============================================================================
void	CSceneObjct::DropUninit(void)
{
	CSceneObjct *pObject;

	switch (GetModel())
	{
	case MODEL_BOX:
		if (SceneCreate(pObject, MODEL_PRIORITY))
		{
			if (rand() % 3 == 0)
			{//経験値アイテム
				pObject->Set(GetPosition() + D3DXVECTOR3(0.0f, 50.0f, 0.0f), GetRotation() + D3DXVECTOR3(D3DX_PI * 0.1f, 0.0f, 0.0f)
					, CSceneModel::MODEL_Potion, false, CSceneObjct::USE_EXP_HEEL);
				pObject->BindTexture(CScene::Load(CScene::TEX_Potion_E));
			}
			else
			{//回復アイテム
				pObject->Set(GetPosition() + D3DXVECTOR3(0.0f, 50.0f, 0.0f), GetRotation() + D3DXVECTOR3(D3DX_PI * 0.1f, 0.0f, 0.0f)
					, CSceneModel::MODEL_Potion, false, CSceneObjct::USE_LIFE_HEEL);
					pObject->BindTexture(CScene::Load(CScene::TEX_Potion_L));
			}
		}
		break;
	}
	CSceneModel::Uninit();
}
//=============================================================================
//ダメージ処理
//=============================================================================
void	CSceneObjct::Damage(float fDamage)
{
	m_fLife -= fDamage;
	if (m_fLife <= 0.0f)
	{//LIFE0以下
		m_fLife = 0.0f;
	}
	CManager::GetSound()->Play(CSound::LABEL_HIT000);

	GetColor() = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
	GetState() = STATE_DAMAGE;
}
//=============================================================================
//あたり判定 オブジェクトを探す
//=============================================================================
bool	CSceneObjct::CollisionAll(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection)
{
	bool bLand = false;
	int nCount = nCntHit;
	CScene *pScene = CScene::GetTop(MODEL_PRIORITY);
	while (pScene != NULL)
	{//終わるまで
		if (pScene->GetObjType() == OBJTYPE_OBJ)
		{//メッシュ発見
			bLand = ((CSceneObjct*)pScene)->Collision(pos, posold, move, length, FNor, nCntHit, bJump, bReflection);
		}
		pScene = pScene->GetpNext();
	}

	return bLand;
}
//=============================================================================
//あたり判定
//=============================================================================
bool	CSceneObjct::Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection)
{
	bool bLand = false;
	CSceneModel::MODEL WKmodel = GetModel();
	D3DXVECTOR3 lengthX; GetLength(GetModel(), lengthX);	//モデルの幅獲得
	D3DXVECTOR3 m_pos = GetPosition();
	float fDistance = powf(lengthX.x, 2) + powf(lengthX.z, 2);	//原点から頂点までの距離獲得
	if (powf(m_pos.x - pos.x, 2) + powf(m_pos.z - pos.z, 2) < (fDistance + length.x * length.x) * 2.0f || !bReflection)
	{//範囲内なら
		bReflection = true;
		fDistance = sqrtf(fDistance);
		int  nHit;
		float fHeight = pos.y;
		float fWKLength = 0.0f;
		float m_frot = GetRotation().y;
		float fRot = atan2f(lengthX.x, lengthX.z);			//頂点の角度を求める
		D3DXVECTOR3 WKnor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 WKpos = pos;
		D3DXVECTOR3 Vtx[8];										//判定用8頂点用意
		bool bJudge = false;

		//左上, 右上, 左下, 右下の順
		Vtx[2] = D3DXVECTOR3(sinf(m_frot - fRot), 0.0f, cosf(m_frot - fRot)) * fDistance + m_pos;
		Vtx[3] = D3DXVECTOR3(sinf(m_frot + fRot), 0.0f, cosf(m_frot + fRot)) * fDistance + m_pos;
		Vtx[1] = D3DXVECTOR3(sinf(m_frot + fRot + D3DX_PI), 0.0f, cosf(m_frot + fRot + D3DX_PI)) * fDistance + m_pos;
		Vtx[0] = D3DXVECTOR3(sinf(m_frot - fRot + D3DX_PI), 0.0f, cosf(m_frot - fRot + D3DX_PI)) * fDistance + m_pos;

		Vtx[6] = Vtx[2] + D3DXVECTOR3(sinf(m_frot + D3DX_PI * -0.25f), 0.0f, cosf(m_frot + D3DX_PI * -0.25f)) * (length.x);
		Vtx[7] = Vtx[3] + D3DXVECTOR3(sinf(m_frot + D3DX_PI * 0.25f), 0.0f, cosf(m_frot + D3DX_PI * 0.25f)) * (length.x);
		Vtx[5] = Vtx[1] + D3DXVECTOR3(sinf(m_frot + D3DX_PI * -0.75f), 0.0f, cosf(m_frot + D3DX_PI * -0.75f)) * (length.x);
		Vtx[4] = Vtx[0] + D3DXVECTOR3(sinf(m_frot + D3DX_PI * 0.75f), 0.0f, cosf(m_frot + D3DX_PI * 0.75f)) * (length.x);
		
		if (CMesh::FieldCheck(Vtx[6], Vtx[7], Vtx[5], Vtx[4], WKpos))
		{//四角形範囲内
			fHeight = CMesh::FieldCollision(Vtx[2], Vtx[3], Vtx[1], Vtx[0], WKpos, pos, WKnor);
			if (fHeight - lengthX.y - length.y < pos.y && fHeight - lengthX.y - length.y >= posold.y) 
			{//天井
				pos.y = fHeight - lengthX.y - length.y;
			}
			else
			{//床
				if (fHeight + lengthX.y > pos.y && fHeight + lengthX.y <= posold.y + (bJump ? 5.0f : 0.0f))
				{
					pos.y = fHeight + lengthX.y;
					FNor = WKnor;
					move.y = 0.0f;
					bJump = true;
					bJudge = true;
				}
			}
		}
		if (!bJudge)
		{
			for (int nCount = 0; nCount < 4; nCount++)
			{//4方向判定
				//壁
				nHit = CMesh::WallCollision(Vtx[nCount % 4], Vtx[(nCount + 1) % 4], WKpos, posold, move, length.x, nCntHit, bReflection);
				if (nHit != 0)
				{//XZで当たった
				 //外積でＹチェック
					//float fDistance2[2];
					//float fAngle[3];

					//fDistance2[0] = sqrtf(powf((WKpos.x - posold.x), 2) + powf((WKpos.z - posold.z), 2));	//オブジェ
					//fDistance2[1] = sqrtf(powf((pos.x - posold.x), 2) + powf((pos.z - posold.z), 2));		//対象

					//fAngle[0] = atan2f(fDistance2[0], (GetPosition().y + lengthX.y * 0.9f) - (pos.y - (bReflection ? length.y : 0.0f)));
					//fAngle[1] = atan2f(fDistance2[0], (GetPosition().y - lengthX.y) - (pos.y + (bReflection ? length.y : 0.0f)));
					//fAngle[2] = 1.57f;
					//if (CMesh::AngleCheck(fAngle[2], fAngle[0]) > 0 && CMesh::AngleCheck(fAngle[2], fAngle[1]) < 0)
					//{//Y範囲内
					//	pos.x = WKpos.x;
					//	pos.z = WKpos.z;
					//}
					if (pos.y - move.y < GetPosition().y + lengthX.y && pos.y + length.y - move.y > GetPosition().y - lengthX.y)
					{//Y範囲内
						pos.x = WKpos.x;
						pos.z = WKpos.z;
					}
					else
					{//Y範囲外の為そのオブジェクトは無視
						break;
					}
					bJudge = false;
				}
				if (nHit == 2) { break; }
			}
		}
	}//if(範囲内なら)

	return bLand;
}
//=============================================================================
//あたり判定
//=============================================================================
void	CSceneObjct::SetObjField(void)
{
	bool bLand = false;
	CScene *pScene = CScene::GetTop(MODEL_PRIORITY);
	D3DXVECTOR3 WKpos, pos, posold, nor, length;
	bool bJump = true;
	length = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	while (pScene != NULL)
	{//終わるまで
		if (pScene->GetObjType() == OBJTYPE_OBJ || pScene->GetObjType() == OBJTYPE_OBJ_NO)
		{//オブジェ発見
			pos = ((CSceneObjct*)pScene)->GetPosition();
			posold = pos;
			pos.y = -10000.0f;
			posold.y = 10000.0f;
			CMesh::MeshCollisionField(pos, posold, WKpos, length, nor, bJump);
			switch (((CSceneObjct*)pScene)->GetModel())
			{//モデルごとに地面からの高さ設定
			case MODEL_STONE:	pos.y -= 65.0f; break;
			case MODEL_Earth:	pos.y += 10.0f; break;
			case MODEL_STONE_M:	pos.y = ((CSceneObjct*)pScene)->GetPosition().y; break;
			case MODEL_COLUMN:	pos.y = ((CSceneObjct*)pScene)->GetPosition().y + 30.0f; break;
			}
			((CSceneObjct*)pScene)->GetPosition().y = pos.y;
			((CSceneObjct*)pScene)->SetMtx();
		}
		pScene = pScene->GetpNext();
	}
}
//=============================================================================
//衛星の設定
//=============================================================================
void	CSatellite::Set(D3DXMATRIX &pMtx, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL model, D3DXVECTOR3 &move, float &fFrame, float fRot, float fDistance, bool &bDelete)
{
	m_pMtx = &pMtx;	m_bDelete = &bDelete;		m_pmove = &move;		m_pfFrame = &fFrame;
	m_fRot = fRot;	m_fDistance = fDistance;
	m_fMoveRot = 0.0f;

	D3DXVECTOR3 WKpos = D3DXVECTOR3(pMtx._41, pMtx._42, pMtx._43) + D3DXVECTOR3(sinf(m_fRot), 0.0f, cosf(m_fRot)) * m_fDistance;
	CSceneModel::Set(WKpos,rot, col, model, CScene::DRAW_TYPE_NORMAL, false);

	SetMtx();
	SetObjType(CScene::OBJTYPE_Satellite);
}
//=============================================================================
//衛星の更新
//=============================================================================
void	CSatellite::Update(void)
{
	m_fRot			 += ((sqrtf(m_pmove->x * m_pmove->x + m_pmove->z * m_pmove->z) * 0.75f + 1.0f) * 0.0035f) * D3DX_PI;
	GetRotation().y	 += (m_pfFrame[0] * 0.01f) * D3DX_PI;
	m_fMoveRot += D3DX_PI * 0.01f;

	GetPosition()	 = D3DXVECTOR3(m_pMtx->_41, m_pMtx->_42 + cosf(m_fRot * 2.0f) * 10.0f, m_pMtx->_43) + D3DXVECTOR3(sinf(m_fRot), 0.0f, cosf(m_fRot)) * m_fDistance;
}
//=============================================================================
//衛星の描画
//=============================================================================
void	CSatellite::Draw(void)
{
	SetMtx();
	CSceneModel::Draw();
}
//=============================================================================
//衛星の削除確認と破棄
//=============================================================================
void CSatellite::Delete(void)
{
	CScene *pScene;

	pScene = CScene::GetTop(SATELLITE_PRIORITY);
	while (pScene != NULL)
	{//終わるまで
		if (pScene->GetObjType() == OBJTYPE_Satellite)
		{//メッシュ発見
			if (((CSatellite*)pScene)->m_bDelete[0])
			{
				pScene->Uninit();
			}
		}
		pScene = pScene->GetpNext();
	}
}

//=============================================================================
//衛星のリセット
//=============================================================================
void CSatellite::ReSet(void)
{
	CScene *pScene;

	pScene = CScene::GetTop(SATELLITE_PRIORITY);
	while (pScene != NULL)
	{//終わるまで
		if (pScene->GetObjType() == OBJTYPE_Satellite)
		{//メッシュ発見
			D3DXMATRIX *&m_pMtx = ((CSatellite*)pScene)->GetpMtx();
			float &m_fRot = ((CSatellite*)pScene)->GetfRot();
			((CSatellite*)pScene)->GetPosition() = D3DXVECTOR3(m_pMtx->_41, m_pMtx->_42, m_pMtx->_43) + D3DXVECTOR3(sinf(m_fRot), 0.0f, cosf(m_fRot)) * ((CSatellite*)pScene)->m_fDistance;
		}
		pScene = pScene->GetpNext();
	}
}

//=============================================================================
//シャドウの描画
//=============================================================================
void	CShadow::Draw(void)
{
	LPDIRECT3DDEVICE9 &pDevice = CManager::GetRenderer()->GetDevice();
	GetDrawType() = CScene::DRAW_TYPE_SUBTRACT;
	pDevice->Clear(0, NULL, (D3DCLEAR_STENCIL), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);				// 深度バッファに書き込みはしない
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);	// レンダリングターゲットに書き込みはしない
	pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);		// フラットシェーディングする
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			// 両面描く

	// 両面ステンシルを使用する
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_CCW_STENCILFUNC, D3DCMP_ALWAYS);

	// ステンシルバッファの増減を1に設定する
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x1);
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	pDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);

	// 表面は深度テストに合格したらステンシルバッファの内容を+1する
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

	// 裏面は深度テストに合格したらステンシルバッファの内容を-1する
	pDevice->SetRenderState(D3DRS_CCW_STENCILPASS, D3DSTENCILOP_DECR);
	pDevice->SetRenderState(D3DRS_CCW_STENCILZFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_CCW_STENCILFAIL, D3DSTENCILOP_KEEP);

	CSceneModel::DrawModelOne(GetModel(), GetColor());

	// 状態を元に戻す
	pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0x0000000F);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
	pDevice->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, FALSE);

// ----------------------------------------------------------
// パス2:影の描画
// ----------------------------------------------------------
// 深度テストはしない
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	// ステンシルテストはする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	// アルファブレンディングは線形に掛ける
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// ポリゴンを描画するときには、テクスチャと頂点色の両方を見る
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	// ステンシルバッファの値が==2のときに書き込む
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_CCW_STENCILZFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_CCW_STENCILFAIL, D3DSTENCILOP_KEEP);

	C2D *p2D;
	if (Create(p2D))
	{
		p2D->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0, 1, 1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
		p2D->Draw();
		p2D->Uninit();
	}

	// 状態を元に戻す
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
}
//=============================================================================
// 設定処理
//=============================================================================
void	CMoveModel::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col, MODEL model, DRAW_TYPE DrawType, bool bHit)
{
	m_move = move;
	CSceneModel::Set(pos, rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), model, CScene::DRAW_TYPE_NORMAL, bHit);

	SetMtx();
	CScene::SetObjType(OBJTYPE_OBJ);
}
//=============================================================================
// 動くモデルの更新
//=============================================================================
void	CMoveModel::Update(void)
{

}
//=============================================================================
// 動くモデルの描画
//=============================================================================
void	CMoveModel::Draw(void)
{
	SetMtx();
	CSceneModel::Draw();
}
//=============================================================================
// 移動
//=============================================================================
void	CMoveModel::Move(void)
{
	CSceneModel::MODEL type = GetModel();
	D3DXVECTOR3 &ModelPos = GetPosition();

	switch (type)
	{
	case CSceneModel::MODEL_TITLE000:	//タイトルモデル(P)
		if (ModelPos.y == T_MODEL_LINEUPHEIGHT)
		{// 設定した値まできたら
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			m_move.y += 0.07f;
			ModelPos.y -= m_move.y;
		}
		break;

	case CSceneModel::MODEL_TITLE001:	//タイトルモデル(C)
		if (ModelPos.y == T_MODEL_LINEUPHEIGHT)
		{// 設定した値まできたら
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			m_move.y += 0.065f;
			ModelPos.y -= m_move.y;
		}
		break;

	case CSceneModel::MODEL_TITLE002:	//タイトルモデル(原)
		if (ModelPos.y == T_MODEL_LINEUPHEIGHT)
		{// 設定した値まできたら
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			m_move.y += 0.06f;
			ModelPos.y -= m_move.y;
		}
		break;

	case CSceneModel::MODEL_TITLE003:	//タイトルモデル(人)
		if (ModelPos.y == T_MODEL_LINEUPHEIGHT)
		{// 設定した値まできたら
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			m_move.y += 0.055f;
			ModelPos.y -= m_move.y;
		}
		break;

	case CSceneModel::MODEL_MISSILE:	//ミサイル
		m_move.x -= 0.004f;
		ModelPos.x += m_move.x;
		break;
	}

	SetMtx();
}
//=============================================================================
// ぐちゃぐちゃ
//=============================================================================
void	CMoveModel::Messy(void)
{
	D3DXVECTOR3 &ModelPos = GetPosition();
	D3DXVECTOR3 &ModelRot = GetRotation();

	ModelPos.y = T_MODEL_MESSYHEIGHT;

	ModelRot = D3DXVECTOR3((float)(rand() % 60), (float)(rand() % 60), (float)(rand() % 60));

	// 回転止める
	ModelRot = ModelPos;
}
//=============================================================================
// 浮いてくる
//=============================================================================
void	CMoveModel::Floating(void)
{
	D3DXVECTOR3 &ModelPos = GetPosition();
	D3DXVECTOR3 &ModelRot = GetRotation();

	m_move.y -= 0.005f;
	ModelPos.y += m_move.y;

	SetMtx();
}
