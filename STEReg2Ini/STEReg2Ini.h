// STEReg2Ini.h : STEREG2INI �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_STEREG2INI_H__DDDFB67E_EB5C_424F_B2ED_8A1958E0187E__INCLUDED_)
#define AFX_STEREG2INI_H__DDDFB67E_EB5C_424F_B2ED_8A1958E0187E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CSTEReg2IniApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� STEReg2Ini.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CSTEReg2IniApp : public CWinApp
{
public:
	CSTEReg2IniApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSTEReg2IniApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CSTEReg2IniApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_STEREG2INI_H__DDDFB67E_EB5C_424F_B2ED_8A1958E0187E__INCLUDED_)
