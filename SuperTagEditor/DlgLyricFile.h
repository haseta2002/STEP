#if !defined(AFX_DLGLYRICFILE_H__34B29241_448D_4BF4_950D_35DE90673465__INCLUDED_)
#define AFX_DLGLYRICFILE_H__34B29241_448D_4BF4_950D_35DE90673465__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLyricFile.h : �w�b�_�[ �t�@�C��
//
#include "OptionPage/OptionPage.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgLyricFile �_�C�A���O

class CDlgLyricFile : public COptionPage
{
	DECLARE_DYNCREATE(CDlgLyricFile)

// �R���X�g���N�V����
public:
	CDlgLyricFile();
	~CDlgLyricFile();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgLyricFile)
	enum { IDD = IDD_DLG_LYRIC };
	CButton	m_btSearchLyricsSubDir;
	CEdit	m_editLyricsPath;
	CButton	m_btSetLyricsDir;
	CButton	m_btRefLyrics;
	BOOL	m_bChangeTextFile;
	CString	m_strLyricsPath;
	BOOL	m_bSetLyricsDir;
	BOOL	m_bSearchLyricsSubDir;
	//}}AFX_DATA

	void	UpdateStatus(void);

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CDlgLyricFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgLyricFile)
	afx_msg void OnBtRefLyrics();
	afx_msg void OnChSetLyricsDir();
	afx_msg void OnChChangeTextFilename();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtResetPage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGLYRICFILE_H__34B29241_448D_4BF4_950D_35DE90673465__INCLUDED_)
