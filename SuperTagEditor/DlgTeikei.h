#if !defined(AFX_DLGTEIKEI_H__FFEA78C8_E872_4903_9D2C_B2D2C6CC159E__INCLUDED_)
#define AFX_DLGTEIKEI_H__FFEA78C8_E872_4903_9D2C_B2D2C6CC159E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTeikei.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTeikei �_�C�A���O

class CDlgTeikei : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgTeikei)

// �R���X�g���N�V����
public:
	CDlgTeikei();
	~CDlgTeikei();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgTeikei)
	enum { IDD = IDD_DIALOG_TEIKEI };
	CString	m_strTeikei1;
	CString	m_strTeikei10;
	CString	m_strTeikei2;
	CString	m_strTeikei3;
	CString	m_strTeikei4;
	CString	m_strTeikei5;
	CString	m_strTeikei6;
	CString	m_strTeikei7;
	CString	m_strTeikei8;
	CString	m_strTeikei9;
	CString	m_strGroupName;
	//}}AFX_DATA

	TEIKEI_INFO m_teikeiInfo[10];


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CDlgTeikei)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgTeikei)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtDetail01();
	afx_msg void OnBtDetail10();
	afx_msg void OnBtDetail02();
	afx_msg void OnBtDetail03();
	afx_msg void OnBtDetail04();
	afx_msg void OnBtDetail05();
	afx_msg void OnBtDetail06();
	afx_msg void OnBtDetail07();
	afx_msg void OnBtDetail08();
	afx_msg void OnBtDetail09();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BYTE m_nGroupNumber;
private:
	void OnDetail(int nIndex);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGTEIKEI_H__FFEA78C8_E872_4903_9D2C_B2D2C6CC159E__INCLUDED_)
