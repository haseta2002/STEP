// STEReg2IniDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_STEREG2INIDLG_H__2615F1A7_BD85_4F0C_8934_2D0203261CCF__INCLUDED_)
#define AFX_STEREG2INIDLG_H__2615F1A7_BD85_4F0C_8934_2D0203261CCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSTEReg2IniDlg �_�C�A���O

class CSTEReg2IniDlg : public CDialog
{
// �\�z
public:
	CSTEReg2IniDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^
	void ReadRegistry(void);
	void ReadWindowStatus(char *sKey, RECT *rect);
	int GetProfileInt(LPCTSTR sSec, LPCTSTR sKey, int nDefault);
	void ReadCellStateControl();
	void WriteCellStateControl();
	void ReadGenreList(void);
	void WriteGenreList(void);
	void ReadKeyConfig(bool bUpdate);
	void WriteKeyConfig(bool bUpdate);

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSTEReg2IniDlg)
	enum { IDD = IDD_STEREG2INI_DIALOG };
		// ����: ���̈ʒu�� ClassWizard �ɂ���ăf�[�^ �����o���ǉ�����܂��B
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSTEReg2IniDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSTEReg2IniDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_STEREG2INIDLG_H__2615F1A7_BD85_4F0C_8934_2D0203261CCF__INCLUDED_)
