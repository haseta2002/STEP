#if !defined(AFX_DLGADDNUMBER_H__44D702A8_6504_45B4_AE28_A8512B372D7D__INCLUDED_)
#define AFX_DLGADDNUMBER_H__44D702A8_6504_45B4_AE28_A8512B372D7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAddNumber.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// DlgAddNumber �_�C�A���O

class DlgAddNumber : public CDialog
{
// �R���X�g���N�V����
public:
	DlgAddNumber(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(DlgAddNumber)
	enum { IDD = IDD_DLG_ADD_NUMBER };
	UINT	m_nWidth;
	CString	m_strSeparator;
	int		m_nAddPosition;
	BOOL	m_bSpaceInitNumber;
	UINT	m_nAddNumber;
	UINT	m_nInitNumber;
	CString	m_strAfter;
	CString	m_strBefore;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(DlgAddNumber)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(DlgAddNumber)
	afx_msg void OnRadioReplace();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGADDNUMBER_H__44D702A8_6504_45B4_AE28_A8512B372D7D__INCLUDED_)
