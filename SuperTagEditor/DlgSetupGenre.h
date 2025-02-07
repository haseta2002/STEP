#if !defined(AFX_DLGSETUPGENRE_H__F618C220_2DE7_11D4_9459_00402641B29B__INCLUDED_)
#define AFX_DLGSETUPGENRE_H__F618C220_2DE7_11D4_9459_00402641B29B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetupGenre.h : �w�b�_�[ �t�@�C��
//
#include "OptionPage/OptionPage.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgSetupGenre �_�C�A���O


class CDlgSetupGenre : public COptionPage
{
	DECLARE_DYNCREATE(CDlgSetupGenre)

// �R���X�g���N�V����
public:
	CDlgSetupGenre();
	~CDlgSetupGenre();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgSetupGenre)
	enum { IDD = IDD_DLG_SETUP_GENRE };
	CListCtrl	m_listGenre;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CDlgSetupGenre)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgSetupGenre)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBtCheckAll();
	afx_msg void OnBtUncheckAll();
	afx_msg void OnBtCheckId3();
	afx_msg void OnBtCheckWinamp();
	afx_msg void OnBtCheckScmpx();
	afx_msg void OnBtResetPage();
	afx_msg void OnBtAddUser();
	afx_msg void OnBtDelUser();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void AddUserGenre(int nIndex);
public:
	USER_GENRE_LIST*	m_genreListUSER;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGSETUPGENRE_H__F618C220_2DE7_11D4_9459_00402641B29B__INCLUDED_)
