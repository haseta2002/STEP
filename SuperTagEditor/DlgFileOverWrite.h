#if !defined(AFX_DLGFILEOVERWRITE_H__AF8B4A60_059E_11D4_9459_00402641B29B__INCLUDED_)
#define AFX_DLGFILEOVERWRITE_H__AF8B4A60_059E_11D4_9459_00402641B29B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFileOverWrite.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFileOverWrite �_�C�A���O

class CDlgFileOverWrite : public CDialog
{
// �R���X�g���N�V����
public:
	CDlgFileOverWrite(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgFileOverWrite)
	enum { IDD = IDD_DLG_FILE_OVERWRITE };
	CString	m_strFileName;
	CString	m_strTimeStamp;
	CString	m_strSize;
	//}}AFX_DATA

	int		m_nResult;


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgFileOverWrite)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgFileOverWrite)
	virtual void OnOK();
	afx_msg void OnBtOverwrite();
	afx_msg void OnBtAllOverwrite();
	afx_msg void OnBtSkip();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGFILEOVERWRITE_H__AF8B4A60_059E_11D4_9459_00402641B29B__INCLUDED_)
