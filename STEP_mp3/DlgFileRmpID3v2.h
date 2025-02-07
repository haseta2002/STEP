#if !defined(AFX_DLGFILERMPID3V2_H__DB58BAE7_750F_475F_A29E_95CD220EE90D__INCLUDED_)
#define AFX_DLGFILERMPID3V2_H__DB58BAE7_750F_475F_A29E_95CD220EE90D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFileRmpID3v2.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFileRmpID3v2 �_�C�A���O

class CDlgFileRmpID3v2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgFileRmpID3v2)

// �R���X�g���N�V����
public:
	CDlgFileRmpID3v2();
	~CDlgFileRmpID3v2();

	void	UpdateStatus(void);

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgFileRmpID3v2)
	enum { IDD = IDD_DLG_FILE_RMP_ID3V2 };
	BOOL	m_bRmpID3tagAutoWrite;
	BOOL	m_bAutoConvRMP;
	int		m_nSIFieldConvertType;
	BOOL	m_bRmpGenreListSelect;
	BOOL	m_bChangeFileExt;
	BOOL	m_bAutoConvID3v2;
	BOOL	m_bID3v2ID3tagAutoWrite;
	BOOL	m_bID3v2GenreListSelect;
	BOOL	m_bID3v2GenreAddNumber;
	BOOL	m_bID3v2Id3tagAutoDelete;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CDlgFileRmpID3v2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgFileRmpID3v2)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtResetPage();
	afx_msg void OnChAutoConvRmp();
	afx_msg void OnChAutoConvId3v2();
	afx_msg void OnChId3v2Id3tagAutoWrite();
	afx_msg void OnChId3v2Id3tagAutoDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGFILERMPID3V2_H__DB58BAE7_750F_475F_A29E_95CD220EE90D__INCLUDED_)
