// STEP_mp3.h : STEP_MP3 �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_STEP_MP3_H__F4707E45_2B14_44B2_8276_EFAFAFC465EE__INCLUDED_)
#define AFX_STEP_MP3_H__F4707E45_2B14_44B2_8276_EFAFAFC465EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CSTEP_mp3App
// ���̃N���X�̓���̒�`�Ɋւ��Ă� STEP_mp3.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CSTEP_mp3App : public CWinApp
{
public:
	CSTEP_mp3App();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSTEP_mp3App)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSTEP_mp3App)
		// ���� -  ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//         ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#define TYPE_IS_MP3(nFormat) (nFormat == nFileTypeMP3 || nFormat == nFileTypeMP3V1 || nFormat == nFileTypeMP3V11 || nFormat == nFileTypeID3V2)
#define TYPE_IS_MP3V1(nFormat) (nFormat == nFileTypeMP3 || nFormat == nFileTypeMP3V1 || nFormat == nFileTypeMP3V11)
#define TYPE_IS_MP3V2(nFormat) (nFormat == nFileTypeID3V2)
#define TYPE_IS_RMP(nFormat) (nFormat == nFileTypeRMP)
#define	TYPE_IS_SUPPORT(nFormat) (TYPE_IS_MP3(nFormat) || TYPE_IS_RMP(nFormat))

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_STEP_MP3_H__F4707E45_2B14_44B2_8276_EFAFAFC465EE__INCLUDED_)
