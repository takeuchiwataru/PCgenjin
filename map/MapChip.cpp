//=============================================================================
//
// マップチップ処理 [MapChip.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS	//Fire Wall突破
#include <stdio.h>				//インクルドファイル
#include <stdlib.h>				//ランド用
#include <time.h>				//同じくランド用
#include <string.h>				//ストリング使用のため

#include "main.h"
#include "MapChip.h"
#include "Chip.h"
#include "MapChip_BG.h"
#include "Story.h"

#include "player.h"
#include "3DPolygon.h"
#include "DebugLog.h"
#include "camera.h"
#include "enemy.h"

#include "renderer.h"
#include "RenderDraw.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_DRAW_RANGE	(12)
#define MAX_UPDATE_RANGE	(16)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//==================================================================================================//
//    *	一つのチップの初期化 *
//==================================================================================================//
HRESULT COneChip::Init(void)
{
	m_nMaxChip = 0;
	m_pChip = NULL;
	m_nMaxFront = 0;
	m_pFront = NULL;
	return S_OK;
}
//==================================================================================================//
//    *	一つのチップの終了 *
//==================================================================================================//
void	COneChip::Uninit(void)
{
	if (m_pChip != NULL)
	{//チップが生成されているなら
		for (int nCount = 0; nCount < m_nMaxChip; nCount++)
		{//管理元のチップの終了
			if (m_pChip[nCount] == NULL) { continue; }
			m_pChip[nCount]->Uninit();
			m_pChip[nCount] = NULL;
		}
		delete[] m_pChip;
	}
	delete this;
}
//==================================================================================================//
//    *	一つのチップの描画 *
//==================================================================================================//
void	COneChip::Draw(void)
{
	if (m_pChip != NULL)
	{//チップが生成されているなら
		for (int nCount = 0; nCount < m_nMaxChip; nCount++)
		{//管理元のチップの描画
			if (m_pChip[nCount] == NULL) { continue; }
			if (m_pChip[nCount]->GetDType() != CManager::GetpMapChip()->GetDType()) { continue; }
			m_pChip[nCount]->Draw();
		}
	}
}
//==================================================================================================//
//    *	一つのチップの更新 *
//==================================================================================================//
void	COneChip::Update(void)
{
	if (m_pChip != NULL)
	{//チップが生成されているなら
		for (int nCount = 0; nCount < m_nMaxChip; nCount++)
		{//管理元のチップの更新
			if (m_pChip[nCount] == NULL) { continue; }
			if (m_pChip[nCount]->Update())
			{//削除命令
				m_pChip[nCount]->Uninit();
				m_pChip[nCount] = NULL;
			}
		}
	}
}
//==================================================================================================//
//    *	一つのチップのマトリックス計算 *
//==================================================================================================//
void	COneChip::SetMtx(D3DXVECTOR3 &pos)
{
	if (m_pChip != NULL)
	{//チップが生成されているなら
		for (int nCount = 0; nCount < m_nMaxChip; nCount++)
		{//管理元のチップの更新
			if (m_pChip[nCount] == NULL) { continue; }
			m_pChip[nCount]->SetMtx(pos);
		}
	}
}
//==================================================================================================//
//    *	一つのチップの当たり判定 *
//==================================================================================================//
bool	COneChip::CollisionY(CCharacter *&pChar)
{
	bool bLand = false;

	if (m_pChip != NULL)
	{//チップが生成されているなら
		for (int nCount = 0; nCount < m_nMaxChip; nCount++)
		{//管理元のチップの更新
			if (m_pChip[nCount] == NULL) { continue; }
			if (m_pChip[nCount]->CollisionY(pChar)) { bLand = true; }
		}
	}

	return bLand;
}
//==================================================================================================//
//    *	一つのチップの当たり判定 *
//==================================================================================================//
bool	COneChip::CollisionXZ(CCharacter *&pChar, int &nHit)
{
	bool bHit = false;

	if (m_pChip != NULL)
	{//チップが生成されているなら
		for (int nCount = 0; nCount < m_nMaxChip; nCount++)
		{//管理元のチップの更新
			if (m_pChip[nCount] == NULL) { continue; }
			if (m_pChip[nCount]->CollisionXZ(pChar, nHit)) { bHit = true; };
		}
	}
	return bHit;
}
//==================================================================================================//
//    *	一つのチップの選択キャンセル *
//==================================================================================================//
void	COneChip::ResetSelect(void)
{
	if (m_pChip != NULL)
	{//チップが生成されているなら
		for (int nCount = 0; nCount < m_nMaxChip; nCount++)
		{//管理元のチップの更新
			if (m_pChip[nCount] == NULL) { continue; }
			m_pChip[nCount]->GetbSelect() = false;
		}
	}
}
//==================================================================================================//
//    *	一つのチップの初期化 *
//==================================================================================================//
void	COneChip::SetChip(int nNumChip)
{
	//if (nNumChip <= 0) { return; }				//0以下ならキャンセル
	if (m_pChip != NULL) { Uninit(); Init(); }	//既に生成されているなら破棄

	m_nMaxChip = 10;						//チップ数代入
	//m_nMaxChip = nNumChip;
	m_pChip = new CChip*[m_nMaxChip];			//指定分生成

	for (int nCount = 0; nCount < m_nMaxChip; nCount++)
	{
		m_pChip[nCount] = NULL;
	}
}
//==================================================================================================//
//    *	一つのチップの初期化 *
//==================================================================================================//
CChip *&COneChip::GetChip(int nNumber)
{
	return m_pChip[nNumber];
}
//==================================================================================================//
//    *	一つのチップの初期化 *
//==================================================================================================//
void	COneChip::Save(FILE *&pFile)
{
	if (m_pChip != NULL)
	{//チップが生成されているなら
		int nCntChip = 0;
		for (int nCount = 0; nCount < m_nMaxChip; nCount++)
		{//チップ情報をセーブ
			if (m_pChip[nCount] != NULL) { nCntChip++; }
		}
		fprintf(pFile, "%d \n", nCntChip);

		for (int nCount = 0; nCount < m_nMaxChip; nCount++)
		{//チップ情報をセーブ
			if (m_pChip[nCount] == NULL) { continue; }
			fprintf(pFile, "%d \n", m_pChip[nCount]->GetType());
			m_pChip[nCount]->Save(pFile);
		}
	}
}
//==================================================================================================//
//    *	一つのチップの初期化 *
//==================================================================================================//
void	COneChip::Load(FILE *&pFile)
{
	int nNumChip, nType;

	fscanf(pFile, "%d \n", &nNumChip);	//チップ数読み込み
	SetChip(nNumChip);				//指定分ポインタを生成

	for (int nCount = 0; nCount < nNumChip; nCount++)
	{//生成分読み込み
		CChip *&pChip = GetChip(nCount);
		fscanf(pFile, "%d \n", &nType);	//チップ数読み込み
		CreateChip(pChip, (CChip::TYPE)nType);
		pChip->Load(pFile);
	}
}
//==================================================================================================//
//    *	一つのチップのチップ生成 *
//==================================================================================================//
void	COneChip::CreateChip(CChip *&pChip, CChip::TYPE type)
{
	if (pChip != NULL)
	{//既に何か生成されている場合
		if (pChip->GetType() == type) { return; }
		pChip->Uninit(); pChip = NULL;
	}

	switch (type)
	{
	case CChip::TYPE_NULL:		pChip = new CChip;			break;
	case CChip::TYPE_MODEL:		pChip = new CChip_Model;	break;
	case CChip::TYPE_POLYGON:	pChip = new CChip_Polygon;	break;
	}

	if (pChip != NULL)
	{
		pChip->GetType() = type;
		pChip->Init();
	}
}
//==================================================================================================//
//    *	一つのチップの状態描画 *
//==================================================================================================//
void	COneChip::StatusLog(int &nMaxSelect)
{
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "最大チップ %d\n", m_nMaxChip);
	nMaxSelect = m_nMaxChip;
	for (int nCount = 0; nCount < m_nMaxChip; nCount++)
	{//生成分読み込み
		if (m_pChip[nCount] == NULL) { continue; }
		CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "%d：", nCount);
		m_pChip[nCount]->StatusLog();
	}
}

//**************************************************************************************************//
//==================================================================================================//
//    * マップチップの初期化 *
//==================================================================================================//
//**************************************************************************************************//
HRESULT CMapChip::Init(void)
{
	CManager::GetpMapChip() = this;
	m_Map			= MAP_1;
	m_bMirror		= false;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nMaxX = 0;	m_nMaxZ = 0;
	m_fInitHeight	= 0;
	m_nMaxOneChip	= 0;
	m_nWKNumber		= 0;
	m_nWait			= 0;
	m_nClear		= 0;
	m_pOneChip		= NULL;
	m_pBG			= NULL;
	m_bEdit			= false;
	m_nEdit			= 0;
	m_DType			= CChip::DTYPE_MAX;
	m_Collision = CChip::COLLISION::COLLISION_NO;

	m_nMaxSelect = 1;
	m_nSelect = 0;
	m_Edit = EDIT_MODEL;
	m_ModelType = CChip_Model::TYPE_BLOCK00;
	m_ItemType = CChip_Model::TYPE_BLOCK00;
	m_PolyType = CChip_Polygon::TYPE_PFIELD;
	if (Create(m_p3D))
	{//真ん中に3Dを表示
		m_p3D->Set(m_pos + D3DXVECTOR3(-MAP_CHIP_SIZE * 0.5f, -0.1f, -MAP_CHIP_SIZE * 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)
			, D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, 1, 1
			, CScene::DRAW_TYPE_ADD, CScene::TEX_MAX, false);
	}
	LPDIRECT3DTEXTURE9	WKpTex;				//画像
	CSceneModel::LoadModel(CSceneModel::MODEL_BLOC00, WKpTex);
	return S_OK;
}
//==================================================================================================//
//    * マップチップの終了 *
//==================================================================================================//
void	CMapChip::Uninit(void)
{
	CManager::GetpMapChip() = NULL;
	Reset();
	CScene::Uninit();
}
//==================================================================================================//
//    * マップチップの更新 *
//==================================================================================================//
void	CMapChip::Update(void)
{
	Edit();

	if (m_pBG != NULL) { m_pBG->Update(); }
	if (m_p3D != NULL) { m_p3D->Update(); }

	if (m_nClear > 0)
	{
		CRenderDraw_Meny *pReDraw;
		m_nClear++;

		//2人プレイで片方ゴールなら待機
		if (CPlayer::WaitGoal() && m_nWait < 180)
		{
			m_nClear = 1;
			m_nWait++;
		}

		switch (m_nClear)
		{
		case CLEAR_ADVANCE: 
			CCharacter::GetbWait() = true;
			//pReDraw = (CRenderDraw_Meny*)CRenderDraw::SetFade(CManager::MODE_GAME, CRenderDraw::FADE_MENY_SPIN, CRenderDraw::STATE_FADE_IN);
			pReDraw = (CRenderDraw_Meny*)CRenderDraw::SetFade(CManager::MODE_GAME, CRenderDraw::FADE_MOVE, CRenderDraw::STATE_FADE_IN);
			pReDraw->SetRotMove(D3DX_PI * -0.5f);
			pReDraw->GetbMode() = false;
			break;
		case CLEAR_FADE:
			Advance();
			break;

		}
	}
	if (m_pOneChip != NULL)
	{//一マスごとのチップが生成されているなら
		int nNumX_Min, nNumX_Max;
		float fCameraX = CManager::GetCamera()->GetPlay(0)->GetChar()->GetposR().x;
		nNumX_Min = (int)(fCameraX / MAP_CHIP_SIZE) - MAX_UPDATE_RANGE + 1;
		nNumX_Max = (int)(fCameraX / MAP_CHIP_SIZE) + MAX_UPDATE_RANGE;
		if (nNumX_Min < 0) { nNumX_Min = 0; }
		if (nNumX_Max > m_nMaxX) { nNumX_Max = m_nMaxX; }

		for (int nCntX = nNumX_Min; nCntX < nNumX_Max; nCntX++)
		{
			for (int nCntZ = 0; nCntZ < m_nMaxZ; nCntZ++)
			{//管理元のチップの描画 & マス目計算
				m_nWKNumber = (nCntZ * m_nMaxX) + nCntX;
				if (m_pOneChip[m_nWKNumber] == NULL) { continue; }	//生成されていないなら無視
				m_pOneChip[m_nWKNumber]->Update();
			}
		}
	}

}
//==================================================================================================//
//    * マップチップの描画 *
//==================================================================================================//
void	CMapChip::DrawMap(int nPriority)
{
	if (m_pOneChip != NULL && nPriority < CChip::DTYPE_MAX)
	{//一マスごとのチップが生成されているなら
		if (nPriority == CChip::DTYPE_NO) { return; }

		int nNumX_Min, nNumX_Max;
		float fCameraX = CManager::GetCamera()->GetPlay(0)->GetChar()->GetposR().x;
		nNumX_Min = (int)(fCameraX / MAP_CHIP_SIZE) - MAX_DRAW_RANGE + 1;
		nNumX_Max = (int)(fCameraX / MAP_CHIP_SIZE) + MAX_DRAW_RANGE;
		if (nNumX_Min < 0) { nNumX_Min = 0; }
		if (nNumX_Max > m_nMaxX) { nNumX_Max = m_nMaxX; }

		m_DType = (CChip::DTYPE)nPriority;

		//描画初めに背景の描画
		if (m_DType == CChip::DTYPE_OBJECT) { if (m_pBG != NULL) { m_pBG->Draw(); } }

		for (int nCntX = nNumX_Min; nCntX < nNumX_Max; nCntX++)
		{
			for (int nCntZ = 0; nCntZ < m_nMaxZ; nCntZ++)
			{//管理元のチップの描画 & マス目計算
				m_nWKNumber = (nCntZ * m_nMaxX) + nCntX;
				if (m_pOneChip[m_nWKNumber] == NULL) { continue; }	//生成されていないなら無視
				m_pOneChip[m_nWKNumber]->Draw();
			}
		}
	}
	if (m_p3D != NULL && m_bEdit)
	{ m_p3D->Draw(); }
}
//==================================================================================================//
//    * マップチップの描画 *
//==================================================================================================//
void	CMapChip::Reset(void)
{
	CCharacter::GetbWait() = false;
	if (m_pOneChip != NULL)
	{//一マスごとのチップが生成されているなら
		for (int nCount = 0; nCount < m_nMaxOneChip; nCount++)
		{//管理元のチップの終了
			if (m_pOneChip[nCount] == NULL) { continue; }	//生成されていないなら無視
			m_pOneChip[nCount]->Uninit();
		}
		delete[] m_pOneChip;
		m_pOneChip = NULL;
		m_nMaxOneChip = 0;
	}
	if (m_p3D != NULL) { m_p3D->Uninit(); m_p3D = NULL; }
	if (m_pBG != NULL) { m_pBG->Uninit(); m_pBG = NULL; }
}
//==================================================================================================//
//    * マップチップの管理元のマトリックス計算 *
//==================================================================================================//
void	CMapChip::SetMtx(void)
{
	if (m_pOneChip != NULL)
	{//一マスごとのチップが生成されているなら
		D3DXVECTOR3 pos = m_pos;
		int nCountX = 0;
		int nCountZ = 0;

		for (nCountX = 0; nCountX < m_nMaxX; nCountX++)
		{//管理元のチップの更新
			for (nCountZ = 0; nCountZ < m_nMaxZ; nCountZ++)
			{
				if (m_pOneChip[m_nMaxX * nCountZ + nCountX] == NULL) { continue; }	//生成されていないなら無視
				pos.x = nCountX * MAP_CHIP_SIZE + m_pos.x;
				pos.z = nCountZ * MAP_CHIP_SIZE + m_pos.z;
				m_pOneChip[m_nMaxX * nCountZ + nCountX]->SetMtx(pos);
			}
		}
	}
}
//==================================================================================================//
//    * マップチップの管理元のチップ選択キャンセル *
//==================================================================================================//
void	CMapChip::ResetSelect(void)
{
	if (m_pOneChip != NULL)
	{//一マスごとのチップが生成されているなら
		int nCountX = 0;
		int nCountZ = 0;

		for (nCountX = 0; nCountX < m_nMaxX; nCountX++)
		{//管理元のチップの更新
			for (nCountZ = 0; nCountZ < m_nMaxZ; nCountZ++)
			{
				if (m_pOneChip[m_nMaxX * nCountZ + nCountX] == NULL) { continue; }	//生成されていないなら無視
				m_pOneChip[m_nMaxX * nCountZ + nCountX]->ResetSelect();
			}
		}
	}
}
//==================================================================================================//
//    * マップチップの進行処理 *
//==================================================================================================//
void	CMapChip::Advance(void)
{
	CPlayer::ResetMoveScale();
	CPlayer::GetnTime() = 0;
	m_Map = (MAP)(m_Map + 1);
	CPlayer::Start();

	if (m_Map == MAP_MAX) 
	{//Resultへ 
		CRenderDraw::SetFade(CManager::MODE_SELECT, CRenderDraw::FADE_ZOOM, CRenderDraw::STATE_FADE_IN); 
		return;
	}

	//マップ切り替え
	SetMap(m_Map);
}
//==================================================================================================//
//    * マップチップの設定 *
//==================================================================================================//
void	CMapChip::Set(D3DXVECTOR3 pos, int nMaxX, int nMaxZ)
{
	if (nMaxX > 0 && nMaxZ > 0)
	{//X, Zともに1以上なら
		if (m_pOneChip != NULL) { Reset(); Init(); }			//既に生成されているなら削除
		m_pos = pos;	m_nMaxX = nMaxX;	m_nMaxZ = nMaxZ;	//設定値代入
		m_nMaxOneChip = nMaxX * nMaxZ;							//最大チップ数計算

		m_pOneChip = new COneChip*[m_nMaxOneChip];				//指定チップ数分生成
		for (int nCount = 0; nCount < m_nMaxOneChip; nCount++)
		{
			m_pOneChip[nCount] = NULL;
		}
	}
}
//==================================================================================================//
//    * マップチップのチップ生成 *
//==================================================================================================//
COneChip	*CMapChip::CreateChip(int nNumber)
{
	if (m_pOneChip == NULL || 0 > nNumber || m_nMaxOneChip < nNumber)
	{//生成範囲外なら
		MessageBox(0, "生成範囲外にチップを生成しようとしてるよ", "MapChip.cpp/関数[CreateChip]", MB_OK);
		return NULL;
	}

	//一つのチップを生成->初期化
	m_pOneChip[nNumber] = NULL;
	m_pOneChip[nNumber] = new COneChip;
	if (m_pOneChip[nNumber] != NULL)
	{
		m_pOneChip[nNumber]->Init();
	}

	return m_pOneChip[nNumber];
}
//==================================================================================================//
//    * マップチップの高さ取得 *
//==================================================================================================//
float CMapChip::GetHeight(D3DXVECTOR3 pos, int nSelect)
{
	int				nNumX, nNumZ, nNumber;

	nNumX = (int)((pos.x - m_pos.x + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumZ = (int)((pos.z - m_pos.z + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumber = (m_nMaxX * nNumZ) + nNumX;

	if (m_pOneChip[nNumber] != NULL)
	{ 
		if (m_pOneChip[nNumber]->GetChip(nSelect) != NULL)
		{
			return m_pOneChip[nNumber]->GetChip(nSelect)->GetHeight();
		}
	}
	return 0.0f;
}
//==================================================================================================//
//    * マップチップのチップ生成 *
//==================================================================================================//
void CMapChip::Collision(CCharacter *pChar)
{
	D3DXVECTOR3		&pos = pChar->Getpos();
	int				nNumX, nNumZ, nNumber;
	bool			bLand = false;

	nNumX = (int)((pos.x - m_pos.x + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumZ = (int)((pos.z - m_pos.z + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumber = (m_nMaxX * nNumZ) + nNumX;
	
	if (m_pOneChip != NULL)
	{//一マスごとのチップが生成されているなら
		
	 //Y判定
		for (int nCntX = 0; nCntX < 3; nCntX++)
		{
			for (int nCntZ = 0; nCntZ < 3; nCntZ++)
			{
				m_nWKNumber = (m_nMaxX * (nNumZ - 1 + nCntZ)) + (nNumX - 1 + nCntX);
				if (m_nWKNumber >= m_nMaxOneChip || m_nWKNumber < 0) { continue; }
				if (m_pOneChip[m_nWKNumber] == NULL) { continue; }
				if (m_pOneChip[m_nWKNumber]->CollisionY(pChar)) { bLand = true; }
			}
		}
		if (CCharacter::CollisionAll(pChar)) { bLand = true; }//キャラ同士当たり判定

		if (bLand) { pChar->Landing(); }
		else { pChar->GetbJump() = false; }

		//X判定
		int nCountX = 0;
		int nCountZ = 0;
		int nHit;

		if (!pChar->GetbCollision()) { return; }
		for (int nCntZ = 0; nCntZ < 3; nCntZ++)
		{
			nHit = 0;
			for (int nCntX = 0; nCntX < 3; nCntX++)
			{
				m_nWKNumber = (m_nMaxX * (nNumZ - 1 + nCntZ)) + (nNumX - 1 + nCntX);
				if (m_nWKNumber >= m_nMaxOneChip || m_nWKNumber < 0) { continue; }
				if (m_pOneChip[m_nWKNumber] == NULL) { continue; }
				m_pOneChip[m_nWKNumber]->CollisionXZ(pChar, nHit);
			}
			if (nHit == 2)
			{//X突っかかり解除
				pos.x -= 0.1f;
			}
		}
	}
}
//==================================================================================================//
//    * マップチップのチップ生成 *
//==================================================================================================//
void	CMapChip::Edit(void)
{
	if (CManager::GetPlayer(0) == NULL) { return; }
	CInputKeyboard	*pInputKey = CManager::GetInputKey();
	D3DXVECTOR3		&pos = CManager::GetPlayer(0)->Getpos();
	int				nNumX, nNumZ, nNumber;
	float			fWKValue = 0.01f;
	bool			bEdit = false;

	nNumX = (int)((pos.x - m_pos.x + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumZ = (int)((pos.z - m_pos.z + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumber = (m_nMaxX * nNumZ) + nNumX;

	ResetSelect();
	StatusLog(nNumX, nNumZ, nNumber);
	if (m_p3D != NULL)
	{
		m_p3D->GetLength() = D3DXVECTOR3(m_nMaxX * MAP_CHIP_SIZE, 0.0f, m_nMaxZ * MAP_CHIP_SIZE);
		m_p3D->SetChipSize();
	}

	if (pInputKey->GetTPress(DIK_F3)) { m_bEdit = (m_bEdit ? false : true); }

	if (!m_bEdit) { return; }
	//マップの大きさ変更
	if (pInputKey->GetRelease(DIK_Y)) { ChangeSize(m_nMaxX, m_nMaxZ + 1); return; }
	if (pInputKey->GetRelease(DIK_H)) { ChangeSize(m_nMaxX, m_nMaxZ - 1); return; }
	if (pInputKey->GetRelease(DIK_O)) { ChangeSize(m_nMaxX + 1, m_nMaxZ); return; }
	if (pInputKey->GetRelease(DIK_U)) { ChangeSize(m_nMaxX - 1, m_nMaxZ); return; }

	if (pInputKey->GetPress(DIK_LCONTROL))
	{
		if (pInputKey->GetRelease(DIK_J)) { ChangePosX(nNumber, 1);		bEdit = true; }
		if (pInputKey->GetRelease(DIK_L)) { ChangePosX(nNumber, -1);	bEdit = true; }
	}
	else
	{
		//マップの移動
		if (pInputKey->GetTrigger(DIK_I)) { ChangePos(0, 1);	bEdit = true; }
		if (pInputKey->GetTrigger(DIK_K)) { ChangePos(0, -1);	bEdit = true; }
		if (pInputKey->GetTrigger(DIK_J)) { ChangePos(-1, 0);	bEdit = true; }
		if (pInputKey->GetTrigger(DIK_L)) { ChangePos(1, 0);	bEdit = true; }
	}
	//選択番号変更
	if (pInputKey->GetTPress(DIK_RIGHT)) { m_nSelect++; }
	if (pInputKey->GetTPress(DIK_LEFT)) { m_nSelect--; }
	if (m_nSelect > m_nMaxSelect) { m_nSelect = m_nMaxSelect; }
	if (m_nSelect < 0) { m_nSelect = 0; }

	//初期高さ変更
	if (pInputKey->GetTPress(DIK_NUMPAD7)) { m_fInitHeight += 0.5f; }
	if (pInputKey->GetTPress(DIK_NUMPAD4)) { m_fInitHeight -= 0.5f; }

	//生成タイプ変更
	if (pInputKey->GetTPress(DIK_NUMPAD1)) { m_Edit = (EDIT)((m_Edit + 1) % EDIT_MAX); }

	if (m_pOneChip != NULL)
	{//一マスごとのチップが生成されているなら
		if (nNumX > -1 && nNumX < m_nMaxX && nNumZ > -1 && nNumZ < m_nMaxZ)
		{
			if (m_pOneChip[nNumber] != NULL)
			{//生成されていないなら無視

			 //削除
				if (pInputKey->GetTrigger(DIK_BACKSPACE)) { DeleteChip(nNumber); bEdit = true; }

				//変更対象の変更
				if (pInputKey->GetTrigger(DIK_ADD)) { m_nEdit++; }
				if (pInputKey->GetTrigger(DIK_SUBTRACT)) { m_nEdit--; }

				if (m_nEdit < 0) { m_nEdit = 0; }
				//設置・変更
				switch (m_Edit)
				{
				case EDIT_MODEL:	EditModel(nNumber, bEdit);		break;
				case EDIT_POLYGON:	EditPolygon(nNumber, bEdit);	break;
				case EDIT_ITEM:		EditItem(nNumber, bEdit);		break;
				}
			}
		}
	}


	//セーブ・ロード
	if (pInputKey->GetTrigger(DIK_F9)) { Save("data/TEXT/EDIT/Editor.txt"); }
	if (pInputKey->GetTrigger(DIK_9)) { Load("data/TEXT/EDIT/Editor.txt"); }

	if (bEdit) { EditTrue(); }
}
//==================================================================================================//
//    * マップチップのモデル設定 *
//==================================================================================================//
void	CMapChip::EditModel(int &nNumber, bool &bEdit)
{
	CInputKeyboard	*pInputKey = CManager::GetInputKey();

	if (m_nEdit >= 2) { m_nEdit = 1; }
	if (pInputKey->GetTPress(DIK_RETURN)) { SettingModel(nNumber);			bEdit = true; }
	if (pInputKey->GetTPress(DIK_UP)) { UpHeightModel(nNumber, 0.25f);		bEdit = true; }
	if (pInputKey->GetTPress(DIK_DOWN)) { UpHeightModel(nNumber, -0.25f);	bEdit = true; }
	if (pInputKey->GetTPress(DIK_NUMPAD8)) { m_ModelType = (CChip_Model::TYPE)((m_ModelType + 1) % CChip_Model::TYPE_MAX); }
	if (pInputKey->GetTPress(DIK_NUMPAD5)) { m_ModelType = (CChip_Model::TYPE)((m_ModelType + (CChip_Model::TYPE_MAX - 1)) % CChip_Model::TYPE_MAX); }

	switch (m_nEdit)
	{
	case 0:
		if (pInputKey->GetTPress(DIK_NUMPAD9)) { UpRotationModel(nNumber, D3DX_PI * 0.5f);		bEdit = true; }
		if (pInputKey->GetTPress(DIK_NUMPAD6)) { UpRotationModel(nNumber, -D3DX_PI * 0.5f);	bEdit = true; }
		break;
	case 1:
		if (pInputKey->GetPress(DIK_LCONTROL))
		{//生成用設定
			if (pInputKey->GetTPress(DIK_NUMPAD9)) { m_Collision = (CChip::COLLISION)(((int)m_Collision + 1) % CChip::COLLISION_MAX); bEdit = true; }
			if (pInputKey->GetTPress(DIK_NUMPAD6)) { m_Collision = (CChip::COLLISION)(((int)m_Collision + 1) % CChip::COLLISION_MAX);	bEdit = true; }
		}
		else
		{//選択モデルモデル設定
			if (pInputKey->GetTPress(DIK_NUMPAD9)) { ChangeCollisionModel(nNumber);		bEdit = true; }
			if (pInputKey->GetTPress(DIK_NUMPAD6)) { ChangeCollisionModel(nNumber);		bEdit = true; }
		}
		break;
	}
}
//==================================================================================================//
//    * マップチップのポリゴン設定 *
//==================================================================================================//
void	CMapChip::EditPolygon(int &nNumber, bool &bEdit)
{
	CInputKeyboard	*pInputKey = CManager::GetInputKey();

	if (m_nEdit >= 2) { m_nEdit = 1; }
	if (pInputKey->GetTPress(DIK_RETURN)) { SettingPolygon(nNumber);			bEdit = true; }
	if (pInputKey->GetTPress(DIK_NUMPAD8)) { m_PolyType = (CChip_Polygon::TYPE)((m_PolyType + 1) % CChip_Polygon::TYPE_MAX); }
	if (pInputKey->GetTPress(DIK_NUMPAD5)) { m_PolyType = (CChip_Polygon::TYPE)((m_PolyType + (CChip_Polygon::TYPE_MAX - 1)) % CChip_Polygon::TYPE_MAX); }

	switch (m_nEdit)
	{
	case 0:
		if (pInputKey->GetTPress(DIK_NUMPAD9)) { UpRotationPolygon(nNumber, D3DX_PI * 0.5f);		bEdit = true; }
		if (pInputKey->GetTPress(DIK_NUMPAD6)) { UpRotationPolygon(nNumber, -D3DX_PI * 0.5f);	bEdit = true; }
		break;
	case 1:
		if (pInputKey->GetPress(DIK_LCONTROL))
		{//生成用設定
			if (pInputKey->GetTPress(DIK_NUMPAD9)) { m_Collision = (CChip::COLLISION)(((int)m_Collision + 1) % CChip::COLLISION_MAX); bEdit = true; }
			if (pInputKey->GetTPress(DIK_NUMPAD6)) { m_Collision = (CChip::COLLISION)(((int)m_Collision + 1) % CChip::COLLISION_MAX);	bEdit = true; }
		}
		else
		{//選択モデルモデル設定
			if (pInputKey->GetTPress(DIK_NUMPAD9)) { ChangeCollisionModel(nNumber);		bEdit = true; }
			if (pInputKey->GetTPress(DIK_NUMPAD6)) { ChangeCollisionModel(nNumber);		bEdit = true; }
		}
		break;
	}
}
//==================================================================================================//
//    * マップチップのアイテム設定 *
//==================================================================================================//
void	CMapChip::EditItem(int &nNumber, bool &bEdit)
{
	CInputKeyboard	*pInputKey = CManager::GetInputKey();

	if (m_nEdit >= 1) { m_nEdit = 0; }
	if (pInputKey->GetTPress(DIK_RETURN))	{ SettingItem(nNumber);			bEdit = true; }
	if (pInputKey->GetTPress(DIK_UP))		{ UpHeightModel(nNumber, 0.25f);		bEdit = true; }
	if (pInputKey->GetTPress(DIK_DOWN))		{ UpHeightModel(nNumber, -0.25f);	bEdit = true; }
	if (pInputKey->GetTPress(DIK_NUMPAD8))	{ m_ItemType = (CChip_Model::TYPE)((m_ItemType + 1) % CChip_Model::TYPE_MAX); }
	if (pInputKey->GetTPress(DIK_NUMPAD5))	{ m_ItemType = (CChip_Model::TYPE)((m_ItemType + (CChip_Model::TYPE_MAX - 1)) % CChip_Model::TYPE_MAX); }

	switch (m_nEdit)
	{
	case 0:
		if (pInputKey->GetTPress(DIK_NUMPAD9)) { UpRotationModel(nNumber, D3DX_PI * 0.5f);		bEdit = true; }
		if (pInputKey->GetTPress(DIK_NUMPAD6)) { UpRotationModel(nNumber, -D3DX_PI * 0.5f);	bEdit = true; }
		break;
	}
}
//==================================================================================================//
//    * マップチップのポリゴン設定 *
//==================================================================================================//
void	CMapChip::EditEnemy(int &nNumber)
{
	CInputKeyboard	*pInputKey = CManager::GetInputKey();
	if (m_nEdit >= 1) { m_nEdit = 0; }

}
//==================================================================================================//
//    * マップの大きさ変更 *
//==================================================================================================//
void	CMapChip::ChangeSize(int nNumX, int nNumZ)
{
	CMapChip *pMap;
	int nCntL, nCntS;	//L = 乗り換え後、S = 乗り換え前
	int nMaxX, nMaxZ;
	bool bEdit = m_bEdit;
	COneChip *pOneChip;

	if (SceneCreate(pMap, MAP_PRIORYITY))
	{
		pMap->Set(m_pos, nNumX, nNumZ);
		for (int nCount = 0; nCount < nNumX * nNumZ; nCount++)
		{
			pMap->CreateChip(nCount)->SetChip(1);
		}

		if (m_nMaxX > nNumX) { nMaxX = nNumX; }
		else { nMaxX = m_nMaxX; }
		if (m_nMaxZ > nNumZ) { nMaxZ = nNumZ; }
		else { nMaxZ = m_nMaxZ; }

		for (int nCountX = 0; nCountX < nMaxX; nCountX++)
		{
			for (int nCountZ = 0; nCountZ < nMaxZ; nCountZ++)
			{
				nCntL = (nNumX * nCountZ) + nCountX;
				nCntS = (m_nMaxX * nCountZ) + nCountX;
				//if (m_pOneChip[nCntS] == NULL) { continue; }	//生成されていないなら無視

				pOneChip = pMap->m_pOneChip[nCntL];
				pMap->m_pOneChip[nCntL] = m_pOneChip[nCntS];
				m_pOneChip[nCntS] = pOneChip;
			}
		}
		pMap->SetMtx();
		pMap->GetbEdit() = true;
		CManager::GetInputKey()->Skip();
	}
	Uninit();
	CManager::GetpMapChip() = pMap;
}
//==================================================================================================//
//    * マップチップの全移動 *
//==================================================================================================//
void	CMapChip::ChangePos(int nNumX, int nNumZ)
{
	int nSNumber, nDNumber;

	if (nNumX < 0)
	{//Xが-1以下の場合：X左にずらす
		for (int nCountZ = 0; nCountZ < m_nMaxZ; nCountZ++)
		{
			for (int nCountX = 1; nCountX < m_nMaxX; nCountX++)
			{
				nSNumber = (m_nMaxX * nCountZ) + nCountX;
				nDNumber = (m_nMaxX * nCountZ) + (nCountX - 1);
				if (m_pOneChip[nDNumber] != NULL) { m_pOneChip[nDNumber]->Uninit(); }
				m_pOneChip[nDNumber] = m_pOneChip[nSNumber];
				m_pOneChip[nSNumber] = NULL;
			}
		}
	}
	if (nNumX > 0)
	{//Xが1以上の場合：右に
		for (int nCountZ = 0; nCountZ < m_nMaxZ; nCountZ++)
		{
			for (int nCountX = m_nMaxX - 2; nCountX >= 0; nCountX--)
			{
				nSNumber = (m_nMaxX * nCountZ) + nCountX;
				nDNumber = (m_nMaxX * nCountZ) + (nCountX + 1);
				if (m_pOneChip[nDNumber] != NULL) { m_pOneChip[nDNumber]->Uninit(); }
				m_pOneChip[nDNumber] = m_pOneChip[nSNumber];
				m_pOneChip[nSNumber] = NULL;
			}
		}
	}

	if (nNumZ < 0)
	{//Zが-1以下の場合：手前にずらす
		for (int nCountX = 0; nCountX < m_nMaxX; nCountX++)
		{
			for (int nCountZ = 1; nCountZ < m_nMaxZ; nCountZ++)
			{
				nSNumber = (m_nMaxX * nCountZ) + nCountX;
				nDNumber = (m_nMaxX * (nCountZ - 1)) + nCountX;
				if (m_pOneChip[nDNumber] != NULL) { m_pOneChip[nDNumber]->Uninit(); }
				m_pOneChip[nDNumber] = m_pOneChip[nSNumber];
				m_pOneChip[nSNumber] = NULL;
			}
		}
	}
	if (nNumZ > 0)
	{//Zが1以上の場合：奥にずらす
		for (int nCountX = 0; nCountX < m_nMaxX; nCountX++)
		{
			for (int nCountZ = m_nMaxZ - 2; nCountZ >= 0; nCountZ--)
			{
				nSNumber = (m_nMaxX * nCountZ) + nCountX;
				nDNumber = (m_nMaxX * (nCountZ + 1)) + nCountX;
				if (m_pOneChip[nDNumber] != NULL) { m_pOneChip[nDNumber]->Uninit(); }
				m_pOneChip[nDNumber] = m_pOneChip[nSNumber];
				m_pOneChip[nSNumber] = NULL;
			}
		}
	}

	for (int nCount = 0; nCount < m_nMaxX * m_nMaxZ; nCount++)
	{//NULLの奴を再生成
		if (m_pOneChip[nCount] != NULL) { continue; }
		CreateChip(nCount)->SetChip(1);
	}
}
//==================================================================================================//
//    * マップチップのX割れ移動 *
//==================================================================================================//
void	CMapChip::ChangePosX(int &nNumber, int nValue)
{
	int nSNumber, nDNumber;
	int nNumX0 = nNumber % m_nMaxX;

	if (nValue > 0)
	{//右に一マスずらす
		for (int nCountZ = 0; nCountZ < m_nMaxZ; nCountZ++)
		{
			for (int nCountX = 1; nCountX < nNumX0; nCountX++)
			{
				nSNumber = (m_nMaxX * nCountZ) + nCountX;
				nDNumber = (m_nMaxX * nCountZ) + (nCountX - 1);
				if (m_pOneChip[nDNumber] != NULL) { m_pOneChip[nDNumber]->Uninit(); }
				m_pOneChip[nDNumber] = m_pOneChip[nSNumber];
				m_pOneChip[nSNumber] = NULL;
			}
		}
	}
	else if (nValue < 0)
	{//左に一マスずらす
		for (int nCountZ = 0; nCountZ < m_nMaxZ; nCountZ++)
		{
			for (int nCountX = m_nMaxX - 2; nCountX >= nNumX0 + 1; nCountX--)
			{
				nSNumber = (m_nMaxX * nCountZ) + nCountX;
				nDNumber = (m_nMaxX * nCountZ) + (nCountX + 1);
				if (m_pOneChip[nDNumber] != NULL) { m_pOneChip[nDNumber]->Uninit(); }
				m_pOneChip[nDNumber] = m_pOneChip[nSNumber];
				m_pOneChip[nSNumber] = NULL;
			}
		}
	}
	for (int nCount = 0; nCount < m_nMaxX * m_nMaxZ; nCount++)
	{//NULLの奴を再生成
		if (m_pOneChip[nCount] != NULL) { continue; }
		CreateChip(nCount)->SetChip(1);
	}
}
//==================================================================================================//
//    * マップチップの管理元の一つのチップの削除 *
//==================================================================================================//
void	CMapChip::DeleteChip(int &nNumber)
{
	CChip *&pChip = m_pOneChip[nNumber]->GetChip(m_nSelect);
	if (pChip != NULL) { pChip->Uninit(); pChip = NULL; }
}
//==================================================================================================//
//    * マップチップの管理元の一つのチップの生成・変更 *
//==================================================================================================//
void	CMapChip::SettingModel(int &nNumber)
{
	if (m_pOneChip[nNumber] != NULL)
	{
		CChip *&pChip = m_pOneChip[nNumber]->GetChip(m_nSelect);
		if (m_pOneChip[nNumber] != NULL)
		{
			m_pOneChip[nNumber]->CreateChip(pChip, CChip::TYPE_MODEL);
			((CChip_Model*)pChip)->Set(m_ModelType);
			((CChip_Model*)pChip)->GetfPosY() = m_fInitHeight;
			((CChip_Model*)pChip)->GetCollision() = m_Collision;

			switch (m_ModelType)
			{
			case CChip_Model::TYPE_ROCK00:	((CChip_Model*)pChip)->GetfPosY() += 0.15f; break;
			case CChip_Model::TYPE_FENCE00: ((CChip_Model*)pChip)->GetfPosY() += 0.25f;	break;
			}
		}
	}
}
//==================================================================================================//
//    * マップチップの管理元の一つのチップの生成・変更 *
//==================================================================================================//
void	CMapChip::SettingItem(int &nNumber)
{
	if (m_pOneChip[nNumber] != NULL)
	{
		CChip *&pChip = m_pOneChip[nNumber]->GetChip(m_nSelect);
		if (m_pOneChip[nNumber] != NULL)
		{
			m_pOneChip[nNumber]->CreateChip(pChip, CChip::TYPE_MODEL);
			((CChip_Model*)pChip)->Set(m_ItemType);
			((CChip_Model*)pChip)->GetfPosY() = m_fInitHeight;
			((CChip_Model*)pChip)->GetCollision() = CChip::COLLISION_NO;
			((CChip_Model*)pChip)->GetState() = CChip_Model::STATE_ITEM;
		}
	}
}
//==================================================================================================//
//    * アイテムのドロップ *
//==================================================================================================//
void	CMapChip::DropItem(D3DXVECTOR3 pos, CChip_Model::TYPE model)
{
	CMapChip *&pMap = CManager::GetpMapChip();

	if (pMap == NULL) { return; }
	COneChip **&m_pOneChip = pMap->m_pOneChip;
	D3DXVECTOR3 &m_pos = pMap->Getpos();
	int			&m_nMaxX = pMap->GetnMaxX();
	int			nNumX, nNumZ, nNumber;

	nNumX = (int)((pos.x - m_pos.x + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumZ = (int)((pos.z - m_pos.z + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumber = (m_nMaxX * nNumZ) + nNumX;

	//チップがないなら
	if (m_pOneChip[nNumber] == NULL) { return; }

	int			&m_nMaxChip = m_pOneChip[nNumber]->GetnMaxChip();
	for (int nCount = 0; nCount < m_nMaxChip; nCount++)
	{//全チップ数回る
		CChip *&pChip = m_pOneChip[nNumber]->GetChip(nCount);
		if (pChip == NULL)
		{
			m_pOneChip[nNumber]->CreateChip(pChip, CChip::TYPE_MODEL);
			((CChip_Model*)pChip)->Set(model);
			((CChip_Model*)pChip)->GetfPosY() = pos.y / MAP_CHIP_SIZE;
			((CChip_Model*)pChip)->GetState() = CChip_Model::STATE_ITEM_MOVE;
			((CChip_Model*)pChip)->GetfCntState() = 1.0f;
			((CChip_Model*)pChip)->GetMove() = D3DXVECTOR3(0.035f, 0.075f, 0.0f);

			D3DXVECTOR3 WKpos = INIT_VECTOR;
			WKpos.x = (nNumber % m_nMaxX) * MAP_CHIP_SIZE + m_pos.x;
			WKpos.z = (nNumber / m_nMaxX) * MAP_CHIP_SIZE + m_pos.z;
			pChip->GetCollision() = CChip::COLLISION_NO;
			pChip->SetMtx(WKpos);
			break;
		}

	}

}
//==================================================================================================//
//    * モデルダウン後0番をNORMALに変更 *
//==================================================================================================//
void	CMapChip::DownSetField(D3DXVECTOR3 pos)
{
	CMapChip *&pMap = CManager::GetpMapChip();

	if (pMap == NULL) { return; }
	COneChip **&m_pOneChip = pMap->m_pOneChip;
	D3DXVECTOR3 &m_pos = pMap->Getpos();
	int			&m_nMaxX = pMap->GetnMaxX();
	int			nNumX, nNumZ, nNumber;

	nNumX = (int)((pos.x - m_pos.x + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumZ = (int)((pos.z - m_pos.z + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumber = (m_nMaxX * nNumZ) + nNumX;

	//チップがないなら
	if (m_pOneChip[nNumber] == NULL) { return; }

	m_pOneChip[nNumber]->GetChip(0)->GetCollision() = CChip::COLLISION_NORMAL;
}
//==================================================================================================//
//    * マップチップのマスの位置を返す *
//==================================================================================================//
D3DXVECTOR3 CMapChip::GetposChip(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 &m_pos = Getpos();
	int			&m_nMaxX = GetnMaxX();
	int			nNumX, nNumZ, nNumber;

	nNumX = (int)((pos.x - m_pos.x + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumZ = (int)((pos.z - m_pos.z + (MAP_CHIP_SIZE * 0.5f)) / MAP_CHIP_SIZE);
	nNumber = (m_nMaxX * nNumZ) + nNumX;

	pos.x = nNumX * MAP_CHIP_SIZE + m_pos.x;
	pos.z = nNumZ * MAP_CHIP_SIZE + m_pos.z;

	return D3DXVECTOR3(pos.x, 0.0f, pos.z);
}
//==================================================================================================//
//    * マップチップの管理元の一つのチップの高さ変更 *
//==================================================================================================//
void	CMapChip::UpHeightModel(int &nNumber, float fValue)
{
	CChip *&pChip = m_pOneChip[nNumber]->GetChip(m_nSelect);
	if (pChip == NULL) { return; }
	if (pChip->GetType() == CChip::TYPE_MODEL)
	{
		((CChip_Model*)pChip)->GetfPosY() += fValue;
	}
}
//==================================================================================================//
//    * マップチップの管理元の一つのチップの高さ変更 *
//==================================================================================================//
void	CMapChip::UpRotationModel(int &nNumber, float fValue)
{
	CChip *&pChip = m_pOneChip[nNumber]->GetChip(m_nSelect);
	if (pChip == NULL) { return; }
	if (pChip->GetType() == CChip::TYPE_MODEL)
	{
		float &fRot = ((CChip_Model*)pChip)->GetRot().y;
		fRot += fValue;
		if (fRot > D3DX_PI) { fRot -= D3DX_PI * 2.0f; }
		if (fRot < D3DX_PI) { fRot += D3DX_PI * 2.0f; }
	}
}
//==================================================================================================//
//    * マップチップの管理元の一つのチップの当たり判定変更 *
//==================================================================================================//
void	CMapChip::ChangeCollisionModel(int &nNumber)
{
	CChip *&pChip = m_pOneChip[nNumber]->GetChip(m_nSelect);
	if (pChip == NULL) { return; }
	pChip->GetCollision() = (CChip::COLLISION)(((int)pChip->GetCollision() + 1) % CChip::COLLISION_MAX);
}
//==================================================================================================//
//    * マップチップの管理元の一つのチップの生成・変更 *
//==================================================================================================//
void	CMapChip::SettingPolygon(int &nNumber)
{
	if (m_pOneChip[nNumber] != NULL)
	{
		CChip *&pChip = m_pOneChip[nNumber]->GetChip(m_nSelect);
		if (m_pOneChip[nNumber] != NULL)
		{
			m_pOneChip[nNumber]->CreateChip(pChip, CChip::TYPE_POLYGON);
			((CChip_Polygon*)pChip)->Set(m_PolyType, m_fInitHeight);
			((CChip_Polygon*)pChip)->GetCollision() = m_Collision;
		}
	}
}
//==================================================================================================//
//    * マップチップの管理元の一つのチップの高さ変更 *
//==================================================================================================//
void	CMapChip::UpRotationPolygon(int &nNumber, float fValue)
{
	CChip *&pChip = m_pOneChip[nNumber]->GetChip(m_nSelect);
	if (pChip == NULL) { return; }
	if (pChip->GetType() == CChip::TYPE_POLYGON)
	{
		float &fRot = ((CChip_Polygon*)pChip)->GetRot().y;
		fRot += fValue;
		if (fRot > D3DX_PI) { fRot -= D3DX_PI * 2.0f; }
		if (fRot < D3DX_PI) { fRot += D3DX_PI * 2.0f; }
	}
}
//==================================================================================================//
//    * マップチップのエディット時更新 *
//==================================================================================================//
void	CMapChip::EditTrue(void)
{
	SetMtx();
}
//==================================================================================================//
//    * マップチップの状態描画 *
//==================================================================================================//
void	CMapChip::StatusLog(int &nNumX, int &nNumZ, int &nNumber)
{
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "X最大  %d,  Z最大  %d\n", m_nMaxX, m_nMaxZ);
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "現在地 X %d,  Z %d\n", nNumX, nNumZ);
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "位置 X %.1f,  Z %.1f\n\n", nNumX * MAP_CHIP_SIZE, nNumZ * MAP_CHIP_SIZE);

	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "選択先 %d,  初期高さ %.1f\n", m_nSelect, m_fInitHeight);
	switch (m_Edit)
	{
	case EDIT_MODEL:
		CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "EDIT:MODEL  生成物%d\n", m_ModelType);
		switch (m_nEdit)
		{
		case 0: CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "変更先：角度d\n");		break;
		case 1: CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "変更先：当たり判定d\n");	break;
		}
		break;
	case EDIT_POLYGON:
		CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "EDIT:POLY   生成物%d\n", m_PolyType);
		switch (m_nEdit)
		{
		case 0: CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "変更先：角度d\n");		break;
		case 1: CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "変更先：当たり判定d\n");	break;
		}
		break;
	case EDIT_ITEM:
		CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "EDIT:ITEM  生成物%d\n", m_ItemType);
		CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "変更先：角度d\n");		break;
		break;
	case EDIT_ENEMY:
		CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "EDIT:ENEMY   生成物%d\n", m_EnmType);
		break;
	}
	m_nMaxSelect = 1;
	if (m_pOneChip != NULL)
	{//一マスごとのチップが生成されているなら
		if (nNumX > -1 && nNumX < m_nMaxX && nNumZ > -1 && nNumZ < m_nMaxZ)
		{//範囲内なら
			if (m_pOneChip[nNumber] != NULL)
			{//生成されていないなら無視
				m_pOneChip[nNumber]->StatusLog(m_nMaxSelect);
				if (m_pOneChip[nNumber]->GetnMaxChip() > 0)
				{//チップが1つ以上あるなら
					if (m_pOneChip[nNumber]->GetChip(m_nSelect) != NULL)
					{
						m_pOneChip[nNumber]->GetChip(m_nSelect)->GetbSelect() = true;
					}
				}
			}
		}
	}
}
//==================================================================================================//
//    * マップチップのマップ設定 *
//==================================================================================================//
void	CMapChip::SetMap(MAP Map)
{
	char aStr[32];

	m_Map = Map;

	GetMapFont(aStr);	//マップの文字列取得
	Load(aStr);			//マップのロード
}
//==================================================================================================//
//    * マップチップのマップごとの文字取得 *
//==================================================================================================//
void	CMapChip::SetMapData(void)
{
	CStory *pStory;
	switch (m_Map)
	{
	case MAP_TITLE:		SetSea();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 4.5f, MAP_CHIP_SIZE * 2.0f, MAP_CHIP_SIZE * 4.5f)); break;
	case MAP_SELECT:	SetSea();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 4.5f, MAP_CHIP_SIZE * 2.0f, MAP_CHIP_SIZE * 4.5f)); break;
	case MAP_PRACTICE:	
		CPlayer::GetnTime() = 100;
		SetSea();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 2.0f, MAP_CHIP_SIZE * 0.5f, MAP_CHIP_SIZE * 3.9f)); break;
	case MAP_PRINCESS:
		if (SceneCreate(pStory, STORY_PRIORITY)) { pStory->Set(CStory::STORY_01_Departure); }
		CPlayer::GetnTime() = 100;
		SetSea();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 6.0f, MAP_CHIP_SIZE * 0.0f, MAP_CHIP_SIZE * 1.0f)); break;
	case MAP_1:			
		CPlayer::GetnTime() = 100;
		SetSea();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 8.0f, 0.0f, MAP_CHIP_SIZE * 4.0f)); break;
	case MAP_2:			SetField();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 6.0f, 0.0f, MAP_CHIP_SIZE * 4.0f)); break;
	case MAP_3:			SetField();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 6.0f, MAP_CHIP_SIZE * 0.5f, MAP_CHIP_SIZE * 11.0f)); break;
	case MAP_4:			SetField();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 5.0f, MAP_CHIP_SIZE * 1.5f, MAP_CHIP_SIZE * 4.0f)); break;
	case MAP_BOSS:		
		if (SceneCreate(pStory, STORY_PRIORITY)) { pStory->Set(CStory::STORY_02_KingBattle); }
		CPlayer::GetnTime() = 100;
		SetField();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 9.0f, MAP_CHIP_SIZE * 5.0f, MAP_CHIP_SIZE * 2.0f));  break;
	case MAP_RESULT:
		if (SceneCreate(pStory, STORY_PRIORITY)) { pStory->Set(CStory::STORY_03_EATEAT); }
		CPlayer::GetnTime() = 100;
		SetSea();	CPlayer::SetPos(D3DXVECTOR3(MAP_CHIP_SIZE * 5.0f, MAP_CHIP_SIZE * 0.0f, MAP_CHIP_SIZE * 1.0f)); break;
	}
	CManager::GetCamera()->Reset();
	if (m_nClear > 0)
	{
		CCamera_Char *pCamera = CManager::GetCamera()->GetPlay(0)->GetChar();
		pCamera->GetposV().x += MAP_CHIP_SIZE * 3.0f;
		pCamera->GetposR().x += MAP_CHIP_SIZE * 3.0f;
	}

}
//==================================================================================================//
//    * マップチップの背景（フィールド）の生成 *
//==================================================================================================//
void	CMapChip::SetSea(void)
{
	CMapChip_BG_SEA *pBG;
	if (Create(pBG)) { m_pBG = pBG; }
	m_bMirror = true;
}
//==================================================================================================//
//    * マップチップの背景（フィールド）の生成 *
//==================================================================================================//
void	CMapChip::SetField(void)
{
	CMapChip_BG_Field *pBG;
	if (Create(pBG)) { m_pBG = pBG; }
	m_bMirror = false;
}
//==================================================================================================//
//    * マップチップのマップごとの文字取得 *
//==================================================================================================//
void	CMapChip::GetMapFont(char *aStr)
{
	switch (m_Map)
	{
	case MAP_TITLE:		strcpy(aStr, "Title.txt"); break;
	case MAP_SELECT:	strcpy(aStr, "Select.txt"); break;
	case MAP_PRACTICE:	strcpy(aStr, "Practice.txt"); break;
	case MAP_PRINCESS:	strcpy(aStr, "Practice.txt"); break;
	case MAP_1:			strcpy(aStr, "1-1.txt"); break;
	case MAP_2:			strcpy(aStr, "1-2.txt"); break;
	case MAP_3:			strcpy(aStr, "1-3.txt"); break;
	case MAP_4:			strcpy(aStr, "1-4.txt"); break;
	case MAP_BOSS:		strcpy(aStr, "Boss.txt"); break;
	case MAP_RESULT:	strcpy(aStr, "Practice.txt"); break;
	}
}
//==================================================================================================//
//    * マップチップのチップ生成 *
//==================================================================================================//
void	CMapChip::SampleMap(void)
{
	Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5, 10);
	for (int nCount = 0; nCount < m_nMaxOneChip; nCount++)
	{
		COneChip *pOneChip = CreateChip(nCount);
		if (pOneChip != NULL)
		{
			pOneChip->SetChip(1);

			CChip *&pChip = pOneChip->GetChip(0);

			//CChip *&pChip2 = pOneChip->GetChip(1);
			//pOneChip->CreateChip(pChip2, CChip::TYPE_MODEL);
			//((CChip_Model*)pChip2)->Set(CChip_Model::TYPE_BOX);
			//((CChip_Model*)pChip2)->GetfPosY() = 50.0f;
		}
	}
	SetMtx();
}
//==================================================================================================//
//    * マップチップのチップ生成 *
//==================================================================================================//
void	CMapChip::Load(char *aStr)
{
	FILE *pFile = NULL;
	MAP WKMap = m_Map;
	char aMap[128] = "data/TEXT/MAP/";		strcat(&aMap[0], &aStr[0]);
	char aEnm[128] = "data/TEXT/ENEMY/";	strcat(&aEnm[0], &aStr[0]);
	pFile = fopen(aMap, "r");
	int nData;

	if (pFile != NULL)
	{//Save　成功
		CScene::BreakObject(CScene::OBJTYPE_ENEMY);
		CEnemy::Load(aEnm);

		Reset(); Init();	//初期化
		m_Map = WKMap;
		fscanf(pFile, "%d %d %d\n", &m_nMaxX, &m_nMaxZ, &m_nMaxOneChip);
		Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_nMaxX, m_nMaxZ);	//生成

		for (int nCount = 0; nCount < m_nMaxOneChip; nCount++)
		{
			fscanf(pFile, "%d \n", &nData);
			
			if (nData != 0)
			{//チップがあるなら読み込み
				CreateChip(nCount)->Load(pFile);
			}
			else { CreateChip(nCount)->SetChip(10); }
			fscanf(pFile, "\n");
		}
		fclose(pFile);
		SetMapData();	//マップごとの処理実行
		SetMtx();		//マトリックス計算
	}
}
//==================================================================================================//
//    * マップチップのチップ生成 *
//==================================================================================================//
void	CMapChip::Save(char *aStr)
{
	FILE *pFile = NULL;
	pFile = fopen(&aStr[0], "w");

	if (pFile != NULL)
	{//Save　成功
		fprintf(pFile, "%d %d %d\n", m_nMaxX, m_nMaxZ, m_nMaxOneChip);
		for (int nCount = 0; nCount < m_nMaxOneChip; nCount++)
		{//チップの保存
			if (m_pOneChip[nCount] == NULL) { fprintf(pFile, "%d \n", 0); }	//生成されていないなら無視
			else
			{
				fprintf(pFile, "%d \n", 1);
				m_pOneChip[nCount]->Save(pFile);
			}
			fprintf(pFile, "\n");
		}
		CEnemy::Save();
		fclose(pFile);
	}
}