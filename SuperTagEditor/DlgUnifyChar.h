#if !defined(AFX_DLGUNIFYCHAR_H__53F97B08_CBFE_40A2_A58E_A9DC1662818A__INCLUDED_)
#define AFX_DLGUNIFYCHAR_H__53F97B08_CBFE_40A2_A58E_A9DC1662818A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUnifyChar.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgUnifyChar �_�C�A���O

class CDlgUnifyChar : public CDialog
{
// �R���X�g���N�V����
public:
	CDlgUnifyChar(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgUnifyChar)
	enum { IDD = IDD_DIALOG_UNIFY_CHAR };
	int		m_nConvAlpha;
	int		m_nConvHiraKata;
	int		m_nConvKata;
	int		m_nConvKigou;
	int		m_nConvSuji;
	int		m_nConvUpLow;
	int		m_nConvFixedUpLow;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgUnifyChar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgUnifyChar)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGUNIFYCHAR_H__53F97B08_CBFE_40A2_A58E_A9DC1662818A__INCLUDED_)
