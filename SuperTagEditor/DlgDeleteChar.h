#if !defined(AFX_DLGDELETECHAR_H__DCE4D8FD_84C9_48B1_BF50_EF59313DEB22__INCLUDED_)
#define AFX_DLGDELETECHAR_H__DCE4D8FD_84C9_48B1_BF50_EF59313DEB22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDeleteChar.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// DlgDeleteChar �_�C�A���O

class DlgDeleteChar : public CDialog
{
// �R���X�g���N�V����
public:
	DlgDeleteChar(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(DlgDeleteChar)
	enum { IDD = IDD_DLG_DELETE_CHAR };
	UINT	m_nDelCount;
	int		m_nPos;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(DlgDeleteChar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(DlgDeleteChar)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGDELETECHAR_H__DCE4D8FD_84C9_48B1_BF50_EF59313DEB22__INCLUDED_)
