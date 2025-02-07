// DlgEnvironment.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "supertageditor.h"
#include "SHBrowseForFolder.h"
#include "DlgEnvironment.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvironment �_�C�A���O
IMPLEMENT_DYNCREATE(CDlgEnvironment, COptionPage)

CDlgEnvironment::CDlgEnvironment() : COptionPage(CDlgEnvironment::IDD)
{
	//{{AFX_DATA_INIT(CDlgEnvironment)
	m_bEditOkDown = FALSE;
	m_bEnterBeginEdit = FALSE;
	m_bKeepTimeStamp = FALSE;
	m_bAutoOpenFolder = FALSE;
	m_bLoadFileAdjustColumn = FALSE;
	m_bSyncCreateTime = FALSE;
	m_bLoadFileChecked = FALSE;
	m_bHideMP3ListFile = FALSE;
	m_bESCEditCancel = FALSE;
	m_bEnableEditCursorExit = FALSE;
	m_bDropSearchSubFolder = FALSE;
	m_bShowZenSpace = FALSE;
	m_bSortIgnoreCase = FALSE;
	m_bSortIgnoreZenHan = FALSE;
	m_bShowTotalParent = FALSE;
	m_bSortIgnoreKataHita = FALSE;
	m_bShowTips = FALSE;
	//}}AFX_DATA_INIT
}

CDlgEnvironment::~CDlgEnvironment()
{
}

void CDlgEnvironment::DoDataExchange(CDataExchange* pDX)
{
	COptionPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEnvironment)
	DDX_Check(pDX, IDC_CH_EDIT_OK_DOWN, m_bEditOkDown);
	DDX_Check(pDX, IDC_CH_ENTER_BEGIN_EDIT, m_bEnterBeginEdit);
	DDX_Check(pDX, IDC_CH_KEEP_TIME_STAMP, m_bKeepTimeStamp);
	DDX_Check(pDX, IDC_CH_AUTO_OPEN_FOLDER, m_bAutoOpenFolder);
	DDX_Check(pDX, IDC_CH_LOAD_FILE_ADJUST_COLUMN, m_bLoadFileAdjustColumn);
	DDX_Check(pDX, IDC_CH_SYNC_CREATE_TIME, m_bSyncCreateTime);
	DDX_Check(pDX, IDC_CH_LOAD_FILE_CHECKED, m_bLoadFileChecked);
	DDX_Check(pDX, IDC_CH_HIDE_MP3_LIST_FILE, m_bHideMP3ListFile);
	DDX_Check(pDX, IDC_CH_ESC_EDIT_CANCEL, m_bESCEditCancel);
	DDX_Check(pDX, IDC_CH_ENABLE_EDIT_CURSOR_EXIT, m_bEnableEditCursorExit);
	DDX_Check(pDX, IDC_CH_DROP_SEARCH_SUBFOLDER, m_bDropSearchSubFolder);
	DDX_Check(pDX, IDC_CH_SHOW_ZEN_SPACE, m_bShowZenSpace);
	DDX_Check(pDX, IDC_CH_SORT_IGNORE_CASE, m_bSortIgnoreCase);
	DDX_Check(pDX, IDC_CH_SORT_IGNORE_ZENHAN, m_bSortIgnoreZenHan);
	DDX_Check(pDX, IDC_CH_SHOW_TOTAL_PARENT, m_bShowTotalParent);
	DDX_Check(pDX, IDC_CH_SORT_IGNORE_KATAHIRA, m_bSortIgnoreKataHita);
	DDX_Check(pDX, IDC_CH_SHOW_TIPS, m_bShowTips);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEnvironment, COptionPage)
	//{{AFX_MSG_MAP(CDlgEnvironment)
	ON_BN_CLICKED(IDC_CH_KEEP_TIME_STAMP, OnChKeepTimeStamp)
	ON_BN_CLICKED(IDC_BT_RESET_PAGE, OnBtResetPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvironment ���b�Z�[�W �n���h��
BOOL CDlgEnvironment::OnInitDialog() 
{
	COptionPage::OnInitDialog();

	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	UpdateStatus();

	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CDlgEnvironment::UpdateStatus(void)
{
	UpdateData();

	((CWnd *)GetDlgItem(IDC_CH_SYNC_CREATE_TIME))->EnableWindow(m_bKeepTimeStamp ? TRUE : FALSE);
}

void CDlgEnvironment::OnChKeepTimeStamp() 
{
	UpdateStatus();
}

// �����l�ɖ߂�
void CDlgEnvironment::OnBtResetPage() 
{
	// ���[�U�[�C���^�[�t�F�[�X
	((CButton *)GetDlgItem(IDC_CH_ESC_EDIT_CANCEL))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_CH_ENABLE_EDIT_CURSOR_EXIT))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_CH_EDIT_OK_DOWN))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_CH_ENTER_BEGIN_EDIT))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_CH_SHOW_ZEN_SPACE))->SetCheck(FALSE);

	// ���̑�
	((CButton *)GetDlgItem(IDC_CH_KEEP_TIME_STAMP))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_CH_SYNC_CREATE_TIME))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_CH_AUTO_OPEN_FOLDER))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_CH_LOAD_FILE_ADJUST_COLUMN))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_CH_LOAD_FILE_CHECKED))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_CH_HIDE_MP3_LIST_FILE))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_CH_DROP_SEARCH_SUBFOLDER))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_CH_SORT_IGNORE_CASE))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_CH_SORT_IGNORE_ZENHAN))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_CH_SHOW_TOTAL_PARENT))->SetCheck(FALSE);

	UpdateStatus();
}
