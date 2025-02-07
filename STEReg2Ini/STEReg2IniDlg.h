// STEReg2IniDlg.h : ヘッダー ファイル
//

#if !defined(AFX_STEREG2INIDLG_H__2615F1A7_BD85_4F0C_8934_2D0203261CCF__INCLUDED_)
#define AFX_STEREG2INIDLG_H__2615F1A7_BD85_4F0C_8934_2D0203261CCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSTEReg2IniDlg ダイアログ

class CSTEReg2IniDlg : public CDialog
{
// 構築
public:
	CSTEReg2IniDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ
	void ReadRegistry(void);
	void ReadWindowStatus(char *sKey, RECT *rect);
	int GetProfileInt(LPCTSTR sSec, LPCTSTR sKey, int nDefault);
	void ReadCellStateControl();
	void WriteCellStateControl();
	void ReadGenreList(void);
	void WriteGenreList(void);
	void ReadKeyConfig(bool bUpdate);
	void WriteKeyConfig(bool bUpdate);

// ダイアログ データ
	//{{AFX_DATA(CSTEReg2IniDlg)
	enum { IDD = IDD_STEREG2INI_DIALOG };
		// メモ: この位置に ClassWizard によってデータ メンバが追加されます。
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSTEReg2IniDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSTEReg2IniDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_STEREG2INIDLG_H__2615F1A7_BD85_4F0C_8934_2D0203261CCF__INCLUDED_)
