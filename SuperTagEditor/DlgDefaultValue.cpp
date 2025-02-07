// DlgDefaultValue.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "supertageditor.h"
#include "DlgDefaultValue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDefaultValue �v���p�e�B �y�[�W

IMPLEMENT_DYNCREATE(CDlgDefaultValue, COptionPage)

CDlgDefaultValue::CDlgDefaultValue() : COptionPage(CDlgDefaultValue::IDD)
{
	//{{AFX_DATA_INIT(CDlgDefaultValue)
	m_bValidFolderSelect = FALSE;
	m_bValidDupExec = FALSE;
	m_nRecentFolder = 0;
	m_bSaveRepDlgPos = FALSE;
	m_bAudioListShow = FALSE;
	//}}AFX_DATA_INIT
}

CDlgDefaultValue::~CDlgDefaultValue()
{
}

void CDlgDefaultValue::DoDataExchange(CDataExchange* pDX)
{
	COptionPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDefaultValue)
	DDX_Check(pDX, IDC_CHECK_VALID_FOLDER_SELECT, m_bValidFolderSelect);
	DDX_Check(pDX, IDC_CHECK_DUP_EXEC, m_bValidDupExec);
	DDX_Text(pDX, IDC_EDIT_RECENT_FOLDER, m_nRecentFolder);
	DDV_MinMaxInt(pDX, m_nRecentFolder, 1, 16);
	DDX_Check(pDX, IDC_SAVE_REP_DLG_POS, m_bSaveRepDlgPos);
	DDX_Check(pDX, IDC_CHECK_AUDIO_LIST_SHOW, m_bAudioListShow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDefaultValue, COptionPage)
	//{{AFX_MSG_MAP(CDlgDefaultValue)
	ON_BN_CLICKED(IDC_BT_RESET_PAGE, OnBtResetPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDefaultValue ���b�Z�[�W �n���h��

void CDlgDefaultValue::OnBtResetPage() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_bValidFolderSelect = FALSE;
	m_bValidDupExec = FALSE;
	m_nRecentFolder = 5;
	m_bSaveRepDlgPos = FALSE; /* WildCherry4 086 */
	m_bAudioListShow = FALSE; /* Conspiracy 194 */
	UpdateData(FALSE);
}
