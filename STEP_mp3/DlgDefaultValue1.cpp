// DlgDefaultValue1.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "STEP_mp3.h"
#include "DlgDefaultValue1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgDefaultValue �_�C�A���O


DlgDefaultValue::DlgDefaultValue(CWnd* pParent /*=NULL*/)
	: CDialog(DlgDefaultValue::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgDefaultValue)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void DlgDefaultValue::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgDefaultValue)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgDefaultValue, CDialog)
	//{{AFX_MSG_MAP(DlgDefaultValue)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgDefaultValue ���b�Z�[�W �n���h��
