#if !defined(AFX_DLGENVCONF_H__5ECD9180_13F6_11D4_9459_00402641B29B__INCLUDED_)
#define AFX_DLGENVCONF_H__5ECD9180_13F6_11D4_9459_00402641B29B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEnvConf.h : �w�b�_�[ �t�@�C��
//
#include "OptionPage/OptionPage.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvConf �_�C�A���O

class CDlgEnvConf : public COptionPage
{
	DECLARE_DYNCREATE(CDlgEnvConf)

// �R���X�g���N�V����
public:
	CDlgEnvConf();
	~CDlgEnvConf();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgEnvConf)
	enum { IDD = IDD_DLG_ENV_CONF };
	BOOL	m_bConfDeleteFile;
	BOOL	m_bConfDeleteList;
	BOOL	m_bConfEditModify;
	BOOL	m_bConfFolderSync;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CDlgEnvConf)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgEnvConf)
	afx_msg void OnBtResetPage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGENVCONF_H__5ECD9180_13F6_11D4_9459_00402641B29B__INCLUDED_)
