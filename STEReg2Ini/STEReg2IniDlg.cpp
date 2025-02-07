// STEReg2IniDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "STEReg2Ini.h"
#include "STEReg2IniDlg.h"

#include "Registry.h"

#include "RegExp.h"

#include "STE/resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CString strINI = "SuperTagEditor.ini";

/////////////////////////////////////////////////////////////////////////////
// CSTEReg2IniDlg ダイアログ

CSTEReg2IniDlg::CSTEReg2IniDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSTEReg2IniDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSTEReg2IniDlg)
		// メモ: この位置に ClassWizard によってメンバの初期化が追加されます。
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSTEReg2IniDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSTEReg2IniDlg)
		// メモ: この場所には ClassWizard によって DDX と DDV の呼び出しが追加されます。
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSTEReg2IniDlg, CDialog)
	//{{AFX_MSG_MAP(CSTEReg2IniDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSTEReg2IniDlg メッセージ ハンドラ

BOOL CSTEReg2IniDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定

	// TODO: 特別な初期化を行う時はこの場所に追加してください。

	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CSTEReg2IniDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CSTEReg2IniDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

enum	{CHECK_STATE_CHECK, CHECK_STATE_REPLACE, CHECK_STATE_MAX};
//extern	CHECK_WORD_STATE	g_chkWord[CHECK_STATE_MAX];

enum	{SIF_CONV_ALL_FIELD, SIF_CONV_LENGTH_OK};

enum	{PLAYER_WINAMP, PLAYER_SCMPX, PLAYER_KBMPLAY, PLAYER_EXTEND, PLAYER_LILITH/* WildCherry 070 */};

#define USER_GENRE_LIST_MAX 50


enum	{
	FILENAME_NO_CHECK,				// チェックしない
	FILENAME_CONV_MULTIBYTE,		// ２バイト文字に変換
};

#define SORT_KEY_MAX		5
struct	SORT_STATE	{				// ソート情報
	int		nKeyColumn;				// ソートキー(カラム番号)
	int		nType;					// タイプ(0:昇順/1:降順)
};

#define CLASS_MAX			5		// 分類階層の深さ(最大)
struct	CLASS_INFO	{				// 分類情報
	int		nType;					// 分類タイプ
	int		nColumn[CLASS_MAX];		// カラム番号
};

enum	{
	COMMAND_GROUP_FILE,
	COMMAND_GROUP_EDIT,
	COMMAND_GROUP_DISP,
	COMMAND_GROUP_PLAYLIST,
	COMMAND_GROUP_PLAYER,
	COMMAND_GROUP_CONV,
	COMMAND_GROUP_MAX,
};

enum	{
	COLUMN_TREE_ITEM = 0,
	COLUMN_FULL_PATH_NAME = 0,
	COLUMN_FILE_NAME,
	COLUMN_TRACK_NAME,		// 曲名
	COLUMN_ARTIST_NAME,		// アーティスト名
	COLUMN_ALBUM_NAME,		// アルバム名／製品名
	COLUMN_TRACK_NUMBER,	// トラック番号(ID3 tag v1.1のみ)
	COLUMN_YEAR,			// リリース年号
	COLUMN_GENRE,			// ジャンル
	COLUMN_COMMENT,			// コメント文字列
	COLUMN_COPYRIGHT,		// 著作権
	COLUMN_ENGINEER,		// エンジニア(製作者)
	COLUMN_SOURCE,			// ソース
	COLUMN_SOFTWARE,		// ソフトウェア
	COLUMN_KEYWORD,			// キーワード
	COLUMN_TECHNICIAN,		// 技術者
	COLUMN_LYRIC,			// 歌詞
	COLUMN_COMMISSION,		// コミッション
	COLUMN_COMPOSER,		// 作曲 /* Baja 154 */
	COLUMN_ORIG_ARTIST,		// Orig.アーティスト /* Baja 154 */
	COLUMN_URL,				// URL /* Baja 154 */
	COLUMN_ENCODEST,		// エンコードした人 /* Baja 154 */
	COLUMN_FILE_SIZE,		// ファイルサイズ
	COLUMN_FILE_TIME,		// ファイルタイムスタンプ
	COLUMN_FILE_PATH,		// ファイルパス名
	COLUMN_PLAY_TIME,		// 演奏時間
	COLUMN_LYRIC_FILE,		// 歌詞ファイル
	COLUMN_FILE_TYPE,		// ファイルの種類
	COLUMN_FORMAT,			// フォーマット /* Conspiracy 198 */
	COLUMN_OTHER,			// その他 /* Conspiracy 196 */
	COLUMN_FILE_CTIME,		// ファイル作成日 /* Hurricane 207 */
	COLUMN_MAX,
};


struct	KEY_CONFIG	{				// キー割り当て
	WORD	wCmdID;					// メニューリソースＩＤ
	DWORD	dwKeyCode;				// ホットキー
	int		nGroupID;				// グループ名
	char	*sName;					// 項目名
	char	*sRegName;				// レジストリ名
};
extern	KEY_CONFIG	g_listKeyConfig[];

#define FILENAME_REPLACE_MAX		12
#define USER_FILENAME_REPLACE_MAX		6	/* FreeFall 050 */
struct	FILENAME_REPLACE {			// ファイル名置換
	CString	strBefore;				// 置換前の文字
	CString	strAfter;				// 置換後の文字
};
const char *g_sRepTable[FILENAME_REPLACE_MAX][2] = {
	{"\"", "”"}, {"*" , "＊"}, {"," , "，"}, {"/" , "／"},
	{":" , "："}, {";" , "；"}, {"<" , "＜"}, {">" , "＞"},
	{"?" , "？"}, {"\\", "￥"}, {"|" , "｜"}, {" " , " "},
};

#define USER_CONV_FORMAT_MAX		5 /*3 LastTrain 057 */
struct	USER_CONV_FORMAT	{		// ユーザー変換書式
	CString	strName;				// 名称
	CString	strTag2File;			// 書式：タグ情報 => ファイル名
	CString	strFile2Tag;			// 書式：ファイル名 => タグ情報
};

#define USER_CONV_FORMAT_EX_MAX		10
struct	USER_CONV_FORMAT_EX	{		// 拡張版ユーザー変換書式
	CString	strName;				// 名称
	CString	strFormat;				// 書式
	CString	strFixString;			// 固定文字列
	int		nInitNumber;			// 連番：初期値
	int		nAddNumber;				// 連番：加算値
	int		nColumnCount;			// 連番：桁数
	bool	bSpaceInitNumber;		// 書き込み不可のセルで連番クリア
};

#define USER_MOVE_FODLER_FORMAT_MAX	5
struct	USER_MOVE_FODLER_FORMAT	{	// 移動先フォルダ書式
	CString	strName;				// 名称
	CString	strFormat;				// 書式
	CString	strFixString;			// 固定文字列
	bool	bCopy;					// コピーする
};

/* FunnyCorn 175 */
#define USER_COPY_FORMAT_FORMAT_MAX	5
struct	USER_COPY_FORMAT_FORMAT	{	// 書式コピー
	CString	strName;				// 名称
	CString	strFormat;				// 書式
	CString	strFixString;			// 固定文字列
};

#define WRITE_FORMAT_MAX			5
struct	WRITE_FORMAT	{			// 拡張版ユーザー変換書式
	CString	strName;				// 名称
	CString	strFileName;			// 書式ファイル
	CString	strExtName;				// 拡張子
	bool	bWriteSelected;			// 選択ファイルのみ上書き
	CString	strCurrentFile;			// カレントファイル名
	bool	bIsHtml;				// HTML ファイル出力用(空の場合に全角スペースを出力)
	bool	bWriteHtml;				// HTML ファイルとして出力（タグを置換する）/* BeachMonster5 120 */
};

struct	CHECK_WORD_STATE	{		// 条件チェック用の情報
	CString	strSearchWord;			// 検索文字列
	CString	strReplaceWord;			// 置換文字列
	int		nTargetColumn;			// 検索対象カラム
	BOOL	bCheckDiffUL;			// 大文字／小文字の区別
	BOOL	bRegExp;				// 正規表現
	BOOL	bRangeSelected;			// 選択範囲のみ
	BOOL	bMatchComplete;			// 完全に一致
	BOOL	bMatchSelected;			// チェックせずに選択状態にする
	int		nMatchColumn;			// (出力)検索結果：一致したカラム
	int		nMatchPos;				// (出力)検索結果：一致した位置
	int		nMatchLength;			// (出力)検索結果：一致した長さ
	CRegExp	regexp;					// 正規表現クラス(内部処理用)
};

static	char	*sSectionOption			= "Option";
static	char	*sKeyVersion			= "Version";
static	char	*sKeyCurrentDir			= "CurrentDir";
static	char	*sKeyCurrentPlayList	= "CurrentPlayList";
static	char	*sKeyEnterBeginEdit		= "EnterBeginEdit";
static	char	*sKeyESCEditCancel		= "ESCEditCancel";
static	char	*sKeyEnableEditCursorExit= "EnableEditCursorExit";
static	char	*sKeyEditOkDown			= "EditOkDown";
static	char	*sKeyKeepTimeStamp		= "KeepTimeStamp";
static	char	*sKeySyncCreateTime		= "SyncCreateTime";
static	char	*sKeyChangeFileExt		= "ChangeFileExt";
static	char	*sKeyAutoConvID3v2		= "AutoConvID3v2";
static	char	*sKeyID3v2ID3tagAutoWrite	= "ID3v2ID3tagAutoWrite";
static	char	*sKeyID3v2ID3tagAutoDelete	= "ID3v2ID3tagAutoDelete";
static	char	*sKeyID3v2GenreListSelect	= "ID3v2GenreListSelect";
static	char	*sKeyAutoConvRMP		= "AutoConvRMP";
static	char	*sKeyRmpID3tagAutoWrite	= "RmpID3tagAutoWrite";
static	char	*sKeyRmpGenreListSelect	= "RmpGenreListSelect";
static	char	*sKeyLoadFileChecked	= "LoadFileChecked";
static	char	*sKeyHideMP3ListFile	= "HideMP3ListFile";
static	char	*sKeyDropSearchSubFolder	= "DropSearchSubFolder";	/* TyphoonSwell 026 */
static	char	*sKeyShowZenSpace	= "ShowZenSpace";	/* BeachMonster 107 */
static	char	*sKeyShowOtherChar	= "ShowOtherChar";	/* BeachMonster 107 */
static	char	*sKeySortIgnoreCase	= "SortIgnoreCase";	/* BeachMonster4 114 */
static	char	*sKeySortIgnoreZenHan	= "SortIgnoreZenHan";	/* BeachMonster4 114 */
static	char	*sKeySortIgnoreKataHira	= "SortIgnoreKataHira";	/* FunnyCorn 179 */
static	char	*sKeyShowTotalParent	= "ShowTotalParent";	/* RockDance 128 */
static	char	*sKeyShowTips	= "ShowTips";	/* Rumble 188 */
static	char	*sKeyChangeTextFile		= "ChangeTextFile";
static	char	*sKeyEditFiledSIF		= "EditFiledSI";
static	char	*sKeyAutoOpenFolder		= "AutoOpenFolder";
static	char	*sKeySIFieldConvType	= "SIFieldConvType";
static	char	*sKeyLoadFileAdjustColumn	= "LoadFileAdjustColumn";
static	char	*sKeySetLyricsDir		= "SetLyricsDir";
static	char	*sKeySearchLyricsSubDir	= "SearchLyricsSubDir";
static	char	*sKeyEnableSearchSubDir	= "EnableSearchSubDir";
static	char	*sKeyLyricsPath			= "LyricsPath";
static	char	*sKeyCheckFileName		= "CheckFileName";
static	char	*sKeyPlayerType			= "PlayerType";
static	char	*sKeyWinAmpPath			= "WinAmpPath";

static	char	*sKeyID3v2GenreAddNumber	= "ID3v2GenreAddNumber";
static	char	*sKeyFileNameMaxCheck	= "FileNameMaxCheck";
static	char	*sKeyFileNameMaxChar	= "FileNameMaxChar";
static	char	*sKeyFileNameMaxCellColor	= "FileNameMaxCellColor";

static	char	*sSectionFolderSync			= "FolderSync";
static	char	*sKeyEnableFolderSync		= "EnableFolderSync";
static	char	*sKeySyncRootFolder			= "RootFolder";
static	char	*sKeySyncSelectAlways		= "SelectAlways";
static	char	*sKeySyncDeleteFolder		= "DeleteFolder";
static	char	*sKeySyncLyricsFileMove		= "LyricsFileMove";

static	char	*sSectionConfMessage	= "ConfMessage";
static	char	*sKeyConfConvMP3		= "ConvMP3";
static	char	*sKeyConfConvRMP		= "ConvRMP";
static	char	*sKeyConfConvID3v2		= "ConvID3v2";
static	char	*sKeyConfDeleteFile		= "DeleteFile";
static	char	*sKeyConfDeleteList		= "DeleteList";
static	char	*sKeyConfEditModify		= "EditModify";
static	char	*sKeyConfFolderSync		= "FolderSync";

static	char	*sSectionLoadPlayList	= "LoadPlayList";
static	char	*sKeyClearList			= "ClearList";
static	char	*sKeyClearCheck			= "ClearCheck";
static	char	*sKeyAddList			= "AddList";
static	char	*sKeyFileCheck			= "FileCheck";

static	char	*sSectionCheckWord[CHECK_STATE_MAX]	= {"CheckWord", "ReplaceWord"};
static	char	*sKeySearchWord		= "SearchWord";
static	char	*sKeyReplaceWord	= "ReplaceWord";
static	char	*sKeyTargetColumn	= "TargetColumn";
static	char	*sKeyCheckDiffUL	= "CheckDiffUL";
static	char	*sKeyRegExp			= "RegExp";
static	char	*sKeyRangeSelected	= "RangeSelected";
static	char	*sKeyMatchComplete	= "MatchComplete";
static	char	*sKeyMatchSelected	= "MatchSelected";

// ユーザー書式変換
static	char	*sSectionUserConvFormat	= "UserConvFormat";
static	char	*sKeyConvFormatType		= "ConvFormatType";
static	char	*sKeyUserFormName		= "Name";
static	char	*sKeyUserFormTag2File	= "TagToFile";
static	char	*sKeyUserFormFile2Tag	= "FileToTag";

// 拡張版書式変換
static	char	*sSectionConvFormatEx	= "ConvFormatEx";
//static	char	*sKeyUserFormName		= "Name";
static	char	*sKeyUserFormat			= "Format";
static	char	*sKeyUserFixString		= "FixString";
static	char	*sKeyUserInitNumber		= "InitNumber";
static	char	*sKeyUserAddNumber		= "AddNumber";
static	char	*sKeyUserColumnCount	= "ColumnCount";
static	char	*sKeyUserSpaceInit		= "SpaceInit";

// 移動先フォルダ書式
static	char	*sSectionMoveFolder		= "MoveFolderFormat";
//static	char	*sKeyUserFormName		= "Name";
static	char	*sKeyMoveFolderFormat	= "Format";
static	char	*sKeyMoveFolderFixString	= "FixString";
static	char	*sKeyMoveFolderCopy		= "Copy";

// 書式コピー /* FunnyCorn 175 */
static	char	*sSectionCopyFormat		= "CopyFormatFormat";
//static	char	*sKeyUserFormName		= "Name";
static	char	*sKeyCopyFormatFormat	= "Format";
static	char	*sKeyCopyFormatFixString	= "FixString";

// 定型文貼り付け /* SeaKnows 030 */
static	char	*sSectionTeikei			= "Teikei";
static	char	*sSectionTeikeiGroupName	= "TeikeiGroupName";

// ソフトウェア /* SeaKnows 030 */
static	char	*sSectionSoftwareTag	= "SoftwareTag";
// フォルダ単一選択 /* SeaKnows 033 */
static	char	*sSectionValidFolderSelect	= "ValidFolderSelect";
// 多重起動を許可する /* FreeFall 045 */
static	char	*sSectionValidDupExec	= "ValidDupExec";
// 最近使ったフォルダの数
static	char	*sSectionRecentFolderNum	= "RecentFolderNum";
// 検索・置換ダイアログの位置を記憶する
static	char	*sSectionSaveRepDlgPos	= "SaveRepDlgPos";
static	char	*sSectionSaveRepDlgPosX	= "SaveRepDlgPosX";
static	char	*sSectionSaveRepDlgPosY	= "SaveRepDlgPosY";
// 下方向に連番を追加ダイアログの設定 /* Baja 159 */
static	char	*sSectionAddNumberWidth = "AddNumberWidth";
static	char	*sSectionAddNumberPos	= "AddNumberPos";
static	char	*sSectionAddNumberSep	= "AddNumberSep";
static	char	*sSectionAddNumberBef	= "AddNumberBef"; /* Conspiracy 194 */
static	char	*sSectionAddNumberAft	= "AddNumberAft"; /* Conspiracy 194 */
// ID3v2のコメントタグを古い形式で保存する /* FunnyCorn 180 */
static	char	*sSectiongId3v2OldComment	= "Id3v2OldComment";
// ID3v2をUNICODEで保存する /* FunnyCorn 181 */
static	char	*sSectiongId3v2UNICODE	= "Id3v2UNICODE";
// Audio Listに表示されるフォルダ名などの分類をセルサイズを無視して(実際は隣３セル分まで)表示する
static	char	*sSectionAudioListShow	= "AudioListShow"; /* Conspiracy 199 */

// フォント設定
static	char	*sSectionFont			= "Font";
static	char	*sKeyFontFace			= "Face";
static	char	*sKeyFontHeight			= "Height";
static	char	*sKeyFontWidth			= "Width";
static	char	*sKeyFontEscapement		= "Escapement";
static	char	*sKeyFontOrientation	= "Orientation";
static	char	*sKeyFontWeight			= "Weight";
static	char	*sKeyFontItalic			= "Italic";
static	char	*sKeyFontUnderline		= "Underline";
static	char	*sKeyFontStrikeOut		= "StrikeOut";
static	char	*sKeyFontCharSet		= "CharSet";
static	char	*sKeyFontOutPrecision	= "OutPrecision";
static	char	*sKeyFontClipPrecision	= "ClipPrecision";
static	char	*sKeyFontQuality		= "Quality";
static	char	*sKeyFontPitchAndFamily	= "PitchAndFamily";

// リスト出力書式
static	char	*sSectionWriteFormat	= "WriteFormat";
static	char	*sKeyWriteFormName		= "Name";
static	char	*sKeyWriteFileName		= "FileName";
static	char	*sKeyWriteExtName		= "ExtName";
static	char	*sKeyWriteSelected		= "WriteSelected";
static	char	*sKeyWriteCurrentFile	= "CurrentFile";
static	char	*sKeyWriteIsHtml		= "IsHtml";
static	char	*sKeyWriteHtml			= "WriteHtml"; /* BeachMonster5 120 */

static	char	*sSectionRepFileName	= "RepFileName";
static	char	*sKeyRepCharAfter		= "RepCharAfter";
static	char	*sKeyRepCharBefore		= "RepCharBefore";	/* FreeFall 050 */

static	char	*sSectionSort		= "Sort";
static	char	*sKeySortColumn		= "Column";
static	char	*sKeySortType		= "Type";

static	char	*sSectionClass		= "Class";
static	char	*sKeyClassType		= "Type";
static	char	*sKeyClassColumn	= "Column";

static	char	*sSectionWindow		= "Window";
static	char	*sKeyWinZoomed		= "Zoomed";
static	char	*sKeyWinIconic		= "Iconic";
static	char	*sKeyMainWindow		= "MainWindow";
static	char	*sKeySplitSize		= "SplitSize";

static	char	*sSectionKeyConfig	= "KeyConfig";

static	char	*sSectionGenreList	= "GenreList";
static	char	*sSectionUserGenreList	= "UserGenreList";
static	char	*sKeyUserGenreAddList	= "AddList";
static	char	*sKeyUserGenreNo	= "No";
static	char	*sKeyUserGenreName	= "Name";

// 文字種統一 /* StartInaction 054 */
static	char	*sKeyUnifyAlpha	= "UnifyAlpha";
static	char	*sKeyUnifyHiraKata	= "UnifyHiraKata";
static	char	*sKeyUnifyKata	= "UnifyKata";
static	char	*sKeyUnifyKigou	= "UnifyKigou";
static	char	*sKeyUnifySuji	= "UnifySuji";
static	char	*sKeyUnifyUpLow	= "UnifyUpLow";

// ファイル名文字種統一 /* LastTrain 058 */
static	char	*sKeyFileUnifyAlpha	= "FileUnifyAlpha";
static	char	*sKeyFileUnifyHiraKata	= "FileUnifyHiraKata";
static	char	*sKeyFileUnifyKata	= "FileUnifyKata";
static	char	*sKeyFileUnifyKigou	= "FileUnifyKigou";
static	char	*sKeyFileUnifySuji	= "FileUnifySuji";
static	char	*sKeyFileUnifyUpLow	= "FileUnifyUpLow";

// プレイリスト入力設定ダイアログを表示する /* RockDance 126 */
static	char	*sKeyShowLoadPlaylistDlg = "ShowLoadPlaylistDlg";

// お気に入りのフォルダ /* RockDance 129 */
static	char	*sSectionFavorites			= "Favorites";

// 対象の拡張子
static	char	*sKeyValidAllFile	= "ValidAllFile"; /* Conspiracy 195 */



RECT		g_rectMainWindow;		// メインウィンドウの座標
BOOL		g_bMainFrameZoomed;
BOOL		g_bMainFrameIconic;
CString		g_strCurrentDirectory;
CString		g_strCurrentPlayList;
CString		g_strCurrentMoveDirectory;
bool		g_bIsVersionUp;
int			g_nUserConvFormatType;
USER_CONV_FORMAT	g_userConvFormat[USER_CONV_FORMAT_MAX];
USER_CONV_FORMAT_EX	g_userConvFormatEx[USER_CONV_FORMAT_EX_MAX];
USER_MOVE_FODLER_FORMAT	g_userMoveFolder[USER_MOVE_FODLER_FORMAT_MAX];
USER_COPY_FORMAT_FORMAT	g_userCopyFormat[USER_COPY_FORMAT_FORMAT_MAX]; /* FunnyCorn 175 */
WRITE_FORMAT		g_writeFormat[WRITE_FORMAT_MAX];
bool		g_bOptESCEditCancel;
bool		g_bOptEnableEditCursorExit;
bool		g_bOptEnterBeginEdit;
bool		g_bOptEditOkDown;
bool		g_bOptKeepTimeStamp;
bool		g_bOptChangeFileExt;
bool		g_bOptSyncCreateTime;
bool		g_bOptAutoConvRMP;
bool		g_bOptRmpID3tagAutoWrite;
bool		g_bOptRmpGenreListSelect;
bool		g_bOptAutoConvID3v2;
bool		g_bOptID3v2ID3tagAutoWrite;
bool		g_bOptID3v2ID3tagAutoDelete; /* FunnyCorn 173 */
bool		g_bOptID3v2GenreListSelect;
bool		g_bOptChangeTextFile;
int			g_nOptCheckFileName;
CString		g_sOptWinAmpPath;
int			g_nOptPlayerType;
bool		g_bOptEditFieldSIF;
bool		g_bOptAutoOpenFolder;
bool		g_bOptLoadFileChecked;
bool		g_bOptHideMP3ListFile;
bool		g_bOptDropSearchSubFolder; /* TyphoonSwell 026 */
bool		g_bOptShowZenSpace; /* BeachMonster 107 */
CString		g_sOptShowOtherChar; /* BeachMonster 107 */ // とりあえずいれとく
bool		g_bOptSortIgnoreCase; /* BeachMonster4 114 */
bool		g_bOptSortIgnoreZenHan; /* BeachMonster4 114 */
bool		g_bOptSortIgnoreKataHira; /* FunnyCorn 179 */
bool		g_bOptShowTotalParent; /* RockDance 128 */
bool		g_bOptShowTips; /* Rumble 188 */
int			g_nOptSIFieldConvType;
bool		g_bOptLoadFileAdjustColumn;
bool		g_bOptSearchLyricFile;
bool		g_bOptSetLyricsDir;
bool		g_bOptSearchLyricsSubDir;
bool		g_bEnableSearchSubDir;
bool		g_bEnableMoveFolderCopy;
CString		g_strOptLyricsPath;
SORT_STATE	g_sortState[SORT_KEY_MAX];
CLASS_INFO	g_classInfo;
CHECK_WORD_STATE	g_chkWord[CHECK_STATE_MAX];

bool		g_bOptID3v2GenreAddNumber;
bool		g_bConfFileNameMaxCheck;
bool		g_bFileNameMaxCellColor; /* SeaKnows 036 */
int			g_nConfFileNameMaxChar;

bool		g_bEnableFolderSync;
CString		g_strRootFolder;
bool		g_bSyncSelectAlways;
bool		g_bSyncDeleteFolder;
bool		g_bSyncLyricsFileMove;

bool		g_bConfConvMP3;
bool		g_bConfConvRMP;
bool		g_bConfConvID3v2;
bool		g_bConfDeleteFile;
bool		g_bConfDeleteList;
bool		g_bConfEditModify;
bool		g_bConfFolderSync;

bool		g_bPlayListClearList;
bool		g_bPlayListClearCheck;
bool		g_bPlayListAddList;
bool		g_bPlayListFileCheck;

CString		g_strTeikei[10+20];	/* SeaKnows 030 *//* FreeFall 046 */
CString		g_strTeikeiGroupName[3];	/* FreeFall 046 */
CString		g_strSoftwareTag;	/* SeaKnows 031 */
bool		g_bValidFolderSelect;	/* SeaKnows 033 */
bool		g_bValidDupExec;	/* FreeFall 045 */
bool		g_bId3v2OldComment;	/* FunnyCorn 180 */
bool		g_bId3v2UNICODE;	/* FunnyCorn 181 */

int			g_nRecentFolder; /* StartInaction 053 */
bool		g_bSaveRepDlgPos; /* WildCherry4 086 */
int			g_nSaveRepDlgPosX; /* WildCherry4 086 */
int			g_nSaveRepDlgPosY; /* WildCherry4 086 */

// 文字種統一 /* StartInaction 054 */
UINT		g_nUnifyAlpha;
UINT		g_nUnifyHiraKata;
UINT		g_nUnifyKata;
UINT		g_nUnifyKigou;
UINT		g_nUnifySuji;
UINT		g_nUnifyUpLow;

// ファイル名文字種統一 /* LastTrain 058 */
UINT		g_nFileUnifyAlpha;
UINT		g_nFileUnifyHiraKata;
UINT		g_nFileUnifyKata;
UINT		g_nFileUnifyKigou;
UINT		g_nFileUnifySuji;
UINT		g_nFileUnifyUpLow;

bool		g_bEndEditMoveRightCell; /* BeachMonster 091 */

bool		g_bShowLoadPlaylistDlg; /* RockDance 126 */

CString		g_strFavorite[10];	/* RockDance 129 */

int			g_nAddNumberWidth; /* Baja 159 */
int			g_nAddNumberPos; /* Baja 159 */
CString		g_strAddNumberSep; /* Baja 159 */
CString		g_strAddNumberBef; /* Conspiracy 194 */
CString		g_strAddNumberAft; /* Conspiracy 194 */

bool		g_bValidAllFile; /* Conspiracy 195 */

bool		g_bAudioListShow; /* Conspiracy 199 */

LOGFONT		g_fontReport;			// レポートウィンドウのフォント

FILENAME_REPLACE	g_fileNameReplace[FILENAME_REPLACE_MAX];

FILENAME_REPLACE	g_userFileNameReplace[USER_FILENAME_REPLACE_MAX];	/* FreeFall 050 */

struct	GENRE_LIST	{		// ジャンルリスト
	bool	bAddList;		// リストに追加するかどうか
	BYTE	byGenre;		// ジャンル番号
	char	*sName;			// ジャンル名(NULL:リスト終端)
};
struct	USER_GENRE_LIST	{	// ユーザジャンルリスト
	bool	bAddList;		// リストに追加するかどうか
	BYTE	byGenre;		// ジャンル番号
	CString	sName;			// ジャンル名
	bool	bUse;
};

GENRE_LIST	g_genreListSCMPX[] = {
	{true,   0, "Blues"},					// 0(ID3 Tag互換)
	{true,   1, "Classic Rock"},			// 1(ID3 Tag互換)
	{true,   2, "Country"},					// 2(ID3 Tag互換)
	{true,   3, "Dance"},					// 3(ID3 Tag互換)
	{true,   4, "Disco"},					// 4(ID3 Tag互換)
	{true,   5, "Funk"},					// 5(ID3 Tag互換)
	{true,   6, "Grunge"},					// 6(ID3 Tag互換)
	{true,   7, "Hip-Hop"},					// 7(ID3 Tag互換)
	{true,   8, "Jazz"},					// 8(ID3 Tag互換)
	{true,   9, "Metal"},					// 9(ID3 Tag互換)
	{true,  10, "New Age"},					// 10(ID3 Tag互換)
	{true,  11, "Oldies"},					// 11(ID3 Tag互換)
	{true,  12, "Other"},					// 12(ID3 Tag互換)
	{true,  13, "Pop"},						// 13(ID3 Tag互換)
	{true,  14, "R&B"},						// 14(ID3 Tag互換)
	{true,  15, "Rap"},						// 15(ID3 Tag互換)
	{true,  16, "Reggae"},					// 16(ID3 Tag互換)
	{true,  17, "Rock"},					// 17(ID3 Tag互換)
	{true,  18, "Techno"},					// 18(ID3 Tag互換)
	{true,  19, "Industrial"},				// 19(ID3 Tag互換)
	{true,  20, "Alternative"},				// 20(ID3 Tag互換)
	{true,  21, "Ska"},						// 21(ID3 Tag互換)
	{true,  22, "Death Metal"},				// 22(ID3 Tag互換)
	{true,  23, "Pranks"},					// 23(ID3 Tag互換)
	{true,  24, "Soundtrack"},				// 24(ID3 Tag互換)
	{true,  25, "Euro-Techno"},				// 25(ID3 Tag互換)
	{true,  26, "Ambient"},					// 26(ID3 Tag互換)
	{true,  27, "Trip-Hop"},				// 27(ID3 Tag互換)
	{true,  28, "Vocal"},					// 28(ID3 Tag互換)
	{true,  29, "Jazz+Funk"},				// 29(ID3 Tag互換)
	{true,  30, "Fusion"},					// 30(ID3 Tag互換)
	{true,  31, "Trance"},					// 31(ID3 Tag互換)
	{true,  32, "Classical"},				// 32(ID3 Tag互換)
	{true,  33, "Instrumental"},			// 33(ID3 Tag互換)
	{true,  34, "Acid"},					// 34(ID3 Tag互換)
	{true,  35, "House"},					// 35(ID3 Tag互換)
	{true,  36, "Game"},					// 36(ID3 Tag互換)
	{true,  37, "Sound Clip"},				// 37(ID3 Tag互換)
	{true,  38, "Gospel"},					// 38(ID3 Tag互換)
	{true,  39, "Noise"},					// 39(ID3 Tag互換)
	{true,  40, "AlternRock"},				// 40(ID3 Tag互換)
	{true,  41, "Bass"},					// 41(ID3 Tag互換)
	{true,  42, "Soul"},					// 42(ID3 Tag互換)
	{true,  43, "Punk"},					// 43(ID3 Tag互換)
	{true,  44, "Space"},					// 44(ID3 Tag互換)
	{true,  45, "Meditative"},				// 45(ID3 Tag互換)
	{true,  46, "Instrumental Pop"},		// 46(ID3 Tag互換)
	{true,  47, "Instrumental Rock"},		// 47(ID3 Tag互換)
	{true,  48, "Ethnic"},					// 48(ID3 Tag互換)
	{true,  49, "Gothic"},					// 49(ID3 Tag互換)
	{true,  50, "Darkwave"},				// 50(ID3 Tag互換)
	{true,  51, "Techno-Industrial"},		// 51(ID3 Tag互換)
	{true,  52, "Electronic"},				// 52(ID3 Tag互換)
	{true,  53, "Pop-Folk"},				// 53(ID3 Tag互換)
	{true,  54, "Eurodance"},				// 54(ID3 Tag互換)
	{true,  55, "Dream"},					// 55(ID3 Tag互換)
	{true,  56, "Southern Rock"},			// 56(ID3 Tag互換)
	{true,  57, "Comedy"},					// 57(ID3 Tag互換)
	{true,  58, "Cult"},					// 58(ID3 Tag互換)
	{true,  59, "Gangsta"},					// 59(ID3 Tag互換)
	{true,  60, "Top 40"},					// 60(ID3 Tag互換)
	{true,  61, "Christian Rap"},			// 61(ID3 Tag互換)
	{true,  62, "Pop/Funk"},				// 62(ID3 Tag互換)
	{true,  63, "Jungle"},					// 63(ID3 Tag互換)
	{true,  64, "Native American"},			// 64(ID3 Tag互換)
	{true,  65, "Cabaret"},					// 65(ID3 Tag互換)
	{true,  66, "New Wave"},				// 66(ID3 Tag互換)
	{true,  67, "Psychedelic"},				// 67(ID3 Tag互換)
	{true,  68, "Rave"},					// 68(ID3 Tag互換)
	{true,  69, "Showtunes"},				// 69(ID3 Tag互換)
	{true,  70, "Trailer"},					// 70(ID3 Tag互換)
	{true,  71, "Lo-Fi"},					// 71(ID3 Tag互換)
	{true,  72, "Tribal"},					// 72(ID3 Tag互換)
	{true,  73, "Acid Punk"},				// 73(ID3 Tag互換)
	{true,  74, "Acid Jazz"},				// 74(ID3 Tag互換)
	{true,  75, "Polka"},					// 75(ID3 Tag互換)
	{true,  76, "Retro"},					// 76(ID3 Tag互換)
	{true,  77, "Musical"},					// 77(ID3 Tag互換)
	{true,  78, "Rock & Roll"},				// 78(ID3 Tag互換)
	{true,  79, "Hard Rock"},				// 79(ID3 Tag互換)
	{true,  80, "Folk"},					// 80(ID3 Tag互換)
	{true,  81, "Folk/Rock"},				// 81(ID3 Tag互換)
	{true,  82, "National Folk"},			// 82(ID3 Tag互換)
	{true,  83, "Swing"},					// 83(ID3 Tag互換)
	{true,  84, "Fast-Fusion"},				// 84(Winamp互換)
	{true,  85, "Bebob"},					// 85(Winamp互換)
	{true,  86, "Latin"},					// 86(Winamp互換)
	{true,  87, "Revival"},					// 87(Winamp互換)
	{true,  88, "Celtic"},					// 88(Winamp互換)
	{true,  89, "Bluegrass"},				// 89(Winamp互換)
	{true,  90, "Avantgarde"},				// 90(Winamp互換)
	{true,  91, "Gothic Rock"},				// 91(Winamp互換)
	{true,  92, "Progressive Rock"},		// 92(Winamp互換)
	{true,  93, "Psychedelic Rock"},		// 93(Winamp互換)
	{true,  94, "Symphonic Rock"},			// 94(Winamp互換)
	{true,  95, "Slow Rock"},				// 95(Winamp互換)
	{true,  96, "Big Band"},				// 96(Winamp互換)
	{true,  97, "Chorus"},					// 97(Winamp互換)
	{true,  98, "Easy Listening"},			// 98(Winamp互換)
	{true,  99, "Acoustic"},				// 99(Winamp互換)
	{true, 100, "Humour"},					// 100(Winamp互換)
	{true, 101, "Speech"},					// 101(Winamp互換)
	{true, 102, "Chanson"},					// 102(Winamp互換)
	{true, 103, "Opera"},					// 103(Winamp互換)
	{true, 104, "Chamber Music"},			// 104(Winamp互換)
	{true, 105, "Sonata"},					// 105(Winamp互換)
	{true, 106, "Symphony"},				// 106(Winamp互換)
	{true, 107, "Booty Bass"},				// 107(Winamp互換)
	{true, 108, "Primus"},					// 108(Winamp互換)
	{true, 109, "Porn Groove"},				// 109(Winamp互換)
	{true, 110, "Satire"},					// 110(Winamp互換)
	{true, 111, "Slow Jam"},				// 111(Winamp互換)
	{true, 112, "Club"},					// 112(Winamp互換)
	{true, 113, "Tango"},					// 113(Winamp互換)
	{true, 114, "Samba"},					// 114(Winamp互換)
	{true, 115, "Folklore"},				// 115(Winamp互換)
	{true, 116, "Ballad"},					// 116(Winamp互換)
	{true, 117, "Power Ballad"},			// 117(Winamp互換)
	{true, 118, "Phythmic Soul"},			// 118(Winamp互換)
	{true, 119, "Freestyle"},				// 119(Winamp互換)
	{true, 120, "Duet"},					// 120(Winamp互換)
	{true, 121, "Punk Rock"},				// 121(Winamp互換)
	{true, 122, "Drum Solo"},				// 122(Winamp互換)
	{true, 123, "A Cappella"},				// 123(Winamp互換)
	{true, 124, "Euro-House"},				// 124(Winamp互換)
	{true, 125, "Dance Hall"},				// 125(Winamp互換)
	{true, 126, "Goa"},						// 126(Winamp互換)
	{true, 127, "Drum & Bass"},				// 127(Winamp互換)
	{true, 128, "Club-House"},				// 128(Winamp互換)
	{true, 129, "Hardcore"},				// 129(Winamp互換)
	{true, 130, "Terror"},					// 130(Winamp互換)
	{true, 131, "Indie"},					// 131(Winamp互換)
	{true, 132, "BritPop"},					// 132(Winamp互換)
	{true, 133, "Negerpunk"},				// 133(Winamp互換)
	{true, 134, "Polsk Punk"},				// 134(Winamp互換)
	{true, 135, "Beat"},					// 135(Winamp互換)
	{true, 136, "Christian Gangsta Rap"},	// 136(Winamp互換)
	{true, 137, "Heavy Metal"},				// 137(Winamp互換)
	{true, 138, "Black Metal"},				// 138(Winamp互換)
	{true, 139, "Crossover"},				// 139(Winamp互換)
	{true, 140, "Contemporary Christian"},	// 140(Winamp互換)
	{true, 141, "Christian Rock"},			// 141(Winamp互換)
	{true, 142, "Merengue"},				// 142(Winamp互換)
	{true, 143, "Salsa"},					// 143(Winamp互換)
	{true, 144, "Thrash Metal"},			// 144(Winamp互換)
	{true, 145, "Anime"},					// 145(Winamp互換)
	{true, 146, "JPop"},					// 146(Winamp互換)
	{true, 147, "Synthpop"},				// 147(Winamp互換)
	{false, 148, "未定義(148)"},			// 148
	{false, 148, "未定義(148)"},			// 148
	{false, 149, "未定義(149)"},			// 149
	{false, 150, "未定義(150)"},			// 150
	{false, 151, "未定義(151)"},			// 151
	{false, 152, "未定義(152)"},			// 152
	{false, 153, "未定義(153)"},			// 153
	{false, 154, "未定義(154)"},			// 154
	{false, 155, "未定義(155)"},			// 155
	{false, 156, "未定義(156)"},			// 156
	{false, 157, "未定義(157)"},			// 157
	{false, 158, "未定義(158)"},			// 158
	{false, 159, "未定義(159)"},			// 159
	{false, 160, "未定義(160)"},			// 160
	{false, 161, "未定義(161)"},			// 161
	{false, 162, "未定義(162)"},			// 162
	{false, 163, "未定義(163)"},			// 163
	{false, 164, "未定義(164)"},			// 164
	{false, 165, "未定義(165)"},			// 165
	{false, 166, "未定義(166)"},			// 166
	{false, 167, "未定義(167)"},			// 167
	{false, 168, "未定義(168)"},			// 168
	{false, 169, "未定義(169)"},			// 169
	{false, 170, "未定義(170)"},			// 170
	{false, 171, "未定義(171)"},			// 171
	{false, 172, "未定義(172)"},			// 172
	{false, 173, "未定義(173)"},			// 173
	{false, 174, "未定義(174)"},			// 174
	{false, 175, "未定義(175)"},			// 175
	{false, 176, "未定義(176)"},			// 176
	{false, 177, "未定義(177)"},			// 177
	{false, 178, "未定義(178)"},			// 178
	{false, 179, "未定義(179)"},			// 179
	{false, 180, "未定義(180)"},			// 180
	{false, 181, "未定義(181)"},			// 181
	{false, 182, "未定義(182)"},			// 182
	{false, 183, "未定義(183)"},			// 183
	{false, 184, "未定義(184)"},			// 184
	{false, 185, "未定義(185)"},			// 185
	{false, 186, "未定義(186)"},			// 186
	{false, 187, "未定義(187)"},			// 187
	{false, 188, "未定義(188)"},			// 188
	{false, 189, "未定義(189)"},			// 189
	{false, 190, "未定義(190)"},			// 190
	{false, 191, "未定義(191)"},			// 191
	{false, 192, "未定義(192)"},			// 192
	{false, 193, "未定義(193)"},			// 193
	{false, 194, "未定義(194)"},			// 194
	{false, 195, "未定義(195)"},			// 195
	{false, 196, "未定義(196)"},			// 196
	{false, 197, "未定義(197)"},			// 197
	{false, 198, "未定義(198)"},			// 198
	{false, 199, "未定義(199)"},			// 199
	{false, 200, "未定義(200)"},			// 200
	{false, 201, "未定義(201)"},			// 201
	{false, 202, "未定義(202)"},			// 202
	{false, 203, "未定義(203)"},			// 203
	{false, 204, "未定義(204)"},			// 204
	{false, 205, "未定義(205)"},			// 205
	{false, 206, "未定義(206)"},			// 206
	{false, 207, "未定義(207)"},			// 207
	{false, 208, "未定義(208)"},			// 208
	{false, 209, "未定義(209)"},			// 209
	{false, 210, "未定義(210)"},			// 210
	{false, 211, "未定義(211)"},			// 211
	{false, 212, "未定義(212)"},			// 212
	{false, 213, "未定義(213)"},			// 213
	{false, 214, "未定義(214)"},			// 214
	{false, 215, "未定義(215)"},			// 215
	{false, 216, "未定義(216)"},			// 216
	{false, 217, "未定義(217)"},			// 217
	{false, 218, "未定義(218)"},			// 218
	{false, 219, "未定義(219)"},			// 219
	{false, 220, "未定義(220)"},			// 220
	{false, 221, "未定義(221)"},			// 221
	{false, 222, "未定義(222)"},			// 222
	{false, 223, "未定義(223)"},			// 223
	{false, 224, "未定義(224)"},			// 224
	{false, 225, "未定義(225)"},			// 225
	{false, 226, "未定義(226)"},			// 226
	{false, 227, "未定義(227)"},			// 227
	{false, 228, "未定義(228)"},			// 228
	{false, 229, "未定義(229)"},			// 229
	{false, 230, "未定義(230)"},			// 230
	{false, 231, "未定義(231)"},			// 231
	{false, 232, "未定義(232)"},			// 232
	{false, 233, "未定義(233)"},			// 233
	{false, 234, "未定義(234)"},			// 234
	{false, 235, "未定義(235)"},			// 235
	{false, 236, "未定義(236)"},			// 236
	{false, 237, "未定義(237)"},			// 237
	{false, 238, "未定義(238)"},			// 238
	{false, 239, "未定義(239)"},			// 239
	{false, 240, "未定義(240)"},			// 240
	{false, 241, "未定義(241)"},			// 241
	{false, 242, "未定義(242)"},			// 242
	{false, 243, "未定義(243)"},			// 243
	{false, 244, "未定義(244)"},			// 244
	{false, 245, "未定義(245)"},			// 245
	{false, 246, "未定義(246)"},			// 246
	{false, 247, "未定義(247)"},			// 247
	{false, 248, "Heavy Rock(J)"},			// 248(SCMPX互換)
	{false, 249, "Doom Rock(J)"},			// 249(SCMPX互換)
	{false, 250, "J-POP(J)"},				// 250(SCMPX互換)
	{false, 251, "Seiyu(J)"},				// 251(SCMPX互換)
	{false, 252, "Tecno Ambient(J)"},		// 252(SCMPX互換)
	{false, 253, "Moemoe(J)"},				// 253(SCMPX互換)
	{false, 254, "Tokusatsu(J)"},			// 254(SCMPX互換)
	{false, 255, "Anime(J)/未指定"},		// 255(SCMPX互換)
	{false, 255, NULL},						// 終端コード
};
USER_GENRE_LIST*	g_genreListUSER = NULL;

#define HK_CTRL_C				0x00020043
#define HK_CTRL_D				0x00020044
#define HK_CTRL_F				0x00020046
#define HK_CTRL_H				0x00020048
#define HK_CTRL_N				0x0002004e
#define HK_CTRL_O				0x0002004f
#define HK_CTRL_S				0x00020053
#define HK_CTRL_V				0x00020056
#define HK_CTRL_X				0x00020058

KEY_CONFIG	g_listKeyConfig[] = {
	// ファイル処理
	{ID_FILE_NEW                  , 0x00000000, COMMAND_GROUP_FILE, "リストをクリア", "FileNew"},
	{ID_OPEN_FOLDER               , HK_CTRL_O , COMMAND_GROUP_FILE, "フォルダを開く", "FileOpenFolder"},
	{ID_SAVE_ALL_TAG              , HK_CTRL_S , COMMAND_GROUP_FILE, "タグ情報を更新", "FileSaveAllTag"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_FILE, "--------------------", NULL},
	{ID_WRITE_LIST1               , 0x00000000, COMMAND_GROUP_FILE, "リスト出力：書式１", "WriteList1"},
	{ID_WRITE_LIST2               , 0x00000000, COMMAND_GROUP_FILE, "リスト出力：書式２", "WriteList2"},
	{ID_WRITE_LIST3               , 0x00000000, COMMAND_GROUP_FILE, "リスト出力：書式３", "WriteList3"},
	{ID_WRITE_LIST4               , 0x00000000, COMMAND_GROUP_FILE, "リスト出力：書式４", "WriteList4"},
	{ID_WRITE_LIST5               , 0x00000000, COMMAND_GROUP_FILE, "リスト出力：書式５", "WriteList5"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_FILE, "--------------------", NULL},
	{ID_MOVE_FOLDER_01            , 0x00000000, COMMAND_GROUP_FILE, "ファイル移動：書式１", "MoveFolder1"},
	{ID_MOVE_FOLDER_02            , 0x00000000, COMMAND_GROUP_FILE, "ファイル移動：書式２", "MoveFolder2"},
	{ID_MOVE_FOLDER_03            , 0x00000000, COMMAND_GROUP_FILE, "ファイル移動：書式３", "MoveFolder3"},
	{ID_MOVE_FOLDER_04            , 0x00000000, COMMAND_GROUP_FILE, "ファイル移動：書式４", "MoveFolder4"},
	{ID_MOVE_FOLDER_05            , 0x00000000, COMMAND_GROUP_FILE, "ファイル移動：書式５", "MoveFolder5"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_FILE, "--------------------", NULL},
	{ID_FAVORITE_FOLDER_01        , 0x00000000, COMMAND_GROUP_FILE, "お気に入りのフォルダ：お気に入り１", "FavoriteFolder1"},
	{ID_FAVORITE_FOLDER_02        , 0x00000000, COMMAND_GROUP_FILE, "お気に入りのフォルダ：お気に入り２", "FavoriteFolder2"},
	{ID_FAVORITE_FOLDER_03        , 0x00000000, COMMAND_GROUP_FILE, "お気に入りのフォルダ：お気に入り３", "FavoriteFolder3"},
	{ID_FAVORITE_FOLDER_04        , 0x00000000, COMMAND_GROUP_FILE, "お気に入りのフォルダ：お気に入り４", "FavoriteFolder4"},
	{ID_FAVORITE_FOLDER_05        , 0x00000000, COMMAND_GROUP_FILE, "お気に入りのフォルダ：お気に入り５", "FavoriteFolder5"},
	{ID_FAVORITE_FOLDER_06        , 0x00000000, COMMAND_GROUP_FILE, "お気に入りのフォルダ：お気に入り６", "FavoriteFolder6"},
	{ID_FAVORITE_FOLDER_07        , 0x00000000, COMMAND_GROUP_FILE, "お気に入りのフォルダ：お気に入り７", "FavoriteFolder7"},
	{ID_FAVORITE_FOLDER_08        , 0x00000000, COMMAND_GROUP_FILE, "お気に入りのフォルダ：お気に入り８", "FavoriteFolder8"},
	{ID_FAVORITE_FOLDER_09        , 0x00000000, COMMAND_GROUP_FILE, "お気に入りのフォルダ：お気に入り９", "FavoriteFolder9"},
	{ID_FAVORITE_FOLDER_10        , 0x00000000, COMMAND_GROUP_FILE, "お気に入りのフォルダ：お気に入り10", "FavoriteFolder10"},

	// 編集処理
	{ID_EDIT_COPY                 , HK_CTRL_C , COMMAND_GROUP_EDIT, "コピー"  , "EditCopy"},
	{ID_EDIT_PASTE                , HK_CTRL_V , COMMAND_GROUP_EDIT, "貼り付け", "EditPaste"},
	{ID_EDIT_CUT                  , HK_CTRL_X , COMMAND_GROUP_EDIT, "切り取り", "EditCut"},
	{ID_EDIT_PASTE_ADD            , 0x00000000, COMMAND_GROUP_EDIT, "追加で貼り付け", "EditPasteAdd"}, /* FunnyCorn 176 */
	{0x0000                       , 0x00000000, COMMAND_GROUP_EDIT, "----- 定型文 グループ１ -----", NULL},
	{ID_TEIKEI_01                 , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け１-１", "TeikeiPaste1-1"}, /* SeaKnows 030 */
	{ID_TEIKEI_02                 , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け１-２", "TeikeiPaste1-2"}, /* SeaKnows 030 */
	{ID_TEIKEI_03                 , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け１-３", "TeikeiPaste1-3"}, /* SeaKnows 030 */
	{ID_TEIKEI_04                 , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け１-４", "TeikeiPaste1-4"}, /* SeaKnows 030 */
	{ID_TEIKEI_05                 , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け１-５", "TeikeiPaste1-5"}, /* SeaKnows 030 */
	{ID_TEIKEI_06                 , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け１-６", "TeikeiPaste1-6"}, /* SeaKnows 030 */
	{ID_TEIKEI_07                 , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け１-７", "TeikeiPaste1-7"}, /* SeaKnows 030 */
	{ID_TEIKEI_08                 , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け１-８", "TeikeiPaste1-8"}, /* SeaKnows 030 */
	{ID_TEIKEI_09                 , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け１-９", "TeikeiPaste1-9"}, /* SeaKnows 030 */
	{ID_TEIKEI_10                 , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け１-１０", "TeikeiPaste1-10"}, /* SeaKnows 030 */
	{0x0000                       , 0x00000000, COMMAND_GROUP_EDIT, "----- 定型文 グループ２ -----", NULL},
	{ID_TEIKEI_2_01               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け２-１", "TeikeiPaste2-1"}, /* FreeFall 046 */
	{ID_TEIKEI_2_02               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け２-２", "TeikeiPaste2-2"}, /* FreeFall 046 */
	{ID_TEIKEI_2_03               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け２-３", "TeikeiPaste2-3"}, /* FreeFall 046 */
	{ID_TEIKEI_2_04               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け２-４", "TeikeiPaste2-4"}, /* FreeFall 046 */
	{ID_TEIKEI_2_05               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け２-５", "TeikeiPaste2-5"}, /* FreeFall 046 */
	{ID_TEIKEI_2_06               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け２-６", "TeikeiPaste2-6"}, /* FreeFall 046 */
	{ID_TEIKEI_2_07               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け２-７", "TeikeiPaste2-7"}, /* FreeFall 046 */
	{ID_TEIKEI_2_08               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け２-８", "TeikeiPaste2-8"}, /* FreeFall 046 */
	{ID_TEIKEI_2_09               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け２-９", "TeikeiPaste2-9"}, /* FreeFall 046 */
	{ID_TEIKEI_2_10               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け２-１０", "TeikeiPaste2-10"}, /* FreeFall 046 */
	{0x0000                       , 0x00000000, COMMAND_GROUP_EDIT, "----- 定型文 グループ３ -----", NULL},
	{ID_TEIKEI_3_01               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け３-１", "TeikeiPaste3-1"}, /* FreeFall 046 */
	{ID_TEIKEI_3_02               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け３-２", "TeikeiPaste3-2"}, /* FreeFall 046 */
	{ID_TEIKEI_3_03               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け３-３", "TeikeiPaste3-3"}, /* FreeFall 046 */
	{ID_TEIKEI_3_04               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け３-４", "TeikeiPaste3-4"}, /* FreeFall 046 */
	{ID_TEIKEI_3_05               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け３-５", "TeikeiPaste3-5"}, /* FreeFall 046 */
	{ID_TEIKEI_3_06               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け３-６", "TeikeiPaste3-6"}, /* FreeFall 046 */
	{ID_TEIKEI_3_07               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け３-７", "TeikeiPaste3-7"}, /* FreeFall 046 */
	{ID_TEIKEI_3_08               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け３-８", "TeikeiPaste3-8"}, /* FreeFall 046 */
	{ID_TEIKEI_3_09               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け３-９", "TeikeiPaste3-9"}, /* FreeFall 046 */
	{ID_TEIKEI_3_10               , 0x00000000, COMMAND_GROUP_EDIT, "定型文貼り付け３-１０", "TeikeiPaste3-10"}, /* FreeFall 046 */
	{0x0000                       , 0x00000000, COMMAND_GROUP_FILE, "--------------------", NULL},
	{ID_EDIT_COPY_FORMAT_01       , 0x00000000, COMMAND_GROUP_FILE, "書式コピー：書式１", "CopyFormat1"},
	{ID_EDIT_COPY_FORMAT_02       , 0x00000000, COMMAND_GROUP_FILE, "書式コピー：書式２", "CopyFormat2"},
	{ID_EDIT_COPY_FORMAT_03       , 0x00000000, COMMAND_GROUP_FILE, "書式コピー：書式３", "CopyFormat3"},
	{ID_EDIT_COPY_FORMAT_04       , 0x00000000, COMMAND_GROUP_FILE, "書式コピー：書式４", "CopyFormat4"},
	{ID_EDIT_COPY_FORMAT_05       , 0x00000000, COMMAND_GROUP_FILE, "書式コピー：書式５", "CopyFormat5"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_EDIT, "--------------------", NULL},
	{ID_CELL_COPY_DOWN            , HK_CTRL_D , COMMAND_GROUP_EDIT, "下方向へコピー", "EditCopyDown"},
	{ID_SET_NUMBER                , HK_CTRL_N , COMMAND_GROUP_EDIT, "下方向へ連番"  , "EditSetNumber"},
	{ID_SET_NUMBER_ADD            , 0x00000000, COMMAND_GROUP_EDIT, "下方向へ連番（先頭に追加）"  , "EditSetNumberAdd"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_EDIT, "--------------------", NULL},
	{ID_EDIT_FIND                 , 0x00000000, COMMAND_GROUP_EDIT, "検索", "EditFind"},
	{ID_EDIT_REPLACE              , 0x00000000, COMMAND_GROUP_EDIT, "置換", "EditReplace"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_EDIT, "--------------------", NULL},
	{ID_SELECT_DELETE_LIST        , 0x00000000, COMMAND_GROUP_EDIT, "STEのリストから削除"         , "DeleteList"},
	{ID_SELECT_DELETE_FILE        , 0x00000000, COMMAND_GROUP_EDIT, "ファイルの削除"              , "DeleteFile"},
	{ID_DELETE_TAG                , 0x00000000, COMMAND_GROUP_EDIT, "ID3tagの削除"                , "DeleteTag"},
	{ID_SELECT_EDIT_DESTORY       , 0x00000000, COMMAND_GROUP_EDIT, "変更前の状態に戻す"          , "EditModify"},
	{ID_FOLDER_TREE_SYNC          , 0x00000000, COMMAND_GROUP_EDIT, "フォルダ構成の同期"          , "FolderSync"},
	{ID_CHECK_FILE_SYNC           , 0x00000000, COMMAND_GROUP_EDIT, "フォルダ構成の同期(チェックのみ)", "CheckFileSync"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_EDIT, "--------------------", NULL},
	{ID_DELETE_CHAR_SPACE         , 0x00000000, COMMAND_GROUP_EDIT, "先頭/末尾の空白文字を削除"   , "EditDeleteCharSpace"}, /* Rumble 192 */
	{ID_DELETE_CHAR               , 0x00000000, COMMAND_GROUP_EDIT, "先頭/末尾のｎ文字を削除"     , "EditDeleteChar"},

	// 表示
	{ID_ADJUST_COLUMN_WIDTH       , 0x00000000, COMMAND_GROUP_DISP, "全てのカラム幅を調整", "AdjustColumnWidth"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_DISP, "--------------------", NULL},
	{ID_SORT_LIST                 , 0x00000000, COMMAND_GROUP_DISP, "並び替え"        , "ListSort"},
	{ID_SORT_LIST_DIRECT          , 0x00000000, COMMAND_GROUP_DISP, "並び替えを再実行", "ListSortDirect"},
	{ID_EXEC_CLASSIFICATION       , 0x00000000, COMMAND_GROUP_DISP, "分類表示を更新"  , "ExecClassification"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_DISP, "--------------------", NULL},
	{ID_EDIT_FIELD_SI             , 0x00000000, COMMAND_GROUP_DISP, "SIフィールドを表示/編集"       , "EditFieldSI"},
	{ID_EDIT_TD3_TAG              , 0x00000000, COMMAND_GROUP_DISP, "ID3 tag を表示/編集"           , "EditID3tag"},
	{ID_EDIT_CHANGE_FIELD         , 0x00000000, COMMAND_GROUP_DISP, "[ID3 tag]<=>[SIフィールド]切替", "EditChangeField"},

	// プレイリスト
	{ID_LOAD_PLAYLIST             , 0x00000000, COMMAND_GROUP_PLAYLIST, "プレイリストの読み込み"      , "LoadPlayList"},
	{ID_WRITE_PLAYLIST            , 0x00000000, COMMAND_GROUP_PLAYLIST, "プレイリストの出力"          , "WritePlayList"},
	{ID_WRITE_TREE_PLAYLIST       , 0x00000000, COMMAND_GROUP_PLAYLIST, "ツリー分類のプレイリスト出力", "WriteTreePlayList"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_PLAYLIST, "--------------------", NULL},
	{ID_ALL_FILES_CHECK           , 0x00000000, COMMAND_GROUP_PLAYLIST, "全てのファイルをチェックする"  , "AllFilesCheck"},
	{ID_ALL_FILES_UNCHECK         , 0x00000000, COMMAND_GROUP_PLAYLIST, "全てのファイルのチェックを外す", "AllFilesUnCheck"},
	{ID_REVERSE_CHECK             , 0x00000000, COMMAND_GROUP_PLAYLIST, "チェック状態を反転する"        , "ReverseCheck"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_PLAYLIST, "--------------------", NULL},
	{ID_CHECK_FILES_SELECT        , 0x00000000, COMMAND_GROUP_PLAYLIST, "チェックファイルを選択"      , "CheckFilesSelect"},
	{ID_SELECT_FILES_CHECK        , 0x00000000, COMMAND_GROUP_PLAYLIST, "選択ファイルをチェック"      , "SelectFilesCheck"},
	{ID_SELECT_FILES_UNCHECK      , 0x00000000, COMMAND_GROUP_PLAYLIST, "選択ファイルのチェックを外す", "SelectFilesUnCheck"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_PLAYLIST, "--------------------", NULL},
	{ID_CHECK_WORD                , 0x00000000, COMMAND_GROUP_PLAYLIST, "条件を指定してチェック"      , "CheckWord"},
	{ID_CHECK_FILENAME_MAX        , 0x00000000, COMMAND_GROUP_PLAYLIST, "ファイル名の長さをチェック"  , "CheckFileNameMax"}, /* SeaKnows 037 */
	{0x0000                       , 0x00000000, COMMAND_GROUP_PLAYLIST, "--------------------", NULL},
	{ID_SELECT_TREE_COLUM         , 0x00000000, COMMAND_GROUP_PLAYLIST, "ツリー配下のカラム一括選択"  , "SelectTreeColumn"}, /* TyphoonSwell 025 */

	// WinAmp 制御処理
	{ID_WINAMP_PLAY               , 0x00000000, COMMAND_GROUP_PLAYER, "再生"                  , "WinampPlay"},
	{ID_WINAMP_STOP               , 0x00000000, COMMAND_GROUP_PLAYER, "停止(Winampのみ有効)"  , "WinampStop"},
	{ID_WINAMP_EXIT               , 0x00000000, COMMAND_GROUP_PLAYER, "終了"                  , "WinampExit"},
	{ID_WINAMP_PLAY_PREV          , 0x00000000, COMMAND_GROUP_PLAYER, "前の曲(Winampのみ有効)", "WinampPlayPrev"},
	{ID_WINAMP_PLAY_NEXT          , 0x00000000, COMMAND_GROUP_PLAYER, "次の曲(Winampのみ有効)", "WinampPlayNext"},

	// 変換処理
	{0x0000                       , 0x00000000, COMMAND_GROUP_CONV, "----- デフォルト書式変換 -----", NULL},
	{ID_CONV_FILENAME_TO_TRACKNAME, 0x00000000, COMMAND_GROUP_CONV, "ファイル名 => トラック名", "ConvFileNameToTrackName"},
	{ID_CONV_TRACKNAME_TO_FILENAME, 0x00000000, COMMAND_GROUP_CONV, "トラック名 => ファイル名", "ConvTrackNameToFileName"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_CONV, "----- ユーザー指定書式変換 -----", NULL},
	{ID_CONV_TAG2FILE_USER        , 0x00000000, COMMAND_GROUP_CONV, "タグ情報 => ファイル名", "ConvUserTagToFile"},
	{ID_CONV_FILE2TAG_USER        , 0x00000000, COMMAND_GROUP_CONV, "ファイル名 => タグ情報", "ConvUserFileToTag"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_CONV, "------ 文字変換 -----", NULL},
	{ID_CONV_STR_HAN_ALL          , 0x00000000, COMMAND_GROUP_CONV, "全角=>半角(全て)変換"          , "ConvHanAll"},
	{ID_CONV_STR_HAN_KIGOU        , 0x00000000, COMMAND_GROUP_CONV, "全角=>半角(記号)変換"          , "ConvHanKigou"},
	{ID_CONV_STR_HAN_SUJI         , 0x00000000, COMMAND_GROUP_CONV, "全角=>半角(数字)変換"          , "ConvHanSuji"},
	{ID_CONV_STR_HAN_KATA         , 0x00000000, COMMAND_GROUP_CONV, "全角=>半角(カタカナ)変換"      , "ConvHanLata"},
	{ID_CONV_STR_HAN_ALPHA        , 0x00000000, COMMAND_GROUP_CONV, "全角=>半角(アルファベット)変換", "ConvHanAlpha"},
	{ID_CONV_STR_ZEN_ALL          , 0x00000000, COMMAND_GROUP_CONV, "半角=>全角(全て)変換"          , "ConvZenAll"},
	{ID_CONV_STR_ZEN_KIGOU        , 0x00000000, COMMAND_GROUP_CONV, "半角=>全角(記号)変換"          , "ConvZenKigou"},
	{ID_CONV_STR_ZEN_SUJI         , 0x00000000, COMMAND_GROUP_CONV, "半角=>全角(数字)変換"          , "ConvZenSuji"},
	{ID_CONV_STR_ZEN_KATA         , 0x00000000, COMMAND_GROUP_CONV, "半角=>全角(カタカナ)変換"      , "ConvZenKata"},
	{ID_CONV_STR_ZEN_ALPHA        , 0x00000000, COMMAND_GROUP_CONV, "半角=>全角(アルファベット)変換", "ConvZenAlpha"},
	{ID_CONV_STR_TO_UPPER         , 0x00000000, COMMAND_GROUP_CONV, "小文字=>大文字変換"            , "ConvToUpper"},
	{ID_CONV_STR_TO_LOWER         , 0x00000000, COMMAND_GROUP_CONV, "大文字=>小文字変換"            , "ConvToLower"},
	{ID_CONV_STR_FIRST_UPPER      , 0x00000000, COMMAND_GROUP_CONV, "単語の１文字目のみ大文字"      , "ConvFirstUpper"},
	{ID_CONV_STR_HIRA2KATA        , 0x00000000, COMMAND_GROUP_CONV, "ひらがな=>カタカナ変換"        , "ConvHira2Kata"},
	{ID_CONV_STR_KATA2HIRA        , 0x00000000, COMMAND_GROUP_CONV, "カタカナ=>ひらがな変換"        , "ConvKata2Hira"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_CONV, "----- ファイル形式変換 -----", NULL},
	{ID_FILE_CONV_MP3             , 0x00000000, COMMAND_GROUP_CONV, "標準 MP3 に変換", "ConvFileMP3"},
	{ID_FILE_CONV_RMP             , 0x00000000, COMMAND_GROUP_CONV, "RIFF MP3 に変換", "ConvFileRMP"},
	{ID_FILE_CONV_ID3V2           , 0x00000000, COMMAND_GROUP_CONV, "ID3v2 に変換", "ConvFileID3v2"},
	{ID_FILE_CONV_AUTO_ID3        , 0x00000000, COMMAND_GROUP_CONV, "標準MP3形式/ID3v2 形式に自動変換", "AutoConvFileID3"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_CONV, "----- その他の変換 -----", NULL},
	{ID_CONV_SI_FIELD_TO_ID3TAG   , 0x00000000, COMMAND_GROUP_CONV, "SIフィールドからID3tagに変換", "ConvSIFieldToID3Tag"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_CONV, "----- 拡張書式変換 -----", NULL},
	{ID_CONV_FORMAT_EX_01         , 0x00000000, COMMAND_GROUP_CONV, "書式１", "ConvFormatEx01"},
	{ID_CONV_FORMAT_EX_02         , 0x00000000, COMMAND_GROUP_CONV, "書式２", "ConvFormatEx02"},
	{ID_CONV_FORMAT_EX_03         , 0x00000000, COMMAND_GROUP_CONV, "書式３", "ConvFormatEx03"},
	{ID_CONV_FORMAT_EX_04         , 0x00000000, COMMAND_GROUP_CONV, "書式４", "ConvFormatEx04"},
	{ID_CONV_FORMAT_EX_05         , 0x00000000, COMMAND_GROUP_CONV, "書式５", "ConvFormatEx05"},
	{ID_CONV_FORMAT_EX_06         , 0x00000000, COMMAND_GROUP_CONV, "書式６", "ConvFormatEx06"},
	{ID_CONV_FORMAT_EX_07         , 0x00000000, COMMAND_GROUP_CONV, "書式７", "ConvFormatEx07"},
	{ID_CONV_FORMAT_EX_08         , 0x00000000, COMMAND_GROUP_CONV, "書式８", "ConvFormatEx08"},
	{ID_CONV_FORMAT_EX_09         , 0x00000000, COMMAND_GROUP_CONV, "書式９", "ConvFormatEx09"},
	{ID_CONV_FORMAT_EX_10         , 0x00000000, COMMAND_GROUP_CONV, "書式１０", "ConvFormatEx10"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_CONV, "----- ユーザー指定書式 -----", NULL},
	{ID_CONV_FORMAT_USER_01       , 0x00000000, COMMAND_GROUP_CONV, "書式１", "ConvFormatUser01"},
	{ID_CONV_FORMAT_USER_02       , 0x00000000, COMMAND_GROUP_CONV, "書式２", "ConvFormatUser02"},
	{ID_CONV_FORMAT_USER_03       , 0x00000000, COMMAND_GROUP_CONV, "書式３", "ConvFormatUser03"},
	{ID_CONV_FORMAT_USER_04       , 0x00000000, COMMAND_GROUP_CONV, "書式４", "ConvFormatUser04"}, /* LastTrain 057 */
	{ID_CONV_FORMAT_USER_05       , 0x00000000, COMMAND_GROUP_CONV, "書式５", "ConvFormatUser05"}, /* LastTrain 057 */

	{0x0000, 0x00000000, -1, NULL, NULL},		// 終端コード
};

struct	COLUMN_STATUS	{
	char	*sRegKey;		// レジストリーキー名
	BOOL	bShowFlag;		// 表示フラグ
	int		nNumber;		// 項目の順番
	int		nWidth;			// カラム幅
	int		nWidthMax;		// 最大カラム幅
	int		nFormat;		//
};

COLUMN_STATUS	g_columnStatus[COLUMN_MAX] = {
	{"TreeItem"  , TRUE ,  0, 128,   0, LVCFMT_LEFT },	// ツリーアイテム名(フルパス名)
	{"FileName"  , TRUE ,  1, 150,   0, LVCFMT_LEFT },	// ファイル名
	{"TrackName" , TRUE ,  2, 128,   0, LVCFMT_LEFT },	// 曲名
	{"ArtistName", TRUE ,  3, 128,   0, LVCFMT_LEFT },	// アーティスト名
	{"AlbumName" , TRUE ,  4, 128,   0, LVCFMT_LEFT },	// アルバム名／製品名
	{"TrackNo"   , TRUE ,  5,  48,  48, LVCFMT_RIGHT},	// トラック番号(ID3 tag v1.1のみ)
	{"Year"      , TRUE ,  6,  48,  48, LVCFMT_LEFT },	// リリース年号
	{"Genre"     , TRUE ,  7, 128,   0, LVCFMT_LEFT },	// ジャンル
	{"Comment"   , TRUE ,  8, 128,   0, LVCFMT_LEFT },	// コメント文字列
	{"Copyright" , FALSE,  9, 128,   0, LVCFMT_LEFT },	// 著作権
	{"Engineer"  , FALSE, 10, 128,   0, LVCFMT_LEFT },	// エンジニア(製作者)
	{"Source"    , FALSE, 11, 128,   0, LVCFMT_LEFT },	// ソース
	{"Software"  , FALSE, 12, 128,   0, LVCFMT_LEFT },	// ソフトウェア
	{"Keyword"   , FALSE, 13, 128,   0, LVCFMT_LEFT },	// キーワード
	{"Technician", FALSE, 14, 128,   0, LVCFMT_LEFT },	// 技術者
	{"Lyric"     , FALSE, 15, 128,   0, LVCFMT_LEFT },	// 歌詞
	{"Commission", FALSE, 16, 128,   0, LVCFMT_LEFT },	// コミッション
	{"Composer"  , FALSE, 17, 128,   0, LVCFMT_LEFT },	// 作曲 /* Baja 154 */
	{"OrigArtist", FALSE, 18, 128,   0, LVCFMT_LEFT },	// Orig.アーティスト /* Baja 154 */
	{"URL"       , FALSE, 19, 128,   0, LVCFMT_LEFT },	// URL /* Baja 154 */
	{"Encodest"  , FALSE, 20, 128,   0, LVCFMT_LEFT },	// エンコードした人/* Baja 154 */
	{"FileSize"  , TRUE , 21,  56,  56, LVCFMT_RIGHT},	// ファイルサイズ
	{"FileTime"  , FALSE, 22, 128, 128, LVCFMT_LEFT },	// ファイル更新日
	{"FilePath"  , TRUE , 23, 128, 128, LVCFMT_LEFT },	// ファイルパス名
	{"PlayTime"  , FALSE, 24, 128, 128, LVCFMT_LEFT },	// 演奏時間
	{"LyricFile" , FALSE, 25, 128, 128, LVCFMT_LEFT },	// 歌詞ファイル
	{"FileType"  , TRUE , 26, 128, 128, LVCFMT_LEFT },	// ファイルの種類
// 	{"BitRate"   , FALSE, 27, 128, 0, LVCFMT_LEFT },	// ビットレート /* Conspiracy 198 */
	{"Format"    , FALSE, 27, 128, 0, LVCFMT_LEFT },	// フォーマット /* Conspiracy 198 */
	{"Other"     , FALSE, 28, 128, 128, LVCFMT_LEFT },	// その他 /* Conspiracy 196 */
	{"FileCTime" , FALSE, 29, 128, 128, LVCFMT_LEFT },	// ファイル作成日 /* Hurricane 207 */
};


#define PROG_NAME		"SuperTagEditor"	// プログラム名
#define PROG_VERSION	"2.00β7"			// バージョン

HKEY	hKey;
CString GetProfileString(LPCTSTR sSec, LPCTSTR sKey, LPCTSTR sDefault) {
	CString sValue;
	CString section = sSec;
	section += "\\";
	section += sKey;

	CString key = "Software\\MERCURY\\SuperTagEditor\\";
	key += sSec;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, key, 0, KEY_EXECUTE, &hKey) != ERROR_SUCCESS) {
		return sDefault;
	}
	DWORD	dwValueType;
	DWORD	dwValueSize = 1024*2;

	/* レジストリ値の取得 */
	if (RegQueryValueEx(hKey, sKey, NULL, &dwValueType, (LPBYTE)sValue.GetBufferSetLength(dwValueSize), &dwValueSize) != ERROR_SUCCESS) {
		sValue.ReleaseBuffer();
		RegCloseKey(hKey);
		return sDefault;
	}

	sValue.ReleaseBuffer();
	RegCloseKey(hKey);
	return sValue;
}

int CSTEReg2IniDlg::GetProfileInt(LPCTSTR sSec, LPCTSTR sKey, int nDefault) {
	int nValue;
	CString section = sSec;
	section += "\\";
	section += sKey;

	CString key = "Software\\MERCURY\\SuperTagEditor\\";
	key += sSec;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, key, 0, KEY_EXECUTE, &hKey) != ERROR_SUCCESS) {
		return nDefault;
	}
	DWORD	dwValueType;
	DWORD	dwValueSize = sizeof(nValue);

	/* レジストリ値の取得 */
	if (RegQueryValueEx(hKey, sKey, NULL, &dwValueType, (LPBYTE)&nValue, &dwValueSize) != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		return nDefault;
	}

	RegCloseKey(hKey);
	return nValue;
}

void GetWinampPath(void)
{
	HKEY	hKey;
	CString strKeyString = "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\Winamp.exe";

	g_sOptWinAmpPath = "";

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, strKeyString, 0, KEY_EXECUTE, &hKey) == ERROR_SUCCESS) {
		DWORD	dwValueType;
		DWORD	dwValueSize = FILENAME_MAX;
		unsigned char	sValue[FILENAME_MAX];

		/* レジストリ値の取得 */
		RegQueryValueEx(hKey, "", NULL, &dwValueType, &sValue[0], &dwValueSize);

		/* 結果の表示 */
		if (dwValueType == REG_SZ) g_sOptWinAmpPath = sValue;

		/* 終了 */
		RegCloseKey(hKey);
	}
}

void CSTEReg2IniDlg::ReadCellStateControl()
{
	static	char	*sSectionColumnState	= "ColumnState";

	int		nColumn;

	// カラム情報をレジストリから読み出す
	for (nColumn = 0; nColumn < COLUMN_MAX; nColumn++) {
		CString	strKey;
		COLUMN_STATUS	*stat = &g_columnStatus[nColumn];

		// 表示フラグ
		strKey.Format("%sShow", stat->sRegKey);
		stat->bShowFlag = GetProfileInt(sSectionColumnState, strKey, stat->bShowFlag);

		// カラム位置
		strKey.Format("%sColNum", stat->sRegKey);
		stat->nNumber = GetProfileInt(sSectionColumnState, strKey, stat->nNumber);

		// カラム幅
		strKey.Format("%sWidth", stat->sRegKey);
		stat->nWidth = GetProfileInt(sSectionColumnState, strKey, stat->nWidth);

		// 最大カラム幅
		strKey.Format("%sWidthMax", stat->sRegKey);
		stat->nWidthMax = GetProfileInt(sSectionColumnState, strKey, stat->nWidthMax);
	}
}

void CSTEReg2IniDlg::WriteCellStateControl()
{
	//CString strINI = "SuperTagEditor.ini";
	static	char	*sSectionColumnState	= "ColumnState";

	int		nColumn;
	// カラム情報をレジストリに書き出す
	for (nColumn = 0; nColumn < COLUMN_MAX; nColumn++) {
		CString	strKey;
		COLUMN_STATUS	*stat = &g_columnStatus[nColumn];

		// 表示フラグ
		strKey.Format("%sShow", stat->sRegKey);
		MyWriteProfileInt(sSectionColumnState, strKey, stat->bShowFlag);

		// カラム位置
		strKey.Format("%sColNum", stat->sRegKey);
		MyWriteProfileInt(sSectionColumnState, strKey, stat->nNumber);

		// カラム幅
		strKey.Format("%sWidth", stat->sRegKey);
		MyWriteProfileInt(sSectionColumnState, strKey, stat->nWidth);

		// 最大カラム幅
		strKey.Format("%sWidthMax", stat->sRegKey);
		MyWriteProfileInt(sSectionColumnState, strKey, stat->nWidthMax);
	}
	Profile_Flush(strINI);
	//Profile_Free();
}


// ジャンルリストの設定をレジストリから読みこむ
void CSTEReg2IniDlg::ReadGenreList(void)
{
	for (int nIndex = 0; g_genreListSCMPX[nIndex].sName != NULL; nIndex++) {
		GENRE_LIST	*pGenre = &g_genreListSCMPX[nIndex];
		CString	strName;
		strName.Format("%d", pGenre->byGenre);
		pGenre->bAddList = (DWORD)GetProfileInt(sSectionGenreList, strName, 1) ? true : false;
	}
	for (int i = 0; i < USER_GENRE_LIST_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format("haseta\\%s\\%d", sSectionUserGenreList, i);
		g_genreListUSER[i].bAddList = GetProfileInt(strSectionName, sKeyUserGenreAddList, 0) == 0 ? false : true;
		g_genreListUSER[i].byGenre = (BYTE)GetProfileInt(strSectionName, sKeyUserGenreNo, 255);
		g_genreListUSER[i].sName = GetProfileString(strSectionName, sKeyUserGenreName, NULL);
		if (g_genreListUSER[i].sName.GetLength() == 0) {
			g_genreListUSER[i].bUse = false;
		} else {
			g_genreListUSER[i].bUse = true;
		}
	}
}

// ジャンルリストの設定をレジストリに書き出す
void CSTEReg2IniDlg::WriteGenreList(void)
{
	for (int nIndex = 0; g_genreListSCMPX[nIndex].sName != NULL; nIndex++) {
		GENRE_LIST	*pGenre = &g_genreListSCMPX[nIndex];
		CString	strName;
		strName.Format("%d", pGenre->byGenre);
		MyWriteProfileInt(sSectionGenreList, strName, pGenre->bAddList ? 1 : 0);
	}
	if (g_genreListUSER != NULL) {
		for (int i = 0; i < USER_GENRE_LIST_MAX; i++) {
			CString		strSectionName;
			strSectionName.Format("haseta\\%s\\%d", sSectionUserGenreList, i);
			MyWriteProfileInt(strSectionName, sKeyUserGenreAddList, g_genreListUSER[i].bAddList == true ? 1 : 0);
			MyWriteProfileInt(strSectionName, sKeyUserGenreNo, g_genreListUSER[i].byGenre);
			MyWriteProfileString(strSectionName, sKeyUserGenreName, g_genreListUSER[i].sName);
		}
	}
}

void CSTEReg2IniDlg::ReadRegistry(void)
{
	int		i;

	// 各種設定を読み込む
	CString	strVersion;
	strVersion = GetProfileString(sSectionOption, sKeyVersion, "");
//	g_bIsVersionUp = strcmp(strVersion, PROG_VERSION) ? true : false;

	g_strCurrentDirectory	= GetProfileString(sSectionOption, sKeyCurrentDir, "");
	g_strCurrentPlayList	= GetProfileString(sSectionOption, sKeyCurrentPlayList, "*.m3u");

	// 一般 - ユーザーインターフェース
	g_bOptESCEditCancel			= GetProfileInt(sSectionOption, sKeyESCEditCancel, 0) ? true : false;
	g_bOptEnableEditCursorExit	= GetProfileInt(sSectionOption, sKeyEnableEditCursorExit, 1) ? true : false;
	g_bOptEditOkDown		= GetProfileInt(sSectionOption, sKeyEditOkDown, 1) ? true : false;
	g_bOptEnterBeginEdit	= GetProfileInt(sSectionOption, sKeyEnterBeginEdit, 0) ? true : false;

	// 一般 - 動作設定
	g_bOptKeepTimeStamp		= GetProfileInt(sSectionOption, sKeyKeepTimeStamp, 0) ? true : false;
	g_bOptSyncCreateTime	= GetProfileInt(sSectionOption, sKeySyncCreateTime, 0) ? true : false;
	g_bOptChangeFileExt		= GetProfileInt(sSectionOption, sKeyChangeFileExt, 0) ? true : false;
	g_bOptAutoOpenFolder	= GetProfileInt(sSectionOption, sKeyAutoOpenFolder, 0) ? true : false;
	g_bOptLoadFileAdjustColumn	= GetProfileInt(sSectionOption, sKeyLoadFileAdjustColumn, 1) ? true : false;
	g_bOptLoadFileChecked	= GetProfileInt(sSectionOption, sKeyLoadFileChecked, 1) ? true : false;
	g_bOptHideMP3ListFile	= GetProfileInt(sSectionOption, sKeyHideMP3ListFile, 0) ? true : false;

	// 一般 - RIFF MP3
	g_bOptAutoConvID3v2			= GetProfileInt(sSectionOption, sKeyAutoConvID3v2, 0) ? true : false;
	g_bOptID3v2ID3tagAutoWrite	= GetProfileInt(sSectionOption, sKeyID3v2ID3tagAutoWrite, 0) ? true : false;
	g_bOptID3v2GenreListSelect	= GetProfileInt(sSectionOption, sKeyID3v2GenreListSelect, 1) ? true : false;
	g_bOptAutoConvRMP			= GetProfileInt(sSectionOption, sKeyAutoConvRMP, 0) ? true : false;
	g_bOptRmpID3tagAutoWrite	= GetProfileInt(sSectionOption, sKeyRmpID3tagAutoWrite, 0) ? true : false;
	g_bOptRmpGenreListSelect	= GetProfileInt(sSectionOption, sKeyRmpGenreListSelect, 1) ? true : false;
	g_nOptSIFieldConvType		= GetProfileInt(sSectionOption, sKeySIFieldConvType, SIF_CONV_ALL_FIELD);

	// 一般 - 歌詞ファイル
	g_bOptChangeTextFile		= GetProfileInt(sSectionOption, sKeyChangeTextFile, 1) ? true : false;
	g_bOptSetLyricsDir			= GetProfileInt(sSectionOption, sKeySetLyricsDir, 0) ? true : false;
	g_bOptSearchLyricsSubDir	= GetProfileInt(sSectionOption, sKeySearchLyricsSubDir, 0) ? true : false;
	g_strOptLyricsPath			= GetProfileString(sSectionOption, sKeyLyricsPath, "");

	//
	g_bOptEditFieldSIF		= GetProfileInt(sSectionOption, sKeyEditFiledSIF, 1) ? true : false;
	g_nOptCheckFileName		= GetProfileInt(sSectionOption, sKeyCheckFileName, FILENAME_CONV_MULTIBYTE);
	g_bEnableSearchSubDir	= GetProfileInt(sSectionOption, sKeyEnableSearchSubDir, 1) ? true : false;

	// フォルダの同期
	g_bEnableFolderSync		= GetProfileInt(sSectionFolderSync, sKeyEnableFolderSync, 0) ? true : false;
	g_strRootFolder			= GetProfileString(sSectionFolderSync, sKeySyncRootFolder, "");
	g_bSyncSelectAlways		= GetProfileInt(sSectionFolderSync, sKeySyncSelectAlways, 0) ? true : false;
	g_bSyncDeleteFolder		= GetProfileInt(sSectionFolderSync, sKeySyncDeleteFolder, 1) ? true : false;
	g_bSyncLyricsFileMove	= GetProfileInt(sSectionFolderSync, sKeySyncLyricsFileMove, 1) ? true : false;

	// 確認メッセージ表示
	g_bConfConvMP3		= GetProfileInt(sSectionConfMessage, sKeyConfConvMP3, 1) ? true : false;
	g_bConfConvRMP		= GetProfileInt(sSectionConfMessage, sKeyConfConvRMP, 1) ? true : false;
	g_bConfConvID3v2	= GetProfileInt(sSectionConfMessage, sKeyConfConvID3v2, 1) ? true : false;
	g_bConfDeleteFile	= GetProfileInt(sSectionConfMessage, sKeyConfDeleteFile, 1) ? true : false;
	g_bConfDeleteList	= GetProfileInt(sSectionConfMessage, sKeyConfDeleteList, 1) ? true : false;
	g_bConfEditModify	= GetProfileInt(sSectionConfMessage, sKeyConfEditModify, 1) ? true : false;
	g_bConfFolderSync	= GetProfileInt(sSectionConfMessage, sKeyConfFolderSync, 1) ? true : false;

	// プレイリスト
	g_bPlayListClearList	= GetProfileInt(sSectionLoadPlayList, sKeyClearList, 0) ? true : false;
	g_bPlayListClearCheck	= GetProfileInt(sSectionLoadPlayList, sKeyClearCheck, 1) ? true : false;
	g_bPlayListAddList		= GetProfileInt(sSectionLoadPlayList, sKeyAddList, 0) ? true : false;
	g_bPlayListFileCheck	= GetProfileInt(sSectionLoadPlayList, sKeyFileCheck, 1) ? true : false;

	// 条件チェックの状態
	for (i = 0; i < CHECK_STATE_MAX; i++) {
		CHECK_WORD_STATE	*pState = &g_chkWord[i];
		char	*sSectionName = sSectionCheckWord[i];
		pState->strSearchWord	= GetProfileString(sSectionName, sKeySearchWord, "");
		pState->strReplaceWord	= GetProfileString(sSectionName, sKeyReplaceWord, "");
		pState->nTargetColumn	= GetProfileInt(sSectionName, sKeyTargetColumn, -1);
		pState->bCheckDiffUL	= GetProfileInt(sSectionName, sKeyCheckDiffUL, 0) ? true : false;
		pState->bRegExp			= GetProfileInt(sSectionName, sKeyRegExp, 0) ? true : false;
		pState->bRangeSelected	= GetProfileInt(sSectionName, sKeyRangeSelected, 0) ? true : false;
		pState->bMatchComplete	= GetProfileInt(sSectionName, sKeyMatchComplete, 0) ? true : false;
		pState->bMatchSelected	= GetProfileInt(sSectionName, sKeyMatchSelected, 0) ? true : false;
	}

	// ユーザー変換書式
	const char *sDefFormatTag2File = "%ARTIST_NAME%-%ALBUM_NAME%-%TRACK_NAME%";
	const char *sDefFormatFile2Tag = sDefFormatTag2File;
	//g_nUserConvFormatType	= GetProfileInt(sSectionUserConvFormat, sKeyConvFormatType, 0);
	{ /* 数を増やしたので本家併用時に影響を与えないように LastTrain 057 */
		CString		strSectionName;
		strSectionName = "haseta\\";
		strSectionName += sSectionUserConvFormat;
		g_nUserConvFormatType	= GetProfileInt(strSectionName, sKeyConvFormatType, 0);
	}
	for (i = 0; i < USER_CONV_FORMAT_MAX; i++) {
		CString		strKeyName;
		// 名称
		strKeyName.Format("%s%d", sKeyUserFormName, i);
		g_userConvFormat[i].strName = GetProfileString(sSectionUserConvFormat, strKeyName, "名称未設定");
		// タグ情報 => ファイル名
		strKeyName.Format("%s%d", sKeyUserFormTag2File, i);
		g_userConvFormat[i].strTag2File = GetProfileString(sSectionUserConvFormat, strKeyName, sDefFormatTag2File);
		// ファイル名 => タグ情報
		strKeyName.Format("%s%d", sKeyUserFormFile2Tag, i);
		g_userConvFormat[i].strFile2Tag = GetProfileString(sSectionUserConvFormat, strKeyName, sDefFormatFile2Tag);
		// ２つ目以降はデフォルト文字列はクリア
		sDefFormatTag2File = sDefFormatFile2Tag = "";
	}

	// 拡張版ユーザー変換書式
	for (i = 0; i < USER_CONV_FORMAT_EX_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format("%s%d", sSectionConvFormatEx, i);
		// 名称
		g_userConvFormatEx[i].strName = GetProfileString(strSectionName, sKeyUserFormName, "名称未設定");
		// 書式
		g_userConvFormatEx[i].strFormat = GetProfileString(strSectionName, sKeyUserFormat, "");
		// 固定文字列
		g_userConvFormatEx[i].strFixString = GetProfileString(strSectionName, sKeyUserFixString, "");
		// 連番：初期値
		g_userConvFormatEx[i].nInitNumber = GetProfileInt(strSectionName, sKeyUserInitNumber, 1);
		// 連番：加算値
		g_userConvFormatEx[i].nAddNumber = GetProfileInt(strSectionName, sKeyUserAddNumber, 1);
		// 連番：桁数
		g_userConvFormatEx[i].nColumnCount = GetProfileInt(strSectionName, sKeyUserColumnCount, 1);
		// 書き込み不可のセルで連番クリア
		g_userConvFormatEx[i].bSpaceInitNumber = GetProfileInt(strSectionName, sKeyUserSpaceInit, 0) ? true : false;
	}

	// 移動先フォルダ書式
	for (i = 0; i < USER_MOVE_FODLER_FORMAT_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format("haseta\\%s%d", sSectionMoveFolder, i);
		// 名称
		g_userMoveFolder[i].strName = GetProfileString(strSectionName, sKeyUserFormName, "名称未設定");
		// 書式
		g_userMoveFolder[i].strFormat = GetProfileString(strSectionName, sKeyMoveFolderFormat, "");
		// 固定文字列
		g_userMoveFolder[i].strFixString = GetProfileString(strSectionName, sKeyMoveFolderFixString, "");
		// コピー
		g_userMoveFolder[i].bCopy = GetProfileInt(strSectionName, sKeyMoveFolderCopy, 0) ? true : false;
	}
	// 書式コピー /* FunnyCorn 175 */
	for (i = 0; i < USER_COPY_FORMAT_FORMAT_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format("haseta\\%s%d", sSectionCopyFormat, i);
		// 名称
		g_userCopyFormat[i].strName = GetProfileString(strSectionName, sKeyUserFormName, "名称未設定");
		// 書式
		g_userCopyFormat[i].strFormat = GetProfileString(strSectionName, sKeyCopyFormatFormat, "");
		// 固定文字列
		g_userCopyFormat[i].strFixString = GetProfileString(strSectionName, sKeyCopyFormatFixString, "");
	}
	{
		CString		sSectionOption;
		sSectionOption = "haseta";
		g_bOptID3v2GenreAddNumber	= GetProfileInt(sSectionOption, sKeyID3v2GenreAddNumber, 1) ? true : false;
		g_bOptID3v2ID3tagAutoDelete	= GetProfileInt(sSectionOption, sKeyID3v2ID3tagAutoDelete, 0) ? true : false; /* FunnyCorn 173 */
		g_bConfFileNameMaxCheck	= GetProfileInt(sSectionOption, sKeyFileNameMaxCheck, 0) ? true : false;
		g_bFileNameMaxCellColor	= GetProfileInt(sSectionOption, sKeyFileNameMaxCellColor, 0) ? true : false; /* SeaKnows 036 */
		g_nConfFileNameMaxChar	= GetProfileInt(sSectionOption, sKeyFileNameMaxChar, 255);
		g_bOptDropSearchSubFolder	= GetProfileInt(sSectionOption, sKeyDropSearchSubFolder, 0) ? true : false;	/* TyphoonSwell 026 */
		g_bOptShowZenSpace	= GetProfileInt(sSectionOption, sKeyShowZenSpace, 1) ? true : false;	/* BeachMonster 107 */
		g_sOptShowOtherChar = GetProfileString(sSectionOption, sKeyShowOtherChar, "");
		g_bOptSortIgnoreCase	= GetProfileInt(sSectionOption, sKeySortIgnoreCase, 0) ? true : false;	/* BeachMonster4 114 */
		g_bOptSortIgnoreZenHan	= GetProfileInt(sSectionOption, sKeySortIgnoreZenHan, 0) ? true : false;	/* BeachMonster4 114 */
		g_bOptSortIgnoreKataHira= GetProfileInt(sSectionOption, sKeySortIgnoreKataHira, 0) ? true : false;	/* FunnyCorn 179 */
		g_bOptShowTotalParent	= GetProfileInt(sSectionOption, sKeyShowTotalParent, 0) ? true : false;	/* RockDance 128 */
		g_bOptShowTips	= GetProfileInt(sSectionOption, sKeyShowTips, 1) ? true : false;	/* Rumble 188 */
	}
	// 定型文貼り付け /* SeaKnows 030 *//* FreeFall 046 */
	for (int k=0;k<3;k++) {
		CString		sSectionOption;
		CString		strSectionName;
		sSectionOption = "haseta";
		strSectionName.Format("%s%d", sSectionTeikeiGroupName, k);
		g_strTeikeiGroupName[k] = GetProfileString(sSectionOption, strSectionName, "名称未設定");
		for (i = 0; i < 10; i++) {
			if (k == 0) {
				strSectionName.Format("%s%d", sSectionTeikei, i);
			} else {
				strSectionName.Format("%s%d-%d", sSectionTeikei, k, i);
			}
			g_strTeikei[i+k*10] = GetProfileString(sSectionOption, strSectionName, "");
		}
	}
	// ソフトウェア他 /* SeaKnows 031 */
	{
		CString		strSectionName;
		strSectionName = "haseta";
		g_strSoftwareTag = GetProfileString(strSectionName, sSectionSoftwareTag, PROG_NAME " Ver " PROG_VERSION "改");
		g_bValidFolderSelect = GetProfileInt(strSectionName, sSectionValidFolderSelect, 0) ? true : false;
		g_bValidDupExec = GetProfileInt(strSectionName, sSectionValidDupExec, 0) ? true : false; /* FreeFall 045 */
		g_nRecentFolder = GetProfileInt(strSectionName, sSectionRecentFolderNum, 5); /* WriteProfileInt 053 */
		g_bSaveRepDlgPos = GetProfileInt(strSectionName, sSectionSaveRepDlgPos, 0) ? true : false; /* WildCherry4 086 */
		g_nSaveRepDlgPosX = GetProfileInt(strSectionName, sSectionSaveRepDlgPosX, -1); /* WildCherry4 086 */
		g_nSaveRepDlgPosY = GetProfileInt(strSectionName, sSectionSaveRepDlgPosY, -1); /* WildCherry4 086 */
		g_nAddNumberWidth = GetProfileInt(strSectionName, sSectionAddNumberWidth, 2); /* Baja 159 */
		g_nAddNumberPos = GetProfileInt(strSectionName, sSectionAddNumberPos, 0); /* Baja 159 */
		g_strAddNumberSep = GetProfileString(strSectionName, sSectionAddNumberSep, ""); /* Baja 159 */
		g_bId3v2OldComment = GetProfileInt(strSectionName, sSectiongId3v2OldComment, 0) ? true : false; /* FunnyCorn 180 */
		g_bId3v2UNICODE = GetProfileInt(strSectionName, sSectiongId3v2UNICODE, 0) ? true : false; /* FunnyCorn 181 */
		g_strAddNumberBef = GetProfileString(strSectionName, sSectionAddNumberBef, ""); /* Conspiracy 194 */
		g_strAddNumberAft = GetProfileString(strSectionName, sSectionAddNumberAft, ""); /* Conspiracy 194 */
		g_bAudioListShow = GetProfileInt(strSectionName, sSectionAudioListShow, 0) ? true : false; /* Conspiracy 199 */
	}

	// リスト出力書式
	for (i = 0; i < WRITE_FORMAT_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format("%s%d", sSectionWriteFormat, i);
		// 名称
		g_writeFormat[i].strName = GetProfileString(strSectionName, sKeyWriteFormName, "名称未設定");
		// 書式ファイル名
		g_writeFormat[i].strFileName = GetProfileString(strSectionName, sKeyWriteFileName, "");
		// 拡張子
		g_writeFormat[i].strExtName = GetProfileString(strSectionName, sKeyWriteExtName, ".txt");
		// 選択ファイルのみ出力
		g_writeFormat[i].bWriteSelected = GetProfileInt(strSectionName, sKeyWriteSelected, 0) ? true : false;
		// カレントファイル名
		g_writeFormat[i].strCurrentFile = GetProfileString(strSectionName, sKeyWriteCurrentFile, "");
		// HTML ファイル出力用(空の場合に全角スペースを出力)
		g_writeFormat[i].bIsHtml = GetProfileInt(strSectionName, sKeyWriteIsHtml, 0) ? true : false;
		{ /* BeachMonster5 120 */
			g_writeFormat[i].bWriteHtml = GetProfileInt("haseta\\" + strSectionName, sKeyWriteHtml, 0) ? true : false;
		}
	}

	// ファイル名置換文字
	for (i = 0; i < FILENAME_REPLACE_MAX; i++) {
		FILENAME_REPLACE	*pRep = &g_fileNameReplace[i];
		CString		strKeyName;
		// 置換後文字列
		strKeyName.Format("%s%d", sKeyRepCharAfter, i);
		pRep->strBefore = g_sRepTable[i][0];
		pRep->strAfter = GetProfileString(sSectionRepFileName, strKeyName, g_sRepTable[i][1]);
	}
	// ユーザファイル名置換文字 /* FreeFall 050 */
	{
		CString		strSectionName;
		strSectionName = "haseta\\User";
		strSectionName += sSectionRepFileName;
		for (i = 0; i < USER_FILENAME_REPLACE_MAX; i++) {
			FILENAME_REPLACE	*pRep = &g_userFileNameReplace[i];
			CString		strKeyName;
			// 置換後文字列
			strKeyName.Format("%s%d", sKeyRepCharBefore, i);
			pRep->strBefore = GetProfileString(strSectionName, strKeyName, "");
			strKeyName.Format("%s%d", sKeyRepCharAfter, i);
			pRep->strAfter = GetProfileString(strSectionName, strKeyName, "");
		}
	}

	// 分類設定情報
	g_classInfo.nType = GetProfileInt(sSectionClass, sKeyClassType, 0);
	for (i = 0; i < CLASS_MAX; i++) {
		CString		strKeyName;
		// カラム番号
		strKeyName.Format("%s%d", sKeyClassColumn, i);
		g_classInfo.nColumn[i] = GetProfileInt(sSectionClass, strKeyName, -1);
	}

	// ソート情報
	for (i = 0; i < SORT_KEY_MAX; i++) {
		CString		strKeyName;
		SORT_STATE	*state = &g_sortState[i];
		// キー(カラム)
		strKeyName.Format("%s%d", sKeySortColumn, i);
		state->nKeyColumn = GetProfileInt(sSectionSort, strKeyName, -1);
		// タイプ
		strKeyName.Format("%s%d", sKeySortType, i);
		state->nType = GetProfileInt(sSectionSort, strKeyName, 0);
	}

	// ウィンドウのフォントを読み込む
	CString	strFont;
	strFont = GetProfileString(sSectionFont, sKeyFontFace, "");
	strcpy(g_fontReport.lfFaceName, (const char *)strFont);
	g_fontReport.lfHeight			= GetProfileInt(sSectionFont, sKeyFontHeight, 0);
	g_fontReport.lfWidth			= GetProfileInt(sSectionFont, sKeyFontWidth, 0);
	g_fontReport.lfEscapement		= GetProfileInt(sSectionFont, sKeyFontEscapement, 0);
	g_fontReport.lfOrientation		= GetProfileInt(sSectionFont, sKeyFontOrientation, 0);
	g_fontReport.lfWeight			= GetProfileInt(sSectionFont, sKeyFontWeight, 0);
	g_fontReport.lfItalic			= (unsigned char)GetProfileInt(sSectionFont, sKeyFontItalic, 0);
	g_fontReport.lfUnderline		= (unsigned char)GetProfileInt(sSectionFont, sKeyFontUnderline, 0);
	g_fontReport.lfStrikeOut		= (unsigned char)GetProfileInt(sSectionFont, sKeyFontStrikeOut, 0);
	g_fontReport.lfCharSet			= (unsigned char)GetProfileInt(sSectionFont, sKeyFontCharSet, 0);
	g_fontReport.lfOutPrecision		= (unsigned char)GetProfileInt(sSectionFont, sKeyFontOutPrecision, 0);
	g_fontReport.lfClipPrecision	= (unsigned char)GetProfileInt(sSectionFont, sKeyFontClipPrecision, 0);
	g_fontReport.lfQuality			= (unsigned char)GetProfileInt(sSectionFont, sKeyFontQuality, 0);
	g_fontReport.lfPitchAndFamily	= (unsigned char)GetProfileInt(sSectionFont, sKeyFontPitchAndFamily, 0);

	//g_nOptPlayerType		= GetProfileInt(sSectionOption, sKeyPlayerType, PLAYER_WINAMP);
	//g_sOptWinAmpPath		= GetProfileString(sSectionOption, sKeyWinAmpPath, "");
	{ /* 数を増やしたので本家併用時に影響を与えないように WildCherry 070 */
		CString		strSectionName;
		strSectionName = "haseta\\";
		strSectionName += sSectionOption;
		g_nOptPlayerType	= GetProfileInt(strSectionName, sKeyPlayerType, PLAYER_WINAMP);
		g_sOptWinAmpPath		= GetProfileString(strSectionName, sKeyWinAmpPath, "");
	}
	if (g_sOptWinAmpPath.IsEmpty()) {
		// WinAmp のパスを取得
		GetWinampPath();
	}

	g_bMainFrameZoomed		= GetProfileInt(sSectionWindow, sKeyWinZoomed, FALSE);
	g_bMainFrameIconic		= GetProfileInt(sSectionWindow, sKeyWinIconic, FALSE);
	ReadWindowStatus(sKeyMainWindow, &g_rectMainWindow);

	// ユーザ指定ジャンル
	if (g_genreListUSER == NULL) {
		g_genreListUSER = new USER_GENRE_LIST[USER_GENRE_LIST_MAX];
	}

	// 文字種の統一 /* StartInaction 054 */
	{
		CString		strSectionName;
		strSectionName = "haseta";
		g_nUnifyAlpha = GetProfileInt(strSectionName, sKeyUnifyAlpha, 0);
		g_nUnifyHiraKata = GetProfileInt(strSectionName, sKeyUnifyHiraKata, 0);
		g_nUnifyKata = GetProfileInt(strSectionName, sKeyUnifyKata, 0);
		g_nUnifyKigou = GetProfileInt(strSectionName, sKeyUnifyKigou, 0);
		g_nUnifySuji = GetProfileInt(strSectionName, sKeyUnifySuji, 0);
		g_nUnifyUpLow = GetProfileInt(strSectionName, sKeyUnifyUpLow, 0);
	}

	// ファイル名文字種の統一 /* LastTrain 058 */
	{
		CString		strSectionName;
		strSectionName = "haseta";
		g_nFileUnifyAlpha = GetProfileInt(strSectionName, sKeyFileUnifyAlpha, 0);
		g_nFileUnifyHiraKata = GetProfileInt(strSectionName, sKeyFileUnifyHiraKata, 0);
		g_nFileUnifyKata = GetProfileInt(strSectionName, sKeyFileUnifyKata, 0);
		g_nFileUnifyKigou = GetProfileInt(strSectionName, sKeyFileUnifyKigou, 0);
		g_nFileUnifySuji = GetProfileInt(strSectionName, sKeyFileUnifySuji, 0);
		g_nFileUnifyUpLow = GetProfileInt(strSectionName, sKeyFileUnifyUpLow, 0);
	}

	// プレイリスト入力設定ダイアログを表示する /* RockDance 126 */
	{
		CString		strSectionName;
		strSectionName = "haseta";
		g_bShowLoadPlaylistDlg = GetProfileInt(strSectionName, sKeyShowLoadPlaylistDlg, 1) ? true : false;
	}

	// お気に入りのフォルダ /* RockDance 129 */
	{
		CString		sSectionOption;
		CString		strSectionName;
		sSectionOption = "haseta";
		for (i = 0; i < 10; i++) {
			strSectionName.Format("%s%d", sSectionFavorites, i);
			g_strFavorite[i] = GetProfileString(sSectionOption, strSectionName, "");
		}
	}

	// 対象の拡張子 /* Conspiracy 195 */
	{
		CString		strSectionName;
		strSectionName = "haseta";
		g_bValidAllFile = GetProfileInt(strSectionName, sKeyValidAllFile, 0) ? true : false;
	}
}

void CSTEReg2IniDlg::ReadWindowStatus(char *sKey, RECT *rect)
{
	static	char	*sDefault = "0 0 0 0";
	CString	str;
	LPCSTR	sBuffer;
	str = GetProfileString(sSectionWindow, sKey, sDefault);
	sBuffer = (LPCSTR)str;
	sscanf(sBuffer, "%d %d %d %d", &rect->left,
								   &rect->top,
								   &rect->right,
								   &rect->bottom);
}

void CSTEReg2IniDlg::ReadKeyConfig(bool bUpdate)
{
	int		i;
	int		nTableMax = 0;
	for (i = 0; g_listKeyConfig[i].sName != NULL; i++) {
		KEY_CONFIG	*pKey = &g_listKeyConfig[i];
		if (pKey->wCmdID != 0x0000) {
			pKey->dwKeyCode = (DWORD)GetProfileInt(sSectionKeyConfig, pKey->sRegName, pKey->dwKeyCode);
			//if (pKey->dwKeyCode != 0) nTableMax++;
		}
	}

}

void CSTEReg2IniDlg::WriteKeyConfig(bool bUpdate)
{
	//CString strINI = "SuperTagEditor.ini";
	int		i;
	int		nTableMax = 0;
	//CString sValue;
	for (i = 0; g_listKeyConfig[i].sName != NULL; i++) {
		KEY_CONFIG	*pKey = &g_listKeyConfig[i];
		if (pKey->wCmdID != 0x0000) {
			//sValue.Format("%d", pKey->dwKeyCode);
			//WritePrivateProfileString(sSectionKeyConfig, pKey->sRegName, sValue, strINI);
			MyWriteProfileInt(sSectionKeyConfig, pKey->sRegName, pKey->dwKeyCode);
			//if (pKey->dwKeyCode != 0) nTableMax++;
		}
	}

	//SaveProfile();

}


void WriteWindowStatus(char *sKey, RECT *rect)
{
	CString	str;
	str.Format("%d %d %d %d", rect->left,
							  rect->top,
							  rect->right,
							  rect->bottom);
	MyWriteProfileString(sSectionWindow, sKey, str);
}

void WriteRegistry(void)
{
	//CString strINI = "SuperTagEditor.ini";
	//Profile_Initialize(strINI, TRUE);

	/*
	CDlgCommonProgress dlgLoadProgress;
	dlgLoadProgress.Create(AfxGetMainWnd());
	dlgLoadProgress.SetWindowText("終了処理中.....");
	dlgLoadProgress.SetDlgItemText(IDC_ST_MESSAGE, "設定を保存しています...");
	dlgLoadProgress.SetPos(0);
	*/

	int		i;

	// 各種設定を書き込む
	MyWriteProfileString(sSectionOption, sKeyVersion        , PROG_VERSION);
	MyWriteProfileString(sSectionOption, sKeyCurrentDir     , g_strCurrentDirectory);
	MyWriteProfileString(sSectionOption, sKeyCurrentPlayList, g_strCurrentPlayList);
	//dlgLoadProgress.SetPos(5);

	// 一般 - ユーザーインターフェース
	MyWriteProfileInt(sSectionOption, sKeyESCEditCancel       , g_bOptESCEditCancel ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyEnableEditCursorExit, g_bOptEnableEditCursorExit ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyEditOkDown          , g_bOptEditOkDown ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyEnterBeginEdit      , g_bOptEnterBeginEdit ? 1 : 0);
	//dlgLoadProgress.SetPos(10);

	// 一般 - 動作設定
	MyWriteProfileInt(sSectionOption, sKeyKeepTimeStamp       , g_bOptKeepTimeStamp ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeySyncCreateTime      , g_bOptSyncCreateTime ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyChangeFileExt       , g_bOptChangeFileExt ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyAutoOpenFolder      , g_bOptAutoOpenFolder ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyLoadFileAdjustColumn, g_bOptLoadFileAdjustColumn ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyLoadFileChecked     , g_bOptLoadFileChecked ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyHideMP3ListFile     , g_bOptHideMP3ListFile ? 1 : 0);
	//dlgLoadProgress.SetPos(15);

	// 一般 - 歌詞ファイル
	MyWriteProfileInt(sSectionOption, sKeyChangeTextFile    , g_bOptChangeTextFile ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeySetLyricsDir      , g_bOptSetLyricsDir ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeySearchLyricsSubDir, g_bOptSearchLyricsSubDir ? 1 : 0);
	MyWriteProfileString(sSectionOption, sKeyLyricsPath     , g_strOptLyricsPath);
	//dlgLoadProgress.SetPos(20);

	//
	MyWriteProfileInt(sSectionOption, sKeyEditFiledSIF, g_bOptEditFieldSIF ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyCheckFileName, g_nOptCheckFileName);
	MyWriteProfileInt(sSectionOption, sKeyEnableSearchSubDir, g_bEnableSearchSubDir ? 1 : 0);
	//dlgLoadProgress.SetPos(25);

	// フォルダの同期
	MyWriteProfileInt(sSectionFolderSync, sKeyEnableFolderSync, g_bEnableFolderSync ? 1 : 0);
	MyWriteProfileString(sSectionFolderSync, sKeySyncRootFolder, g_strRootFolder);
	MyWriteProfileInt(sSectionFolderSync, sKeySyncSelectAlways, g_bSyncSelectAlways ? 1 : 0);
	MyWriteProfileInt(sSectionFolderSync, sKeySyncDeleteFolder, g_bSyncDeleteFolder ? 1 : 0);
	MyWriteProfileInt(sSectionFolderSync, sKeySyncLyricsFileMove, g_bSyncLyricsFileMove ? 1 : 0);
	//dlgLoadProgress.SetPos(30);

	// 確認メッセージ表示
	MyWriteProfileInt(sSectionConfMessage, sKeyConfDeleteFile, g_bConfDeleteFile ? 1 : 0);
	MyWriteProfileInt(sSectionConfMessage, sKeyConfDeleteList, g_bConfDeleteList ? 1 : 0);
	MyWriteProfileInt(sSectionConfMessage, sKeyConfEditModify, g_bConfEditModify ? 1 : 0);
	MyWriteProfileInt(sSectionConfMessage, sKeyConfFolderSync, g_bConfFolderSync ? 1 : 0);
	//dlgLoadProgress.SetPos(35);

	// プレイリスト
	MyWriteProfileInt(sSectionLoadPlayList, sKeyClearList , g_bPlayListClearList ? 1 : 0);
	MyWriteProfileInt(sSectionLoadPlayList, sKeyClearCheck, g_bPlayListClearCheck ? 1 : 0);
	MyWriteProfileInt(sSectionLoadPlayList, sKeyAddList   , g_bPlayListAddList ? 1 : 0);
	MyWriteProfileInt(sSectionLoadPlayList, sKeyFileCheck , g_bPlayListFileCheck ? 1 : 0);
	//dlgLoadProgress.SetPos(40);

	// 条件チェックの状態
	for (i = 0; i < CHECK_STATE_MAX; i++) {
		CHECK_WORD_STATE	*pState = &g_chkWord[i];
		char	*sSectionName = sSectionCheckWord[i];
		MyWriteProfileString(sSectionName, sKeySearchWord, pState->strSearchWord);
		MyWriteProfileString(sSectionName, sKeyReplaceWord, pState->strReplaceWord);
		MyWriteProfileInt(sSectionName, sKeyTargetColumn , pState->nTargetColumn);
		MyWriteProfileInt(sSectionName, sKeyCheckDiffUL  , pState->bCheckDiffUL ? 1 : 0);
		MyWriteProfileInt(sSectionName, sKeyRegExp       , pState->bRegExp ? 1 : 0);
		MyWriteProfileInt(sSectionName, sKeyRangeSelected, pState->bRangeSelected ? 1 : 0);
		MyWriteProfileInt(sSectionName, sKeyMatchComplete, pState->bMatchComplete ? 1 : 0);
		MyWriteProfileInt(sSectionName, sKeyMatchSelected, pState->bMatchSelected ? 1 : 0);
	}
	//dlgLoadProgress.SetPos(45);

	// ファイル名置換文字
	for (i = 0; i < FILENAME_REPLACE_MAX; i++) {
		FILENAME_REPLACE	*pRep = &g_fileNameReplace[i];
		CString		strKeyName;
		// 置換後文字列
		strKeyName.Format("%s%d", sKeyRepCharAfter, i);
		MyWriteProfileString(sSectionRepFileName, strKeyName, pRep->strAfter);
	}
	//dlgLoadProgress.SetPos(50);
	// ユーザファイル名置換文字 /* FreeFall 050 */
	{
		CString		strSectionName;
		strSectionName = "haseta\\User";
		strSectionName += sSectionRepFileName;
		for (i = 0; i < USER_FILENAME_REPLACE_MAX; i++) {
			FILENAME_REPLACE	*pRep = &g_userFileNameReplace[i];
			CString		strKeyName;
			// 置換後文字列
			strKeyName.Format("%s%d", sKeyRepCharBefore, i);
			MyWriteProfileString(strSectionName, strKeyName, pRep->strBefore);
			strKeyName.Format("%s%d", sKeyRepCharAfter, i);
			MyWriteProfileString(strSectionName, strKeyName, pRep->strAfter);
		}
	}
	//dlgLoadProgress.SetPos(55);

	// ユーザー変換書式
	//MyWriteProfileInt(sSectionUserConvFormat, sKeyConvFormatType, g_nUserConvFormatType);
	{ /* 数を増やしたので本家併用時に影響を与えないように LastTrain 057 */
		CString		strSectionName;
		strSectionName = "haseta\\";
		strSectionName += sSectionUserConvFormat;
		MyWriteProfileInt(strSectionName, sKeyConvFormatType, g_nUserConvFormatType);
	}
	//dlgLoadProgress.SetPos(60);
	for (i = 0; i < USER_CONV_FORMAT_MAX; i++) {
		CString		strKeyName;
		// 名称
		strKeyName.Format("%s%d", sKeyUserFormName, i);
		MyWriteProfileString(sSectionUserConvFormat, strKeyName, g_userConvFormat[i].strName);
		// タグ情報 => ファイル名
		strKeyName.Format("%s%d", sKeyUserFormTag2File, i);
		MyWriteProfileString(sSectionUserConvFormat, strKeyName, g_userConvFormat[i].strTag2File);
		// ファイル名 => タグ情報
		strKeyName.Format("%s%d", sKeyUserFormFile2Tag, i);
		MyWriteProfileString(sSectionUserConvFormat, strKeyName, g_userConvFormat[i].strFile2Tag);
	}
	//dlgLoadProgress.SetPos(65);

	// 拡張版ユーザー変換書式
	for (i = 0; i < USER_CONV_FORMAT_EX_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format("%s%d", sSectionConvFormatEx, i);
		// 名称
		MyWriteProfileString(strSectionName, sKeyUserFormName, g_userConvFormatEx[i].strName);
		// 書式
		MyWriteProfileString(strSectionName, sKeyUserFormat, g_userConvFormatEx[i].strFormat);
		// 固定文字列
		MyWriteProfileString(strSectionName, sKeyUserFixString, g_userConvFormatEx[i].strFixString);
		// 連番：初期値
		MyWriteProfileInt(strSectionName, sKeyUserInitNumber, g_userConvFormatEx[i].nInitNumber);
		// 連番：加算値
		MyWriteProfileInt(strSectionName, sKeyUserAddNumber, g_userConvFormatEx[i].nAddNumber);
		// 連番：桁数
		MyWriteProfileInt(strSectionName, sKeyUserColumnCount, g_userConvFormatEx[i].nColumnCount);
		// 書き込み不可のセルで連番クリア
		MyWriteProfileInt(strSectionName, sKeyUserSpaceInit, g_userConvFormatEx[i].bSpaceInitNumber ? 1 : 0);
	}
	//dlgLoadProgress.SetPos(70);

	// 移動先フォルダ書式
	for (i = 0; i < USER_MOVE_FODLER_FORMAT_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format("haseta\\%s%d", sSectionMoveFolder, i);
		// 名称
		MyWriteProfileString(strSectionName, sKeyUserFormName, g_userMoveFolder[i].strName);
		// 書式
		MyWriteProfileString(strSectionName, sKeyMoveFolderFormat, g_userMoveFolder[i].strFormat);
		// 固定文字列
		MyWriteProfileString(strSectionName, sKeyMoveFolderFixString, g_userMoveFolder[i].strFixString);
		// コピー
		MyWriteProfileInt(strSectionName, sKeyMoveFolderCopy, g_userMoveFolder[i].bCopy ? 1 : 0);
	}
	//dlgLoadProgress.SetPos(75);
	// 書式コピー /* FunnyCorn 175 */
	for (i = 0; i < USER_COPY_FORMAT_FORMAT_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format("haseta\\%s%d", sSectionCopyFormat, i);
		// 名称
		MyWriteProfileString(strSectionName, sKeyUserFormName, g_userCopyFormat[i].strName);
		// 書式
		MyWriteProfileString(strSectionName, sKeyCopyFormatFormat, g_userCopyFormat[i].strFormat);
		// 固定文字列
		MyWriteProfileString(strSectionName, sKeyCopyFormatFixString, g_userCopyFormat[i].strFixString);
	}
	//dlgLoadProgress.SetPos(80);
	{
		CString		sSectionOption;
		sSectionOption = "haseta";
		MyWriteProfileInt(sSectionOption, sKeyID3v2GenreAddNumber, g_bOptID3v2GenreAddNumber ? 1 : 0);
		MyWriteProfileInt(sSectionOption, sKeyFileNameMaxCheck, g_bConfFileNameMaxCheck ? 1 : 0);
		MyWriteProfileInt(sSectionOption, sKeyFileNameMaxCellColor, g_bFileNameMaxCellColor ? 1 : 0);
		MyWriteProfileInt(sSectionOption, sKeyFileNameMaxChar, g_nConfFileNameMaxChar);
		MyWriteProfileInt(sSectionOption, sKeyDropSearchSubFolder, g_bOptDropSearchSubFolder ? 1 : 0); /* TyphoonSwell 026 */
		MyWriteProfileInt(sSectionOption, sKeyShowZenSpace, g_bOptShowZenSpace ? 1 : 0); /* BeachMonster 107 */
		//MyWriteProfileInt(sSectionOption, sKeyShowZenSpace, g_bOptShowZenSpace ? 1 : 0); /* BeachMonster 107 */
		MyWriteProfileInt(sSectionOption, sKeySortIgnoreCase, g_bOptSortIgnoreCase ? 1 : 0); /* BeachMonster4 114 */
		MyWriteProfileInt(sSectionOption, sKeySortIgnoreZenHan, g_bOptSortIgnoreZenHan ? 1 : 0); /* BeachMonster4 114 */
		MyWriteProfileInt(sSectionOption, sKeySortIgnoreKataHira, g_bOptSortIgnoreKataHira ? 1 : 0); /* FunnyCorn 179 */
		MyWriteProfileInt(sSectionOption, sKeyShowTotalParent, g_bOptShowTotalParent ? 1 : 0); /* RockDance 128 */
		MyWriteProfileInt(sSectionOption, sKeyShowTips, g_bOptShowTips ? 1 : 0); /* Rumble 188 */
	}
	//dlgLoadProgress.SetPos(85);
	// 定型文貼り付け /* SeaKnows 030 */
	for (int k=0;k<3;k++) {
		CString		sSectionOption;
		CString		strSectionName;
		sSectionOption = "haseta";
		strSectionName.Format("%s%d", sSectionTeikeiGroupName, k);
		MyWriteProfileString(sSectionOption, strSectionName, g_strTeikeiGroupName[k]);
		for (i = 0; i < 10; i++) {
			if (k == 0) {
				strSectionName.Format("%s%d", sSectionTeikei, i);
			} else {
				strSectionName.Format("%s%d-%d", sSectionTeikei, k, i);
			}
			MyWriteProfileString(sSectionOption, strSectionName, g_strTeikei[i+k*10]);
		}
	}

	// その他 /* SeaKnows 031,033 */
	{
		CString		strSectionName;
		strSectionName = "haseta";
		MyWriteProfileInt(strSectionName, sSectionValidFolderSelect, g_bValidFolderSelect ? 1 : 0);
		MyWriteProfileInt(strSectionName, sSectionValidDupExec, g_bValidDupExec ? 1 : 0); /* FreeFall 045 */
		MyWriteProfileInt(strSectionName, sSectionRecentFolderNum, g_nRecentFolder); /* MyWriteProfileInt 053 */
		MyWriteProfileInt(strSectionName, sSectionSaveRepDlgPos, g_bSaveRepDlgPos ? 1 : 0); /* WildCherry4 086 */
		MyWriteProfileInt(strSectionName, sSectionSaveRepDlgPosX, g_nSaveRepDlgPosX); /* WildCherry4 086 */
		MyWriteProfileInt(strSectionName, sSectionSaveRepDlgPosY, g_nSaveRepDlgPosY); /* WildCherry4 086 */
		MyWriteProfileInt(strSectionName, sSectionAddNumberWidth, g_nAddNumberWidth); /* Baja 159 */
		MyWriteProfileInt(strSectionName, sSectionAddNumberPos, g_nAddNumberPos); /* Baja 159 */
		MyWriteProfileString(strSectionName, sSectionAddNumberSep, g_strAddNumberSep); /* Baja 159 */
		MyWriteProfileString(strSectionName, sSectionAddNumberBef, g_strAddNumberBef); /* Conspiracy 194 */
		MyWriteProfileString(strSectionName, sSectionAddNumberAft, g_strAddNumberAft); /* Conspiracy 194 */
		MyWriteProfileInt(strSectionName, sSectionAudioListShow, g_bAudioListShow ? 1 : 0); /* Conspiracy 199 */
	}

	// リスト出力書式
	for (i = 0; i < WRITE_FORMAT_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format("%s%d", sSectionWriteFormat, i);
		// 名称
		MyWriteProfileString(strSectionName, sKeyWriteFormName, g_writeFormat[i].strName);
		// 書式ファイル名
		MyWriteProfileString(strSectionName, sKeyWriteFileName, g_writeFormat[i].strFileName);
		// 拡張子
		MyWriteProfileString(strSectionName, sKeyWriteExtName, g_writeFormat[i].strExtName);
		// 選択ファイルのみ出力
		MyWriteProfileInt(strSectionName, sKeyWriteSelected, g_writeFormat[i].bWriteSelected ? 1 : 0);
		// カレントファイル名
		MyWriteProfileString(strSectionName, sKeyWriteCurrentFile, g_writeFormat[i].strCurrentFile);
		// HTML ファイル出力用(空の場合に全角スペースを出力)
		MyWriteProfileInt(strSectionName, sKeyWriteIsHtml, g_writeFormat[i].bIsHtml ? 1 : 0);
		{ /* BeachMonster5 120 */
			MyWriteProfileInt("haseta\\" + strSectionName, sKeyWriteHtml, g_writeFormat[i].bWriteHtml ? 1 : 0);
		}
	}
	//dlgLoadProgress.SetPos(90);

	// 分類設定情報
	MyWriteProfileInt(sSectionClass, sKeyClassType, g_classInfo.nType);
	for (i = 0; i < CLASS_MAX; i++) {
		CString		strKeyName;
		// カラム番号
		strKeyName.Format("%s%d", sKeyClassColumn, i);
		MyWriteProfileInt(sSectionClass, strKeyName, g_classInfo.nColumn[i]);
	}

	// ソート情報
	for (i = 0; i < SORT_KEY_MAX; i++) {
		CString		strKeyName;
		SORT_STATE	*state = &g_sortState[i];
		// キー(カラム)
		strKeyName.Format("%s%d", sKeySortColumn, i);
		MyWriteProfileInt(sSectionSort, strKeyName, state->nKeyColumn);
		// タイプ
		strKeyName.Format("%s%d", sKeySortType, i);
		MyWriteProfileInt(sSectionSort, strKeyName, state->nType);
	}

	// ウィンドウのフォントを書き込む
	MyWriteProfileString(sSectionFont, sKeyFontFace, g_fontReport.lfFaceName);
	MyWriteProfileInt(sSectionFont, sKeyFontHeight		, g_fontReport.lfHeight);
	MyWriteProfileInt(sSectionFont, sKeyFontWidth 		, g_fontReport.lfWidth);
	MyWriteProfileInt(sSectionFont, sKeyFontEscapement	, g_fontReport.lfEscapement);
	MyWriteProfileInt(sSectionFont, sKeyFontOrientation	, g_fontReport.lfOrientation);
	MyWriteProfileInt(sSectionFont, sKeyFontWeight		, g_fontReport.lfWeight);
	MyWriteProfileInt(sSectionFont, sKeyFontItalic		, g_fontReport.lfItalic);
	MyWriteProfileInt(sSectionFont, sKeyFontUnderline 	, g_fontReport.lfUnderline);
	MyWriteProfileInt(sSectionFont, sKeyFontStrikeOut 	, g_fontReport.lfStrikeOut);
	MyWriteProfileInt(sSectionFont, sKeyFontCharSet		, g_fontReport.lfCharSet);
	MyWriteProfileInt(sSectionFont, sKeyFontOutPrecision	, g_fontReport.lfOutPrecision);
	MyWriteProfileInt(sSectionFont, sKeyFontClipPrecision , g_fontReport.lfClipPrecision);
	MyWriteProfileInt(sSectionFont, sKeyFontQuality		, g_fontReport.lfQuality);
	MyWriteProfileInt(sSectionFont, sKeyFontPitchAndFamily, g_fontReport.lfPitchAndFamily);

	//MyWriteProfileInt(sSectionOption, sKeyPlayerType, (int)g_nOptPlayerType);
	//MyWriteProfileString(sSectionOption, sKeyWinAmpPath, g_sOptWinAmpPath);
	{ /* 数を増やしたので本家併用時に影響を与えないように WildCherry 070 */
		CString		strSectionName;
		strSectionName = "haseta\\";
		strSectionName += sSectionOption;
		MyWriteProfileInt(strSectionName, sKeyPlayerType, (int)g_nOptPlayerType);
		MyWriteProfileString(strSectionName, sKeyWinAmpPath, g_sOptWinAmpPath);
	}
	//dlgLoadProgress.SetPos(95);

	// ウィンドウの状態を保存
	MyWriteProfileInt(sSectionWindow, sKeyWinZoomed, (int)g_bMainFrameZoomed);
	MyWriteProfileInt(sSectionWindow, sKeyWinIconic, (int)g_bMainFrameIconic);
	WriteWindowStatus(sKeyMainWindow, &g_rectMainWindow);

	// 文字種の統一 /* StartInaction 054 */
	{
		CString		strSectionName;
		strSectionName = "haseta";
		MyWriteProfileInt(strSectionName, sKeyUnifyAlpha, g_nUnifyAlpha);
		MyWriteProfileInt(strSectionName, sKeyUnifyHiraKata, g_nUnifyHiraKata);
		MyWriteProfileInt(strSectionName, sKeyUnifyKata, g_nUnifyKata);
		MyWriteProfileInt(strSectionName, sKeyUnifyKigou, g_nUnifyKigou);
		MyWriteProfileInt(strSectionName, sKeyUnifySuji, g_nUnifySuji);
		MyWriteProfileInt(strSectionName, sKeyUnifyUpLow, g_nUnifyUpLow);
	}

	// ファイル名文字種の統一 /* LastTrain 058 */
	{
		CString		strSectionName;
		strSectionName = "haseta";
		MyWriteProfileInt(strSectionName, sKeyFileUnifyAlpha, g_nFileUnifyAlpha);
		MyWriteProfileInt(strSectionName, sKeyFileUnifyHiraKata, g_nFileUnifyHiraKata);
		MyWriteProfileInt(strSectionName, sKeyFileUnifyKata, g_nFileUnifyKata);
		MyWriteProfileInt(strSectionName, sKeyFileUnifyKigou, g_nFileUnifyKigou);
		MyWriteProfileInt(strSectionName, sKeyFileUnifySuji, g_nFileUnifySuji);
		MyWriteProfileInt(strSectionName, sKeyFileUnifyUpLow, g_nFileUnifyUpLow);
	}
	// プレイリスト入力設定ダイアログを表示する /* RockDance 126 */
	{
		CString		strSectionName;
		strSectionName = "haseta";
		MyWriteProfileInt(strSectionName, sKeyShowLoadPlaylistDlg, g_bShowLoadPlaylistDlg ? 1 : 0);
	}
	//dlgLoadProgress.SetPos(100);
	// お気に入りのフォルダ /* RockDance 129 */
	{
		CString		sSectionOption;
		CString		strSectionName;
		sSectionOption = "haseta";
		for (i = 0; i < 10; i++) {
			strSectionName.Format("%s%d", sSectionFavorites, i);
			MyWriteProfileString(sSectionOption, strSectionName, g_strFavorite[i]);
		}
	}
	/*
	if (dlgLoadProgress.GetSafeHwnd() != NULL) {
		dlgLoadProgress.DestroyWindow();
		dlgLoadProgress.SetCanceled(FALSE);
	}
	*/
	SaveProfile();
//	FreeProfile();
//	m_pRecentFileList->WriteList();
}

void CSTEReg2IniDlg::OnOK()
{
	// TODO: この位置にその他の検証用のコードを追加してください
	//SetRegistryKey(_T("MERCURY"));
	//free((void *)m_pszAppName);
	//m_pszAppName = _strdup("SuperTagEditor");
	ReadRegistry();
	ReadKeyConfig(false);
	ReadCellStateControl();
	ReadGenreList();

	//CString strINI = "SuperTagEditor.ini";
	InitProfile();
	WriteGenreList();
	WriteCellStateControl();
	WriteKeyConfig(false);
	WriteRegistry();
	FreeProfile();

	delete [] g_genreListUSER;

	MessageBox(strINI + " を作成しました。","STEReg2Ini",MB_OK);
	//CDialog::OnOK();
}
