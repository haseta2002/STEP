#if !defined(AFX_DLGFAVORITES_H__72E00FFA_954D_4161_907B_FD5191B44F29__INCLUDED_)
#define AFX_DLGFAVORITES_H__72E00FFA_954D_4161_907B_FD5191B44F29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFavorites.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFavorites �_�C�A���O

class CDlgFavorites : public CDialog
{
// �R���X�g���N�V����
public:
	CDlgFavorites(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgFavorites)
	enum { IDD = IDD_DIALOG_FAVORITES };
	CString	m_strFavirites[10];
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgFavorites)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgFavorites)
	afx_msg void OnBtRefFavorites1();
	afx_msg void OnBtRefFavorites10();
	afx_msg void OnBtRefFavorites2();
	afx_msg void OnBtRefFavorites3();
	afx_msg void OnBtRefFavorites4();
	afx_msg void OnBtRefFavorites5();
	afx_msg void OnBtRefFavorites6();
	afx_msg void OnBtRefFavorites7();
	afx_msg void OnBtRefFavorites8();
	afx_msg void OnBtRefFavorites9();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void OnBtRefFavorites(CString& strFavorite);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGFAVORITES_H__72E00FFA_954D_4161_907B_FD5191B44F29__INCLUDED_)
