#if !defined(AFX_DLGLOADPLAYLIST_H__25201AA0_10AB_11D4_9459_00402641B29B__INCLUDED_)
#define AFX_DLGLOADPLAYLIST_H__25201AA0_10AB_11D4_9459_00402641B29B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLoadPlayList.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLoadPlayList �_�C�A���O

class CDlgLoadPlayList : public CDialog
{
// �R���X�g���N�V����
public:
	CDlgLoadPlayList(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgLoadPlayList)
	enum { IDD = IDD_DLG_LOAD_PLAYLIST };
	BOOL	m_bClearCheck;
	BOOL	m_bClearList;
	int		m_nAddListFlag;
	int		m_nFileCheckFlag;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgLoadPlayList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgLoadPlayList)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGLOADPLAYLIST_H__25201AA0_10AB_11D4_9459_00402641B29B__INCLUDED_)
