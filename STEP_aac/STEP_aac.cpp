// STEP_aac.cpp : DLL 用の初期化処理の定義を行います。
//

#include "stdafx.h"
#include "STEP_aac.h"
#include "STEPlugin.h"

#include "DlgSetup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CSTEP_aacApp

BEGIN_MESSAGE_MAP(CSTEP_aacApp, CWinApp)
	//{{AFX_MSG_MAP(CSTEP_aacApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSTEP_aacApp の構築

CSTEP_aacApp::CSTEP_aacApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance の中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CSTEP_aacApp オブジェクト

CSTEP_aacApp theApp;

UINT nPluginID;
UINT nFileTypeAAC;

CString strINI;
bool bOptGenreListSelect;

STEP_API LPCTSTR WINAPI STEPGetPluginInfo(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return "Version 1.01 Copyright (C) 2004-2010 haseta\r\nAAC(iTunes)形式をサポートしています\r\nタグ更新はmp4v2.dllを使用していますが、STEP用にカスタマイズしたものです";
}

STEP_API bool WINAPI STEPInit(UINT pID, LPCTSTR szPluginFolder)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (Initialize() == false)	return false;
	nPluginID = pID;

	// INIファイルの読み込み
	strINI = szPluginFolder;
	strINI += "STEP_aac.ini";
	bOptGenreListSelect = GetPrivateProfileInt("AAC", "GenreListSelect", 0, strINI) ? true : false;

	HBITMAP hAACBitmap = LoadBitmap(theApp.m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_AAC));
	nFileTypeAAC = STEPRegisterExt(nPluginID, "m4a", hAACBitmap);
	DeleteObject(hAACBitmap);

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
	return "STEP_aac";
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
	case COLUMN_COPYRIGHT:
	case COLUMN_COMPOSER:
	case COLUMN_KEYWORD:
	case COLUMN_SOFTWARE:
	case COLUMN_ALBUM_ARTIST:
	case COLUMN_DISK_NUMBER: /* STEP 045 */
		return _EDIT;
	case COLUMN_COMMENT:
		return _MEDIT;
	case COLUMN_GENRE:
		if (bOptGenreListSelect) {
			return _CBOX;
		} else {
			return _EDIT;
		}
	case COLUMN_COMPILATION: /* STEP  049 */
		return _CBOX;
	}
	return _NULL;
}

STEP_API UINT WINAPI STEPGetColumnMax(UINT nFormat, COLUMNTYPE nColumn, bool isEditSIF) {
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	switch (nColumn) { // iTunesに準拠
	case COLUMN_TRACK_NAME:		return 260;
	case COLUMN_ARTIST_NAME:	return 260;
	case COLUMN_ALBUM_NAME:		return 260;
	case COLUMN_TRACK_NUMBER:	return 7;
	case COLUMN_YEAR:			return 260;
	case COLUMN_GENRE:			return 260;
	case COLUMN_COMMENT:		return 260;
	case COLUMN_COPYRIGHT:		return 260;
	case COLUMN_COMPOSER:		return 260;
	case COLUMN_KEYWORD:		return 260;
	case COLUMN_SOFTWARE:		return 260;
	case COLUMN_ALBUM_ARTIST:	return 260;
	case COLUMN_DISK_NUMBER:	return 7; /* STEP 045 */
	case COLUMN_COMPILATION:	return 7; /* STEP 049 */
	}
	return 0;
}

STEP_API UINT WINAPI STEPLoad(FILE_INFO *pFileMP3, LPCTSTR szExt)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (stricmp(szExt, "m4a") == 0) {
		extern	bool LoadFileAAC(FILE_INFO *pFile);
		if (LoadFileAAC(pFileMP3) == false) {
			CString	strMsg;
			strMsg.Format("%s の読み込みに失敗しました", GetFullPath(pFileMP3));
			MessageBox(NULL, strMsg, "AACファイルの読み込み失敗", MB_ICONSTOP|MB_OK|MB_TOPMOST);
			return STEP_ERROR;
		} else {
			SetFormat(pFileMP3, nFileTypeAAC);
			SetFileTypeName(pFileMP3, "AAC(iTunes)");
			return STEP_SUCCESS;
		}
	}
	return STEP_UNKNOWN_FORMAT;
}

STEP_API UINT WINAPI STEPSave(FILE_INFO *pFileMP3)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	UINT nFormat = GetFormat(pFileMP3);

	if (nFormat == nFileTypeAAC) {
		extern bool WriteFileAAC(FILE_INFO *pFileMP3);
		if (WriteFileAAC(pFileMP3) == false) {
			CString	strMsg;
			strMsg.Format("%s の書き込みに失敗しました", GetFullPath(pFileMP3));
			MessageBox(NULL, strMsg, "AACファイルの書き込み失敗", MB_ICONSTOP|MB_OK|MB_TOPMOST);
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

		WritePrivateProfileString("AAC", "GenreListSelect", bOptGenreListSelect ? "1" : "0", strINI);
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
	case COLUMN_KEYWORD:
		return "分類";
	case COLUMN_TRACK_NUMBER:
		return "TrackNo/Total";
	}
	return NULL;
}

STEP_API bool WINAPI STEPHasSpecificColumnName(UINT)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return true;
}
