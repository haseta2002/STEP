// DlgLoadPlayList.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "supertageditor.h"
#include "DlgLoadPlayList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLoadPlayList �_�C�A���O


CDlgLoadPlayList::CDlgLoadPlayList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLoadPlayList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLoadPlayList)
	m_bClearCheck = FALSE;
	m_bClearList = FALSE;
	m_nAddListFlag = -1;
	m_nFileCheckFlag = -1;
	//}}AFX_DATA_INIT
}


void CDlgLoadPlayList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLoadPlayList)
	DDX_Check(pDX, IDC_CH_CLEAR_CHECK, m_bClearCheck);
	DDX_Check(pDX, IDC_CH_CLEAR_LIST, m_bClearList);
	DDX_Radio(pDX, IDC_RA_ADD_LIST_ON, m_nAddListFlag);
	DDX_Radio(pDX, IDC_RA_FILE_CHECK_ON, m_nFileCheckFlag);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLoadPlayList, CDialog)
	//{{AFX_MSG_MAP(CDlgLoadPlayList)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLoadPlayList ���b�Z�[�W �n���h��
