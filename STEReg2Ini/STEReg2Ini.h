// STEReg2Ini.h : STEREG2INI アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_STEREG2INI_H__DDDFB67E_EB5C_424F_B2ED_8A1958E0187E__INCLUDED_)
#define AFX_STEREG2INI_H__DDDFB67E_EB5C_424F_B2ED_8A1958E0187E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CSTEReg2IniApp:
// このクラスの動作の定義に関しては STEReg2Ini.cpp ファイルを参照してください。
//

class CSTEReg2IniApp : public CWinApp
{
public:
	CSTEReg2IniApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSTEReg2IniApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CSTEReg2IniApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_STEREG2INI_H__DDDFB67E_EB5C_424F_B2ED_8A1958E0187E__INCLUDED_)
