#if !defined(AFX_DLGFIXEDSTRING_H__242A5F81_213F_11D4_9459_00402641B29B__INCLUDED_)
#define AFX_DLGFIXEDSTRING_H__242A5F81_213F_11D4_9459_00402641B29B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFixedString.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFixedString �_�C�A���O

class CDlgFixedString : public CDialog
{
// �R���X�g���N�V����
public:
	CDlgFixedString(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgFixedString)
	enum { IDD = IDD_DLG_FIXED_STRING };
	CString	m_strText;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgFixedString)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgFixedString)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGFIXEDSTRING_H__242A5F81_213F_11D4_9459_00402641B29B__INCLUDED_)
