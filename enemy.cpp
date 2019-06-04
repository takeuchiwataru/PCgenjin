//=============================================================================
//
// エネミー処理 [enemy.cpp]{CEnemy}
// Author : Ryo Sugimoto
// Editor : Yuto Kodama
//
//=============================================================================
#include "main.h"
#include "motion.h"
#include "enemy.h"
#include "player.h"
#include "bullet.h"
#include "camera.h"
#include "Game.h"
#include "Survival.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CEnemy::DIFFICULTY CEnemy::m_Difficulty = DIFFICULTY_NORMAL;
//==================================================================================================//
//    * エネミーのセット関数 *
//==================================================================================================//
void CEnemy::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE Mtype, TYPE Etype, int nLevel)
{
	float fValue = (CManager::GetbDuo() ? 1.35f : 1.0f);
	CCharacter::Set(pos, rot, Mtype);
	m_Type = Etype;
	SetStatus();

	switch (m_Type)
	{
	case TYPE_VERSUS:
		SetObjType(OBJTYPE_BOSS);
		break;
	case TYPE_NONE:		GetfMaxLife() *= 0.06f * fValue; GetfLife() = GetfMaxLife();	break;
	case TYPE_GOBURINN:	GetfMaxLife() *= 0.1f  * fValue; GetfLife() = GetfMaxLife();	break;
	case TYPE_TITLE:	GetfMaxLife() *= 1.0f * fValue; GetfLife() = GetfMaxLife();		break;
	}


	//AI
	m_pEnemyAI = NULL;
	switch (Mtype)
	{
	case CMotion::TYPE::TYPE_ENEMY_0:
		m_pEnemyAI = new CEnemyAI_Normal;
		break;
	}

	if (m_pEnemyAI != NULL)
	{
		m_pEnemyAI->Init();
	}

}
//=============================================================================
// エネミーの初期化処理
//=============================================================================
HRESULT  CEnemy::Init(void)
{
	CCharacter::Init();
	tex = CScene::TEX_ENEMY_000;
	m_pTarget	= NULL;
	m_nCntFrame = 0;
	m_nMaxFrame = 0;
	m_fMove		= 0.0f;

	SetObjType(CScene::OBJTYPE_ENEMY);
	GetTeam() = CCharacter::TEAM_ENEMY;


	return S_OK;
}
//=============================================================================
// エネミーの更新処理
//=============================================================================
void	CEnemy::Update(void)
{
	CInputKeyboard	*pInputKey = CManager::GetInputKey();
	bool			bMove = false;
	D3DXVECTOR3 &m_pos = Getpos();

	//AIの制御
	if (m_pEnemyAI != NULL)
	{
		bMove = m_pEnemyAI->AIUpdate(this);
	}

	//モーション確認用
	if (pInputKey->GetPress(DIK_T))
	{
		D3DXVECTOR3 &pos = CManager::GetPlayer(0)->Getpos();
		GetnNumMotion(1) = MOTION_WALK; bMove = true;
		GetfRot() = atan2f(pos.x - m_pos.x, pos.z - m_pos.z) + D3DX_PI;
	}
	if (pInputKey->GetPress(DIK_G)) { GetnNumMotion(1) = 2; }
	if (pInputKey->GetPress(DIK_B)) { GetnNumMotion(1) = 4; }
	if (pInputKey->GetPress(DIK_V)) { GetnNumMotion(1) = 5; }
	if (pInputKey->GetPress(DIK_C)) { GetnNumMotion(1) = 6; Dead(); GetfLife() = 0; }

	//親の更新
	CCharacter::Update(bMove);
}
//=============================================================================
// エネミーの描画処理
//=============================================================================
void	CEnemy::Draw(void)
{
	if (CManager::GetCamera()->GetInfo().pCamera->GetnNumCamera() == 0) { m_bDraw = false; }
	if (CManager::GetCamera()->DrawCheck(Getpos(), 100.0f))
	{
		LPDIRECT3DDEVICE9	&pDevice = CManager::GetRenderer()->GetDevice();	//デバイスの取得

		m_bDraw = true;
		pDevice->SetTexture(0, CScene::Load(tex));
		CCharacter::Draw();
		pDevice->SetTexture(0, NULL);

		CCharacter::DrawGage();
	}
}
//=============================================================================
// エネミーの死亡処理
//=============================================================================
void	CEnemy::Dead(void)
{
	if (m_pEnemyAI != NULL)
	{
		m_pEnemyAI->Uninit();

		delete m_pEnemyAI;
		m_pEnemyAI = NULL;
	}

	if (CManager::GetMode() == CManager::MODE_SURVIVAL) { CManager::GetSurvival()->DeadEnemy(); }
	if (CManager::GetMode() == CManager::MODE_PRACTICE) { GetfLife() = 1.0f; }
	CCharacter::Dead();
}
//=============================================================================
// エネミーの消失処理
//=============================================================================
void	CEnemy::Over(void)
{
	if (m_pEnemyAI != NULL)
	{
		m_pEnemyAI->Uninit();

		delete m_pEnemyAI;
		m_pEnemyAI = NULL;
	}

	switch (m_Type)
	{
	case TYPE_NONE: break;
	case TYPE_TITLE: CManager::GetGame()->SetState(CGame::STATE_CLEAR); break;
	}
	CCharacter::Over();
}

//=============================================================================
// エネミーのAI設定処理
//=============================================================================
void CEnemy::SetAIState(AIState state) {

}
void	CEnemy::SetAIState(AIState state, D3DXVECTOR3 start, D3DXVECTOR3 goal){
	if (state == AIState_Normal)
	{
		if (m_pEnemyAI != NULL&& m_pEnemyAI->GetAItype() == CEnemyAIBase::TYPE_NORMAL)
		{
			CEnemyAI_Normal* pAI = (CEnemyAI_Normal*)m_pEnemyAI;
			pAI->SetVecLeapPos(start, goal);
		}
	}
}


//=============================================================================
//
// "敵001"基本敵AIの処理 [enemy.cpp] {CEnemyAI_Normal}
// Author : Yuto Kodama
//
//=============================================================================
//==============================================================
// 初期化処理{CEnemyAI_Normal}
//==============================================================
void CEnemyAI_Normal::Init(void) {
	m_vecLeapPos[0] = D3DXVECTOR3(255.0f, 0.0f, 85.0f);
	m_vecLeapPos[1] = D3DXVECTOR3(595.0f, 0.0f, 85.0f);
	m_nNumLeap = 0;

	m_AItype = TYPE_NORMAL;
}

//==============================================================
// 終了処理{CEnemyAI_Normal}
//==============================================================
void CEnemyAI_Normal::Uninit(void) {

}

//==============================================================
// 更新処理{CEnemyAI_Normal}
//==============================================================
bool CEnemyAI_Normal::AIUpdate(CEnemy* pThis)
{
	if (pThis != NULL)
	{
		bool bMove = true;
		D3DXVECTOR3 &PlayerPos = CManager::GetPlayer(0)->Getpos();		//プレイヤの座標
		D3DXVECTOR3 &ThisPos = pThis->Getpos();							//自身の座標

		//移動量の倍率設定
		pThis->GetMoveScaling() = 0.25f;

		//移動制御
		pThis->GetnNumMotion(1) = CEnemy::MOTION_WALK;
		pThis->GetfRot() = CalMoveVector(NULL, ThisPos) + D3DX_PI;

		//攻撃制御
		if (sqrtf((PlayerPos.x - ThisPos.x) * (PlayerPos.x - ThisPos.x) +
			(PlayerPos.y - ThisPos.y) * (PlayerPos.y - ThisPos.y) +
			(PlayerPos.z - ThisPos.z) * (PlayerPos.z - ThisPos.z)) <= 250.0f)
		{
			if (pThis->GetnNumMotion(1) != 2)
			{
				pThis->GetfRot() = atan2f(PlayerPos.x - ThisPos.x, PlayerPos.z - ThisPos.z) + D3DX_PI;
				pThis->GetnNumMotion(1) = 2;
			}
		}
		return bMove;
	}

	return false;
}

//==============================================================
// 移動角度計算処理{CEnemyAI_Normal}
//==============================================================
float CEnemyAI_Normal::CalMoveVector(float* pOut, D3DXVECTOR3 pos){
	D3DXVECTOR3 posDest = m_vecLeapPos[m_nNumLeap];	//目標
	float fRot = 0.0f;

	if (sqrtf((posDest.x - pos.x) * (posDest.x - pos.x) +
		(posDest.y - pos.y) * (posDest.y - pos.y) +
		(posDest.z - pos.z) * (posDest.z - pos.z)) >= 5.0f)
	{//目標との距離が一定以下なら
		fRot = atan2f(posDest.x - pos.x,posDest.z - pos.z);
	}
	else
	{
		m_nNumLeap = (m_nNumLeap + 1) % 2;
	}

	if (pOut != NULL) { *pOut = fRot; }//結果を格納

	return fRot;
}

//==============================================================
// 目標地点設定処理{CEnemyAI_Normal}
//==============================================================
void CEnemyAI_Normal::SetVecLeapPos(D3DXVECTOR3 start, D3DXVECTOR3 goal){
	m_vecLeapPos[0] = start;
	m_vecLeapPos[1] = goal;
}

//=============================================================================
//
// "敵002"睡眠敵AIの処理 [enemy.cpp] {CEnemyAI_Sleep}
// Author : Yuto Kodama
//
//=============================================================================

//==============================================================
// 初期化処理{CEnemyAI_Sleep}
//==============================================================
void CEnemyAI_Sleep::Init(void){
	m_nCntSleepInterval = 0;
	m_AItype = TYPE_SLEEP;
}

//==============================================================
// 終了処理{CEnemyAI_Sleep}
//==============================================================
void CEnemyAI_Sleep::Uninit(void) {

}

//==============================================================
// 更新処理{CEnemyAI_Sleep}
//==============================================================
bool CEnemyAI_Sleep::AIUpdate(CEnemy* pThis){
	return false;
}