// MyFileDialog.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "supertageditor.h"
#include "MyFileDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFileDialog

IMPLEMENT_DYNAMIC(CMyFileDialog, CFileDialog)

CMyFileDialog::CMyFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
	SetTemplate(0, IDD_CUSTOM_FILE_OPEN);
	m_bIsWriteAppend = FALSE;
}

BEGIN_MESSAGE_MAP(CMyFileDialog, CFileDialog)
	//{{AFX_MSG_MAP(CMyFileDialog)
		// ���� -  ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CMyFileDialog::OnFileNameOK( )
{
	m_bIsWriteAppend = ((CButton *)GetDlgItem(IDC_CH_FILE_ADDPEND))->GetCheck();
	return(0);
}
