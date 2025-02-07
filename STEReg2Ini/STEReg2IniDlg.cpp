// STEReg2IniDlg.cpp : �C���v�������e�[�V���� �t�@�C��
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
// CSTEReg2IniDlg �_�C�A���O

CSTEReg2IniDlg::CSTEReg2IniDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSTEReg2IniDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSTEReg2IniDlg)
		// ����: ���̈ʒu�� ClassWizard �ɂ���ă����o�̏��������ǉ�����܂��B
	//}}AFX_DATA_INIT
	// ����: LoadIcon �� Win32 �� DestroyIcon �̃T�u�V�[�P���X��v�����܂���B
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSTEReg2IniDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSTEReg2IniDlg)
		// ����: ���̏ꏊ�ɂ� ClassWizard �ɂ���� DDX �� DDV �̌Ăяo�����ǉ�����܂��B
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSTEReg2IniDlg, CDialog)
	//{{AFX_MSG_MAP(CSTEReg2IniDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSTEReg2IniDlg ���b�Z�[�W �n���h��

BOOL CSTEReg2IniDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���̃_�C�A���O�p�̃A�C�R����ݒ肵�܂��B�t���[�����[�N�̓A�v���P�[�V�����̃��C��
	// �E�B���h�E���_�C�A���O�łȂ����͎����I�ɐݒ肵�܂���B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�

	// TODO: ���ʂȏ��������s�����͂��̏ꏊ�ɒǉ����Ă��������B

	return TRUE;  // TRUE ��Ԃ��ƃR���g���[���ɐݒ肵���t�H�[�J�X�͎����܂���B
}

// �����_�C�A���O�{�b�N�X�ɍŏ����{�^����ǉ�����Ȃ�΁A�A�C�R����`�悷��
// �R�[�h���ȉ��ɋL�q����K�v������܂��BMFC �A�v���P�[�V������ document/view
// ���f�����g���Ă���̂ŁA���̏����̓t���[�����[�N�ɂ�莩���I�ɏ�������܂��B

void CSTEReg2IniDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// �N���C�A���g�̋�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R����`�悵�܂��B
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// �V�X�e���́A���[�U�[���ŏ����E�B���h�E���h���b�O���Ă���ԁA
// �J�[�\����\�����邽�߂ɂ������Ăяo���܂��B
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
	FILENAME_NO_CHECK,				// �`�F�b�N���Ȃ�
	FILENAME_CONV_MULTIBYTE,		// �Q�o�C�g�����ɕϊ�
};

#define SORT_KEY_MAX		5
struct	SORT_STATE	{				// �\�[�g���
	int		nKeyColumn;				// �\�[�g�L�[(�J�����ԍ�)
	int		nType;					// �^�C�v(0:����/1:�~��)
};

#define CLASS_MAX			5		// ���ފK�w�̐[��(�ő�)
struct	CLASS_INFO	{				// ���ޏ��
	int		nType;					// ���ރ^�C�v
	int		nColumn[CLASS_MAX];		// �J�����ԍ�
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
	COLUMN_TRACK_NAME,		// �Ȗ�
	COLUMN_ARTIST_NAME,		// �A�[�e�B�X�g��
	COLUMN_ALBUM_NAME,		// �A���o�����^���i��
	COLUMN_TRACK_NUMBER,	// �g���b�N�ԍ�(ID3 tag v1.1�̂�)
	COLUMN_YEAR,			// �����[�X�N��
	COLUMN_GENRE,			// �W������
	COLUMN_COMMENT,			// �R�����g������
	COLUMN_COPYRIGHT,		// ���쌠
	COLUMN_ENGINEER,		// �G���W�j�A(�����)
	COLUMN_SOURCE,			// �\�[�X
	COLUMN_SOFTWARE,		// �\�t�g�E�F�A
	COLUMN_KEYWORD,			// �L�[���[�h
	COLUMN_TECHNICIAN,		// �Z�p��
	COLUMN_LYRIC,			// �̎�
	COLUMN_COMMISSION,		// �R�~�b�V����
	COLUMN_COMPOSER,		// ��� /* Baja 154 */
	COLUMN_ORIG_ARTIST,		// Orig.�A�[�e�B�X�g /* Baja 154 */
	COLUMN_URL,				// URL /* Baja 154 */
	COLUMN_ENCODEST,		// �G���R�[�h�����l /* Baja 154 */
	COLUMN_FILE_SIZE,		// �t�@�C���T�C�Y
	COLUMN_FILE_TIME,		// �t�@�C���^�C���X�^���v
	COLUMN_FILE_PATH,		// �t�@�C���p�X��
	COLUMN_PLAY_TIME,		// ���t����
	COLUMN_LYRIC_FILE,		// �̎��t�@�C��
	COLUMN_FILE_TYPE,		// �t�@�C���̎��
	COLUMN_FORMAT,			// �t�H�[�}�b�g /* Conspiracy 198 */
	COLUMN_OTHER,			// ���̑� /* Conspiracy 196 */
	COLUMN_FILE_CTIME,		// �t�@�C���쐬�� /* Hurricane 207 */
	COLUMN_MAX,
};


struct	KEY_CONFIG	{				// �L�[���蓖��
	WORD	wCmdID;					// ���j���[���\�[�X�h�c
	DWORD	dwKeyCode;				// �z�b�g�L�[
	int		nGroupID;				// �O���[�v��
	char	*sName;					// ���ږ�
	char	*sRegName;				// ���W�X�g����
};
extern	KEY_CONFIG	g_listKeyConfig[];

#define FILENAME_REPLACE_MAX		12
#define USER_FILENAME_REPLACE_MAX		6	/* FreeFall 050 */
struct	FILENAME_REPLACE {			// �t�@�C�����u��
	CString	strBefore;				// �u���O�̕���
	CString	strAfter;				// �u����̕���
};
const char *g_sRepTable[FILENAME_REPLACE_MAX][2] = {
	{"\"", "�h"}, {"*" , "��"}, {"," , "�C"}, {"/" , "�^"},
	{":" , "�F"}, {";" , "�G"}, {"<" , "��"}, {">" , "��"},
	{"?" , "�H"}, {"\\", "��"}, {"|" , "�b"}, {" " , " "},
};

#define USER_CONV_FORMAT_MAX		5 /*3 LastTrain 057 */
struct	USER_CONV_FORMAT	{		// ���[�U�[�ϊ�����
	CString	strName;				// ����
	CString	strTag2File;			// �����F�^�O��� => �t�@�C����
	CString	strFile2Tag;			// �����F�t�@�C���� => �^�O���
};

#define USER_CONV_FORMAT_EX_MAX		10
struct	USER_CONV_FORMAT_EX	{		// �g���Ń��[�U�[�ϊ�����
	CString	strName;				// ����
	CString	strFormat;				// ����
	CString	strFixString;			// �Œ蕶����
	int		nInitNumber;			// �A�ԁF�����l
	int		nAddNumber;				// �A�ԁF���Z�l
	int		nColumnCount;			// �A�ԁF����
	bool	bSpaceInitNumber;		// �������ݕs�̃Z���ŘA�ԃN���A
};

#define USER_MOVE_FODLER_FORMAT_MAX	5
struct	USER_MOVE_FODLER_FORMAT	{	// �ړ���t�H���_����
	CString	strName;				// ����
	CString	strFormat;				// ����
	CString	strFixString;			// �Œ蕶����
	bool	bCopy;					// �R�s�[����
};

/* FunnyCorn 175 */
#define USER_COPY_FORMAT_FORMAT_MAX	5
struct	USER_COPY_FORMAT_FORMAT	{	// �����R�s�[
	CString	strName;				// ����
	CString	strFormat;				// ����
	CString	strFixString;			// �Œ蕶����
};

#define WRITE_FORMAT_MAX			5
struct	WRITE_FORMAT	{			// �g���Ń��[�U�[�ϊ�����
	CString	strName;				// ����
	CString	strFileName;			// �����t�@�C��
	CString	strExtName;				// �g���q
	bool	bWriteSelected;			// �I���t�@�C���̂ݏ㏑��
	CString	strCurrentFile;			// �J�����g�t�@�C����
	bool	bIsHtml;				// HTML �t�@�C���o�͗p(��̏ꍇ�ɑS�p�X�y�[�X���o��)
	bool	bWriteHtml;				// HTML �t�@�C���Ƃ��ďo�́i�^�O��u������j/* BeachMonster5 120 */
};

struct	CHECK_WORD_STATE	{		// �����`�F�b�N�p�̏��
	CString	strSearchWord;			// ����������
	CString	strReplaceWord;			// �u��������
	int		nTargetColumn;			// �����ΏۃJ����
	BOOL	bCheckDiffUL;			// �啶���^�������̋��
	BOOL	bRegExp;				// ���K�\��
	BOOL	bRangeSelected;			// �I��͈͂̂�
	BOOL	bMatchComplete;			// ���S�Ɉ�v
	BOOL	bMatchSelected;			// �`�F�b�N�����ɑI����Ԃɂ���
	int		nMatchColumn;			// (�o��)�������ʁF��v�����J����
	int		nMatchPos;				// (�o��)�������ʁF��v�����ʒu
	int		nMatchLength;			// (�o��)�������ʁF��v��������
	CRegExp	regexp;					// ���K�\���N���X(���������p)
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

// ���[�U�[�����ϊ�
static	char	*sSectionUserConvFormat	= "UserConvFormat";
static	char	*sKeyConvFormatType		= "ConvFormatType";
static	char	*sKeyUserFormName		= "Name";
static	char	*sKeyUserFormTag2File	= "TagToFile";
static	char	*sKeyUserFormFile2Tag	= "FileToTag";

// �g���ŏ����ϊ�
static	char	*sSectionConvFormatEx	= "ConvFormatEx";
//static	char	*sKeyUserFormName		= "Name";
static	char	*sKeyUserFormat			= "Format";
static	char	*sKeyUserFixString		= "FixString";
static	char	*sKeyUserInitNumber		= "InitNumber";
static	char	*sKeyUserAddNumber		= "AddNumber";
static	char	*sKeyUserColumnCount	= "ColumnCount";
static	char	*sKeyUserSpaceInit		= "SpaceInit";

// �ړ���t�H���_����
static	char	*sSectionMoveFolder		= "MoveFolderFormat";
//static	char	*sKeyUserFormName		= "Name";
static	char	*sKeyMoveFolderFormat	= "Format";
static	char	*sKeyMoveFolderFixString	= "FixString";
static	char	*sKeyMoveFolderCopy		= "Copy";

// �����R�s�[ /* FunnyCorn 175 */
static	char	*sSectionCopyFormat		= "CopyFormatFormat";
//static	char	*sKeyUserFormName		= "Name";
static	char	*sKeyCopyFormatFormat	= "Format";
static	char	*sKeyCopyFormatFixString	= "FixString";

// ��^���\��t�� /* SeaKnows 030 */
static	char	*sSectionTeikei			= "Teikei";
static	char	*sSectionTeikeiGroupName	= "TeikeiGroupName";

// �\�t�g�E�F�A /* SeaKnows 030 */
static	char	*sSectionSoftwareTag	= "SoftwareTag";
// �t�H���_�P��I�� /* SeaKnows 033 */
static	char	*sSectionValidFolderSelect	= "ValidFolderSelect";
// ���d�N���������� /* FreeFall 045 */
static	char	*sSectionValidDupExec	= "ValidDupExec";
// �ŋߎg�����t�H���_�̐�
static	char	*sSectionRecentFolderNum	= "RecentFolderNum";
// �����E�u���_�C�A���O�̈ʒu���L������
static	char	*sSectionSaveRepDlgPos	= "SaveRepDlgPos";
static	char	*sSectionSaveRepDlgPosX	= "SaveRepDlgPosX";
static	char	*sSectionSaveRepDlgPosY	= "SaveRepDlgPosY";
// �������ɘA�Ԃ�ǉ��_�C�A���O�̐ݒ� /* Baja 159 */
static	char	*sSectionAddNumberWidth = "AddNumberWidth";
static	char	*sSectionAddNumberPos	= "AddNumberPos";
static	char	*sSectionAddNumberSep	= "AddNumberSep";
static	char	*sSectionAddNumberBef	= "AddNumberBef"; /* Conspiracy 194 */
static	char	*sSectionAddNumberAft	= "AddNumberAft"; /* Conspiracy 194 */
// ID3v2�̃R�����g�^�O���Â��`���ŕۑ����� /* FunnyCorn 180 */
static	char	*sSectiongId3v2OldComment	= "Id3v2OldComment";
// ID3v2��UNICODE�ŕۑ����� /* FunnyCorn 181 */
static	char	*sSectiongId3v2UNICODE	= "Id3v2UNICODE";
// Audio List�ɕ\�������t�H���_���Ȃǂ̕��ނ��Z���T�C�Y�𖳎�����(���ۂׂ͗R�Z�����܂�)�\������
static	char	*sSectionAudioListShow	= "AudioListShow"; /* Conspiracy 199 */

// �t�H���g�ݒ�
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

// ���X�g�o�͏���
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

// �����퓝�� /* StartInaction 054 */
static	char	*sKeyUnifyAlpha	= "UnifyAlpha";
static	char	*sKeyUnifyHiraKata	= "UnifyHiraKata";
static	char	*sKeyUnifyKata	= "UnifyKata";
static	char	*sKeyUnifyKigou	= "UnifyKigou";
static	char	*sKeyUnifySuji	= "UnifySuji";
static	char	*sKeyUnifyUpLow	= "UnifyUpLow";

// �t�@�C���������퓝�� /* LastTrain 058 */
static	char	*sKeyFileUnifyAlpha	= "FileUnifyAlpha";
static	char	*sKeyFileUnifyHiraKata	= "FileUnifyHiraKata";
static	char	*sKeyFileUnifyKata	= "FileUnifyKata";
static	char	*sKeyFileUnifyKigou	= "FileUnifyKigou";
static	char	*sKeyFileUnifySuji	= "FileUnifySuji";
static	char	*sKeyFileUnifyUpLow	= "FileUnifyUpLow";

// �v���C���X�g���͐ݒ�_�C�A���O��\������ /* RockDance 126 */
static	char	*sKeyShowLoadPlaylistDlg = "ShowLoadPlaylistDlg";

// ���C�ɓ���̃t�H���_ /* RockDance 129 */
static	char	*sSectionFavorites			= "Favorites";

// �Ώۂ̊g���q
static	char	*sKeyValidAllFile	= "ValidAllFile"; /* Conspiracy 195 */



RECT		g_rectMainWindow;		// ���C���E�B���h�E�̍��W
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
CString		g_sOptShowOtherChar; /* BeachMonster 107 */ // �Ƃ肠��������Ƃ�
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

// �����퓝�� /* StartInaction 054 */
UINT		g_nUnifyAlpha;
UINT		g_nUnifyHiraKata;
UINT		g_nUnifyKata;
UINT		g_nUnifyKigou;
UINT		g_nUnifySuji;
UINT		g_nUnifyUpLow;

// �t�@�C���������퓝�� /* LastTrain 058 */
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

LOGFONT		g_fontReport;			// ���|�[�g�E�B���h�E�̃t�H���g

FILENAME_REPLACE	g_fileNameReplace[FILENAME_REPLACE_MAX];

FILENAME_REPLACE	g_userFileNameReplace[USER_FILENAME_REPLACE_MAX];	/* FreeFall 050 */

struct	GENRE_LIST	{		// �W���������X�g
	bool	bAddList;		// ���X�g�ɒǉ����邩�ǂ���
	BYTE	byGenre;		// �W�������ԍ�
	char	*sName;			// �W��������(NULL:���X�g�I�[)
};
struct	USER_GENRE_LIST	{	// ���[�U�W���������X�g
	bool	bAddList;		// ���X�g�ɒǉ����邩�ǂ���
	BYTE	byGenre;		// �W�������ԍ�
	CString	sName;			// �W��������
	bool	bUse;
};

GENRE_LIST	g_genreListSCMPX[] = {
	{true,   0, "Blues"},					// 0(ID3 Tag�݊�)
	{true,   1, "Classic Rock"},			// 1(ID3 Tag�݊�)
	{true,   2, "Country"},					// 2(ID3 Tag�݊�)
	{true,   3, "Dance"},					// 3(ID3 Tag�݊�)
	{true,   4, "Disco"},					// 4(ID3 Tag�݊�)
	{true,   5, "Funk"},					// 5(ID3 Tag�݊�)
	{true,   6, "Grunge"},					// 6(ID3 Tag�݊�)
	{true,   7, "Hip-Hop"},					// 7(ID3 Tag�݊�)
	{true,   8, "Jazz"},					// 8(ID3 Tag�݊�)
	{true,   9, "Metal"},					// 9(ID3 Tag�݊�)
	{true,  10, "New Age"},					// 10(ID3 Tag�݊�)
	{true,  11, "Oldies"},					// 11(ID3 Tag�݊�)
	{true,  12, "Other"},					// 12(ID3 Tag�݊�)
	{true,  13, "Pop"},						// 13(ID3 Tag�݊�)
	{true,  14, "R&B"},						// 14(ID3 Tag�݊�)
	{true,  15, "Rap"},						// 15(ID3 Tag�݊�)
	{true,  16, "Reggae"},					// 16(ID3 Tag�݊�)
	{true,  17, "Rock"},					// 17(ID3 Tag�݊�)
	{true,  18, "Techno"},					// 18(ID3 Tag�݊�)
	{true,  19, "Industrial"},				// 19(ID3 Tag�݊�)
	{true,  20, "Alternative"},				// 20(ID3 Tag�݊�)
	{true,  21, "Ska"},						// 21(ID3 Tag�݊�)
	{true,  22, "Death Metal"},				// 22(ID3 Tag�݊�)
	{true,  23, "Pranks"},					// 23(ID3 Tag�݊�)
	{true,  24, "Soundtrack"},				// 24(ID3 Tag�݊�)
	{true,  25, "Euro-Techno"},				// 25(ID3 Tag�݊�)
	{true,  26, "Ambient"},					// 26(ID3 Tag�݊�)
	{true,  27, "Trip-Hop"},				// 27(ID3 Tag�݊�)
	{true,  28, "Vocal"},					// 28(ID3 Tag�݊�)
	{true,  29, "Jazz+Funk"},				// 29(ID3 Tag�݊�)
	{true,  30, "Fusion"},					// 30(ID3 Tag�݊�)
	{true,  31, "Trance"},					// 31(ID3 Tag�݊�)
	{true,  32, "Classical"},				// 32(ID3 Tag�݊�)
	{true,  33, "Instrumental"},			// 33(ID3 Tag�݊�)
	{true,  34, "Acid"},					// 34(ID3 Tag�݊�)
	{true,  35, "House"},					// 35(ID3 Tag�݊�)
	{true,  36, "Game"},					// 36(ID3 Tag�݊�)
	{true,  37, "Sound Clip"},				// 37(ID3 Tag�݊�)
	{true,  38, "Gospel"},					// 38(ID3 Tag�݊�)
	{true,  39, "Noise"},					// 39(ID3 Tag�݊�)
	{true,  40, "AlternRock"},				// 40(ID3 Tag�݊�)
	{true,  41, "Bass"},					// 41(ID3 Tag�݊�)
	{true,  42, "Soul"},					// 42(ID3 Tag�݊�)
	{true,  43, "Punk"},					// 43(ID3 Tag�݊�)
	{true,  44, "Space"},					// 44(ID3 Tag�݊�)
	{true,  45, "Meditative"},				// 45(ID3 Tag�݊�)
	{true,  46, "Instrumental Pop"},		// 46(ID3 Tag�݊�)
	{true,  47, "Instrumental Rock"},		// 47(ID3 Tag�݊�)
	{true,  48, "Ethnic"},					// 48(ID3 Tag�݊�)
	{true,  49, "Gothic"},					// 49(ID3 Tag�݊�)
	{true,  50, "Darkwave"},				// 50(ID3 Tag�݊�)
	{true,  51, "Techno-Industrial"},		// 51(ID3 Tag�݊�)
	{true,  52, "Electronic"},				// 52(ID3 Tag�݊�)
	{true,  53, "Pop-Folk"},				// 53(ID3 Tag�݊�)
	{true,  54, "Eurodance"},				// 54(ID3 Tag�݊�)
	{true,  55, "Dream"},					// 55(ID3 Tag�݊�)
	{true,  56, "Southern Rock"},			// 56(ID3 Tag�݊�)
	{true,  57, "Comedy"},					// 57(ID3 Tag�݊�)
	{true,  58, "Cult"},					// 58(ID3 Tag�݊�)
	{true,  59, "Gangsta"},					// 59(ID3 Tag�݊�)
	{true,  60, "Top 40"},					// 60(ID3 Tag�݊�)
	{true,  61, "Christian Rap"},			// 61(ID3 Tag�݊�)
	{true,  62, "Pop/Funk"},				// 62(ID3 Tag�݊�)
	{true,  63, "Jungle"},					// 63(ID3 Tag�݊�)
	{true,  64, "Native American"},			// 64(ID3 Tag�݊�)
	{true,  65, "Cabaret"},					// 65(ID3 Tag�݊�)
	{true,  66, "New Wave"},				// 66(ID3 Tag�݊�)
	{true,  67, "Psychedelic"},				// 67(ID3 Tag�݊�)
	{true,  68, "Rave"},					// 68(ID3 Tag�݊�)
	{true,  69, "Showtunes"},				// 69(ID3 Tag�݊�)
	{true,  70, "Trailer"},					// 70(ID3 Tag�݊�)
	{true,  71, "Lo-Fi"},					// 71(ID3 Tag�݊�)
	{true,  72, "Tribal"},					// 72(ID3 Tag�݊�)
	{true,  73, "Acid Punk"},				// 73(ID3 Tag�݊�)
	{true,  74, "Acid Jazz"},				// 74(ID3 Tag�݊�)
	{true,  75, "Polka"},					// 75(ID3 Tag�݊�)
	{true,  76, "Retro"},					// 76(ID3 Tag�݊�)
	{true,  77, "Musical"},					// 77(ID3 Tag�݊�)
	{true,  78, "Rock & Roll"},				// 78(ID3 Tag�݊�)
	{true,  79, "Hard Rock"},				// 79(ID3 Tag�݊�)
	{true,  80, "Folk"},					// 80(ID3 Tag�݊�)
	{true,  81, "Folk/Rock"},				// 81(ID3 Tag�݊�)
	{true,  82, "National Folk"},			// 82(ID3 Tag�݊�)
	{true,  83, "Swing"},					// 83(ID3 Tag�݊�)
	{true,  84, "Fast-Fusion"},				// 84(Winamp�݊�)
	{true,  85, "Bebob"},					// 85(Winamp�݊�)
	{true,  86, "Latin"},					// 86(Winamp�݊�)
	{true,  87, "Revival"},					// 87(Winamp�݊�)
	{true,  88, "Celtic"},					// 88(Winamp�݊�)
	{true,  89, "Bluegrass"},				// 89(Winamp�݊�)
	{true,  90, "Avantgarde"},				// 90(Winamp�݊�)
	{true,  91, "Gothic Rock"},				// 91(Winamp�݊�)
	{true,  92, "Progressive Rock"},		// 92(Winamp�݊�)
	{true,  93, "Psychedelic Rock"},		// 93(Winamp�݊�)
	{true,  94, "Symphonic Rock"},			// 94(Winamp�݊�)
	{true,  95, "Slow Rock"},				// 95(Winamp�݊�)
	{true,  96, "Big Band"},				// 96(Winamp�݊�)
	{true,  97, "Chorus"},					// 97(Winamp�݊�)
	{true,  98, "Easy Listening"},			// 98(Winamp�݊�)
	{true,  99, "Acoustic"},				// 99(Winamp�݊�)
	{true, 100, "Humour"},					// 100(Winamp�݊�)
	{true, 101, "Speech"},					// 101(Winamp�݊�)
	{true, 102, "Chanson"},					// 102(Winamp�݊�)
	{true, 103, "Opera"},					// 103(Winamp�݊�)
	{true, 104, "Chamber Music"},			// 104(Winamp�݊�)
	{true, 105, "Sonata"},					// 105(Winamp�݊�)
	{true, 106, "Symphony"},				// 106(Winamp�݊�)
	{true, 107, "Booty Bass"},				// 107(Winamp�݊�)
	{true, 108, "Primus"},					// 108(Winamp�݊�)
	{true, 109, "Porn Groove"},				// 109(Winamp�݊�)
	{true, 110, "Satire"},					// 110(Winamp�݊�)
	{true, 111, "Slow Jam"},				// 111(Winamp�݊�)
	{true, 112, "Club"},					// 112(Winamp�݊�)
	{true, 113, "Tango"},					// 113(Winamp�݊�)
	{true, 114, "Samba"},					// 114(Winamp�݊�)
	{true, 115, "Folklore"},				// 115(Winamp�݊�)
	{true, 116, "Ballad"},					// 116(Winamp�݊�)
	{true, 117, "Power Ballad"},			// 117(Winamp�݊�)
	{true, 118, "Phythmic Soul"},			// 118(Winamp�݊�)
	{true, 119, "Freestyle"},				// 119(Winamp�݊�)
	{true, 120, "Duet"},					// 120(Winamp�݊�)
	{true, 121, "Punk Rock"},				// 121(Winamp�݊�)
	{true, 122, "Drum Solo"},				// 122(Winamp�݊�)
	{true, 123, "A Cappella"},				// 123(Winamp�݊�)
	{true, 124, "Euro-House"},				// 124(Winamp�݊�)
	{true, 125, "Dance Hall"},				// 125(Winamp�݊�)
	{true, 126, "Goa"},						// 126(Winamp�݊�)
	{true, 127, "Drum & Bass"},				// 127(Winamp�݊�)
	{true, 128, "Club-House"},				// 128(Winamp�݊�)
	{true, 129, "Hardcore"},				// 129(Winamp�݊�)
	{true, 130, "Terror"},					// 130(Winamp�݊�)
	{true, 131, "Indie"},					// 131(Winamp�݊�)
	{true, 132, "BritPop"},					// 132(Winamp�݊�)
	{true, 133, "Negerpunk"},				// 133(Winamp�݊�)
	{true, 134, "Polsk Punk"},				// 134(Winamp�݊�)
	{true, 135, "Beat"},					// 135(Winamp�݊�)
	{true, 136, "Christian Gangsta Rap"},	// 136(Winamp�݊�)
	{true, 137, "Heavy Metal"},				// 137(Winamp�݊�)
	{true, 138, "Black Metal"},				// 138(Winamp�݊�)
	{true, 139, "Crossover"},				// 139(Winamp�݊�)
	{true, 140, "Contemporary Christian"},	// 140(Winamp�݊�)
	{true, 141, "Christian Rock"},			// 141(Winamp�݊�)
	{true, 142, "Merengue"},				// 142(Winamp�݊�)
	{true, 143, "Salsa"},					// 143(Winamp�݊�)
	{true, 144, "Thrash Metal"},			// 144(Winamp�݊�)
	{true, 145, "Anime"},					// 145(Winamp�݊�)
	{true, 146, "JPop"},					// 146(Winamp�݊�)
	{true, 147, "Synthpop"},				// 147(Winamp�݊�)
	{false, 148, "����`(148)"},			// 148
	{false, 148, "����`(148)"},			// 148
	{false, 149, "����`(149)"},			// 149
	{false, 150, "����`(150)"},			// 150
	{false, 151, "����`(151)"},			// 151
	{false, 152, "����`(152)"},			// 152
	{false, 153, "����`(153)"},			// 153
	{false, 154, "����`(154)"},			// 154
	{false, 155, "����`(155)"},			// 155
	{false, 156, "����`(156)"},			// 156
	{false, 157, "����`(157)"},			// 157
	{false, 158, "����`(158)"},			// 158
	{false, 159, "����`(159)"},			// 159
	{false, 160, "����`(160)"},			// 160
	{false, 161, "����`(161)"},			// 161
	{false, 162, "����`(162)"},			// 162
	{false, 163, "����`(163)"},			// 163
	{false, 164, "����`(164)"},			// 164
	{false, 165, "����`(165)"},			// 165
	{false, 166, "����`(166)"},			// 166
	{false, 167, "����`(167)"},			// 167
	{false, 168, "����`(168)"},			// 168
	{false, 169, "����`(169)"},			// 169
	{false, 170, "����`(170)"},			// 170
	{false, 171, "����`(171)"},			// 171
	{false, 172, "����`(172)"},			// 172
	{false, 173, "����`(173)"},			// 173
	{false, 174, "����`(174)"},			// 174
	{false, 175, "����`(175)"},			// 175
	{false, 176, "����`(176)"},			// 176
	{false, 177, "����`(177)"},			// 177
	{false, 178, "����`(178)"},			// 178
	{false, 179, "����`(179)"},			// 179
	{false, 180, "����`(180)"},			// 180
	{false, 181, "����`(181)"},			// 181
	{false, 182, "����`(182)"},			// 182
	{false, 183, "����`(183)"},			// 183
	{false, 184, "����`(184)"},			// 184
	{false, 185, "����`(185)"},			// 185
	{false, 186, "����`(186)"},			// 186
	{false, 187, "����`(187)"},			// 187
	{false, 188, "����`(188)"},			// 188
	{false, 189, "����`(189)"},			// 189
	{false, 190, "����`(190)"},			// 190
	{false, 191, "����`(191)"},			// 191
	{false, 192, "����`(192)"},			// 192
	{false, 193, "����`(193)"},			// 193
	{false, 194, "����`(194)"},			// 194
	{false, 195, "����`(195)"},			// 195
	{false, 196, "����`(196)"},			// 196
	{false, 197, "����`(197)"},			// 197
	{false, 198, "����`(198)"},			// 198
	{false, 199, "����`(199)"},			// 199
	{false, 200, "����`(200)"},			// 200
	{false, 201, "����`(201)"},			// 201
	{false, 202, "����`(202)"},			// 202
	{false, 203, "����`(203)"},			// 203
	{false, 204, "����`(204)"},			// 204
	{false, 205, "����`(205)"},			// 205
	{false, 206, "����`(206)"},			// 206
	{false, 207, "����`(207)"},			// 207
	{false, 208, "����`(208)"},			// 208
	{false, 209, "����`(209)"},			// 209
	{false, 210, "����`(210)"},			// 210
	{false, 211, "����`(211)"},			// 211
	{false, 212, "����`(212)"},			// 212
	{false, 213, "����`(213)"},			// 213
	{false, 214, "����`(214)"},			// 214
	{false, 215, "����`(215)"},			// 215
	{false, 216, "����`(216)"},			// 216
	{false, 217, "����`(217)"},			// 217
	{false, 218, "����`(218)"},			// 218
	{false, 219, "����`(219)"},			// 219
	{false, 220, "����`(220)"},			// 220
	{false, 221, "����`(221)"},			// 221
	{false, 222, "����`(222)"},			// 222
	{false, 223, "����`(223)"},			// 223
	{false, 224, "����`(224)"},			// 224
	{false, 225, "����`(225)"},			// 225
	{false, 226, "����`(226)"},			// 226
	{false, 227, "����`(227)"},			// 227
	{false, 228, "����`(228)"},			// 228
	{false, 229, "����`(229)"},			// 229
	{false, 230, "����`(230)"},			// 230
	{false, 231, "����`(231)"},			// 231
	{false, 232, "����`(232)"},			// 232
	{false, 233, "����`(233)"},			// 233
	{false, 234, "����`(234)"},			// 234
	{false, 235, "����`(235)"},			// 235
	{false, 236, "����`(236)"},			// 236
	{false, 237, "����`(237)"},			// 237
	{false, 238, "����`(238)"},			// 238
	{false, 239, "����`(239)"},			// 239
	{false, 240, "����`(240)"},			// 240
	{false, 241, "����`(241)"},			// 241
	{false, 242, "����`(242)"},			// 242
	{false, 243, "����`(243)"},			// 243
	{false, 244, "����`(244)"},			// 244
	{false, 245, "����`(245)"},			// 245
	{false, 246, "����`(246)"},			// 246
	{false, 247, "����`(247)"},			// 247
	{false, 248, "Heavy Rock(J)"},			// 248(SCMPX�݊�)
	{false, 249, "Doom Rock(J)"},			// 249(SCMPX�݊�)
	{false, 250, "J-POP(J)"},				// 250(SCMPX�݊�)
	{false, 251, "Seiyu(J)"},				// 251(SCMPX�݊�)
	{false, 252, "Tecno Ambient(J)"},		// 252(SCMPX�݊�)
	{false, 253, "Moemoe(J)"},				// 253(SCMPX�݊�)
	{false, 254, "Tokusatsu(J)"},			// 254(SCMPX�݊�)
	{false, 255, "Anime(J)/���w��"},		// 255(SCMPX�݊�)
	{false, 255, NULL},						// �I�[�R�[�h
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
	// �t�@�C������
	{ID_FILE_NEW                  , 0x00000000, COMMAND_GROUP_FILE, "���X�g���N���A", "FileNew"},
	{ID_OPEN_FOLDER               , HK_CTRL_O , COMMAND_GROUP_FILE, "�t�H���_���J��", "FileOpenFolder"},
	{ID_SAVE_ALL_TAG              , HK_CTRL_S , COMMAND_GROUP_FILE, "�^�O�����X�V", "FileSaveAllTag"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_FILE, "--------------------", NULL},
	{ID_WRITE_LIST1               , 0x00000000, COMMAND_GROUP_FILE, "���X�g�o�́F�����P", "WriteList1"},
	{ID_WRITE_LIST2               , 0x00000000, COMMAND_GROUP_FILE, "���X�g�o�́F�����Q", "WriteList2"},
	{ID_WRITE_LIST3               , 0x00000000, COMMAND_GROUP_FILE, "���X�g�o�́F�����R", "WriteList3"},
	{ID_WRITE_LIST4               , 0x00000000, COMMAND_GROUP_FILE, "���X�g�o�́F�����S", "WriteList4"},
	{ID_WRITE_LIST5               , 0x00000000, COMMAND_GROUP_FILE, "���X�g�o�́F�����T", "WriteList5"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_FILE, "--------------------", NULL},
	{ID_MOVE_FOLDER_01            , 0x00000000, COMMAND_GROUP_FILE, "�t�@�C���ړ��F�����P", "MoveFolder1"},
	{ID_MOVE_FOLDER_02            , 0x00000000, COMMAND_GROUP_FILE, "�t�@�C���ړ��F�����Q", "MoveFolder2"},
	{ID_MOVE_FOLDER_03            , 0x00000000, COMMAND_GROUP_FILE, "�t�@�C���ړ��F�����R", "MoveFolder3"},
	{ID_MOVE_FOLDER_04            , 0x00000000, COMMAND_GROUP_FILE, "�t�@�C���ړ��F�����S", "MoveFolder4"},
	{ID_MOVE_FOLDER_05            , 0x00000000, COMMAND_GROUP_FILE, "�t�@�C���ړ��F�����T", "MoveFolder5"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_FILE, "--------------------", NULL},
	{ID_FAVORITE_FOLDER_01        , 0x00000000, COMMAND_GROUP_FILE, "���C�ɓ���̃t�H���_�F���C�ɓ���P", "FavoriteFolder1"},
	{ID_FAVORITE_FOLDER_02        , 0x00000000, COMMAND_GROUP_FILE, "���C�ɓ���̃t�H���_�F���C�ɓ���Q", "FavoriteFolder2"},
	{ID_FAVORITE_FOLDER_03        , 0x00000000, COMMAND_GROUP_FILE, "���C�ɓ���̃t�H���_�F���C�ɓ���R", "FavoriteFolder3"},
	{ID_FAVORITE_FOLDER_04        , 0x00000000, COMMAND_GROUP_FILE, "���C�ɓ���̃t�H���_�F���C�ɓ���S", "FavoriteFolder4"},
	{ID_FAVORITE_FOLDER_05        , 0x00000000, COMMAND_GROUP_FILE, "���C�ɓ���̃t�H���_�F���C�ɓ���T", "FavoriteFolder5"},
	{ID_FAVORITE_FOLDER_06        , 0x00000000, COMMAND_GROUP_FILE, "���C�ɓ���̃t�H���_�F���C�ɓ���U", "FavoriteFolder6"},
	{ID_FAVORITE_FOLDER_07        , 0x00000000, COMMAND_GROUP_FILE, "���C�ɓ���̃t�H���_�F���C�ɓ���V", "FavoriteFolder7"},
	{ID_FAVORITE_FOLDER_08        , 0x00000000, COMMAND_GROUP_FILE, "���C�ɓ���̃t�H���_�F���C�ɓ���W", "FavoriteFolder8"},
	{ID_FAVORITE_FOLDER_09        , 0x00000000, COMMAND_GROUP_FILE, "���C�ɓ���̃t�H���_�F���C�ɓ���X", "FavoriteFolder9"},
	{ID_FAVORITE_FOLDER_10        , 0x00000000, COMMAND_GROUP_FILE, "���C�ɓ���̃t�H���_�F���C�ɓ���10", "FavoriteFolder10"},

	// �ҏW����
	{ID_EDIT_COPY                 , HK_CTRL_C , COMMAND_GROUP_EDIT, "�R�s�["  , "EditCopy"},
	{ID_EDIT_PASTE                , HK_CTRL_V , COMMAND_GROUP_EDIT, "�\��t��", "EditPaste"},
	{ID_EDIT_CUT                  , HK_CTRL_X , COMMAND_GROUP_EDIT, "�؂���", "EditCut"},
	{ID_EDIT_PASTE_ADD            , 0x00000000, COMMAND_GROUP_EDIT, "�ǉ��œ\��t��", "EditPasteAdd"}, /* FunnyCorn 176 */
	{0x0000                       , 0x00000000, COMMAND_GROUP_EDIT, "----- ��^�� �O���[�v�P -----", NULL},
	{ID_TEIKEI_01                 , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���P-�P", "TeikeiPaste1-1"}, /* SeaKnows 030 */
	{ID_TEIKEI_02                 , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���P-�Q", "TeikeiPaste1-2"}, /* SeaKnows 030 */
	{ID_TEIKEI_03                 , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���P-�R", "TeikeiPaste1-3"}, /* SeaKnows 030 */
	{ID_TEIKEI_04                 , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���P-�S", "TeikeiPaste1-4"}, /* SeaKnows 030 */
	{ID_TEIKEI_05                 , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���P-�T", "TeikeiPaste1-5"}, /* SeaKnows 030 */
	{ID_TEIKEI_06                 , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���P-�U", "TeikeiPaste1-6"}, /* SeaKnows 030 */
	{ID_TEIKEI_07                 , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���P-�V", "TeikeiPaste1-7"}, /* SeaKnows 030 */
	{ID_TEIKEI_08                 , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���P-�W", "TeikeiPaste1-8"}, /* SeaKnows 030 */
	{ID_TEIKEI_09                 , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���P-�X", "TeikeiPaste1-9"}, /* SeaKnows 030 */
	{ID_TEIKEI_10                 , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���P-�P�O", "TeikeiPaste1-10"}, /* SeaKnows 030 */
	{0x0000                       , 0x00000000, COMMAND_GROUP_EDIT, "----- ��^�� �O���[�v�Q -----", NULL},
	{ID_TEIKEI_2_01               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���Q-�P", "TeikeiPaste2-1"}, /* FreeFall 046 */
	{ID_TEIKEI_2_02               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���Q-�Q", "TeikeiPaste2-2"}, /* FreeFall 046 */
	{ID_TEIKEI_2_03               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���Q-�R", "TeikeiPaste2-3"}, /* FreeFall 046 */
	{ID_TEIKEI_2_04               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���Q-�S", "TeikeiPaste2-4"}, /* FreeFall 046 */
	{ID_TEIKEI_2_05               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���Q-�T", "TeikeiPaste2-5"}, /* FreeFall 046 */
	{ID_TEIKEI_2_06               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���Q-�U", "TeikeiPaste2-6"}, /* FreeFall 046 */
	{ID_TEIKEI_2_07               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���Q-�V", "TeikeiPaste2-7"}, /* FreeFall 046 */
	{ID_TEIKEI_2_08               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���Q-�W", "TeikeiPaste2-8"}, /* FreeFall 046 */
	{ID_TEIKEI_2_09               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���Q-�X", "TeikeiPaste2-9"}, /* FreeFall 046 */
	{ID_TEIKEI_2_10               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���Q-�P�O", "TeikeiPaste2-10"}, /* FreeFall 046 */
	{0x0000                       , 0x00000000, COMMAND_GROUP_EDIT, "----- ��^�� �O���[�v�R -----", NULL},
	{ID_TEIKEI_3_01               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���R-�P", "TeikeiPaste3-1"}, /* FreeFall 046 */
	{ID_TEIKEI_3_02               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���R-�Q", "TeikeiPaste3-2"}, /* FreeFall 046 */
	{ID_TEIKEI_3_03               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���R-�R", "TeikeiPaste3-3"}, /* FreeFall 046 */
	{ID_TEIKEI_3_04               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���R-�S", "TeikeiPaste3-4"}, /* FreeFall 046 */
	{ID_TEIKEI_3_05               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���R-�T", "TeikeiPaste3-5"}, /* FreeFall 046 */
	{ID_TEIKEI_3_06               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���R-�U", "TeikeiPaste3-6"}, /* FreeFall 046 */
	{ID_TEIKEI_3_07               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���R-�V", "TeikeiPaste3-7"}, /* FreeFall 046 */
	{ID_TEIKEI_3_08               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���R-�W", "TeikeiPaste3-8"}, /* FreeFall 046 */
	{ID_TEIKEI_3_09               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���R-�X", "TeikeiPaste3-9"}, /* FreeFall 046 */
	{ID_TEIKEI_3_10               , 0x00000000, COMMAND_GROUP_EDIT, "��^���\��t���R-�P�O", "TeikeiPaste3-10"}, /* FreeFall 046 */
	{0x0000                       , 0x00000000, COMMAND_GROUP_FILE, "--------------------", NULL},
	{ID_EDIT_COPY_FORMAT_01       , 0x00000000, COMMAND_GROUP_FILE, "�����R�s�[�F�����P", "CopyFormat1"},
	{ID_EDIT_COPY_FORMAT_02       , 0x00000000, COMMAND_GROUP_FILE, "�����R�s�[�F�����Q", "CopyFormat2"},
	{ID_EDIT_COPY_FORMAT_03       , 0x00000000, COMMAND_GROUP_FILE, "�����R�s�[�F�����R", "CopyFormat3"},
	{ID_EDIT_COPY_FORMAT_04       , 0x00000000, COMMAND_GROUP_FILE, "�����R�s�[�F�����S", "CopyFormat4"},
	{ID_EDIT_COPY_FORMAT_05       , 0x00000000, COMMAND_GROUP_FILE, "�����R�s�[�F�����T", "CopyFormat5"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_EDIT, "--------------------", NULL},
	{ID_CELL_COPY_DOWN            , HK_CTRL_D , COMMAND_GROUP_EDIT, "�������փR�s�[", "EditCopyDown"},
	{ID_SET_NUMBER                , HK_CTRL_N , COMMAND_GROUP_EDIT, "�������֘A��"  , "EditSetNumber"},
	{ID_SET_NUMBER_ADD            , 0x00000000, COMMAND_GROUP_EDIT, "�������֘A�ԁi�擪�ɒǉ��j"  , "EditSetNumberAdd"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_EDIT, "--------------------", NULL},
	{ID_EDIT_FIND                 , 0x00000000, COMMAND_GROUP_EDIT, "����", "EditFind"},
	{ID_EDIT_REPLACE              , 0x00000000, COMMAND_GROUP_EDIT, "�u��", "EditReplace"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_EDIT, "--------------------", NULL},
	{ID_SELECT_DELETE_LIST        , 0x00000000, COMMAND_GROUP_EDIT, "STE�̃��X�g����폜"         , "DeleteList"},
	{ID_SELECT_DELETE_FILE        , 0x00000000, COMMAND_GROUP_EDIT, "�t�@�C���̍폜"              , "DeleteFile"},
	{ID_DELETE_TAG                , 0x00000000, COMMAND_GROUP_EDIT, "ID3tag�̍폜"                , "DeleteTag"},
	{ID_SELECT_EDIT_DESTORY       , 0x00000000, COMMAND_GROUP_EDIT, "�ύX�O�̏�Ԃɖ߂�"          , "EditModify"},
	{ID_FOLDER_TREE_SYNC          , 0x00000000, COMMAND_GROUP_EDIT, "�t�H���_�\���̓���"          , "FolderSync"},
	{ID_CHECK_FILE_SYNC           , 0x00000000, COMMAND_GROUP_EDIT, "�t�H���_�\���̓���(�`�F�b�N�̂�)", "CheckFileSync"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_EDIT, "--------------------", NULL},
	{ID_DELETE_CHAR_SPACE         , 0x00000000, COMMAND_GROUP_EDIT, "�擪/�����̋󔒕������폜"   , "EditDeleteCharSpace"}, /* Rumble 192 */
	{ID_DELETE_CHAR               , 0x00000000, COMMAND_GROUP_EDIT, "�擪/�����̂��������폜"     , "EditDeleteChar"},

	// �\��
	{ID_ADJUST_COLUMN_WIDTH       , 0x00000000, COMMAND_GROUP_DISP, "�S�ẴJ�������𒲐�", "AdjustColumnWidth"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_DISP, "--------------------", NULL},
	{ID_SORT_LIST                 , 0x00000000, COMMAND_GROUP_DISP, "���ёւ�"        , "ListSort"},
	{ID_SORT_LIST_DIRECT          , 0x00000000, COMMAND_GROUP_DISP, "���ёւ����Ď��s", "ListSortDirect"},
	{ID_EXEC_CLASSIFICATION       , 0x00000000, COMMAND_GROUP_DISP, "���ޕ\�����X�V"  , "ExecClassification"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_DISP, "--------------------", NULL},
	{ID_EDIT_FIELD_SI             , 0x00000000, COMMAND_GROUP_DISP, "SI�t�B�[���h��\��/�ҏW"       , "EditFieldSI"},
	{ID_EDIT_TD3_TAG              , 0x00000000, COMMAND_GROUP_DISP, "ID3 tag ��\��/�ҏW"           , "EditID3tag"},
	{ID_EDIT_CHANGE_FIELD         , 0x00000000, COMMAND_GROUP_DISP, "[ID3 tag]<=>[SI�t�B�[���h]�ؑ�", "EditChangeField"},

	// �v���C���X�g
	{ID_LOAD_PLAYLIST             , 0x00000000, COMMAND_GROUP_PLAYLIST, "�v���C���X�g�̓ǂݍ���"      , "LoadPlayList"},
	{ID_WRITE_PLAYLIST            , 0x00000000, COMMAND_GROUP_PLAYLIST, "�v���C���X�g�̏o��"          , "WritePlayList"},
	{ID_WRITE_TREE_PLAYLIST       , 0x00000000, COMMAND_GROUP_PLAYLIST, "�c���[���ނ̃v���C���X�g�o��", "WriteTreePlayList"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_PLAYLIST, "--------------------", NULL},
	{ID_ALL_FILES_CHECK           , 0x00000000, COMMAND_GROUP_PLAYLIST, "�S�Ẵt�@�C�����`�F�b�N����"  , "AllFilesCheck"},
	{ID_ALL_FILES_UNCHECK         , 0x00000000, COMMAND_GROUP_PLAYLIST, "�S�Ẵt�@�C���̃`�F�b�N���O��", "AllFilesUnCheck"},
	{ID_REVERSE_CHECK             , 0x00000000, COMMAND_GROUP_PLAYLIST, "�`�F�b�N��Ԃ𔽓]����"        , "ReverseCheck"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_PLAYLIST, "--------------------", NULL},
	{ID_CHECK_FILES_SELECT        , 0x00000000, COMMAND_GROUP_PLAYLIST, "�`�F�b�N�t�@�C����I��"      , "CheckFilesSelect"},
	{ID_SELECT_FILES_CHECK        , 0x00000000, COMMAND_GROUP_PLAYLIST, "�I���t�@�C�����`�F�b�N"      , "SelectFilesCheck"},
	{ID_SELECT_FILES_UNCHECK      , 0x00000000, COMMAND_GROUP_PLAYLIST, "�I���t�@�C���̃`�F�b�N���O��", "SelectFilesUnCheck"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_PLAYLIST, "--------------------", NULL},
	{ID_CHECK_WORD                , 0x00000000, COMMAND_GROUP_PLAYLIST, "�������w�肵�ă`�F�b�N"      , "CheckWord"},
	{ID_CHECK_FILENAME_MAX        , 0x00000000, COMMAND_GROUP_PLAYLIST, "�t�@�C�����̒������`�F�b�N"  , "CheckFileNameMax"}, /* SeaKnows 037 */
	{0x0000                       , 0x00000000, COMMAND_GROUP_PLAYLIST, "--------------------", NULL},
	{ID_SELECT_TREE_COLUM         , 0x00000000, COMMAND_GROUP_PLAYLIST, "�c���[�z���̃J�����ꊇ�I��"  , "SelectTreeColumn"}, /* TyphoonSwell 025 */

	// WinAmp ���䏈��
	{ID_WINAMP_PLAY               , 0x00000000, COMMAND_GROUP_PLAYER, "�Đ�"                  , "WinampPlay"},
	{ID_WINAMP_STOP               , 0x00000000, COMMAND_GROUP_PLAYER, "��~(Winamp�̂ݗL��)"  , "WinampStop"},
	{ID_WINAMP_EXIT               , 0x00000000, COMMAND_GROUP_PLAYER, "�I��"                  , "WinampExit"},
	{ID_WINAMP_PLAY_PREV          , 0x00000000, COMMAND_GROUP_PLAYER, "�O�̋�(Winamp�̂ݗL��)", "WinampPlayPrev"},
	{ID_WINAMP_PLAY_NEXT          , 0x00000000, COMMAND_GROUP_PLAYER, "���̋�(Winamp�̂ݗL��)", "WinampPlayNext"},

	// �ϊ�����
	{0x0000                       , 0x00000000, COMMAND_GROUP_CONV, "----- �f�t�H���g�����ϊ� -----", NULL},
	{ID_CONV_FILENAME_TO_TRACKNAME, 0x00000000, COMMAND_GROUP_CONV, "�t�@�C���� => �g���b�N��", "ConvFileNameToTrackName"},
	{ID_CONV_TRACKNAME_TO_FILENAME, 0x00000000, COMMAND_GROUP_CONV, "�g���b�N�� => �t�@�C����", "ConvTrackNameToFileName"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_CONV, "----- ���[�U�[�w�菑���ϊ� -----", NULL},
	{ID_CONV_TAG2FILE_USER        , 0x00000000, COMMAND_GROUP_CONV, "�^�O��� => �t�@�C����", "ConvUserTagToFile"},
	{ID_CONV_FILE2TAG_USER        , 0x00000000, COMMAND_GROUP_CONV, "�t�@�C���� => �^�O���", "ConvUserFileToTag"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_CONV, "------ �����ϊ� -----", NULL},
	{ID_CONV_STR_HAN_ALL          , 0x00000000, COMMAND_GROUP_CONV, "�S�p=>���p(�S��)�ϊ�"          , "ConvHanAll"},
	{ID_CONV_STR_HAN_KIGOU        , 0x00000000, COMMAND_GROUP_CONV, "�S�p=>���p(�L��)�ϊ�"          , "ConvHanKigou"},
	{ID_CONV_STR_HAN_SUJI         , 0x00000000, COMMAND_GROUP_CONV, "�S�p=>���p(����)�ϊ�"          , "ConvHanSuji"},
	{ID_CONV_STR_HAN_KATA         , 0x00000000, COMMAND_GROUP_CONV, "�S�p=>���p(�J�^�J�i)�ϊ�"      , "ConvHanLata"},
	{ID_CONV_STR_HAN_ALPHA        , 0x00000000, COMMAND_GROUP_CONV, "�S�p=>���p(�A���t�@�x�b�g)�ϊ�", "ConvHanAlpha"},
	{ID_CONV_STR_ZEN_ALL          , 0x00000000, COMMAND_GROUP_CONV, "���p=>�S�p(�S��)�ϊ�"          , "ConvZenAll"},
	{ID_CONV_STR_ZEN_KIGOU        , 0x00000000, COMMAND_GROUP_CONV, "���p=>�S�p(�L��)�ϊ�"          , "ConvZenKigou"},
	{ID_CONV_STR_ZEN_SUJI         , 0x00000000, COMMAND_GROUP_CONV, "���p=>�S�p(����)�ϊ�"          , "ConvZenSuji"},
	{ID_CONV_STR_ZEN_KATA         , 0x00000000, COMMAND_GROUP_CONV, "���p=>�S�p(�J�^�J�i)�ϊ�"      , "ConvZenKata"},
	{ID_CONV_STR_ZEN_ALPHA        , 0x00000000, COMMAND_GROUP_CONV, "���p=>�S�p(�A���t�@�x�b�g)�ϊ�", "ConvZenAlpha"},
	{ID_CONV_STR_TO_UPPER         , 0x00000000, COMMAND_GROUP_CONV, "������=>�啶���ϊ�"            , "ConvToUpper"},
	{ID_CONV_STR_TO_LOWER         , 0x00000000, COMMAND_GROUP_CONV, "�啶��=>�������ϊ�"            , "ConvToLower"},
	{ID_CONV_STR_FIRST_UPPER      , 0x00000000, COMMAND_GROUP_CONV, "�P��̂P�����ڂ̂ݑ啶��"      , "ConvFirstUpper"},
	{ID_CONV_STR_HIRA2KATA        , 0x00000000, COMMAND_GROUP_CONV, "�Ђ炪��=>�J�^�J�i�ϊ�"        , "ConvHira2Kata"},
	{ID_CONV_STR_KATA2HIRA        , 0x00000000, COMMAND_GROUP_CONV, "�J�^�J�i=>�Ђ炪�ȕϊ�"        , "ConvKata2Hira"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_CONV, "----- �t�@�C���`���ϊ� -----", NULL},
	{ID_FILE_CONV_MP3             , 0x00000000, COMMAND_GROUP_CONV, "�W�� MP3 �ɕϊ�", "ConvFileMP3"},
	{ID_FILE_CONV_RMP             , 0x00000000, COMMAND_GROUP_CONV, "RIFF MP3 �ɕϊ�", "ConvFileRMP"},
	{ID_FILE_CONV_ID3V2           , 0x00000000, COMMAND_GROUP_CONV, "ID3v2 �ɕϊ�", "ConvFileID3v2"},
	{ID_FILE_CONV_AUTO_ID3        , 0x00000000, COMMAND_GROUP_CONV, "�W��MP3�`��/ID3v2 �`���Ɏ����ϊ�", "AutoConvFileID3"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_CONV, "----- ���̑��̕ϊ� -----", NULL},
	{ID_CONV_SI_FIELD_TO_ID3TAG   , 0x00000000, COMMAND_GROUP_CONV, "SI�t�B�[���h����ID3tag�ɕϊ�", "ConvSIFieldToID3Tag"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_CONV, "----- �g�������ϊ� -----", NULL},
	{ID_CONV_FORMAT_EX_01         , 0x00000000, COMMAND_GROUP_CONV, "�����P", "ConvFormatEx01"},
	{ID_CONV_FORMAT_EX_02         , 0x00000000, COMMAND_GROUP_CONV, "�����Q", "ConvFormatEx02"},
	{ID_CONV_FORMAT_EX_03         , 0x00000000, COMMAND_GROUP_CONV, "�����R", "ConvFormatEx03"},
	{ID_CONV_FORMAT_EX_04         , 0x00000000, COMMAND_GROUP_CONV, "�����S", "ConvFormatEx04"},
	{ID_CONV_FORMAT_EX_05         , 0x00000000, COMMAND_GROUP_CONV, "�����T", "ConvFormatEx05"},
	{ID_CONV_FORMAT_EX_06         , 0x00000000, COMMAND_GROUP_CONV, "�����U", "ConvFormatEx06"},
	{ID_CONV_FORMAT_EX_07         , 0x00000000, COMMAND_GROUP_CONV, "�����V", "ConvFormatEx07"},
	{ID_CONV_FORMAT_EX_08         , 0x00000000, COMMAND_GROUP_CONV, "�����W", "ConvFormatEx08"},
	{ID_CONV_FORMAT_EX_09         , 0x00000000, COMMAND_GROUP_CONV, "�����X", "ConvFormatEx09"},
	{ID_CONV_FORMAT_EX_10         , 0x00000000, COMMAND_GROUP_CONV, "�����P�O", "ConvFormatEx10"},
	{0x0000                       , 0x00000000, COMMAND_GROUP_CONV, "----- ���[�U�[�w�菑�� -----", NULL},
	{ID_CONV_FORMAT_USER_01       , 0x00000000, COMMAND_GROUP_CONV, "�����P", "ConvFormatUser01"},
	{ID_CONV_FORMAT_USER_02       , 0x00000000, COMMAND_GROUP_CONV, "�����Q", "ConvFormatUser02"},
	{ID_CONV_FORMAT_USER_03       , 0x00000000, COMMAND_GROUP_CONV, "�����R", "ConvFormatUser03"},
	{ID_CONV_FORMAT_USER_04       , 0x00000000, COMMAND_GROUP_CONV, "�����S", "ConvFormatUser04"}, /* LastTrain 057 */
	{ID_CONV_FORMAT_USER_05       , 0x00000000, COMMAND_GROUP_CONV, "�����T", "ConvFormatUser05"}, /* LastTrain 057 */

	{0x0000, 0x00000000, -1, NULL, NULL},		// �I�[�R�[�h
};

struct	COLUMN_STATUS	{
	char	*sRegKey;		// ���W�X�g���[�L�[��
	BOOL	bShowFlag;		// �\���t���O
	int		nNumber;		// ���ڂ̏���
	int		nWidth;			// �J������
	int		nWidthMax;		// �ő�J������
	int		nFormat;		//
};

COLUMN_STATUS	g_columnStatus[COLUMN_MAX] = {
	{"TreeItem"  , TRUE ,  0, 128,   0, LVCFMT_LEFT },	// �c���[�A�C�e����(�t���p�X��)
	{"FileName"  , TRUE ,  1, 150,   0, LVCFMT_LEFT },	// �t�@�C����
	{"TrackName" , TRUE ,  2, 128,   0, LVCFMT_LEFT },	// �Ȗ�
	{"ArtistName", TRUE ,  3, 128,   0, LVCFMT_LEFT },	// �A�[�e�B�X�g��
	{"AlbumName" , TRUE ,  4, 128,   0, LVCFMT_LEFT },	// �A���o�����^���i��
	{"TrackNo"   , TRUE ,  5,  48,  48, LVCFMT_RIGHT},	// �g���b�N�ԍ�(ID3 tag v1.1�̂�)
	{"Year"      , TRUE ,  6,  48,  48, LVCFMT_LEFT },	// �����[�X�N��
	{"Genre"     , TRUE ,  7, 128,   0, LVCFMT_LEFT },	// �W������
	{"Comment"   , TRUE ,  8, 128,   0, LVCFMT_LEFT },	// �R�����g������
	{"Copyright" , FALSE,  9, 128,   0, LVCFMT_LEFT },	// ���쌠
	{"Engineer"  , FALSE, 10, 128,   0, LVCFMT_LEFT },	// �G���W�j�A(�����)
	{"Source"    , FALSE, 11, 128,   0, LVCFMT_LEFT },	// �\�[�X
	{"Software"  , FALSE, 12, 128,   0, LVCFMT_LEFT },	// �\�t�g�E�F�A
	{"Keyword"   , FALSE, 13, 128,   0, LVCFMT_LEFT },	// �L�[���[�h
	{"Technician", FALSE, 14, 128,   0, LVCFMT_LEFT },	// �Z�p��
	{"Lyric"     , FALSE, 15, 128,   0, LVCFMT_LEFT },	// �̎�
	{"Commission", FALSE, 16, 128,   0, LVCFMT_LEFT },	// �R�~�b�V����
	{"Composer"  , FALSE, 17, 128,   0, LVCFMT_LEFT },	// ��� /* Baja 154 */
	{"OrigArtist", FALSE, 18, 128,   0, LVCFMT_LEFT },	// Orig.�A�[�e�B�X�g /* Baja 154 */
	{"URL"       , FALSE, 19, 128,   0, LVCFMT_LEFT },	// URL /* Baja 154 */
	{"Encodest"  , FALSE, 20, 128,   0, LVCFMT_LEFT },	// �G���R�[�h�����l/* Baja 154 */
	{"FileSize"  , TRUE , 21,  56,  56, LVCFMT_RIGHT},	// �t�@�C���T�C�Y
	{"FileTime"  , FALSE, 22, 128, 128, LVCFMT_LEFT },	// �t�@�C���X�V��
	{"FilePath"  , TRUE , 23, 128, 128, LVCFMT_LEFT },	// �t�@�C���p�X��
	{"PlayTime"  , FALSE, 24, 128, 128, LVCFMT_LEFT },	// ���t����
	{"LyricFile" , FALSE, 25, 128, 128, LVCFMT_LEFT },	// �̎��t�@�C��
	{"FileType"  , TRUE , 26, 128, 128, LVCFMT_LEFT },	// �t�@�C���̎��
// 	{"BitRate"   , FALSE, 27, 128, 0, LVCFMT_LEFT },	// �r�b�g���[�g /* Conspiracy 198 */
	{"Format"    , FALSE, 27, 128, 0, LVCFMT_LEFT },	// �t�H�[�}�b�g /* Conspiracy 198 */
	{"Other"     , FALSE, 28, 128, 128, LVCFMT_LEFT },	// ���̑� /* Conspiracy 196 */
	{"FileCTime" , FALSE, 29, 128, 128, LVCFMT_LEFT },	// �t�@�C���쐬�� /* Hurricane 207 */
};


#define PROG_NAME		"SuperTagEditor"	// �v���O������
#define PROG_VERSION	"2.00��7"			// �o�[�W����

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

	/* ���W�X�g���l�̎擾 */
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

	/* ���W�X�g���l�̎擾 */
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

		/* ���W�X�g���l�̎擾 */
		RegQueryValueEx(hKey, "", NULL, &dwValueType, &sValue[0], &dwValueSize);

		/* ���ʂ̕\�� */
		if (dwValueType == REG_SZ) g_sOptWinAmpPath = sValue;

		/* �I�� */
		RegCloseKey(hKey);
	}
}

void CSTEReg2IniDlg::ReadCellStateControl()
{
	static	char	*sSectionColumnState	= "ColumnState";

	int		nColumn;

	// �J�����������W�X�g������ǂݏo��
	for (nColumn = 0; nColumn < COLUMN_MAX; nColumn++) {
		CString	strKey;
		COLUMN_STATUS	*stat = &g_columnStatus[nColumn];

		// �\���t���O
		strKey.Format("%sShow", stat->sRegKey);
		stat->bShowFlag = GetProfileInt(sSectionColumnState, strKey, stat->bShowFlag);

		// �J�����ʒu
		strKey.Format("%sColNum", stat->sRegKey);
		stat->nNumber = GetProfileInt(sSectionColumnState, strKey, stat->nNumber);

		// �J������
		strKey.Format("%sWidth", stat->sRegKey);
		stat->nWidth = GetProfileInt(sSectionColumnState, strKey, stat->nWidth);

		// �ő�J������
		strKey.Format("%sWidthMax", stat->sRegKey);
		stat->nWidthMax = GetProfileInt(sSectionColumnState, strKey, stat->nWidthMax);
	}
}

void CSTEReg2IniDlg::WriteCellStateControl()
{
	//CString strINI = "SuperTagEditor.ini";
	static	char	*sSectionColumnState	= "ColumnState";

	int		nColumn;
	// �J�����������W�X�g���ɏ����o��
	for (nColumn = 0; nColumn < COLUMN_MAX; nColumn++) {
		CString	strKey;
		COLUMN_STATUS	*stat = &g_columnStatus[nColumn];

		// �\���t���O
		strKey.Format("%sShow", stat->sRegKey);
		MyWriteProfileInt(sSectionColumnState, strKey, stat->bShowFlag);

		// �J�����ʒu
		strKey.Format("%sColNum", stat->sRegKey);
		MyWriteProfileInt(sSectionColumnState, strKey, stat->nNumber);

		// �J������
		strKey.Format("%sWidth", stat->sRegKey);
		MyWriteProfileInt(sSectionColumnState, strKey, stat->nWidth);

		// �ő�J������
		strKey.Format("%sWidthMax", stat->sRegKey);
		MyWriteProfileInt(sSectionColumnState, strKey, stat->nWidthMax);
	}
	Profile_Flush(strINI);
	//Profile_Free();
}


// �W���������X�g�̐ݒ�����W�X�g������ǂ݂���
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

// �W���������X�g�̐ݒ�����W�X�g���ɏ����o��
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

	// �e��ݒ��ǂݍ���
	CString	strVersion;
	strVersion = GetProfileString(sSectionOption, sKeyVersion, "");
//	g_bIsVersionUp = strcmp(strVersion, PROG_VERSION) ? true : false;

	g_strCurrentDirectory	= GetProfileString(sSectionOption, sKeyCurrentDir, "");
	g_strCurrentPlayList	= GetProfileString(sSectionOption, sKeyCurrentPlayList, "*.m3u");

	// ��� - ���[�U�[�C���^�[�t�F�[�X
	g_bOptESCEditCancel			= GetProfileInt(sSectionOption, sKeyESCEditCancel, 0) ? true : false;
	g_bOptEnableEditCursorExit	= GetProfileInt(sSectionOption, sKeyEnableEditCursorExit, 1) ? true : false;
	g_bOptEditOkDown		= GetProfileInt(sSectionOption, sKeyEditOkDown, 1) ? true : false;
	g_bOptEnterBeginEdit	= GetProfileInt(sSectionOption, sKeyEnterBeginEdit, 0) ? true : false;

	// ��� - ����ݒ�
	g_bOptKeepTimeStamp		= GetProfileInt(sSectionOption, sKeyKeepTimeStamp, 0) ? true : false;
	g_bOptSyncCreateTime	= GetProfileInt(sSectionOption, sKeySyncCreateTime, 0) ? true : false;
	g_bOptChangeFileExt		= GetProfileInt(sSectionOption, sKeyChangeFileExt, 0) ? true : false;
	g_bOptAutoOpenFolder	= GetProfileInt(sSectionOption, sKeyAutoOpenFolder, 0) ? true : false;
	g_bOptLoadFileAdjustColumn	= GetProfileInt(sSectionOption, sKeyLoadFileAdjustColumn, 1) ? true : false;
	g_bOptLoadFileChecked	= GetProfileInt(sSectionOption, sKeyLoadFileChecked, 1) ? true : false;
	g_bOptHideMP3ListFile	= GetProfileInt(sSectionOption, sKeyHideMP3ListFile, 0) ? true : false;

	// ��� - RIFF MP3
	g_bOptAutoConvID3v2			= GetProfileInt(sSectionOption, sKeyAutoConvID3v2, 0) ? true : false;
	g_bOptID3v2ID3tagAutoWrite	= GetProfileInt(sSectionOption, sKeyID3v2ID3tagAutoWrite, 0) ? true : false;
	g_bOptID3v2GenreListSelect	= GetProfileInt(sSectionOption, sKeyID3v2GenreListSelect, 1) ? true : false;
	g_bOptAutoConvRMP			= GetProfileInt(sSectionOption, sKeyAutoConvRMP, 0) ? true : false;
	g_bOptRmpID3tagAutoWrite	= GetProfileInt(sSectionOption, sKeyRmpID3tagAutoWrite, 0) ? true : false;
	g_bOptRmpGenreListSelect	= GetProfileInt(sSectionOption, sKeyRmpGenreListSelect, 1) ? true : false;
	g_nOptSIFieldConvType		= GetProfileInt(sSectionOption, sKeySIFieldConvType, SIF_CONV_ALL_FIELD);

	// ��� - �̎��t�@�C��
	g_bOptChangeTextFile		= GetProfileInt(sSectionOption, sKeyChangeTextFile, 1) ? true : false;
	g_bOptSetLyricsDir			= GetProfileInt(sSectionOption, sKeySetLyricsDir, 0) ? true : false;
	g_bOptSearchLyricsSubDir	= GetProfileInt(sSectionOption, sKeySearchLyricsSubDir, 0) ? true : false;
	g_strOptLyricsPath			= GetProfileString(sSectionOption, sKeyLyricsPath, "");

	//
	g_bOptEditFieldSIF		= GetProfileInt(sSectionOption, sKeyEditFiledSIF, 1) ? true : false;
	g_nOptCheckFileName		= GetProfileInt(sSectionOption, sKeyCheckFileName, FILENAME_CONV_MULTIBYTE);
	g_bEnableSearchSubDir	= GetProfileInt(sSectionOption, sKeyEnableSearchSubDir, 1) ? true : false;

	// �t�H���_�̓���
	g_bEnableFolderSync		= GetProfileInt(sSectionFolderSync, sKeyEnableFolderSync, 0) ? true : false;
	g_strRootFolder			= GetProfileString(sSectionFolderSync, sKeySyncRootFolder, "");
	g_bSyncSelectAlways		= GetProfileInt(sSectionFolderSync, sKeySyncSelectAlways, 0) ? true : false;
	g_bSyncDeleteFolder		= GetProfileInt(sSectionFolderSync, sKeySyncDeleteFolder, 1) ? true : false;
	g_bSyncLyricsFileMove	= GetProfileInt(sSectionFolderSync, sKeySyncLyricsFileMove, 1) ? true : false;

	// �m�F���b�Z�[�W�\��
	g_bConfConvMP3		= GetProfileInt(sSectionConfMessage, sKeyConfConvMP3, 1) ? true : false;
	g_bConfConvRMP		= GetProfileInt(sSectionConfMessage, sKeyConfConvRMP, 1) ? true : false;
	g_bConfConvID3v2	= GetProfileInt(sSectionConfMessage, sKeyConfConvID3v2, 1) ? true : false;
	g_bConfDeleteFile	= GetProfileInt(sSectionConfMessage, sKeyConfDeleteFile, 1) ? true : false;
	g_bConfDeleteList	= GetProfileInt(sSectionConfMessage, sKeyConfDeleteList, 1) ? true : false;
	g_bConfEditModify	= GetProfileInt(sSectionConfMessage, sKeyConfEditModify, 1) ? true : false;
	g_bConfFolderSync	= GetProfileInt(sSectionConfMessage, sKeyConfFolderSync, 1) ? true : false;

	// �v���C���X�g
	g_bPlayListClearList	= GetProfileInt(sSectionLoadPlayList, sKeyClearList, 0) ? true : false;
	g_bPlayListClearCheck	= GetProfileInt(sSectionLoadPlayList, sKeyClearCheck, 1) ? true : false;
	g_bPlayListAddList		= GetProfileInt(sSectionLoadPlayList, sKeyAddList, 0) ? true : false;
	g_bPlayListFileCheck	= GetProfileInt(sSectionLoadPlayList, sKeyFileCheck, 1) ? true : false;

	// �����`�F�b�N�̏��
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

	// ���[�U�[�ϊ�����
	const char *sDefFormatTag2File = "%ARTIST_NAME%-%ALBUM_NAME%-%TRACK_NAME%";
	const char *sDefFormatFile2Tag = sDefFormatTag2File;
	//g_nUserConvFormatType	= GetProfileInt(sSectionUserConvFormat, sKeyConvFormatType, 0);
	{ /* ���𑝂₵���̂Ŗ{�ƕ��p���ɉe����^���Ȃ��悤�� LastTrain 057 */
		CString		strSectionName;
		strSectionName = "haseta\\";
		strSectionName += sSectionUserConvFormat;
		g_nUserConvFormatType	= GetProfileInt(strSectionName, sKeyConvFormatType, 0);
	}
	for (i = 0; i < USER_CONV_FORMAT_MAX; i++) {
		CString		strKeyName;
		// ����
		strKeyName.Format("%s%d", sKeyUserFormName, i);
		g_userConvFormat[i].strName = GetProfileString(sSectionUserConvFormat, strKeyName, "���̖��ݒ�");
		// �^�O��� => �t�@�C����
		strKeyName.Format("%s%d", sKeyUserFormTag2File, i);
		g_userConvFormat[i].strTag2File = GetProfileString(sSectionUserConvFormat, strKeyName, sDefFormatTag2File);
		// �t�@�C���� => �^�O���
		strKeyName.Format("%s%d", sKeyUserFormFile2Tag, i);
		g_userConvFormat[i].strFile2Tag = GetProfileString(sSectionUserConvFormat, strKeyName, sDefFormatFile2Tag);
		// �Q�ڈȍ~�̓f�t�H���g������̓N���A
		sDefFormatTag2File = sDefFormatFile2Tag = "";
	}

	// �g���Ń��[�U�[�ϊ�����
	for (i = 0; i < USER_CONV_FORMAT_EX_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format("%s%d", sSectionConvFormatEx, i);
		// ����
		g_userConvFormatEx[i].strName = GetProfileString(strSectionName, sKeyUserFormName, "���̖��ݒ�");
		// ����
		g_userConvFormatEx[i].strFormat = GetProfileString(strSectionName, sKeyUserFormat, "");
		// �Œ蕶����
		g_userConvFormatEx[i].strFixString = GetProfileString(strSectionName, sKeyUserFixString, "");
		// �A�ԁF�����l
		g_userConvFormatEx[i].nInitNumber = GetProfileInt(strSectionName, sKeyUserInitNumber, 1);
		// �A�ԁF���Z�l
		g_userConvFormatEx[i].nAddNumber = GetProfileInt(strSectionName, sKeyUserAddNumber, 1);
		// �A�ԁF����
		g_userConvFormatEx[i].nColumnCount = GetProfileInt(strSectionName, sKeyUserColumnCount, 1);
		// �������ݕs�̃Z���ŘA�ԃN���A
		g_userConvFormatEx[i].bSpaceInitNumber = GetProfileInt(strSectionName, sKeyUserSpaceInit, 0) ? true : false;
	}

	// �ړ���t�H���_����
	for (i = 0; i < USER_MOVE_FODLER_FORMAT_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format("haseta\\%s%d", sSectionMoveFolder, i);
		// ����
		g_userMoveFolder[i].strName = GetProfileString(strSectionName, sKeyUserFormName, "���̖��ݒ�");
		// ����
		g_userMoveFolder[i].strFormat = GetProfileString(strSectionName, sKeyMoveFolderFormat, "");
		// �Œ蕶����
		g_userMoveFolder[i].strFixString = GetProfileString(strSectionName, sKeyMoveFolderFixString, "");
		// �R�s�[
		g_userMoveFolder[i].bCopy = GetProfileInt(strSectionName, sKeyMoveFolderCopy, 0) ? true : false;
	}
	// �����R�s�[ /* FunnyCorn 175 */
	for (i = 0; i < USER_COPY_FORMAT_FORMAT_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format("haseta\\%s%d", sSectionCopyFormat, i);
		// ����
		g_userCopyFormat[i].strName = GetProfileString(strSectionName, sKeyUserFormName, "���̖��ݒ�");
		// ����
		g_userCopyFormat[i].strFormat = GetProfileString(strSectionName, sKeyCopyFormatFormat, "");
		// �Œ蕶����
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
	// ��^���\��t�� /* SeaKnows 030 *//* FreeFall 046 */
	for (int k=0;k<3;k++) {
		CString		sSectionOption;
		CString		strSectionName;
		sSectionOption = "haseta";
		strSectionName.Format("%s%d", sSectionTeikeiGroupName, k);
		g_strTeikeiGroupName[k] = GetProfileString(sSectionOption, strSectionName, "���̖��ݒ�");
		for (i = 0; i < 10; i++) {
			if (k == 0) {
				strSectionName.Format("%s%d", sSectionTeikei, i);
			} else {
				strSectionName.Format("%s%d-%d", sSectionTeikei, k, i);
			}
			g_strTeikei[i+k*10] = GetProfileString(sSectionOption, strSectionName, "");
		}
	}
	// �\�t�g�E�F�A�� /* SeaKnows 031 */
	{
		CString		strSectionName;
		strSectionName = "haseta";
		g_strSoftwareTag = GetProfileString(strSectionName, sSectionSoftwareTag, PROG_NAME " Ver " PROG_VERSION "��");
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

	// ���X�g�o�͏���
	for (i = 0; i < WRITE_FORMAT_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format("%s%d", sSectionWriteFormat, i);
		// ����
		g_writeFormat[i].strName = GetProfileString(strSectionName, sKeyWriteFormName, "���̖��ݒ�");
		// �����t�@�C����
		g_writeFormat[i].strFileName = GetProfileString(strSectionName, sKeyWriteFileName, "");
		// �g���q
		g_writeFormat[i].strExtName = GetProfileString(strSectionName, sKeyWriteExtName, ".txt");
		// �I���t�@�C���̂ݏo��
		g_writeFormat[i].bWriteSelected = GetProfileInt(strSectionName, sKeyWriteSelected, 0) ? true : false;
		// �J�����g�t�@�C����
		g_writeFormat[i].strCurrentFile = GetProfileString(strSectionName, sKeyWriteCurrentFile, "");
		// HTML �t�@�C���o�͗p(��̏ꍇ�ɑS�p�X�y�[�X���o��)
		g_writeFormat[i].bIsHtml = GetProfileInt(strSectionName, sKeyWriteIsHtml, 0) ? true : false;
		{ /* BeachMonster5 120 */
			g_writeFormat[i].bWriteHtml = GetProfileInt("haseta\\" + strSectionName, sKeyWriteHtml, 0) ? true : false;
		}
	}

	// �t�@�C�����u������
	for (i = 0; i < FILENAME_REPLACE_MAX; i++) {
		FILENAME_REPLACE	*pRep = &g_fileNameReplace[i];
		CString		strKeyName;
		// �u���㕶����
		strKeyName.Format("%s%d", sKeyRepCharAfter, i);
		pRep->strBefore = g_sRepTable[i][0];
		pRep->strAfter = GetProfileString(sSectionRepFileName, strKeyName, g_sRepTable[i][1]);
	}
	// ���[�U�t�@�C�����u������ /* FreeFall 050 */
	{
		CString		strSectionName;
		strSectionName = "haseta\\User";
		strSectionName += sSectionRepFileName;
		for (i = 0; i < USER_FILENAME_REPLACE_MAX; i++) {
			FILENAME_REPLACE	*pRep = &g_userFileNameReplace[i];
			CString		strKeyName;
			// �u���㕶����
			strKeyName.Format("%s%d", sKeyRepCharBefore, i);
			pRep->strBefore = GetProfileString(strSectionName, strKeyName, "");
			strKeyName.Format("%s%d", sKeyRepCharAfter, i);
			pRep->strAfter = GetProfileString(strSectionName, strKeyName, "");
		}
	}

	// ���ސݒ���
	g_classInfo.nType = GetProfileInt(sSectionClass, sKeyClassType, 0);
	for (i = 0; i < CLASS_MAX; i++) {
		CString		strKeyName;
		// �J�����ԍ�
		strKeyName.Format("%s%d", sKeyClassColumn, i);
		g_classInfo.nColumn[i] = GetProfileInt(sSectionClass, strKeyName, -1);
	}

	// �\�[�g���
	for (i = 0; i < SORT_KEY_MAX; i++) {
		CString		strKeyName;
		SORT_STATE	*state = &g_sortState[i];
		// �L�[(�J����)
		strKeyName.Format("%s%d", sKeySortColumn, i);
		state->nKeyColumn = GetProfileInt(sSectionSort, strKeyName, -1);
		// �^�C�v
		strKeyName.Format("%s%d", sKeySortType, i);
		state->nType = GetProfileInt(sSectionSort, strKeyName, 0);
	}

	// �E�B���h�E�̃t�H���g��ǂݍ���
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
	{ /* ���𑝂₵���̂Ŗ{�ƕ��p���ɉe����^���Ȃ��悤�� WildCherry 070 */
		CString		strSectionName;
		strSectionName = "haseta\\";
		strSectionName += sSectionOption;
		g_nOptPlayerType	= GetProfileInt(strSectionName, sKeyPlayerType, PLAYER_WINAMP);
		g_sOptWinAmpPath		= GetProfileString(strSectionName, sKeyWinAmpPath, "");
	}
	if (g_sOptWinAmpPath.IsEmpty()) {
		// WinAmp �̃p�X���擾
		GetWinampPath();
	}

	g_bMainFrameZoomed		= GetProfileInt(sSectionWindow, sKeyWinZoomed, FALSE);
	g_bMainFrameIconic		= GetProfileInt(sSectionWindow, sKeyWinIconic, FALSE);
	ReadWindowStatus(sKeyMainWindow, &g_rectMainWindow);

	// ���[�U�w��W������
	if (g_genreListUSER == NULL) {
		g_genreListUSER = new USER_GENRE_LIST[USER_GENRE_LIST_MAX];
	}

	// ������̓��� /* StartInaction 054 */
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

	// �t�@�C����������̓��� /* LastTrain 058 */
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

	// �v���C���X�g���͐ݒ�_�C�A���O��\������ /* RockDance 126 */
	{
		CString		strSectionName;
		strSectionName = "haseta";
		g_bShowLoadPlaylistDlg = GetProfileInt(strSectionName, sKeyShowLoadPlaylistDlg, 1) ? true : false;
	}

	// ���C�ɓ���̃t�H���_ /* RockDance 129 */
	{
		CString		sSectionOption;
		CString		strSectionName;
		sSectionOption = "haseta";
		for (i = 0; i < 10; i++) {
			strSectionName.Format("%s%d", sSectionFavorites, i);
			g_strFavorite[i] = GetProfileString(sSectionOption, strSectionName, "");
		}
	}

	// �Ώۂ̊g���q /* Conspiracy 195 */
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
	dlgLoadProgress.SetWindowText("�I��������.....");
	dlgLoadProgress.SetDlgItemText(IDC_ST_MESSAGE, "�ݒ��ۑ����Ă��܂�...");
	dlgLoadProgress.SetPos(0);
	*/

	int		i;

	// �e��ݒ����������
	MyWriteProfileString(sSectionOption, sKeyVersion        , PROG_VERSION);
	MyWriteProfileString(sSectionOption, sKeyCurrentDir     , g_strCurrentDirectory);
	MyWriteProfileString(sSectionOption, sKeyCurrentPlayList, g_strCurrentPlayList);
	//dlgLoadProgress.SetPos(5);

	// ��� - ���[�U�[�C���^�[�t�F�[�X
	MyWriteProfileInt(sSectionOption, sKeyESCEditCancel       , g_bOptESCEditCancel ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyEnableEditCursorExit, g_bOptEnableEditCursorExit ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyEditOkDown          , g_bOptEditOkDown ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyEnterBeginEdit      , g_bOptEnterBeginEdit ? 1 : 0);
	//dlgLoadProgress.SetPos(10);

	// ��� - ����ݒ�
	MyWriteProfileInt(sSectionOption, sKeyKeepTimeStamp       , g_bOptKeepTimeStamp ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeySyncCreateTime      , g_bOptSyncCreateTime ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyChangeFileExt       , g_bOptChangeFileExt ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyAutoOpenFolder      , g_bOptAutoOpenFolder ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyLoadFileAdjustColumn, g_bOptLoadFileAdjustColumn ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyLoadFileChecked     , g_bOptLoadFileChecked ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyHideMP3ListFile     , g_bOptHideMP3ListFile ? 1 : 0);
	//dlgLoadProgress.SetPos(15);

	// ��� - �̎��t�@�C��
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

	// �t�H���_�̓���
	MyWriteProfileInt(sSectionFolderSync, sKeyEnableFolderSync, g_bEnableFolderSync ? 1 : 0);
	MyWriteProfileString(sSectionFolderSync, sKeySyncRootFolder, g_strRootFolder);
	MyWriteProfileInt(sSectionFolderSync, sKeySyncSelectAlways, g_bSyncSelectAlways ? 1 : 0);
	MyWriteProfileInt(sSectionFolderSync, sKeySyncDeleteFolder, g_bSyncDeleteFolder ? 1 : 0);
	MyWriteProfileInt(sSectionFolderSync, sKeySyncLyricsFileMove, g_bSyncLyricsFileMove ? 1 : 0);
	//dlgLoadProgress.SetPos(30);

	// �m�F���b�Z�[�W�\��
	MyWriteProfileInt(sSectionConfMessage, sKeyConfDeleteFile, g_bConfDeleteFile ? 1 : 0);
	MyWriteProfileInt(sSectionConfMessage, sKeyConfDeleteList, g_bConfDeleteList ? 1 : 0);
	MyWriteProfileInt(sSectionConfMessage, sKeyConfEditModify, g_bConfEditModify ? 1 : 0);
	MyWriteProfileInt(sSectionConfMessage, sKeyConfFolderSync, g_bConfFolderSync ? 1 : 0);
	//dlgLoadProgress.SetPos(35);

	// �v���C���X�g
	MyWriteProfileInt(sSectionLoadPlayList, sKeyClearList , g_bPlayListClearList ? 1 : 0);
	MyWriteProfileInt(sSectionLoadPlayList, sKeyClearCheck, g_bPlayListClearCheck ? 1 : 0);
	MyWriteProfileInt(sSectionLoadPlayList, sKeyAddList   , g_bPlayListAddList ? 1 : 0);
	MyWriteProfileInt(sSectionLoadPlayList, sKeyFileCheck , g_bPlayListFileCheck ? 1 : 0);
	//dlgLoadProgress.SetPos(40);

	// �����`�F�b�N�̏��
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

	// �t�@�C�����u������
	for (i = 0; i < FILENAME_REPLACE_MAX; i++) {
		FILENAME_REPLACE	*pRep = &g_fileNameReplace[i];
		CString		strKeyName;
		// �u���㕶����
		strKeyName.Format("%s%d", sKeyRepCharAfter, i);
		MyWriteProfileString(sSectionRepFileName, strKeyName, pRep->strAfter);
	}
	//dlgLoadProgress.SetPos(50);
	// ���[�U�t�@�C�����u������ /* FreeFall 050 */
	{
		CString		strSectionName;
		strSectionName = "haseta\\User";
		strSectionName += sSectionRepFileName;
		for (i = 0; i < USER_FILENAME_REPLACE_MAX; i++) {
			FILENAME_REPLACE	*pRep = &g_userFileNameReplace[i];
			CString		strKeyName;
			// �u���㕶����
			strKeyName.Format("%s%d", sKeyRepCharBefore, i);
			MyWriteProfileString(strSectionName, strKeyName, pRep->strBefore);
			strKeyName.Format("%s%d", sKeyRepCharAfter, i);
			MyWriteProfileString(strSectionName, strKeyName, pRep->strAfter);
		}
	}
	//dlgLoadProgress.SetPos(55);

	// ���[�U�[�ϊ�����
	//MyWriteProfileInt(sSectionUserConvFormat, sKeyConvFormatType, g_nUserConvFormatType);
	{ /* ���𑝂₵���̂Ŗ{�ƕ��p���ɉe����^���Ȃ��悤�� LastTrain 057 */
		CString		strSectionName;
		strSectionName = "haseta\\";
		strSectionName += sSectionUserConvFormat;
		MyWriteProfileInt(strSectionName, sKeyConvFormatType, g_nUserConvFormatType);
	}
	//dlgLoadProgress.SetPos(60);
	for (i = 0; i < USER_CONV_FORMAT_MAX; i++) {
		CString		strKeyName;
		// ����
		strKeyName.Format("%s%d", sKeyUserFormName, i);
		MyWriteProfileString(sSectionUserConvFormat, strKeyName, g_userConvFormat[i].strName);
		// �^�O��� => �t�@�C����
		strKeyName.Format("%s%d", sKeyUserFormTag2File, i);
		MyWriteProfileString(sSectionUserConvFormat, strKeyName, g_userConvFormat[i].strTag2File);
		// �t�@�C���� => �^�O���
		strKeyName.Format("%s%d", sKeyUserFormFile2Tag, i);
		MyWriteProfileString(sSectionUserConvFormat, strKeyName, g_userConvFormat[i].strFile2Tag);
	}
	//dlgLoadProgress.SetPos(65);

	// �g���Ń��[�U�[�ϊ�����
	for (i = 0; i < USER_CONV_FORMAT_EX_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format("%s%d", sSectionConvFormatEx, i);
		// ����
		MyWriteProfileString(strSectionName, sKeyUserFormName, g_userConvFormatEx[i].strName);
		// ����
		MyWriteProfileString(strSectionName, sKeyUserFormat, g_userConvFormatEx[i].strFormat);
		// �Œ蕶����
		MyWriteProfileString(strSectionName, sKeyUserFixString, g_userConvFormatEx[i].strFixString);
		// �A�ԁF�����l
		MyWriteProfileInt(strSectionName, sKeyUserInitNumber, g_userConvFormatEx[i].nInitNumber);
		// �A�ԁF���Z�l
		MyWriteProfileInt(strSectionName, sKeyUserAddNumber, g_userConvFormatEx[i].nAddNumber);
		// �A�ԁF����
		MyWriteProfileInt(strSectionName, sKeyUserColumnCount, g_userConvFormatEx[i].nColumnCount);
		// �������ݕs�̃Z���ŘA�ԃN���A
		MyWriteProfileInt(strSectionName, sKeyUserSpaceInit, g_userConvFormatEx[i].bSpaceInitNumber ? 1 : 0);
	}
	//dlgLoadProgress.SetPos(70);

	// �ړ���t�H���_����
	for (i = 0; i < USER_MOVE_FODLER_FORMAT_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format("haseta\\%s%d", sSectionMoveFolder, i);
		// ����
		MyWriteProfileString(strSectionName, sKeyUserFormName, g_userMoveFolder[i].strName);
		// ����
		MyWriteProfileString(strSectionName, sKeyMoveFolderFormat, g_userMoveFolder[i].strFormat);
		// �Œ蕶����
		MyWriteProfileString(strSectionName, sKeyMoveFolderFixString, g_userMoveFolder[i].strFixString);
		// �R�s�[
		MyWriteProfileInt(strSectionName, sKeyMoveFolderCopy, g_userMoveFolder[i].bCopy ? 1 : 0);
	}
	//dlgLoadProgress.SetPos(75);
	// �����R�s�[ /* FunnyCorn 175 */
	for (i = 0; i < USER_COPY_FORMAT_FORMAT_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format("haseta\\%s%d", sSectionCopyFormat, i);
		// ����
		MyWriteProfileString(strSectionName, sKeyUserFormName, g_userCopyFormat[i].strName);
		// ����
		MyWriteProfileString(strSectionName, sKeyCopyFormatFormat, g_userCopyFormat[i].strFormat);
		// �Œ蕶����
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
	// ��^���\��t�� /* SeaKnows 030 */
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

	// ���̑� /* SeaKnows 031,033 */
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

	// ���X�g�o�͏���
	for (i = 0; i < WRITE_FORMAT_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format("%s%d", sSectionWriteFormat, i);
		// ����
		MyWriteProfileString(strSectionName, sKeyWriteFormName, g_writeFormat[i].strName);
		// �����t�@�C����
		MyWriteProfileString(strSectionName, sKeyWriteFileName, g_writeFormat[i].strFileName);
		// �g���q
		MyWriteProfileString(strSectionName, sKeyWriteExtName, g_writeFormat[i].strExtName);
		// �I���t�@�C���̂ݏo��
		MyWriteProfileInt(strSectionName, sKeyWriteSelected, g_writeFormat[i].bWriteSelected ? 1 : 0);
		// �J�����g�t�@�C����
		MyWriteProfileString(strSectionName, sKeyWriteCurrentFile, g_writeFormat[i].strCurrentFile);
		// HTML �t�@�C���o�͗p(��̏ꍇ�ɑS�p�X�y�[�X���o��)
		MyWriteProfileInt(strSectionName, sKeyWriteIsHtml, g_writeFormat[i].bIsHtml ? 1 : 0);
		{ /* BeachMonster5 120 */
			MyWriteProfileInt("haseta\\" + strSectionName, sKeyWriteHtml, g_writeFormat[i].bWriteHtml ? 1 : 0);
		}
	}
	//dlgLoadProgress.SetPos(90);

	// ���ސݒ���
	MyWriteProfileInt(sSectionClass, sKeyClassType, g_classInfo.nType);
	for (i = 0; i < CLASS_MAX; i++) {
		CString		strKeyName;
		// �J�����ԍ�
		strKeyName.Format("%s%d", sKeyClassColumn, i);
		MyWriteProfileInt(sSectionClass, strKeyName, g_classInfo.nColumn[i]);
	}

	// �\�[�g���
	for (i = 0; i < SORT_KEY_MAX; i++) {
		CString		strKeyName;
		SORT_STATE	*state = &g_sortState[i];
		// �L�[(�J����)
		strKeyName.Format("%s%d", sKeySortColumn, i);
		MyWriteProfileInt(sSectionSort, strKeyName, state->nKeyColumn);
		// �^�C�v
		strKeyName.Format("%s%d", sKeySortType, i);
		MyWriteProfileInt(sSectionSort, strKeyName, state->nType);
	}

	// �E�B���h�E�̃t�H���g����������
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
	{ /* ���𑝂₵���̂Ŗ{�ƕ��p���ɉe����^���Ȃ��悤�� WildCherry 070 */
		CString		strSectionName;
		strSectionName = "haseta\\";
		strSectionName += sSectionOption;
		MyWriteProfileInt(strSectionName, sKeyPlayerType, (int)g_nOptPlayerType);
		MyWriteProfileString(strSectionName, sKeyWinAmpPath, g_sOptWinAmpPath);
	}
	//dlgLoadProgress.SetPos(95);

	// �E�B���h�E�̏�Ԃ�ۑ�
	MyWriteProfileInt(sSectionWindow, sKeyWinZoomed, (int)g_bMainFrameZoomed);
	MyWriteProfileInt(sSectionWindow, sKeyWinIconic, (int)g_bMainFrameIconic);
	WriteWindowStatus(sKeyMainWindow, &g_rectMainWindow);

	// ������̓��� /* StartInaction 054 */
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

	// �t�@�C����������̓��� /* LastTrain 058 */
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
	// �v���C���X�g���͐ݒ�_�C�A���O��\������ /* RockDance 126 */
	{
		CString		strSectionName;
		strSectionName = "haseta";
		MyWriteProfileInt(strSectionName, sKeyShowLoadPlaylistDlg, g_bShowLoadPlaylistDlg ? 1 : 0);
	}
	//dlgLoadProgress.SetPos(100);
	// ���C�ɓ���̃t�H���_ /* RockDance 129 */
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
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
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

	MessageBox(strINI + " ���쐬���܂����B","STEReg2Ini",MB_OK);
	//CDialog::OnOK();
}
