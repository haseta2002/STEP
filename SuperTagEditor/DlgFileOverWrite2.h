#if !defined(AFX_DLGFILEOVERWRITE2_H__9D17F0DE_039D_4CFE_9106_52E983245F50__INCLUDED_)
#define AFX_DLGFILEOVERWRITE2_H__9D17F0DE_039D_4CFE_9106_52E983245F50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFileOverWrite2.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFileOverWrite22 �_�C�A���O

class CDlgFileOverWrite2 : public CDialog
{
// �R���X�g���N�V����
public:
	CDlgFileOverWrite2(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgFileOverWrite2)
	enum { IDD = IDD_DLG_FILE_OVERWRITE2 };
	CString	m_strFileName;
	CString	m_strTimeStamp;
	CString	m_strSize;
	//}}AFX_DATA

	int		m_nResult;


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgFileOverWrite2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgFileOverWrite2)
	virtual void OnOK();
	afx_msg void OnBtOverwrite();
	afx_msg void OnBtAllOverwrite();
	afx_msg void OnBtRename();
	afx_msg void OnBtSkip();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGFILEOVERWRITE2_H__9D17F0DE_039D_4CFE_9106_52E983245F50__INCLUDED_)
