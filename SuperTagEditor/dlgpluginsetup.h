#if !defined(AFX_CDLGPLUGINSETUP_H__45B0172E_AA3B_4139_97BC_FF5564E3C887__INCLUDED_)
#define AFX_CDLGPLUGINSETUP_H__45B0172E_AA3B_4139_97BC_FF5564E3C887__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CDlgPluginSetup.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPluginSetup �_�C�A���O

class CDlgPluginSetup : public CDialog
{
// �R���X�g���N�V����
public:
	CDlgPluginSetup(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgPluginSetup)
	enum { IDD = IDD_DLG_SETUP_PLUGIN };
	CListCtrl	m_listPlugin;
	CString	m_strPluginInfo;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgPluginSetup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgPluginSetup)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedListPlugin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtSetup();
	afx_msg void OnBtInstall();
	afx_msg void OnBtUp();
	afx_msg void OnBtDown();
	virtual void OnOK();
	afx_msg void OnBtUninstall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CDLGPLUGINSETUP_H__45B0172E_AA3B_4139_97BC_FF5564E3C887__INCLUDED_)
