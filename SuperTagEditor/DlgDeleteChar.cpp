// DlgDeleteChar.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "supertageditor.h"
#include "DlgDeleteChar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgDeleteChar �_�C�A���O


DlgDeleteChar::DlgDeleteChar(CWnd* pParent /*=NULL*/)
	: CDialog(DlgDeleteChar::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgDeleteChar)
	m_nDelCount = 0;
	m_nPos = -1;
	//}}AFX_DATA_INIT
}


void DlgDeleteChar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgDeleteChar)
	DDX_Text(pDX, IDC_EDIT_DELETE_CHAR, m_nDelCount);
	DDV_MinMaxUInt(pDX, m_nDelCount, 1, 999);
	DDX_Radio(pDX, IDC_RADIO_ADD_START, m_nPos);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgDeleteChar, CDialog)
	//{{AFX_MSG_MAP(DlgDeleteChar)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgDeleteChar ���b�Z�[�W �n���h��
