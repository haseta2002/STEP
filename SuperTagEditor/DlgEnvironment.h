#if !defined(AFX_DLGENVIRONMENT_H__FE011EA3_EADB_11D3_9459_00402641B29B__INCLUDED_)
#define AFX_DLGENVIRONMENT_H__FE011EA3_EADB_11D3_9459_00402641B29B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEnvironment.h : �w�b�_�[ �t�@�C��
//
#include "OptionPage/OptionPage.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvironment �_�C�A���O

class CDlgEnvironment : public COptionPage
{
	DECLARE_DYNCREATE(CDlgEnvironment)

// �R���X�g���N�V����
public:
	CDlgEnvironment();
	~CDlgEnvironment();

	void	UpdateStatus(void);

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgEnvironment)
	enum { IDD = IDD_DLG_ENVIRONMENT };
	BOOL	m_bEditOkDown;
	BOOL	m_bEnterBeginEdit;
	BOOL	m_bKeepTimeStamp;
	BOOL	m_bAutoOpenFolder;
	BOOL	m_bLoadFileAdjustColumn;
	BOOL	m_bSyncCreateTime;
	BOOL	m_bLoadFileChecked;
	BOOL	m_bHideMP3ListFile;
	BOOL	m_bESCEditCancel;
	BOOL	m_bEnableEditCursorExit;
	BOOL	m_bDropSearchSubFolder;
	BOOL	m_bShowZenSpace;
	BOOL	m_bSortIgnoreCase;
	BOOL	m_bSortIgnoreZenHan;
	BOOL	m_bShowTotalParent;
	BOOL	m_bSortIgnoreKataHita;
	BOOL	m_bShowTips;
	//}}AFX_DATA

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgEnvironment)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgEnvironment)
	virtual BOOL OnInitDialog();
	afx_msg void OnChKeepTimeStamp();
	afx_msg void OnBtResetPage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGENVIRONMENT_H__FE011EA3_EADB_11D3_9459_00402641B29B__INCLUDED_)
