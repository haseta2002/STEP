#if !defined(AFX_DLGWRITEFORM_H__F38CAF64_740C_11D4_9459_00402641B29B__INCLUDED_)
#define AFX_DLGWRITEFORM_H__F38CAF64_740C_11D4_9459_00402641B29B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWriteForm.h : �w�b�_�[ �t�@�C��
//
#include "OptionPage/OptionPage.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgWriteForm �_�C�A���O

class CDlgWriteForm : public COptionPage
{
	DECLARE_DYNCREATE(CDlgWriteForm)

// �R���X�g���N�V����
public:
	CDlgWriteForm();
	~CDlgWriteForm();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgWriteForm)
	enum { IDD = IDD_DLG_WRITE_FORM };
	CButton	m_btWriteHtml;
	CButton	m_btIsHtml;
	CButton	m_btWriteSelected;
	CEdit	m_editFileName;
	CEdit	m_editExtName;
	CComboBox	m_listFormatType;
	int		m_nFormatType;
	//}}AFX_DATA

	WRITE_FORMAT	m_writeFormat[WRITE_FORMAT_MAX];

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CDlgWriteForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgWriteForm)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtNameChange();
	afx_msg void OnBtRefFile();
	afx_msg void OnSelChangeListFormatType();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGWRITEFORM_H__F38CAF64_740C_11D4_9459_00402641B29B__INCLUDED_)
