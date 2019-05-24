//=============================================================================
//
// �G�l�~�[���� [enemy.h]
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
// �}�N���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X�̒�`
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
		AIState_Normal = 0,		//�ʏ�G(���E�ړ�)
		AIState_MAX,
	}AIState;

	CEnemy(int nPrioryity = CHAR_PRIORITY) : CCharacter::CCharacter(nPrioryity) {};
	~CEnemy() {};

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE Mtype, TYPE Etype, int nLevel);		//�Z�b�g����
	HRESULT Init(void);																				//����������
	void	Update(void);																			//�X�V����
	void	Draw(void);																				//�`�揈��
	void	Dead(void);																				//���S����
	void	Over(void);																				//��������

	static DIFFICULTY &GetDifficulty(void) { return m_Difficulty; }
	CCharacter *&GetpTarget(void)	{ return m_pTarget; }

	//AI�ݒ�(�I�[�o�[���[�h)
	void SetAIState(AIState state);
	void SetAIState(AIState state,D3DXVECTOR3 start,D3DXVECTOR3 goal);	//�ʏ�G(���E�ړ�)

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	static DIFFICULTY m_Difficulty;	//��Փx
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
// �G�l�~�[AI�N���X [enemy.h]
// Author : Yuto Kodama
//
//=============================================================================
class CEnemyAIBase		//�GAI���N���X
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

class CEnemyAI_Normal : public CEnemyAIBase		//�GAI(���E�ړ�)�N���X(���N���X�p��)
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
	D3DXVECTOR3 m_vecLeapPos[2];	//��_�Ԉړ��p�̖ڕW���W
	int			m_nNumLeap;			//���Ɉړ�����ׂ��ʒu(m_vecLeapPos�̔z������w��)
};

class CEnemyAI_Sleep : public CEnemyAIBase		//�GAI(����)�N���X
{
public:
	CEnemyAI_Sleep() {};
	~CEnemyAI_Sleep() {};

	void Init(void);
	void Uninit(void);
	bool AIUpdate(CEnemy* pThis);

private:
	int m_nCntSleepInterval;	//�ēx�����ɓ���܂ł̎��Ԍv���p
};
#endif
