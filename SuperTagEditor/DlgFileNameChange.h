#if !defined(AFX_DLGFILENAMECHANGE_H__F4B855B0_E32B_4803_A6B4_02F39BCFB362__INCLUDED_)
#define AFX_DLGFILENAMECHANGE_H__F4B855B0_E32B_4803_A6B4_02F39BCFB362__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFileNameChange.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFileNameChange �_�C�A���O

class CDlgFileNameChange : public CDialog
{
public:
	CString m_strMsgFormat;
// �R���X�g���N�V����
public:
	CDlgFileNameChange(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

	UINT m_nMaxChar;
// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgFileNameChange)
	enum { IDD = IDD_DLG_FILENAME_CHANGE };
	CStatic	m_staticMsg;
	CEdit	m_editName;
	CString	m_strFileName;
	CString	m_strMsg;
	CString	m_strOrgFileName;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgFileNameChange)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgFileNameChange)
	afx_msg void OnChangeEditName();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGFILENAMECHANGE_H__F4B855B0_E32B_4803_A6B4_02F39BCFB362__INCLUDED_)
