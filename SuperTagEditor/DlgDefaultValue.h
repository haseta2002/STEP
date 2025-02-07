#if !defined(AFX_DLGDEFAULTVALUE_H__1F3F9F21_D999_4375_814B_07A16F70BB22__INCLUDED_)
#define AFX_DLGDEFAULTVALUE_H__1F3F9F21_D999_4375_814B_07A16F70BB22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDefaultValue.h : �w�b�_�[ �t�@�C��
//
#include "OptionPage/OptionPage.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgDefaultValue �_�C�A���O

class CDlgDefaultValue : public COptionPage
{
	DECLARE_DYNCREATE(CDlgDefaultValue)

// �R���X�g���N�V����
public:
	CDlgDefaultValue();
	~CDlgDefaultValue();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgDefaultValue)
	enum { IDD = IDD_DLG_DEFAUT_VALUE };
	BOOL	m_bValidFolderSelect;
	BOOL	m_bValidDupExec;
	int		m_nRecentFolder;
	BOOL	m_bSaveRepDlgPos;
	BOOL	m_bAudioListShow;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CDlgDefaultValue)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgDefaultValue)
	afx_msg void OnBtResetPage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGDEFAULTVALUE_H__1F3F9F21_D999_4375_814B_07A16F70BB22__INCLUDED_)
