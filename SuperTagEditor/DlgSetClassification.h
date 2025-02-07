#if !defined(AFX_DLGSETCLASSIFICATION_H__F4B6D821_00F8_11D4_9459_00402641B29B__INCLUDED_)
#define AFX_DLGSETCLASSIFICATION_H__F4B6D821_00F8_11D4_9459_00402641B29B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetClassification.h : �w�b�_�[ �t�@�C��
//
#include "OptionPage/OptionPage.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgSetClassification �_�C�A���O

class CDlgSetClassification : public COptionPage
{
	DECLARE_DYNCREATE(CDlgSetClassification)

// �R���X�g���N�V����
public:
	CDlgSetClassification();
	~CDlgSetClassification();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgSetClassification)
	enum { IDD = IDD_DLG_SET_CLASSIFICATION };
	CButton	m_btExecClassificasion;
	CStatic	m_stClass5;
	CStatic	m_stClass4;
	CStatic	m_stClass3;
	CStatic	m_stClass2;
	CStatic	m_stClass1;
	CComboBox	m_listClass5;
	CComboBox	m_listClass4;
	CComboBox	m_listClass3;
	CComboBox	m_listClass2;
	CComboBox	m_listClass1;
	int		m_nClassType;
	int		m_nClass1;
	int		m_nClass2;
	int		m_nClass3;
	int		m_nClass4;
	int		m_nClass5;
	BOOL	m_bExecClassification;
	//}}AFX_DATA

	bool	m_bFirstEdit;
	void	UpdateStatus(void);

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgSetClassification)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgSetClassification)
	afx_msg void OnRaFileTag();
	virtual BOOL OnInitDialog();
	afx_msg void OnRaFolder();
	afx_msg void OnSelChangeListClass();
	afx_msg void OnBtResetPage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGSETCLASSIFICATION_H__F4B6D821_00F8_11D4_9459_00402641B29B__INCLUDED_)
