#if !defined(AFX_DlgConv_H__205D5D6E_8399_4AF8_8224_4F1BD0A912EC__INCLUDED_)
#define AFX_DlgConv_H__205D5D6E_8399_4AF8_8224_4F1BD0A912EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CDlgConv.h : �w�b�_�[ �t�@�C��
//

#include "OptionPage/OptionPage.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgConv �_�C�A���O

class CDlgConv : public COptionPage
{
	DECLARE_DYNCREATE(CDlgConv)

// �R���X�g���N�V����
public:
	CDlgConv();
	~CDlgConv();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgConv)
	enum { IDD = IDD_DIALOG_CONV };
	CEdit	m_cFirstUpperSentenceSeparator;
	CEdit	m_cFirstUperIgnoreWords;
	BOOL	m_bFirstUpperIgnoreWord;
	CString	m_strFirstUpperIgnoreWords;
	CString	m_strFirstUpperSentenceSeparator;
	BOOL	m_bUserConvAddMenu;
	BOOL	m_bZenHanKigouKana;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CDlgConv)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgConv)
	afx_msg void OnCheckFirstUpperIgnoreWord();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtResetPage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CDlgConv_H__205D5D6E_8399_4AF8_8224_4F1BD0A912EC__INCLUDED_)
