#if !defined(AFX_DLGKEYCONFIG_H__37E97340_12D4_11D4_9459_00402641B29B__INCLUDED_)
#define AFX_DLGKEYCONFIG_H__37E97340_12D4_11D4_9459_00402641B29B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgKeyConfig.h : �w�b�_�[ �t�@�C��
//
#include "OptionPage/OptionPage.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgKeyConfig �_�C�A���O

class CDlgKeyConfig : public COptionPage
{
	DECLARE_DYNCREATE(CDlgKeyConfig)

// �R���X�g���N�V����
public:
	CDlgKeyConfig();
	~CDlgKeyConfig();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgKeyConfig)
	enum { IDD = IDD_DLG_KEY_CONFIG };
	CButton	m_btAlt;
	CButton	m_btCtrl;
	CListBox	m_listKey;
	CComboBox	m_listGroup;
	CListBox	m_listCommand;
	//}}AFX_DATA

	bool	m_bExecCommandChange;
	void	UpdateKeyList(void);
	void	UpdateCommandList(void);
	void	UpdateHotKey(void);

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgKeyConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgKeyConfig)
	afx_msg void OnChCtrl();
	afx_msg void OnChAlt();
	afx_msg void OnSelChangeListCommand();
	afx_msg void OnSelChangeListGroup();
	afx_msg void OnSelChangeListKey();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGKEYCONFIG_H__37E97340_12D4_11D4_9459_00402641B29B__INCLUDED_)
