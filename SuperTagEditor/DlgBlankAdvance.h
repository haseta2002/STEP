#if !defined(AFX_DLGBLANKADVANCE_H__1D5F7C64_5549_4A48_B632_BEDF3B74F01F__INCLUDED_)
#define AFX_DLGBLANKADVANCE_H__1D5F7C64_5549_4A48_B632_BEDF3B74F01F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBlankAdvance.h : �w�b�_�[ �t�@�C��
//
#include "OptionPage/OptionPage.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgBlankAdvance �_�C�A���O

class CDlgBlankAdvance : public COptionPage
{
	DECLARE_DYNCREATE(CDlgBlankAdvance)

// �R���X�g���N�V����
public:
	CDlgBlankAdvance();
	~CDlgBlankAdvance();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgBlankAdvance)
	enum { IDD = IDD_DIALOG_BLANK_ADVANCE };
		// ���� - ClassWizard �͂��̈ʒu�Ƀf�[�^ �����o��ǉ����܂��B
		//    ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CDlgBlankAdvance)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgBlankAdvance)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGBLANKADVANCE_H__1D5F7C64_5549_4A48_B632_BEDF3B74F01F__INCLUDED_)
