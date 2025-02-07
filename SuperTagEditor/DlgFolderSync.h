#if !defined(AFX_DLGFOLDERSYNC_H__6BDA3360_3651_11D4_9459_00402641B29B__INCLUDED_)
#define AFX_DLGFOLDERSYNC_H__6BDA3360_3651_11D4_9459_00402641B29B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFolderSync.h : �w�b�_�[ �t�@�C��
//
#include "OptionPage/OptionPage.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgFolderSync �_�C�A���O

class CDlgFolderSync : public COptionPage
{
	DECLARE_DYNCREATE(CDlgFolderSync)

// �R���X�g���N�V����
public:
	CDlgFolderSync();
	~CDlgFolderSync();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgFolderSync)
	enum { IDD = IDD_DLG_FOLDER_SYNC };
	CEdit	m_editRootFolder;
	BOOL	m_bEnableFolderSync;
	CString	m_strRootFolder;
	BOOL	m_bMoveLyricsFile;
	BOOL	m_bDeleteFolder;
	BOOL	m_bSelectAlways;
	//}}AFX_DATA

	void	UpdateStatus(void);


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CDlgFolderSync)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgFolderSync)
	virtual BOOL OnInitDialog();
	afx_msg void OnChEnableFolderSync();
	afx_msg void OnBtRefRoot();
	afx_msg void OnBtResetPage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGFOLDERSYNC_H__6BDA3360_3651_11D4_9459_00402641B29B__INCLUDED_)
