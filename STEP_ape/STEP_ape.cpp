// STEP_ape.cpp : DLL 用の初期化処理の定義を行います。
//

#include "stdafx.h"
#include "STEP_ape.h"
#include "STEPlugin.h"

#include "Tag_Ape.h"

#include "DlgSetup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern bool GetValues_mp3infp(FILE_INFO *pFileMP3);
extern void Free_mp3infp();

#define ID3_LEN_TRACK_NAME		30		// トラック名    (文字列…30BYTE)
#define ID3_LEN_ARTIST_NAME		30		// アーティスト名(文字列…30BYTE)
#define ID3_LEN_ALBUM_NAME		30		// アルバム名    (文字列…30BYTE)
#define ID3_LEN_COMMENT			30		// コメント      (文字列…30BYTE)
#define ID3_LEN_YEAR			4		// リリース年号  (文字列… 4BYTE)

//
//	メモ!
//
//		この DLL が MFC DLL に対して動的にリンクされる場合、
//		MFC 内で呼び出されるこの DLL からエクスポートされた
//		どの関数も関数の最初に追加される AFX_MANAGE_STATE 
//		マクロを含んでいなければなりません。
//
//		例:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 通常関数の本体はこの位置にあります
//		}
//
//		このマクロが各関数に含まれていること、MFC 内の
//		どの呼び出しより優先することは非常に重要です。
//		これは関数内の最初のステートメントでなければな
//		らないことを意味します、コンストラクタが MFC 
//		DLL 内への呼び出しを行う可能性があるので、オブ
//		ジェクト変数の宣言よりも前でなければなりません。
//
//		詳細については MFC テクニカル ノート 33 および
//		58 を参照してください。
//

/////////////////////////////////////////////////////////////////////////////
// CSTEP_apeApp

BEGIN_MESSAGE_MAP(CSTEP_apeApp, CWinApp)
	//{{AFX_MSG_MAP(CSTEP_apeApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSTEP_apeApp の構築

CSTEP_apeApp::CSTEP_apeApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance の中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CSTEP_apeApp オブジェクト

CSTEP_apeApp theApp;

UINT nPluginID;
UINT nFileTypeAPE;
UINT nFileTypeAPEID3; /* タグがID3形式 */

CString strINI;
bool bOptGenreListSelect;

STEP_API LPCTSTR WINAPI STEPGetPluginInfo(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return "Version 1.01 Copyright (C) 2003-2006 haseta\r\nMonkey's Audio形式をサポートしています";
}


STEP_API bool WINAPI STEPInit(UINT pID, LPCTSTR szPluginFolder)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (Initialize() == false)	return false;
	nPluginID = pID;

	// INIファイルの読み込み
	strINI = szPluginFolder;
	strINI += "STEP_ape.ini";
	bOptGenreListSelect = GetPrivateProfileInt("APE", "GenreListSelect", 0, strINI) ? true : false;

	HBITMAP hAPEBitmap = LoadBitmap(theApp.m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_APE));
	nFileTypeAPE = STEPRegisterExt(nPluginID, "ape", hAPEBitmap);
	nFileTypeAPEID3 = STEPRegisterExt(nPluginID, "ape", hAPEBitmap);
	DeleteObject(hAPEBitmap);

	return true;
}

STEP_API void WINAPI STEPFinalize() {
	Finalize();
}

STEP_API UINT WINAPI STEPGetAPIVersion(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return STEP_API_VERSION;
}

STEP_API LPCTSTR WINAPI STEPGetPluginName(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return "STEP_ape";
}

STEP_API bool WINAPI STEPSupportSIF(UINT nFormat) {
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return true;
}

STEP_API bool WINAPI STEPSupportTrackNumberSIF(UINT nFormat) {
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return true;
}

STEP_API CONTROLTYPE WINAPI STEPGetControlType(UINT nFormat, COLUMNTYPE nColumn, bool isEditSIF)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (!isEditSIF)	return _NULL;
	switch (nColumn) {
	case COLUMN_TRACK_NAME:
	case COLUMN_ARTIST_NAME:
	case COLUMN_ALBUM_NAME:
	case COLUMN_TRACK_NUMBER:
	case COLUMN_YEAR:
	case COLUMN_COMPOSER:
	case COLUMN_ORIG_ARTIST:
		return _EDIT;
	case COLUMN_COMMENT:
		return _MEDIT;
	case COLUMN_GENRE:
		if (bOptGenreListSelect) {
			return _CBOX;
		} else {
			return _EDIT;
		}
	}
	return _NULL;
}

STEP_API UINT WINAPI STEPGetColumnMax(UINT nFormat, COLUMNTYPE nColumn, bool isEditSIF) {
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (nFormat == nFileTypeAPE || true) {
		switch (nColumn) {
		case COLUMN_TRACK_NAME:		return 1024;
		case COLUMN_ARTIST_NAME:	return 1024;
		case COLUMN_ALBUM_NAME:		return 1024;
		case COLUMN_TRACK_NUMBER:	return 1024;
		case COLUMN_YEAR:			return 1024;
		case COLUMN_GENRE:			return 1024;
		case COLUMN_COMMENT:		return 1024;
		case COLUMN_COMPOSER:		return 1024;
		case COLUMN_ORIG_ARTIST:	return 1024;
		}
	/*
	} else if (nFormat == nFileTypeAPEID3) {
		switch (nColumn) {
		case COLUMN_TRACK_NAME:		return ID3_LEN_TRACK_NAME;
		case COLUMN_ARTIST_NAME:	return ID3_LEN_ARTIST_NAME;
		case COLUMN_ALBUM_NAME:		return ID3_LEN_ALBUM_NAME;
		case COLUMN_TRACK_NUMBER:	return 3;
		case COLUMN_YEAR:			return ID3_LEN_YEAR;
		case COLUMN_GENRE:			return 3;
		case COLUMN_COMMENT:		return ID3_LEN_COMMENT;
		}
	*/
	}
	return 0;
}

bool ReadTagAPE(FILE_INFO *pFileMP3)
{
	GetValues_mp3infp(pFileMP3);
	CTag_Ape ape;
	if (ape.Load(GetFullPath(pFileMP3)) != ERROR_SUCCESS) {
		return false;
	}

	
	CString buff;
	// トラック名
	ape.GetComment(CTag_Ape::APE_TAG_FIELD_TITLE, buff);
	SetTrackNameSI(pFileMP3, buff);
	// アーティスト名
	ape.GetComment(CTag_Ape::APE_TAG_FIELD_ARTIST, buff);
	SetArtistNameSI(pFileMP3, buff);
	// アルバム名
	ape.GetComment(CTag_Ape::APE_TAG_FIELD_ALBUM, buff);
	SetAlbumNameSI(pFileMP3, buff);
	// リリース年号
	ape.GetComment(CTag_Ape::APE_TAG_FIELD_YEAR, buff);
	SetYearSI(pFileMP3, buff);
	// コメント
	ape.GetComment(CTag_Ape::APE_TAG_FIELD_COMMENT, buff);
	SetCommentSI(pFileMP3, buff);
	// トラック番号
	ape.GetComment(CTag_Ape::APE_TAG_FIELD_TRACK, buff);
	SetTrackNumberSI(pFileMP3, buff);
	// ジャンル番号
	ape.GetComment(CTag_Ape::APE_TAG_FIELD_GENRE, buff);
	SetGenreSI(pFileMP3, buff);
	//SetBGenre(STEPGetGenreCode(buff));
	// 作曲者
	ape.GetComment("Composer", buff);
	SetComposerSI(pFileMP3, buff);
	// パフォーマー
	ape.GetComment("Performer", buff);
	SetOrigArtistSI(pFileMP3, buff);
	// ファイル形式：APE
	SetFileTypeName(pFileMP3, "Monkey's Audio");
	if (!ape.HasApetag() && ape.HasId3tag()) {
		SetFormat(pFileMP3, nFileTypeAPEID3);
		SetFileTypeName(pFileMP3, "Monkey's Audio(ID3)");
	} else {
		SetFormat(pFileMP3, nFileTypeAPE);
		if (ape.HasApetag()) {
			if (ape.isApetagV1()) {
				SetFileTypeName(pFileMP3, "Monkey's Audio(APE)");
			} else {
				SetFileTypeName(pFileMP3, "Monkey's Audio(APEv2)");
			}
		}
	}

	return true;
}

STEP_API UINT WINAPI STEPLoad(FILE_INFO *pFileMP3, LPCTSTR szExt)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (stricmp(szExt, "ape") == 0) {
		if (ReadTagAPE(pFileMP3) == false) {
			CString	strMsg;
			strMsg.Format("%s の読み込みに失敗しました", GetFullPath(pFileMP3));
			MessageBox(NULL, strMsg, "Monkey's Audioファイルの読み込み失敗", MB_ICONSTOP|MB_OK|MB_TOPMOST);
			return STEP_ERROR;
		} else {
			return STEP_SUCCESS;
		}
	}
	return STEP_UNKNOWN_FORMAT;
}

bool WriteTagAPE(FILE_INFO *pFileMP3)
{
	CTag_Ape ape;
	if (ape.Load(GetFullPath(pFileMP3)) != ERROR_SUCCESS) {
		return false;
	}
	//ape.Release();
	// トラック名
	ape.SetComment(CTag_Ape::APE_TAG_FIELD_TITLE, GetTrackNameSI(pFileMP3));
	// アーティスト名
	ape.SetComment(CTag_Ape::APE_TAG_FIELD_ARTIST, GetArtistNameSI(pFileMP3));
	// アルバム名
	ape.SetComment(CTag_Ape::APE_TAG_FIELD_ALBUM, GetAlbumNameSI(pFileMP3));
	// リリース年号
	ape.SetComment(CTag_Ape::APE_TAG_FIELD_YEAR, GetYearSI(pFileMP3));
	// コメント
	ape.SetComment(CTag_Ape::APE_TAG_FIELD_COMMENT, GetCommentSI(pFileMP3));
	// トラック番号
	ape.SetComment(CTag_Ape::APE_TAG_FIELD_TRACK, GetTrackNumberSI(pFileMP3));
	// ジャンル番号
	ape.SetComment(CTag_Ape::APE_TAG_FIELD_GENRE, GetGenreSI(pFileMP3));
	// 作曲者
	ape.SetComment("Composer", GetComposerSI(pFileMP3));
	//  パフォーマー
	ape.SetComment("Performer", GetOrigArtistSI(pFileMP3));

	if (ape.Save(GetFullPath(pFileMP3)) != ERROR_SUCCESS) {
		return false;
	}

	return true;
}

STEP_API UINT WINAPI STEPSave(FILE_INFO *pFileMP3)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	UINT nFormat = GetFormat(pFileMP3);

	if (nFormat == nFileTypeAPE || nFormat == nFileTypeAPEID3) {
		if (WriteTagAPE(pFileMP3) == false) {
			CString	strMsg;
			strMsg.Format("%s の書き込みに失敗しました", GetFullPath(pFileMP3));
			MessageBox(NULL, strMsg, "Monkey's Audioファイルの書き込み失敗", MB_ICONSTOP|MB_OK|MB_TOPMOST);
			return STEP_ERROR;
		}
		return STEP_SUCCESS;
	}
	return STEP_UNKNOWN_FORMAT;
}

STEP_API void WINAPI STEPShowOptionDialog(HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CDlgSetup dlg1;
	CPropertySheet page;
	dlg1.m_bGenreListSelect = bOptGenreListSelect;
	page.AddPage(&dlg1);
	page.SetTitle(CString(STEPGetPluginName()) + " オプション設定");
	if (page.DoModal() == IDOK) {
		bOptGenreListSelect = dlg1.m_bGenreListSelect ? true : false;

		WritePrivateProfileString("APE", "GenreListSelect", bOptGenreListSelect ? "1" : "0", strINI);
	}
}

/*
STEP_API LPCTSTR WINAPI STEPGetToolTipText(UINT nID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return NULL;
}
*/

/*
STEP_API LPCTSTR WINAPI STEPGetStatusMessage(UINT nID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return NULL;
}
*/

/*
STEP_API bool WINAPI STEPOnUpdateCommand(UINT nID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return false;
}
*/

/*
STEP_API bool WINAPI STEPOnCommand(UINT nID, HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return false;
}
*/

/*
STEP_API void WINAPI STEPOnLoadMenu(HMENU hMenu, UINT nType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
}
*/

STEP_API LPCTSTR WINAPI STEPGetColumnName(UINT nFormatType, COLUMNTYPE nColumn)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	switch (nColumn) {
	case COLUMN_ORIG_ARTIST:
		return "パフォーマー";
	}
	return NULL;
}

STEP_API bool WINAPI STEPHasSpecificColumnName(UINT)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return true;
}
