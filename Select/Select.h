//=============================================================================
//
// セレクト処理 [Select.h]
// Author : 小松　啓祐
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
// クラスの定義
//*****************************************************************************
#define MAX_GAME_PAUSE		(6)
#define GAME_PAUSE_INTERVAL	(50.0f)
#define GAME_PAUSE_LOGOX	(150.0f)
#define GAME_PAUSE_LOGOY	(50.0f)
#define MAX_OPTION_SELECT	(4)

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSelect
{
public:
	typedef enum
	{
		STATE_NONE,			// 通常
		STATE_GAME,			// ゲーム開始
		STATE_CREDIT,		// クレジット画面
		STATE_TITLE,		// タイトルに戻る
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
		//変数宣言//***********************************************************************
	static	bool	m_bDuo;	//2人プレイかどうか
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
