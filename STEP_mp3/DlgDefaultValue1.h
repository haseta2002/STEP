#if !defined(AFX_DLGDEFAULTVALUE1_H__DDCBFFF9_307E_4029_81DA_4F28BE3094BA__INCLUDED_)
#define AFX_DLGDEFAULTVALUE1_H__DDCBFFF9_307E_4029_81DA_4F28BE3094BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDefaultValue1.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// DlgDefaultValue �_�C�A���O

class DlgDefaultValue : public CDialog
{
// �R���X�g���N�V����
public:
	DlgDefaultValue(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(DlgDefaultValue)
	enum { IDD = IDD_DLG_DEFAUT_VALUE };
		// ����: ClassWizard �͂��̈ʒu�Ƀf�[�^ �����o��ǉ����܂��B
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(DlgDefaultValue)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(DlgDefaultValue)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGDEFAULTVALUE1_H__DDCBFFF9_307E_4029_81DA_4F28BE3094BA__INCLUDED_)
