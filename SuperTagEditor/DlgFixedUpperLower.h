#if !defined(AFX_DLGFIXEDUPPERLOWER_H__78AD705E_543C_4335_865A_1551CDDE8E8B__INCLUDED_)
#define AFX_DLGFIXEDUPPERLOWER_H__78AD705E_543C_4335_865A_1551CDDE8E8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFixedUpperLower.h : �w�b�_�[ �t�@�C��
//
#include "OptionPage/OptionPage.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgFixedUpperLower �_�C�A���O

class CDlgFixedUpperLower : public COptionPage
{
	DECLARE_DYNCREATE(CDlgFixedUpperLower)

// �R���X�g���N�V����
public:
	void EnableButton();
	CDlgFixedUpperLower();
	~CDlgFixedUpperLower();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgFixedUpperLower)
	enum { IDD = IDD_DLG_FIXED_UPPER_LOWER };
	CEdit	m_editFixedWord;
	CButton	m_buttonDelete;
	CButton	m_buttonAdd;
	CListCtrl	m_listUpperLower;
	CString	m_strFixedWord;
	//}}AFX_DATA

	CStringArray m_arFixedWords;
	BOOL m_bModify;

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CDlgFixedUpperLower)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgFixedUpperLower)
	afx_msg void OnBtAdd();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditFixedWord();
	afx_msg void OnBtDelete();
	afx_msg void OnItemchangedListUpperLower(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGFIXEDUPPERLOWER_H__78AD705E_543C_4335_865A_1551CDDE8E8B__INCLUDED_)
