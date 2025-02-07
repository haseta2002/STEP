// DlgSetup.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "STEP_mpc.h"
#include "DlgSetup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetup �v���p�e�B �y�[�W

IMPLEMENT_DYNCREATE(CDlgSetup, CPropertyPage)

CDlgSetup::CDlgSetup() : CPropertyPage(CDlgSetup::IDD)
{
	//{{AFX_DATA_INIT(CDlgSetup)
	m_bGenreListSelect = FALSE;
	//}}AFX_DATA_INIT
}

CDlgSetup::~CDlgSetup()
{
}

void CDlgSetup::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetup)
	DDX_Check(pDX, IDC_CH_GENRE_LIST_SELECT, m_bGenreListSelect);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSetup, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgSetup)
		// ����: ClassWizard �͂��̈ʒu�� DDX ����� DDV �̌Ăяo���R�[�h��ǉ����܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetup ���b�Z�[�W �n���h��
