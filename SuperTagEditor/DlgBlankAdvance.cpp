// DlgBlankAdvance.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "supertageditor.h"
#include "DlgBlankAdvance.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBlankAdvance �v���p�e�B �y�[�W

IMPLEMENT_DYNCREATE(CDlgBlankAdvance, COptionPage)

CDlgBlankAdvance::CDlgBlankAdvance() : COptionPage(CDlgBlankAdvance::IDD)
{
	//{{AFX_DATA_INIT(CDlgBlankAdvance)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�̏�����������ǉ����܂��B
	//}}AFX_DATA_INIT
}

CDlgBlankAdvance::~CDlgBlankAdvance()
{
}

void CDlgBlankAdvance::DoDataExchange(CDataExchange* pDX)
{
	COptionPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBlankAdvance)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBlankAdvance, COptionPage)
	//{{AFX_MSG_MAP(CDlgBlankAdvance)
		// ����: ClassWizard �͂��̈ʒu�� DDX ����� DDV �̌Ăяo���R�[�h��ǉ����܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBlankAdvance ���b�Z�[�W �n���h��
