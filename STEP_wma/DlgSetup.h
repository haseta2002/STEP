#if !defined(AFX_CDLGSETUP_H__BAB08FBC_1AFB_4304_9AD2_1D604A3CF061__INCLUDED_)
#define AFX_CDLGSETUP_H__BAB08FBC_1AFB_4304_9AD2_1D604A3CF061__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CDlgSetup.h : �w�b�_�[ �t�@�C��
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
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CDLGSETUP_H__BAB08FBC_1AFB_4304_9AD2_1D604A3CF061__INCLUDED_)
