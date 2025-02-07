#if !defined(AFX_DLGEDITSHOWCOLUMN_H__D7E15A02_13B7_11D4_9459_00402641B29B__INCLUDED_)
#define AFX_DLGEDITSHOWCOLUMN_H__D7E15A02_13B7_11D4_9459_00402641B29B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEditShowColumn.h : �w�b�_�[ �t�@�C��
//
#include "OptionPage/OptionPage.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgEditShowColumn �_�C�A���O

class CDlgEditShowColumn : public COptionPage
{
	DECLARE_DYNCREATE(CDlgEditShowColumn)

// �R���X�g���N�V����
public:
	CDlgEditShowColumn();
	~CDlgEditShowColumn();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgEditShowColumn)
	enum { IDD = IDD_DLG_EDIT_SHOW_COLUMN };
	CListCtrl	m_listColumn;
	//}}AFX_DATA


	void	SwapListItem(int, int);
	void	SelChangeList(void);

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgEditShowColumn)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgEditShowColumn)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtDown();
	afx_msg void OnBtUp();
	virtual void OnOK();
	afx_msg void OnBtResetPage();
	afx_msg void OnChangeEditMaxWidth();
	afx_msg void OnItemChangedListColumn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemChangingListColumn(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGEDITSHOWCOLUMN_H__D7E15A02_13B7_11D4_9459_00402641B29B__INCLUDED_)
