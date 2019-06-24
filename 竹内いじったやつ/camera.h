//=============================================================================
//
// カメラ処理 [camera.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#include "manager.h"
//*****************************************************************************
// マクロの定義
//*****************************************************************************
#define		DRAW_ANGLE		(45.0f)				//カメラ本体 +上, -下
#define		DRAW_ANGLEP		(DRAW_ANGLE + 10.0f)				//カメラ本体 +上, -下
#define		DRAW_DISTANCE	(2000.0f * 2000.0f)				//カメラ本体 +上, -下
#define		DRAW_DISTANCE2	(100.0f * 100.0f)				//カメラ本体 +上, -下
#define		MAX_CAMERA_SPEED	(15)

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCamera
{
public:
	typedef enum
	{//モデルの種類
		CAMERA_TYPE_NORMAL,
		CAMERA_TYPE_CHAR,
		CAMERA_TYPE_OBJ,
		CAMERA_TYPE_EVENT,
		CAMERA_TYPE_MAX,
	}CAMERA_TYPE;
	CCamera() {};
	~CCamera() {};

	void Init(void);
	void Draw(void);
	void SetCamera(D3DXVECTOR3 WKposV);
	bool DrawCheck(D3DXVECTOR3 &pos, float fLength);
	void SetViewport(int left, int up, int right, int bottom);

	D3DXVECTOR3 &GetRot(void) { return m_rot; };
	D3DXVECTOR3 &GetposV(void) { return m_posV; };
	D3DXVECTOR3 &GetposR(void) { return m_posR; };
	D3DXVECTOR3 &GetvecU(void) { return m_vecU; };
	D3DXVECTOR3 &Gettargetpos(void) { return m_targetpos; };
	float		&GetfDistance(void) { return m_fDistance; };
	CAMERA_TYPE	&GetType(void) { return m_Type; };
	int	&GetnNumCamera(void) { return m_nNumCamera; };

	D3DXMATRIX	&GetMtxProjection(void) { return m_mtxProjection; };
	D3DXMATRIX	&GetMtxView(void) { return m_mtxView; };
	D3DVIEWPORT9	&GetViewPort(void) { return m_viewport; };


private://*****************************************************************************

	//変数宣言//***********************************************************************
	int			m_nNumCamera;	//カメラ番号
	CAMERA_TYPE m_Type;			//カメラタイプ
	D3DXVECTOR3 m_posV;			//視点
	D3DXVECTOR3 m_posR;			//注視点
	D3DXVECTOR3 m_vecU;
	D3DXVECTOR3 m_targetpos;	//追従する場所
	D3DXVECTOR3 m_rot;			//角度
	float		m_fDistance;	//カメラと注視点の距離

	D3DXMATRIX m_mtxProjection;		//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			//ビューマトリックス
	D3DVIEWPORT9 m_viewport;		//カメラ設定用
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCamera_Char : public CCamera
{
public:
	CCamera_Char()	{};
	~CCamera_Char() {};

	void Init(void);
	void Uninit(void) { delete this; };
	void Update(void);
	void Draw(void);
	void Reset(void);
	void SetCamera(void);
	void SetQuake(float fQuake, int nQuake);
	void SceneSmash(void);
	void SceneLabyrinth(void);
	void SceneBoss(void);
	void SceneEnd(void);

	bool		&GetbOperation(void)	{ return m_bOperation; }
	float		*&GetpDistance(void)	{ return m_pDistance; };
	D3DXVECTOR3 *&GetpChare(void)		{ return m_pChar; };
	D3DXVECTOR3 &GetAddPos(void)		{ return m_addpos; };
private://*****************************************************************************
		//変数宣言//***********************************************************************
	D3DXVECTOR3	*m_pChar;		//何のキャラを追従するか
	D3DXVECTOR3 m_addpos;		//キャラに加算する位置
	D3DXVECTOR3 m_goal;			//向かう位置
	float		m_fQuake;		//揺れの大きさ
	int			m_nQuake;		//F数カウント
	int			m_nMaxQuake;	//最大F数
	int			m_nQuakeAngle;	//揺れの角度保存用
	bool		m_bOperation;	//操作可能かどうか

	float		*m_pDistance;		//カメラと注視点の距離の目的値
	float		m_fGMagnification;	//目的にいくまでの倍率

	D3DXMATRIX m_mtxProjection;		//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			//ビューマトリックス
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCamera_Play
{
public:
	CCamera_Play() {};
	~CCamera_Play() {};

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Reset(void);

	CCamera_Char *&GetChar(void) { return m_pCamera_Char; }
	CCamera		 *&GetObj(void)  { return m_pCamera_Obj; }
private://*****************************************************************************
		//変数宣言//***********************************************************************
	CCamera_Char	*m_pCamera_Char;	//キャラクター追尾
	CCamera			*m_pCamera_Obj;		//オブジェのみ
};

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCamera_Manager
{
public:
	typedef enum
	{//モデルの種類
		STATE_NONE = 0,	//動かせない
		STATE_GAME,		//ゲーム
		STATE_MOVIE,	//ムービー
	}CAMERA_STATE;
	typedef enum
	{//モデルの種類
		VIEW_IGNORE = 0,	//何にも関わらない
		VIEW_FOLLOW,		//追従
		VIEW_WATCH,			//追わずに見るだけ

	}CAMERA_VIEW;
	typedef enum
	{//モデルの種類
		SCENE_VIEW_NORMAL = 0,	//通常通り動く
		SCENE_VIEW_STOP,		//モデルのみ止まる

	}SCENE_VIEW;
	typedef enum
	{//モデルの種類
		SCENE_TYPE_NO = 0,		//戻る　間違えようの対処
		SCENE_TYPE_SMASH,		//ボス前のシーン
		SCENE_TYPE_LABYRINTH,	//ラビリンス開始シーン
		SCENE_TYPE_BOSS,		//ボス前のシーン

	}SCENE_TYPE;
	typedef struct
	{
		CAMERA_STATE	state;		//状態
		CAMERA_VIEW		ViewC;		//見る状態 カメラ
		SCENE_VIEW		ViewS;		//見る状態 カメラ以外(モデル等)
		SCENE_TYPE		scene;			//何のシーンか
		D3DXVECTOR3		move;			//カメラの移動量
		CCamera			*pCamera;		//現在描画中のカメラ
		CSceneAnim2D	*p2DAnim;		//演出用アニメーション
		int				nCntState;		//ムービーの進行度
		int				nCntTime;		//シーンのフレーム数記録
		float			m_fDistance;	//シーンのキャラ間
		int				nSpeedX[MAX_PLAYER];		//X軸に動くカメラの速度
		int				nSpeedY[MAX_PLAYER];		//Y軸に動くカメラの速度
		bool			bReturnX[MAX_PLAYER];		//X軸の反転の有無
		bool			bReturnY[MAX_PLAYER];		//Y軸の反転の有無
	}Info;
	CCamera_Manager() {};
	~CCamera_Manager() {};

	void Init(void);
	void Update(void);
	void Uninit(void);
	void Uninit_Event(void);
	void Draw(void);
	void Reset(void);
	static void Save(void);
	static void Load(void);

	CCamera_Char *&GetEvent(void) { return m_pEvent; }
	CCamera_Play *&GetPlay(int nID) { return m_pPlay[nID]; }

	static bool DrawCheck(D3DXVECTOR3 &pos, float fLength);
	static CCamera_Char *&Create_Event(void);
	static CCamera_Play *&Create_Play(int nCount);
	static CCamera_Char *&SetScene(CCamera_Manager::SCENE_TYPE type);
	static Info &GetInfo(void) { return m_info; };
	void UpdateScene(void);
private://*****************************************************************************
	static Info	m_info;

	//変数宣言//***********************************************************************
	CCamera_Char *m_pEvent;
	CCamera_Play *m_pPlay[MAX_PLAYER];
};
#endif
