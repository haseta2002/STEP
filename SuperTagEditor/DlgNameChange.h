#if !defined(AFX_DLGNAMECHANGE_H__F6C936A0_0F4C_11D4_9459_00402641B29B__INCLUDED_)
#define AFX_DLGNAMECHANGE_H__F6C936A0_0F4C_11D4_9459_00402641B29B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNameChange.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNameChange �_�C�A���O

class CDlgNameChange : public CDialog
{
// �R���X�g���N�V����
public:
	CDlgNameChange(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgNameChange)
	enum { IDD = IDD_DLG_NAME_CHANGE };
	CEdit	m_editName;
	CString	m_strName;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgNameChange)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgNameChange)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGNAMECHANGE_H__F6C936A0_0F4C_11D4_9459_00402641B29B__INCLUDED_)
