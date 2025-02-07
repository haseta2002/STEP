#if !defined(AFX_DLGENVPLAYER_H__893320E2_73F8_11D4_9459_00402641B29B__INCLUDED_)
#define AFX_DLGENVPLAYER_H__893320E2_73F8_11D4_9459_00402641B29B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEnvPlayer.h : �w�b�_�[ �t�@�C��
//
#include "OptionPage/OptionPage.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvPlayer �_�C�A���O

class CDlgEnvPlayer : public COptionPage
{
	DECLARE_DYNCREATE(CDlgEnvPlayer)

// �R���X�g���N�V����
public:
	CDlgEnvPlayer();
	~CDlgEnvPlayer();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgEnvPlayer)
	enum { IDD = IDD_DLG_ENV_PLAYER };
	int		m_nPlayerType;
	CString	m_strWinAmpPath;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CDlgEnvPlayer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgEnvPlayer)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtRefWinamp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGENVPLAYER_H__893320E2_73F8_11D4_9459_00402641B29B__INCLUDED_)
