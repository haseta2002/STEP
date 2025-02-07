#if !defined(AFX_DLGADDUSERGENRE_H__C4EF4D09_D12B_46A5_9B88_2A819FF6BA40__INCLUDED_)
#define AFX_DLGADDUSERGENRE_H__C4EF4D09_D12B_46A5_9B88_2A819FF6BA40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAddUserGenre.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAddUserGenre �_�C�A���O

class CDlgAddUserGenre : public CDialog
{
// �R���X�g���N�V����
public:
	CDlgAddUserGenre(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgAddUserGenre)
	enum { IDD = IDD_DLG_SETUP_USER_GENRE };
	CButton	m_cBtAdd;
	CListCtrl	m_listGenre;
	CString	m_strName;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgAddUserGenre)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgAddUserGenre)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtAdd();
	afx_msg void OnItemchangedListGenre(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditName();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	USER_GENRE_LIST*	m_genreListUSER;

private:
	void EnableButton();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGADDUSERGENRE_H__C4EF4D09_D12B_46A5_9B88_2A819FF6BA40__INCLUDED_)
