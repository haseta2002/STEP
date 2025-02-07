#if !defined(AFX_DLGSETUP_H__E7A8FD8E_E882_4311_84B7_810018582F8F__INCLUDED_)
#define AFX_DLGSETUP_H__E7A8FD8E_E882_4311_84B7_810018582F8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetup.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSetup �_�C�A���O

class CDlgSetup : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgSetup)

// �R���X�g���N�V����
public:
	CDlgSetup();
	~CDlgSetup();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgSetup)
	enum { IDD = IDD_DLG_SETUP };
	BOOL	m_bGenreListSelect;
	BOOL	m_bID3TagAutoDelete;
	BOOL	m_bID3TagAutoWrite;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgSetup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgSetup)
	afx_msg void OnChId3tagAutoDelete();
	afx_msg void OnChId3tagAutoWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGSETUP_H__E7A8FD8E_E882_4311_84B7_810018582F8F__INCLUDED_)
