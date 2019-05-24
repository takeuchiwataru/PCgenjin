//=============================================================================
//
// エネミー処理 [enemy.h]
// Author : Ryo Sugimoto
// Editor : Yuto Kodama
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "scene.h"
#include "motion.h"
class CPlayer;
class CEnemyAIBase;

//*****************************************************************************
// マクロの定義
//*****************************************************************************

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CEnemy : public CCharacter
{
public:
	typedef enum
	{
		DIFFICULTY_NORMAL,
		DIFFICULTY_HARD,
		DIFFICULTY_MAX
	}DIFFICULTY;
	typedef enum
	{
		TYPE_NONE,
		TYPE_GOBURINN,
		TYPE_TITLE,
		TYPE_VERSUS,
		TYPE_PRACTICE,
		TYPE_MAX
	}TYPE;

	typedef enum
	{
		AIState_Normal = 0,		//通常敵(左右移動)
		AIState_MAX,
	}AIState;

	CEnemy(int nPrioryity = CHAR_PRIORITY) : CCharacter::CCharacter(nPrioryity) {};
	~CEnemy() {};

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE Mtype, TYPE Etype, int nLevel);		//セット処理
	HRESULT Init(void);																				//初期化処理
	void	Update(void);																			//更新処理
	void	Draw(void);																				//描画処理
	void	Dead(void);																				//死亡処理
	void	Over(void);																				//消失処理

	static DIFFICULTY &GetDifficulty(void) { return m_Difficulty; }
	CCharacter *&GetpTarget(void)	{ return m_pTarget; }

	//AI設定(オーバーロード)
	void SetAIState(AIState state);
	void SetAIState(AIState state,D3DXVECTOR3 start,D3DXVECTOR3 goal);	//通常敵(左右移動)

private://*****************************************************************************
		//変数宣言//***********************************************************************
	static DIFFICULTY m_Difficulty;	//難易度
	CScene::TEXTURE tex;
	TYPE		m_Type;
	float		m_fMove;
	int			m_nCntFrame;
	int			m_nMaxFrame;
	bool		m_bDraw;
	CCharacter	*m_pTarget;

	//AI
	CEnemyAIBase*	m_pEnemyAI;
};

//=============================================================================
//
// エネミーAIクラス [enemy.h]
// Author : Yuto Kodama
//
//=============================================================================
class CEnemyAIBase		//敵AI基底クラス
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,
		TYPE_SLEEP,
		TYPE_MAX
	}AI_TYPE;
	CEnemyAIBase() {};
	~CEnemyAIBase() {};

	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual bool AIUpdate(CEnemy* pThis) = 0;

	AI_TYPE GetAItype(void) { return m_AItype; };
protected:
	AI_TYPE m_AItype;
private:
};

class CEnemyAI_Normal : public CEnemyAIBase		//敵AI(左右移動)クラス(基底クラス継承)
{
public:
	CEnemyAI_Normal() {};
	~CEnemyAI_Normal() {};

	void Init(void);
	void Uninit(void);
	bool AIUpdate(CEnemy* pThis);
	float CalMoveVector(float* pOut, D3DXVECTOR3 pos);
	void SetVecLeapPos(D3DXVECTOR3 start,D3DXVECTOR3 goal);

private:
	D3DXVECTOR3 m_vecLeapPos[2];	//二点間移動用の目標座標
	int			m_nNumLeap;			//次に移動するべき位置(m_vecLeapPosの配列内を指す)
};

class CEnemyAI_Sleep : public CEnemyAIBase		//敵AI(睡眠)クラス
{
public:
	CEnemyAI_Sleep() {};
	~CEnemyAI_Sleep() {};

	void Init(void);
	void Uninit(void);
	bool AIUpdate(CEnemy* pThis);

private:
	int m_nCntSleepInterval;	//再度睡眠に入るまでの時間計測用
};
#endif
