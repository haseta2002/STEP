#if !defined(AFX_DLGTEIKEIPASTE_H__6FE8BF7D_7406_43FB_B10A_E5309B977462__INCLUDED_)
#define AFX_DLGTEIKEIPASTE_H__6FE8BF7D_7406_43FB_B10A_E5309B977462__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTeikeiPaste.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTeikeiPaste �_�C�A���O

class CDlgTeikeiPaste : public CDialog
{
// �R���X�g���N�V����
public:
	CString m_strTitle;
	CDlgTeikeiPaste(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgTeikeiPaste)
	enum { IDD = IDD_DIALOG_TEIKEI_PASTE };
	int		m_nTeikeiPaste;
	BOOL	m_bAddSpace;
	CString	m_strFront;
	CString	m_strBack;
	BOOL	m_bAddChar;
	BOOL	m_bShowDialog;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgTeikeiPaste)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgTeikeiPaste)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGTEIKEIPASTE_H__6FE8BF7D_7406_43FB_B10A_E5309B977462__INCLUDED_)
