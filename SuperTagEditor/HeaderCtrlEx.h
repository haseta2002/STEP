#if !defined(AFX_HEADERCTRLEX_H__C6C3D360_E1BC_11D3_9459_00402641B29B__INCLUDED_)
#define AFX_HEADERCTRLEX_H__C6C3D360_E1BC_11D3_9459_00402641B29B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HeaderCtrlEx.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx �E�B���h�E

class CHeaderCtrlEx : public CHeaderCtrl
{
// �R���X�g���N�V����
public:
	CHeaderCtrlEx();

protected:
	int		m_nSortCol;
	BOOL	m_bSortAsc;

public:
	int		SetSortImage(int, BOOL);

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CHeaderCtrlEx)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CHeaderCtrlEx();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CHeaderCtrlEx)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	afx_msg void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_HEADERCTRLEX_H__C6C3D360_E1BC_11D3_9459_00402641B29B__INCLUDED_)
