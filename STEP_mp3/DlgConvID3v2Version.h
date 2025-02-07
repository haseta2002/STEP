#if !defined(AFX_DLGCONVID3V2VERSION_H__949D751B_4994_4BBA_8532_64763197473C__INCLUDED_)
#define AFX_DLGCONVID3V2VERSION_H__949D751B_4994_4BBA_8532_64763197473C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgConvID3v2Version.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgConvID3v2Version �_�C�A���O

class CDlgConvID3v2Version : public CDialog
{
// �R���X�g���N�V����
public:
	CDlgConvID3v2Version(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgConvID3v2Version)
	enum { IDD = IDD_DLG_CONV_ID3V2_VERSION };
	CComboBox	m_cbId3v2Version;
	CComboBox	m_cbId3v2Encode;
	int		m_nId3v2Encode;
	int		m_nId3v2Version;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgConvID3v2Version)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgConvID3v2Version)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboId3v2Version();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGCONVID3V2VERSION_H__949D751B_4994_4BBA_8532_64763197473C__INCLUDED_)
