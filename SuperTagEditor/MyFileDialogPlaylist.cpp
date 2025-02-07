// MyFileDialogPlaylist.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "supertageditor.h"
#include "MyFileDialogPlaylist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFileDialogPlaylist

IMPLEMENT_DYNAMIC(CMyFileDialogPlaylist, CFileDialog)

CMyFileDialogPlaylist::CMyFileDialogPlaylist(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
	SetTemplate(0, IDD_CUSTOM_FILE_OPEN_PLAYLIST);
	m_bShowLoadPlaylistDlg = TRUE;
}


BEGIN_MESSAGE_MAP(CMyFileDialogPlaylist, CFileDialog)
	//{{AFX_MSG_MAP(CMyFileDialogPlaylist)
		// メモ -  ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CMyFileDialogPlaylist::OnFileNameOK()
{
	m_bShowLoadPlaylistDlg = ((CButton *)GetDlgItem(IDC_CH_SHOW_LOAD_PLAYLIST))->GetCheck();
	return(0);

}

void  CMyFileDialogPlaylist::OnInitDone()
{
	CFileDialog::OnInitDone();
	((CButton *)GetDlgItem(IDC_CH_SHOW_LOAD_PLAYLIST))->SetCheck(m_bShowLoadPlaylistDlg);
}