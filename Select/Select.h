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
class CEnemy;
//*****************************************************************************
// マクロの定義
//*****************************************************************************
#define MAX_GAME_PAUSE		(6)
#define GAME_PAUSE_INTERVAL	(50.0f)
#define GAME_PAUSE_LOGOX	(150.0f)
#define GAME_PAUSE_LOGOY	(50.0f)
#define MAX_OPTION_SELECT	(4)
#define MAX_MODE_SELECT	(3)

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

	CSelect() {};
	~CSelect() {};

	HRESULT Init(void);
	void	Update(void);
	void	EnemyUpdate(void);
	void	Uninit(void);

	void	SetState(STATE state);

	static bool &GetbDuo(void) { return m_bDuo; }
	STATE		&GetState(void) { return m_state; }

private://*****************************************************************************
		//変数宣言//***********************************************************************
	static	bool	m_bDuo;	//2人プレイかどうか
	STATE	m_state;
	float	m_fCntState;
	int		m_nCntWorkState;
	int		m_nSelect;
	int		m_nNumber;
	bool	m_bOption;
	CEnemy	*m_pEnemy[MAX_MODE_SELECT];
};

#endif
