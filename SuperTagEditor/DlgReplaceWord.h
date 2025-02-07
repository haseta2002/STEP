#if !defined(AFX_DLGREPLACEWORD_H__AA7CFC00_157D_11D4_9459_00402641B29B__INCLUDED_)
#define AFX_DLGREPLACEWORD_H__AA7CFC00_157D_11D4_9459_00402641B29B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgReplaceWord.h : �w�b�_�[ �t�@�C��
//

#include "HistoryComboEx.h"

class	CMySuperGrid;

/////////////////////////////////////////////////////////////////////////////
// CDlgReplaceWord �_�C�A���O

class CDlgReplaceWord : public CDialog
{
// �R���X�g���N�V����
public:
	CRect m_rect; /* WildCherry4 086 */
	CDlgReplaceWord(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgReplaceWord)
	enum { IDD = IDD_DLG_REPLACE_WORD };
	CHistoryComboEx	m_listReplaceWord;
	CHistoryComboEx	m_listSearchWord;
	CStatic	m_stReplace;
	CButton	m_btAllReplace;
	CButton	m_btReplace;
	CButton	m_btRegExp;
	CButton	m_btRangeSelected;
	CButton	m_btMatchComplete;
	CButton	m_btCheckDiffUL;
	CComboBox	m_listTargetColumn;
	BOOL	m_bCheckDiffUL;
	BOOL	m_bMatchComplete;
	BOOL	m_bRangeSelected;
	int		m_nTargetColumn;
	BOOL	m_bRegExp;
	CString	m_strReplaceWord;
	CString	m_strSearchWord;
	//}}AFX_DATA

	CMySuperGrid	*m_pList;
	BOOL	m_bModeReplace;
	BOOL	m_bEnableRangeSelected;
	void	UpdateStatus(void);

	void	UpdateCheckWordState(void);
	void	ExecSearch(bool);

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgReplaceWord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgReplaceWord)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtSearchBefore();
	afx_msg void OnBtSearchNext();
	afx_msg void OnBtReplace();
	virtual void OnOK();
	afx_msg void OnSelChangeListTarget();
	afx_msg void OnChRegexp();
	afx_msg void OnChRangeSelected();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool m_bAddCurrentItemtoHistory;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGREPLACEWORD_H__AA7CFC00_157D_11D4_9459_00402641B29B__INCLUDED_)
