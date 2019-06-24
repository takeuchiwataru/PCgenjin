//=============================================================================
//
// シーン処理 [scene.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
//*****************************************************************************
// マクロの定義
//*****************************************************************************
#define MAX_SCENE		(8)					//シーンの最大優先順位
#define OBJ_PRIORITY	(5)					//3Dオブジェの優先順位
#define MAX_3DSCENE		(OBJ_PRIORITY + 1)					//3D最大の優先順位
#define START_2DSCENE	(MAX_3DSCENE)	//2D開始の優先順位
#define PAUSE_PRIORITY	(MAX_SCENE - 1)		//ポーズの優先順位

#define PAUSE_PRIORITY	(MAX_SCENE - 1)		//ポーズの優先順位
#define PAUSE_LENGTH	(75.0f)				//ポーズ上下枠の長さ

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CScene
{
public://*****************************************************************************
	typedef enum
	{
		DRAW_TYPE_NORMAL = 0,		//通常描画
		DRAW_TYPE_ADD,				//加算合成
		DRAW_TYPE_SUBTRACT,			//減算合成
		DRAW_TYPE_MULTIPLY,			//乗算合成
		DRAW_TYPE_OVERLAY,			//黒無視加算無し
		DRAW_TYPE_AER,			//黒無視加算無し
		DRAW_TYPE_ZNORMAL = 10,		//Z無視通常
		DRAW_TYPE_ZADD,				//Z無視加算
		DRAW_TYPE_ZSUBTRACT,		//Z無視減算
		DRAW_TYPE_ZMULTIPLY,		//乗算合成
		DRAW_TYPE_ZOVERLAY,			//黒無視加算無し
		DRAW_TYPE_NO,				//描画しない
		DRAW_TYPE_MIRROR,			//鏡
		DRAW_TYPE_MAX
	}DRAW_TYPE;
	typedef enum
	{//判定したい全クラス お前誰よ？->俺だよ俺ってやつ
		OBJTYPE_NONE,
		OBJTYPE_DUNGEON, OBJTYPE_MESH,
		OBJTYPE_EFFECT, OBJTYPE_ANIM3D, OBJTYPE_SALE,
		OBJTYPE_Satellite, OBJTYPE_ORBIT, OBJTYPE_LINE
		, OBJTYPE_CYLINDER, OBJTYPE_BULLET, OBJTYPE_BLOOD,
		OBJTYPE_BOSS, 
		//モデル//**********************************************
		OBJTYPE_PLAYER, OBJTYPE_ENEMY, OBJTYPE_OBJ,
		//画像//**********************************************
		OBJTYPE_OBJ_NO,	//モデル　判定：(有/無し)
		OBJTYPE_D_OBJ,	//ダンジョンオブジェ
		OBJTYPE_OTHER,	//ゲーム外カメラ用(UI用)
		OBJTYPE_UI,		//ユーザーインターフェイス
		OBJTYPE_NUMBER,
		OBJTYPE_TIMER,	//タイマー
		OBJTYPE_GOAL, OBJTYPE_SHOP,
		OBJTYPE_MAX
	}OBJTYPE;
	typedef struct
	{//種類ごとのモデル情報保存
		LPD3DXMESH		MeshModel = NULL;		//メッシュ情報へのポインタ
		LPD3DXBUFFER	pBuffMatModel = NULL;	//マテリアル情報へのポインタ
		DWORD			nNumMatModel = NULL;	//マテリアルの情報数
	}MODEL_DRAW;
	typedef enum
	{
		/* BG */			TEX_Title, TEX_Select, TEX_Select0,
		TEX_G_EXPLOSION, TEX_BG_EVENT, TEX_BG_BLOOD,
		TEX_Sea, TEX_UnderSea,
		/*ポーズ*/			TEX_Pause_BG, TEX_Pause_Logo,
		/* 雲 */			TEX_Fog000, TEX_Fog001,
		/* ロゴ */			TEX_TitleLogo, TEX_Press, TEX_HitLogo, TEX_Versus_Logo, TEX_ResultLogo,
		/* UI */			TEX_Arrow, TEX_S_Move, TEX_Weapon, TEX_CLEAR, TEX_Chat_Button, TEX_Tutorial000,
		/*GAME_UI*/			TEX_Help, TEX_PIcon, TEX_Objective, TEX_PUSH000, TEX_PUSH001,
		/*ロックオン*/		TEX_Lock_On,	/*ボタンUI*/		TEX_Button_UI,
		/*ゲージ*/			TEX_Gage, TEX_GageDeco,
		/*数字*/			TEX_Number,
		/*ランキング*/		TEX_RANKING0,	/*ランキング*/		TEX_RANKING1,
		/*ランキング*/		TEX_RANKING2,	/*ランキング*/		TEX_RANKING_TYPE,
		/*ヒット*/			TEX_HIT0, TEX_HIT1, TEX_HIT_BLOOD,
		/*死亡*/			TEX_Dead,		/*消失前兆*/		TEX_Omen,		/*消失*/			TEX_Over,
		/*エフェクト*/		TEX_Fire,		/*軌跡*/			TEX_Orbit,		/*波エフェクト*/	TEX_Circle,
		/*ゲート*/			TEX_GateE,		/*E 消える*/		TEX_Disappear,
		/*キャラ*/			TEX_BSword,		/*キャラ*/			TEX_BGoburin,
		/*選択マップ*/		TEX_SelectMap,
		/*Lポーション*/		TEX_Potion_L,	/*Eポーション*/		TEX_Potion_E,
		/*洞窟*/			TEX_Dungeon,	/*ゲート*/			TEX_Gate,
		/* 柵 */			TEX_Fence,		/* 岩 */			TEX_Stone,		/*白岩*/			TEX_Stone_M,
		/*鉄骨*/			TEX_Steel,		/*衛星*/			TEX_Satellite,	/*UI背景用の木*/	TEX_UI_Wood,
		/*方位磁針(本体)*/	TEX_Pos_Mag,	/*方位磁針(針)*/	TEX_Pos_Nee,

		/*チップ*/			TEX_BLOCK00, TEX_BLOCK01,

		/*自機*/			TEX_PLAYER_000,
		/*敵_0*/			TEX_ENEMY_000,

		/*ここからモデル用*/TEX_CHAR,
		/*マント*/			TEX_Cloak = TEX_CHAR,
		/*剣*/				TEX_AXE,		/*槍*/				TEX_Spear,		/*棍*/				TEX_Stick,
		/*爺顔*/			TEX_S_Face,		/*鬼顔*/			TEX_G_Face,

		/*タイトルモデル*/	TEX_TITLE_MODEL,// 竹内追加
		/*エンドロール*/	TEX_ENDROLL,	// 竹内追加
		/*タイトル3D*/		TEX_TITLE_3D,	// 竹内追加
		/*タイトル文字*/	TEX_TITLE_MOJI,	// 竹内追加
		/*ミサイル*/		TEX_MISSILE,	// 竹内追加
		TEX_MAX
	}TEXTURE;
	CScene::CScene(int nPrioryity = 3);
	~CScene();

	static LPDIRECT3DTEXTURE9	&Load(TEXTURE tex);
	static void	UnLoad(void);
	static void	ReleaseAll(void);
	static void	UpdateAll(void);
	static void	DrawAll(LPDIRECT3DDEVICE9 &pDevice);
	static void	Draw3D(LPDIRECT3DDEVICE9 &pDevice);
	static void	DrawObj(LPDIRECT3DDEVICE9 &pDevice);
	static void	Draw2D(LPDIRECT3DDEVICE9 &pDevice);
	static void	DrawMirror(LPDIRECT3DDEVICE9 &pD3DDevice);
	static D3DXPLANE GetPlane(void);

	static void	UninitAll(void);
	static void	BreakObject(void);			//オブジェクトの全破壊
	static void	BreakObject(OBJTYPE obj);	//指定したオブジェクトを破壊

	static CScene *&GetTop(int nPrioryity) { return m_pTop[nPrioryity]; };
	static CScene *&GetCur(int nPrioryity) { return m_pCur[nPrioryity]; };
	static int &GetnNumAll(int nPrioryity) { return m_nNumAll[nPrioryity]; };
	//*****************************************************************************
	virtual HRESULT Init(void)					 { return S_OK; };
	virtual void	Uninit(void) { m_bDeath = true; SetObjType(OBJTYPE_NONE); };
	virtual void	Draw(void)					 {};
	virtual void	Update(void)				 {};
	virtual void	DrawMirror(LPDIRECT3DDEVICE9 &pD3DDevice, D3DXPLANE &mtx)	 {};

	static int		&GetnCntStart(void)			 { return m_nCntStart; }
	static bool		&GetbPause(void)			 { return m_bPause; }
	static bool		DrawPrepare(CScene::DRAW_TYPE DrawType, LPDIRECT3DDEVICE9 &pD3DDevice);	//描画準備処理
	static bool		EndDraw(CScene::DRAW_TYPE DrawType, LPDIRECT3DDEVICE9 &pD3DDevice);	//描画準備処理

	D3DXVECTOR3	*Getpos(void);
	CScene	*&GetpNext(void) { return m_pNext; }
	CScene	*&GetpPrev(void) { return m_pPrev; }
	bool	&GetbDeath(void) { return m_bDeath; }
	void	SetObjType(OBJTYPE ObjType)			 { m_ObjType = ObjType; }
	OBJTYPE GetObjType(void)					 { return m_ObjType; }
	static LPDIRECT3DTEXTURE9	&GetTexture(int nNumber) { return m_pTexture[nNumber]; }
	static DRAW_TYPE	GetDrawTypeBase(void) { return m_nDraw; }
protected://*****************************************************************************
	void			Release(void);											//解放処理			
private://*****************************************************************************
	//変数宣言//***********************************************************************
	static DRAW_TYPE	m_nDraw;			//現在の描画方法
	static LPDIRECT3DTEXTURE9	m_pTexture[TEX_MAX];		// テクスチャへのポインタ
	static CScene	*m_pTop[MAX_SCENE];		// 開始位置
	static CScene	*m_pCur[MAX_SCENE];		// 最後尾(カレントの略->現在)
	static int		m_nNumAll[MAX_SCENE];				//Updateのスタート位置
	static int		m_nCntStart;				//Updateのスタート位置
	static bool		m_bPause;					//ポーズの有無

	CScene *m_pNext;				//次
	CScene *m_pPrev;				//前
	int				m_nPriority;	//自分の優先順位
	OBJTYPE			m_ObjType;		//オブジェクトタイプ
	bool			m_bDeath;		//死亡フラグ
};

//==================================================================================================//
//    * テンプレート定義 *
//==================================================================================================//
template<class T> bool SceneCreate(T *&pScene, int nPriority)
{
	pScene = NULL;
	pScene = new T(nPriority);
	if (pScene != NULL) { pScene->Init(); return true; }

	return false;
}
//==================================================================================================//
//    * テンプレート定義 *
//==================================================================================================//
template<class T> bool Create(T *&pScene)
{
	pScene = NULL;
	pScene = new T;
	if (pScene != NULL) { pScene->Init(); return true; }
	//MessageBox(0, "生成できない！", "", MB_OK);

	return false;
}

#endif
