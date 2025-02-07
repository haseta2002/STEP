#if !defined(AFX_DLGFILENAMEMAXCHECK_H__28A60472_8836_4BED_AF9A_D1A1BFCE90DC__INCLUDED_)
#define AFX_DLGFILENAMEMAXCHECK_H__28A60472_8836_4BED_AF9A_D1A1BFCE90DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFileNameMaxCheck.h : �w�b�_�[ �t�@�C��
//
#include "OptionPage/OptionPage.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgFileNameMaxCheck �_�C�A���O

class CDlgFileNameMaxCheck : public COptionPage
{
// �R���X�g���N�V����
public:
	CDlgFileNameMaxCheck(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgFileNameMaxCheck)
	enum { IDD = IDD_DLG_FILENAME_MAX_CHECK };
	CButton	m_checkFileNameMaxCellColor;
	BOOL	m_bFileNameMaxCheck;
	UINT	m_nFileNameMaxChar;
	BOOL	m_bFileNameMaxCellColor;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgFileNameMaxCheck)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgFileNameMaxCheck)
	afx_msg void OnChFilenameMaxCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGFILENAMEMAXCHECK_H__28A60472_8836_4BED_AF9A_D1A1BFCE90DC__INCLUDED_)
