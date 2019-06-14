//=============================================================================
//
// �Z���N�g���� [Select.h]
// Author : �����@�[�S
//
//=============================================================================
#ifndef _SELECT_H_
#define _SELECT_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

class CFont;
class CTime;
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
#define MAX_GAME_PAUSE		(6)
#define GAME_PAUSE_INTERVAL	(50.0f)
#define GAME_PAUSE_LOGOX	(150.0f)
#define GAME_PAUSE_LOGOY	(50.0f)
#define MAX_OPTION_SELECT	(4)

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSelect
{
public:
	typedef enum
	{
		STATE_NONE,			// �ʏ�
		STATE_GAME,			// �Q�[���J�n
		STATE_CREDIT,		// �N���W�b�g���
		STATE_TITLE,		// �^�C�g���ɖ߂�
		STATE_MAX
	}STATE;

	CSelect() { for (int nCount = 0; nCount < MAX_GAME_PAUSE; nCount++) { m_pScene2D[nCount] = NULL; } };
	~CSelect() {};

	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);

	void	SetState(STATE state);

	static bool &GetbDuo(void) { return m_bDuo; }
	STATE		&GetState(void) { return m_state; }

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	static	bool	m_bDuo;	//2�l�v���C���ǂ���
	STATE	m_state;
	STATE	m_workState;
	float	m_fCntState;
	int		m_nCntWorkState;
	int		m_nSelect;
	int		m_nNumber;
	bool	m_bOption;
	CFont	 *m_pFont[MAX_OPTION_SELECT];
	CScene2D *m_pScene2D[MAX_GAME_PAUSE];
};

#endif
