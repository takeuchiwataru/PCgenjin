//=============================================================================
//
// レンダリング処理 [renderer.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "SceneModel.h"
#include "Font.h"
#include "motion.h"

#include "2DPolygon.h"
#include "2DGage.h"
#include "3DPolygon.h"

#include "collision.h"
#include "renderer.h"
#include "camera.h"
#include "light.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CScene	*CScene::m_pTop[MAX_SCENE] = {};					// 現在の描画状態
CScene	*CScene::m_pCur[MAX_SCENE] = {};					// 現在の描画状態
int		CScene::m_nNumAll[MAX_SCENE] = { 0, 0, 0, 0, 0, 0, 0, 0 };	// 生成数
CScene::DRAW_TYPE		CScene::m_nDraw = CScene::DRAW_TYPE_NORMAL;					// 現在の描画状態
int		CScene::m_nCntStart = 0;				// 現在の描画状態
bool	CScene::m_bPause = false;				//ポーズの有無
LPDIRECT3DTEXTURE9	CScene::m_pTexture[TEX_MAX] = {};		// テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(int nPrioryity)
{
	//前に今のオブジェを入れる
	if (m_pCur[nPrioryity] != NULL) { m_pCur[nPrioryity]->GetpNext() = this; }	//前がいる
	else { m_pTop[nPrioryity] = this; }				//自分先頭

													//今に前のオブジェを入れる
	m_pPrev = m_pCur[nPrioryity];
	m_pNext = NULL;

	//今にこのオブジェを入れる
	m_pCur[nPrioryity] = this;
	m_nPriority = nPrioryity;
	m_nNumAll[nPrioryity]++;

	//何にも部類されないオブジェタイプに
	SetObjType(OBJTYPE_NONE);
	m_bDeath = false;
}
//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene(void) {}

//=============================================================================
// 画像の読み込み
//=============================================================================
LPDIRECT3DTEXTURE9	&CScene::Load(TEXTURE tex)
{
	if (tex < TEX_MAX)
	{//範囲確認
		if (m_pTexture[tex] == NULL)
		{//読み込んでないなら
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			switch (tex)
			{//読み込み 
			case TEX_Title:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/Title000.jpg", &m_pTexture[tex]);				break;
			case TEX_Select:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/Select001.jpg", &m_pTexture[tex]);				break;
			case TEX_Select0:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SELECT/Select000.png", &m_pTexture[tex]);			break;
			case TEX_G_EXPLOSION:D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/Game_BG2.jpg", &m_pTexture[tex]);				break;
			case TEX_BG_EVENT:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/Smash000.jpg", &m_pTexture[tex]);				break;
			case TEX_BG_BLOOD:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/blood_BG.jpg", &m_pTexture[tex]);				break;
			case TEX_Sea:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/sea000.jpg", &m_pTexture[tex]);				break;
			case TEX_UnderSea:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/river000.jpg", &m_pTexture[tex]);				break;

			case TEX_RANKING0:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SURVIVAL/RANKING000.jpg", &m_pTexture[tex]);		break;
			case TEX_RANKING1:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SURVIVAL/RANKING001.png", &m_pTexture[tex]);		break;
			case TEX_RANKING2:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SURVIVAL/kaenbeam.jpg", &m_pTexture[tex]);			break;
			case TEX_RANKING_TYPE:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SURVIVAL/RANKING002.png", &m_pTexture[tex]);	break;

			case TEX_Pause_BG:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/pause100.png", &m_pTexture[tex]);				break;
			case TEX_Pause_Logo:D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/LOGO/Pause_Logo.png", &m_pTexture[tex]);			break;
			case TEX_ResultLogo:D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/LOGO/Result_Logo.png", &m_pTexture[tex]);			break;

			case TEX_Tutorial000:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SELECT/Weapon_Tutorial.jpg", &m_pTexture[tex]);					break;
			case TEX_PIcon:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/PIcon.png", &m_pTexture[tex]);					break;
			case TEX_Weapon:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/LOGO/WEAPON_LOGO.png", &m_pTexture[tex]);			break;
			case TEX_CLEAR:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/congratulations.jpg", &m_pTexture[tex]);			break;
			case TEX_Objective:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/ObjectiveUI.png", &m_pTexture[tex]);				break;
			case TEX_PUSH000:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Push000.jpg", &m_pTexture[tex]);					break;
			case TEX_PUSH001:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Push001.jpg", &m_pTexture[tex]);					break;
			case TEX_Chat_Button:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Chat_Button000.png", &m_pTexture[tex]);		break;

			case TEX_Fog000:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Fog000.jpg", &m_pTexture[tex]);				break;
			case TEX_Fog001:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Fog001.jpg", &m_pTexture[tex]);				break;
			case TEX_GateE:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Gate000.jpg", &m_pTexture[tex]);				break;
			case TEX_Disappear:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Disappear.jpg", &m_pTexture[tex]);			break;

			case TEX_TitleLogo:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/LOGO/LABYRINTH_OF_BRAVE.png", &m_pTexture[tex]);				break;
			case TEX_Press:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/LOGO/Press_Any_Button.png", &m_pTexture[tex]);		break;
			case TEX_HitLogo:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/LOGO/Hit_Logo.png", &m_pTexture[tex]);				break;
			case TEX_Versus_Logo:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/LOGO/Versus_Logo.png", &m_pTexture[tex]);			break;

			case TEX_Dead:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Dead.jpg", &m_pTexture[tex]);				break;
			case TEX_Omen:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/OverOmen.jpg", &m_pTexture[tex]);			break;
			case TEX_Over:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/explosion.jpg", &m_pTexture[tex]);			break;

			case TEX_Arrow:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SELECT/Arrow.png", &m_pTexture[tex]);				break;
			case TEX_S_Move:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SELECT/Select_Move.jpg", &m_pTexture[tex]);			break;

			case TEX_BSword:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/BoxChar_100.jpg", &m_pTexture[tex]);			break;
			case TEX_BGoburin:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/goburinn_000.jpg", &m_pTexture[tex]);			break;

			case TEX_Potion_L:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Potion000.jpg", &m_pTexture[tex]);			break;
			case TEX_Potion_E:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Potion001.jpg", &m_pTexture[tex]);			break;
			case TEX_SelectMap:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/CharSelectMap0.jpg", &m_pTexture[tex]);		break;
			case TEX_Dungeon:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/DUNGEON/Dungeon000.jpg", &m_pTexture[tex]);			break;
			case TEX_Fence:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/fence.jpg", &m_pTexture[tex]);				break;
			case TEX_Stone:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/998_stone_.jpg", &m_pTexture[tex]);			break;
			case TEX_Stone_M:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/stone100.jpg", &m_pTexture[tex]);				break;
			case TEX_Steel:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Steel000.jpg", &m_pTexture[tex]);				break;
			case TEX_Satellite:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/satellite.jpg", &m_pTexture[tex]);			break;
			case TEX_Orbit:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Orbit000.jpg", &m_pTexture[tex]);			break;
			case TEX_Circle:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Effect_Circle000.jpg", &m_pTexture[tex]);	break;
			case TEX_GageDeco:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Gage_Decoration00.png", &m_pTexture[tex]);		break;
			case TEX_UI_Wood:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/UI_Wood000.jpg", &m_pTexture[tex]);			break;
			case TEX_Pos_Mag:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Position_Magnetic000.jpg", &m_pTexture[tex]);	break;
			case TEX_Pos_Nee:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Position_Needle000.jpg", &m_pTexture[tex]);	break;

			case TEX_Number:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/number000.png", &m_pTexture[tex]);				break;
			case TEX_Lock_On:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Lock_On000.jpg", &m_pTexture[tex]);				break;
			case TEX_Button_UI:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Button_UI001.jpg", &m_pTexture[tex]);			break;
			case TEX_Help:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Help.jpg", &m_pTexture[tex]);					break;
			case TEX_HIT0:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Hit000.jpg", &m_pTexture[tex]);				break;
			case TEX_HIT1:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Effect_DASH000.jpg", &m_pTexture[tex]);		break;
			case TEX_HIT_BLOOD:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Hit_Blood000.jpg", &m_pTexture[tex]);		break;
			case TEX_Fire:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/EFFECT/Fire000.png", &m_pTexture[tex]);				break;

			case TEX_BLOCK00:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/CHIP/TEXTURE/Field_000.jpg", &m_pTexture[tex]);		break;
			case TEX_BLOCK01:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/CHIP/TEXTURE/Field_001.jpg", &m_pTexture[tex]);		break;
			
			case TEX_PLAYER_000:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/CHARACTER/Player/PCgenjin_player_uv.jpg", &m_pTexture[tex]);		break;
			case TEX_ENEMY_000:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/CHARACTER/Enemy_0/PCgenjin_enemy_uv.jpg", &m_pTexture[tex]);		break;

			case TEX_Cloak:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Cloak000.jpg", &m_pTexture[tex]);				break;
			case TEX_AXE:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/axe_uv.jpg", &m_pTexture[tex]);				break;
			case TEX_Spear:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Spear000.jpg", &m_pTexture[tex]);				break;
			case TEX_Stick:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Sticks.jpg", &m_pTexture[tex]);				break;
			case TEX_S_Face:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Face000.jpg", &m_pTexture[tex]);				break;
			case TEX_G_Face:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/goburin000.jpg", &m_pTexture[tex]);			break;

			// 竹内追加
			case TEX_TITLE_MODEL:D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/title.jpg", &m_pTexture[tex]);				break;
			case TEX_ENDROLL:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/Endroll.jpg", &m_pTexture[tex]);					break;
			case TEX_TITLE_3D:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/3D.png", &m_pTexture[tex]);						break;
			case TEX_TITLE_MOJI:D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BG/pc.png", &m_pTexture[tex]);						break;
			case TEX_MISSILE:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/missile.jpg", &m_pTexture[tex]);				break;

			}
		}
		return m_pTexture[tex];
	}
	return m_pTexture[0];
}
//=============================================================================
// 画像の解放
//=============================================================================
void	CScene::UnLoad(void)
{
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{//全画像破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//==================================================================================================//
//    * 全解放関数 *
//==================================================================================================//
void CScene::ReleaseAll(void)
{
	CSceneModel::UnLoadModel();	//Modelの削除
	CCharacter::UnLoad();		//キャラパーツの削除
	CMotion::UnLoad();			//モーションの削除
	CFont::UnLoad();			//文字の終了
	UnLoad();

	if (CManager::GetCamera() != NULL) { CManager::GetCamera()->Uninit(); }
	if (CManager::GetLight() != NULL) { CManager::GetLight()->Uninit(); }

	BreakObject();
}
//=============================================================================
// 更新処理
//=============================================================================
void  CScene::UpdateAll(void)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;

	//生成数表示
	CManager::GetDLog()->Update();
	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "生成数\n 零：%d,  壱：%d,  弐：%d,  参：%d,  四：%d,  伍：%d,  六：%d,  七：%d\n"
	//	, m_nNumAll[0], m_nNumAll[1], m_nNumAll[2], m_nNumAll[3], m_nNumAll[4], m_nNumAll[5], m_nNumAll[6], m_nNumAll[7]);

	for (int nCntScene = (m_bPause ? MAX_SCENE - 1 : m_nCntStart); nCntScene < MAX_SCENE; nCntScene++)
	{//優先順位分回る
		pScene = m_pTop[nCntScene];
		while (pScene != NULL)
		{//NULLになるまで繰り返す
			pNext = pScene->GetpNext();	//Update中に消える可能性があるから
			if (!pScene->m_bDeath) { pScene->Update(); }
			pScene = pNext;
		}
	}
	CCollision::CollisionAll();
}
//=============================================================================
// 描画処理
//=============================================================================
void  CScene::DrawAll(LPDIRECT3DDEVICE9 &pDevice)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{//優先順位分回る
		pScene = m_pTop[nCntScene];
		while (pScene != NULL)
		{//NULLになるまで繰り返す
			pNext = pScene->GetpNext();	//Draw中に消えるかもしれないから
			if (!pScene->m_bDeath) { pScene->Draw(); }
			pScene = pNext;
		}
	}
}
//==================================================================================================//
//    * 3D描画処理 *
//==================================================================================================//
void	CScene::Draw3D(LPDIRECT3DDEVICE9 &pDevice)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;
	for (int nCntScene = 0; nCntScene < MAX_3DSCENE; nCntScene++)
	{//優先順位分回る
		pScene = m_pTop[nCntScene];
		while (pScene != NULL)
		{//NULLになるまで繰り返す
			pNext = pScene->GetpNext();	//Draw中に消えるかもしれないから
			if (!pScene->m_bDeath) { pScene->Draw(); }
			pScene = pNext;
		}
	}
}
//==================================================================================================//
//    * 3Dオブジェ描画処理 *
//==================================================================================================//
void	CScene::DrawObj(LPDIRECT3DDEVICE9 &pDevice)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;
	pScene = m_pTop[OBJ_PRIORITY];
	while (pScene != NULL)
	{//NULLになるまで繰り返す
		pNext = pScene->GetpNext();	//Draw中に消えるかもしれないから
		if (!pScene->m_bDeath) { pScene->Draw(); }
		pScene = pNext;
	}
}
//==================================================================================================//
//    * 2D描画処理 *
//==================================================================================================//
void	CScene::Draw2D(LPDIRECT3DDEVICE9 &pDevice)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;
	for (int nCntScene = START_2DSCENE; nCntScene < MAX_SCENE; nCntScene++)
	{//優先順位分回る
		pScene = m_pTop[nCntScene];
		while (pScene != NULL)
		{//NULLになるまで繰り返す
			pNext = pScene->GetpNext();	//Draw中に消えるかもしれないから
			if (!pScene->m_bDeath) { pScene->Draw(); }
			pScene = pNext;
		}
	}
}
//==================================================================================================//
//    * 反転描画処理 *
//==================================================================================================//
void	CScene::DrawMirror(LPDIRECT3DDEVICE9 &pD3DDevice)
{
	D3DXMATRIX	WKmtx;			//ワールドマトリックス
	CScene		*pScene = NULL;
	CScene		*pNext = NULL;
	D3DXPLANE	planeField;
	D3DXVECTOR3	pos, normal;
	D3DXVECTOR4	vecLight;
	D3DLIGHT9 &light = CManager::GetLight()->Getlight(0);

	pD3DDevice->GetTransform(D3DTS_WORLD, &WKmtx);

	//平面作成

	vecLight = D3DXVECTOR4(-light.Direction.x, -light.Direction.y, -light.Direction.z, 0.0f);
	pos = D3DXVECTOR3(WKmtx._41, -WKmtx._42, WKmtx._43);
	normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	D3DXMatrixShadow(&WKmtx, &vecLight, &planeField);

	for (int nCntScene = 0; nCntScene < MAX_3DSCENE; nCntScene++)
	{//優先順位分回る
		pScene = m_pTop[nCntScene];
		while (pScene != NULL)
		{//NULLになるまで繰り返す
			pNext = pScene->GetpNext();	//Draw中に消えるかもしれないから
			if (!pScene->m_bDeath) { pScene->DrawMirror(pD3DDevice, planeField); }
			pScene = pNext;
		}
	}
}
//==================================================================================================//
//    * 反転描画用平面取得処理 *
//==================================================================================================//
D3DXPLANE CScene::GetPlane(void)
{
	D3DXVECTOR3	pos, normal;
	D3DXPLANE	planeField;

	pos = INIT_VECTOR;
	normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	return planeField;
}
//==================================================================================================//
//    * 終了関数 *
//==================================================================================================//
void	CScene::UninitAll(void)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{//優先順位分回る
		pScene = m_pTop[nCntScene];
		while (pScene != NULL)
		{//NULLになるまで繰り返す
			pNext = pScene->GetpNext();	//保険
			if (pScene->m_bDeath) { pScene->Release(); }
			pScene = pNext;
		}
	}
}
//==================================================================================================//
//    * 描画準備関数 *
//==================================================================================================//
bool CScene::DrawPrepare(CScene::DRAW_TYPE DrawType, LPDIRECT3DDEVICE9 &pD3DDevice)
{
	if (DrawType == DRAW_TYPE_NO) { return true; }

	if (DrawType < DRAW_TYPE_NO)
	{
		if (m_nDraw / 10 != DrawType / 10)
		{//現在のZテストと描画方法が違うなら
			if (DrawType >= CScene::DRAW_TYPE_ZNORMAL)
			{// Zテスト解除
				pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
			}
			else
			{// Zテスト始動
				pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
			}
		}
		if (m_nDraw % 10 != DrawType % 10)
		{//現在の合成方法が違うなら
			switch (DrawType % 10)
			{//ほんとは3行あることを忘れてはいけない...
			case CScene::DRAW_TYPE_NORMAL:// 通常
				pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				break;
			case CScene::DRAW_TYPE_ADD:// αブレンディングを加算合成に設定
				pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				break;
			case CScene::DRAW_TYPE_SUBTRACT:// 減算
				pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
				pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				break;
			case CScene::DRAW_TYPE_MULTIPLY:
				pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO | D3DBLEND_ONE);
				pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);
				break;
			case CScene::DRAW_TYPE_OVERLAY:
				pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO | D3DBLEND_ONE);
				pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				break;
			case CScene::DRAW_TYPE_AER:
				pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				break;
			}
		}
		m_nDraw = DrawType;	//描画方法の代入
	}
	else
	{
		switch (DrawType)
		{
		case DRAW_TYPE_MIRROR:
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO | D3DBLEND_ONE);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);
			m_nDraw = DRAW_TYPE_MULTIPLY;

			//CManager::GetRenderer()->SetRenderer(false);
			//pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			// 深度バッファに書き込みはしない
			pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);			// 反転面描く

			pD3DDevice->Clear(0, NULL, (D3DCLEAR_STENCIL), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

			// ステンシルテストを使用する
			pD3DDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
			pD3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

			// ステンシルバッファの増減を1に設定する
			pD3DDevice->SetRenderState(D3DRS_STENCILREF, 0x1);
			pD3DDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
			pD3DDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);

			DrawMirror(pD3DDevice);
			pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			// 表面描く

			pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0x0000000F);
			pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
			pD3DDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
			//return true;

			break;
		}
	}

	return false;
}
//==================================================================================================//
//    * 描画終了時処理 *
//==================================================================================================//
bool CScene::EndDraw(CScene::DRAW_TYPE DrawType, LPDIRECT3DDEVICE9 &pD3DDevice)
{
	switch (DrawType)
	{
	case DRAW_TYPE_MIRROR:
		CManager::GetRenderer()->SetRenderer(true);

		//// 状態を元に戻す
		//pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		//pD3DDevice->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, FALSE);
		////pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		//// 深度テストはする
		//pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		//// ステンシルテストはする
		//pD3DDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		//// ステンシルバッファの値が==1のときに書き込む
		//pD3DDevice->SetRenderState(D3DRS_STENCILREF, 1);
		//pD3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		//pD3DDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
		//pD3DDevice->SetRenderState(D3DRS_CCW_STENCILZFAIL, D3DSTENCILOP_KEEP);
		//pD3DDevice->SetRenderState(D3DRS_CCW_STENCILFAIL, D3DSTENCILOP_KEEP);
		//pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);			// 両面描く


		//pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		return true;
	}
	return false;
}
//==================================================================================================//
//    * 自分削除関数 *
//==================================================================================================//
void CScene::Release()
{
	//前のやつに自分の次を託す
	if (m_pPrev != NULL) { m_pPrev->GetpNext() = m_pNext; }	//遺言書
	else { m_pTop[m_nPriority] = m_pNext; }	//先頭交代

											//次のやつに自分が消えたことを伝える
	if (m_pNext != NULL) { m_pNext->GetpPrev() = m_pPrev; }	//次と前をつなげる
	else { m_pCur[m_nPriority] = m_pPrev; } //最後尾交代

											//自分の削除
	m_nNumAll[m_nPriority]--;
	delete this;
}
//=============================================================================
//	全オブジェクトを破壊
//=============================================================================
void CScene::BreakObject(void)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{//優先順位分回る
		pScene = m_pTop[nCntScene];
		while (pScene != NULL)
		{//NULLになるまで繰り返す
			pNext = pScene->GetpNext();	//保険
			if (!pScene->m_bDeath) { pScene->Uninit(); }
			pScene = pNext;
		}
	}
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{//優先順位分回る
		while (m_pTop[nCntScene] != NULL)
		{//NULLになるまで繰り返す
			if (m_pTop[nCntScene]->m_bDeath) { m_pTop[nCntScene]->Release(); }
		}
	}
}
//=============================================================================
//	指定したオブジェクトを破壊
//=============================================================================
void CScene::BreakObject(OBJTYPE obj)
{
	CScene *pNext = NULL;
	CScene *pTarget = NULL;
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{//優先順位分回る
		pNext = m_pTop[nCntScene];
		while (pNext != NULL)
		{//NULLになるまで繰り返す
			pTarget = pNext;
			pNext = pNext->GetpNext();

			if (pTarget->GetObjType() == obj)
			{//オブジェタイプがかぶっているなら削除
				pTarget->Uninit();
				pTarget->SetObjType(OBJTYPE_NONE);
			}
		}
	}
}
//=============================================================================
// 位置を返す
//=============================================================================
D3DXVECTOR3	*CScene::Getpos(void)
{
	switch (m_ObjType)
	{
	case OBJTYPE_PLAYER:
	case OBJTYPE_ENEMY:
	case OBJTYPE_BOSS:
		return &((CCharacter*)this)->Getpos();
		break;
	}

	return NULL;
}
