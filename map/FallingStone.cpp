//=============================================================================
//
// 落石処理 [FallingStone.cpp]
// Author : 小松　啓祐
//
//=============================================================================
#include "FallingStone.h"
#include "manager.h"
#include "player.h"
#include "MapChip.h"

//*****************************************************************************
// マクロの定義
//*****************************************************************************

//=============================================================================
// 静的メンバ変数
//=============================================================================

//=============================================================================
// 落石の初期化処理
//=============================================================================
HRESULT CFallingStone::Init(void)
{
	CSceneModel::Init();

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSpeed = 0.0f;

	return S_OK;
}

//=============================================================================
// 落石の終了処理
//=============================================================================
void CFallingStone::Uninit(void)
{
	CSceneModel::Uninit();
}

//=============================================================================
// 落石の更新処理
//=============================================================================
void CFallingStone::Update(void)
{
	D3DXVECTOR3 &pos = CSceneModel::GetPosition();
	D3DXVECTOR3 &rot = CSceneModel::GetRotation();
	CPlayer *pPlayer;

	//CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "落石体力 : %d\n", m_nLife);

	m_move += D3DXVECTOR3(sinf(rot.y) * -m_fSpeed, 0.0f, cosf(rot.y) * -m_fSpeed);	// 移動
	m_move.x *= 0.95f;
	m_move.z *= 0.95f;
	rot += D3DXVECTOR3(-(m_fSpeed * 0.3f), 0.0f, 0.0f);	// 回転

	// 角度のリセット
	if (rot.x < -D3DX_PI)
	{
		rot.x += D3DX_PI * 2.0f;
	}
	if (rot.x > D3DX_PI)
	{
		rot.x -= D3DX_PI * 2.0f;
	}

	// 落下開始
	m_nLife--;
	if (m_nLife <= 0)
	{
		m_move.y -= 0.3f;
	}

	// 消去
	if (m_nLife < -120)
	{
		Uninit();
		return;
	}

	pos += m_move;	// 位置の更新
	CSceneModel::SetMtx();

	//　プレイヤーとの当たり判定
	pPlayer = CSceneModel::HitPlayer();
	if (pPlayer != NULL)
	{
		CCharacter *pChar = NULL;
		pPlayer->Damage(1.0f, pChar);
	}
}
//=============================================================================
// 落石の設定処理
//=============================================================================
void	CFallingStone::Set(D3DXVECTOR3 pos, float fRot)
{
	int nLife = 100;
	CSceneModel::Set(pos, D3DXVECTOR3(0.0f, fRot, 0.0f), INIT_COLLAR, MODEL_STONE, DRAW_TYPE_NORMAL, false);

	switch (CManager::GetpMapChip()->GetMap())
	{
	case CMapChip::MAP_1:	nLife = 220;	break;
	case CMapChip::MAP_2:	nLife = 90;		break;
	case CMapChip::MAP_3:	nLife = 420;	break;
	case CMapChip::MAP_4:	nLife = 220;	break;
	}
	SetState(nLife, 0.3f);
}
