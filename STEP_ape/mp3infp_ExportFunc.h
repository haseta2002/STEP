#ifndef _MP3INFP_EXPORT_FUNC_H
#define _MP3INFP_EXPORT_FUNC_H

/*
■改変履歴
2004-10-13 Ver.2.47
・mp3infp_mp3_MakeApeTag()/mp3infp_mp3_DelApeTag()を追加
・#define MP3INFP_HAS_MP3_APEV1	0x00000100	// v2.47〜
　#define MP3INFP_HAS_MP3_APEV2	0x00000200	// v2.47〜
　を追加

2004-01-2x Ver.2.43
・IN hWndを廃止
・char *szFileName -> const char *szFileNameに変更
・char *szValueName -> const char *szValueNameに変更
・cahr *buf -> const char *bufに変更(mp3infp_SetValue()のみ)
・mp3infp_SetConf()の戻り値を 0/-1 -> TRUE/FASLE に変更
・書込み系APIを追加

■mp3infp APIの利用・dllの再配布について　2002-09-16/2004-01-20(編集)

1.APIを利用する前に必ず mp3infp_GetVer() を呼び出して、必要なバージョンを調べてください
(古いmp3infpはmp3infp_GetVer()をサポートしていないため、エントリポイントのNULLチェックも必要です)
2.mp3infp.dllのフリーソフトへの同梱はご自由にどうぞ。
・この場合、利用ソフトのカレントDirにmp3infp.dllを置いて利用します(system/system32やwindows/winntには置かないでください)
・カレントとWindowsシステム(mp3infpがインストールされているdir)のどちらを優先してロードするのか、よく考えて設計してください
(どちらを優先させるかは開発者の自由です)
*/

#if __cplusplus
extern "C"{
#endif

/*=======================================================================================
名前：	mp3infp_GetVer
概要：	mp3infpのバージョンを取得する
引数：	なし
戻値：	DWORD	バージョン情報 
			Ver.2.11	= 0x0211
備考：	
対応：	Ver2.11〜
*/
DWORD __stdcall mp3infp_GetVer();
typedef DWORD (WINAPI *LPMP3INFP_GETVER)();

/*=======================================================================================
名前：	mp3infp_ViewProp
概要：	mp3infpに対応したファイル形式のプロパティを開く
説明：	指定ファイルのプロパティをmp3infpのタブをアクティブにして開きます
引数：
		IN DWORD reserved	予約済み(NULLを設定すること)
		IN char *szFileName	対象ファイル名をフルパスで指定。
		IN DWORD dwPage		・mp3infpの何ページ目をアクティブにするか指定する(0=ID3v1 / 1=ID3v2 / 2=RiffSIF / 3=APE(Ver2.47))
							・タグを含まないmp3の場合のみ有効
							・タグを含む場合はID3v2/APE/RiffSIF/ID3v1の順で検索して、最初に見つかったタグをアクティブにします

戻値：	BOOL 成功=TRUE/失敗=FALSE
対応：	Ver2.00〜
*/
BOOL __stdcall mp3infp_ViewProp(HWND hWnd,const char *szFileName,DWORD dwDummy);
typedef BOOL (WINAPI *LPMP3INFP_VIEWPROP)(HWND hWnd,const char *szFileName,DWORD dwDummy);

/*=======================================================================================
名前：	mp3infp_Load
概要：	タグ情報をロードする
引数：
		IN HWND hWnd		呼び出し元ウインドウを指定します。無い場合はNULL。
		IN const char *szFileName	対象ファイル名をフルパスで指定。
戻値：	DWORD 
		-1=ロード失敗
		ERROR_SUCCESS=成功
		(その他)=Win32エラーコード (FormatMessageで文字列を取得できる)
対応：	Ver2.26〜
*/
DWORD __stdcall mp3infp_Load(HWND hWnd,const char *szFileName);
typedef DWORD (WINAPI *LPMP3INFP_LOAD)(HWND hWnd,const char *szFileName);

/*=======================================================================================
////////////////////////////////////////////////////////////////////
表1　mp3infp_GetValue()/mp3infp_SetValue()でszValueNameに指定する名前一覧
////////////////////////////////////////////////////////////////////

	[共通](※1)
	ファイル名				"FILE"	(v2.41〜)
	拡張子					"FEXT"	(v2.41〜)
	パス					"PATH"	(v2.41〜)
	サイズ(byte単位)		"SIZ1"	(v2.41〜)
	サイズ(Kbyte単位)		"SIZK"	(v2.41〜)
	サイズ(Mbyte単位)		"SIZM"	(v2.41〜)

	[MP3]					ID3v1		ID3v2		RiffSIF
	フォーマット(※1)		"AFMT"		"AFMT"		"AFMT"	
	演奏時間(※1)			"TIME"		"TIME"		"TIME"
	タイトル				"INAM_v1"	"INAM_v2"	"INAM_rmp"
	アーティスト			"IART_v1"	"IART_v2"	"IART_rmp"
	アルバム				"IPRD_v1"	"IPRD_v2"	"IPRD_rmp"
	コメント				"ICMT_v1"	"ICMT_v2"	"ICMT_rmp"
	作成日					"ICRD_v1"	"ICRD_v2"	"ICRD_rmp"
	ジャンル				"IGNR_v1"	"IGNR_v2"	"IGNR_rmp"
	(ID3v2/RiffSIF)
	著作権								"ICOP_v2"	"ICOP_rmp"
	ソフトウェア						"ISFT_v2"	"ISFT_rmp"
	(ID3v2)
	作曲								"COMP_v2"
	Orig.アーティスト					"OART_v2"
	URL									"URL_v2"
	(RiffSIF)
	ソース											"ISRC_rmp"
	エンジニア										"IENG_rmp"
	(ID3v1/2)
	トラック番号			"TRACK_v1"	"TRACK_v2"

	[WAV]
	フォーマット(※1)		"AFMT"
	演奏時間(※1)			"TIME"
	タイトル(※2)			"INAM"
	タイトル(※2)			"ISBJ"
	アーティスト			"IART"
	アルバム				"IPRD"
	コメント				"ICMT"
	作成日					"ICRD"
	ジャンル				"IGNR"
	著作権					"ICOP"
	ソフトウェア			"ISFT"
	ソース					"ISRC"
	エンジニア				"IENG"

	[AVI]
	音声フォーマット(※1)	"AFMT"	
	映像フォーマット(※1)	"VFMT"
	時間(※1)				"TIME"
	タイトル(※2)			"INAM"
	タイトル(※2)			"ISBJ"
	アーティスト			"IART"
	コメント				"ICMT"
	作成日					"ICRD"
	ジャンル				"IGNR"
	著作権					"ICOP"
	ソフトウェア			"ISFT"
	ソース					"ISRC"
	エンジニア				"IENG"
	AVIバージョン			"AVIV"	(v2.37〜)

	[VQF]
	フォーマット(※1)		"AFMT"
	演奏時間(※1)			"TIME"
	タイトル				"INAM"
	アーティスト			"IART"
	コメント				"ICMT"
	著作権					"ICOP"
	保存名					"FILE"

	[WMA]
	音声フォーマット(※1)	"AFMT"
	映像フォーマット(※1)	"VFMT"
	時間(※1)				"TIME"
	タイトル				"INAM"
	トラック				"TRACK"
	アーティスト			"IART"
	アルバム				"IPRD"
	コメント				"ICMT"
	作成日					"ICRD"
	ジャンル				"IGNR"
	著作権					"ICOP"
	URL(Album)				"URL1"
	URL(関連)				"URL2"

	[OGG]
	フォーマット(※1)		"AFMT"
	演奏時間(※1)			"TIME"
	タイトル				"INAM"
	アーティスト			"IART"
	アルバム				"IPRD"
	コメント				"ICMT"
	作成日					"ICRD"
	ジャンル				"IGNR"
	トラック番号			"TRACK"

	[APE]
	フォーマット(※1)		"AFMT"
	演奏時間(※1)			"TIME"
	タイトル				"INAM"
	アーティスト			"IART"
	アルバム				"IPRD"
	コメント				"ICMT"
	作成日					"ICRD"
	ジャンル				"IGNR"
	トラック番号			"TRACK"

(※1)mp3infp_SetValue()では利用できません。
(※2)mp3infpではロード時にINAMを優先、無ければISBJを表示。セーブ時にはISBJを削除、INAMを保存します。

*/

#define MP3INFP_FILE_UNKNOWN	0x00
#define MP3INFP_FILE_MP3		0x01
#define MP3INFP_FILE_WAV		0x02
#define MP3INFP_FILE_AVI		0x03
#define MP3INFP_FILE_VQF		0x04
#define MP3INFP_FILE_WMA		0x05
#define MP3INFP_FILE_OGG		0x07
#define MP3INFP_FILE_APE		0x08
/*=======================================================================================
名前：	mp3infp_GetType
概要：	ファイルの種類を取得する
補足：	mp3infp_Load()の後に呼び出してください
引数：	なし
戻値：	DWORD
#define MP3INFP_FILE_UNKNOWN	0x00
#define MP3INFP_FILE_MP3		0x01
#define MP3INFP_FILE_WAV		0x02
#define MP3INFP_FILE_AVI		0x03
#define MP3INFP_FILE_VQF		0x04
#define MP3INFP_FILE_WMA		0x05
#define MP3INFP_FILE_OGG		0x07
#define MP3INFP_FILE_APE		0x08
対応：	Ver2.26〜
*/
DWORD __stdcall mp3infp_GetType();
typedef DWORD (WINAPI *LPMP3INFP_GETTYPE)();

/*=======================================================================================
名前：	mp3infp_GetValue
概要：	タグ情報を取得する
補足：	mp3infp_Load()の後に呼び出してください
引数：	
		IN const char *szValueName	タグの種類を示す名前(表1を参照)
		OUT char **buf			タグ情報を示すバッファのポインタを受け取るポインタ
戻値：	BOOL 成功=TRUE/失敗=FALSE
対応：	Ver2.26〜
*/
BOOL __stdcall mp3infp_GetValue(const char *szValueName,char **buf);
typedef BOOL (WINAPI *LPMP3INFP_GETVALUE)(const char *szValueName,char **buf);

#define MP3INFP_HAS_MP3_ID3V1	0x00000001
#define MP3INFP_HAS_MP3_ID3V2	0x00000002
#define MP3INFP_HAS_MP3_RIFFSIF	0x00000004
#define MP3INFP_HAS_MP3_ID3V1_0	0x00000008	// v2.43〜
#define MP3INFP_HAS_MP3_ID3V1_1	0x00000010	// v2.43〜
#define MP3INFP_HAS_MP3_ID3V2_2	0x00000020	// v2.43〜
#define MP3INFP_HAS_MP3_ID3V2_3	0x00000040	// v2.43〜
#define MP3INFP_HAS_MP3_ID3V2_4	0x00000080	// v2.43〜
#define MP3INFP_HAS_MP3_APEV1	0x00000100	// v2.47〜
#define MP3INFP_HAS_MP3_APEV2	0x00000200	// v2.47〜
/*=======================================================================================
名前：	mp3infp_mp3_GetTagType
概要：	mp3が持っているタグの種類を取得する
補足：	mp3infp_Load()の後に呼び出してください
引数：	なし
戻値：	DWORD (OR)
#define MP3INFP_HAS_MP3_ID3V1	0x00000001
#define MP3INFP_HAS_MP3_ID3V2	0x00000002
#define MP3INFP_HAS_MP3_RIFFSIF	0x00000004
#define MP3INFP_HAS_MP3_ID3V1_0	0x00000008	// v2.43〜
#define MP3INFP_HAS_MP3_ID3V1_1	0x00000010	// v2.43〜
#define MP3INFP_HAS_MP3_ID3V2_2	0x00000020	// v2.43〜
#define MP3INFP_HAS_MP3_ID3V2_3	0x00000040	// v2.43〜
#define MP3INFP_HAS_MP3_ID3V2_4	0x00000080	// v2.43〜
#define MP3INFP_HAS_MP3_APEV1	0x00000100	// v2.47〜
#define MP3INFP_HAS_MP3_APEV2	0x00000200	// v2.47〜
対応：	Ver2.27〜
*/
DWORD __stdcall mp3infp_mp3_GetTagType();
typedef DWORD (WINAPI *LPMP3INFP_MP3_GETTAGTYPE)();

/*=======================================================================================
名前：	mp3infp_SetConf
概要：	mp3infpの動作設定
引数：	IN char *tag		設定項目(表2参照)
		IN char *val		設定値(表2参照)
戻値：	BOOL 成功=TRUE/失敗=FALSE
対応：	Ver2.42〜
補足：	・他のプロセスのmp3infp.dll/シェル拡張のmp3infpには影響しない
		・設定内容は保存されない
*/
BOOL __stdcall mp3infp_SetConf(char *tag,char *value);
typedef BOOL (WINAPI *LPMP3INFP_SETCONF)(char *tag,char *value);

/*=======================================================================================
////////////////////////////////////////////////////////////////////
mp3infp_SetConf()指定する設定項目・値一覧
////////////////////////////////////////////////////////////////////

	[Waveファイルのコーデック名称の取得方法](Ver2.42〜)
	(項目名)
	"wave_CodecFind"
	(値)
	"0"(default)	mp3infp内蔵辞書 → Windows APIを利用の順で検索(高速)
	"1"				Windows APIを利用 → 自力解析の順で検索(低速)
	"2"				mp3infp内蔵辞書(高速)
	"3"				Windows APIを利用(低速)
	
	[Aviファイルのコーデック名称の取得方法](Ver2.42〜)
	(項目名)
	"avi_CodecFind"
	(値)
	"0"(default)	mp3infp内蔵辞書 → Windows APIを利用の順で検索(高速)
	"1"				Windows APIを利用 → 自力解析の順で検索(低速)
	"2"				mp3infp内蔵辞書(高速)
	"3"				Windows APIを利用(低速)

	[ID3v1で拡張ジャンルを使用する](Ver2.43〜)
	(項目名)
	"mp3_UseExtGenre"
	(値)
	"0"(default)	無効
	"1"				有効

	[ID3v2で文字列をUnicodeで書き込む](Ver2.43〜)
	(項目名)
	"mp3_ID3v2Unicode"
	(値)
	"0"(default)	無効
	"1"				有効

	[ID3v2を非同期化する](Ver2.43〜)
	(項目名)
	"mp3_ID3v2Unsync"
	(値)
	"0"				無効
	"1"(default)	有効

	[保存時のID3v2バージョン](Ver2.43〜)
	※この設定値はmp3infp_Load()の実行によって上書きされます。
	(項目名)
	"mp3_SaveID3v2Version"
	(値)
	"2.2"			ID3v2.2
	"2.3"(default)	ID3v2.3
	"2.4"			ID3v2.4
*/

/*=======================================================================================
名前：	mp3infp_SetValue
概要：	タグ情報を設定する
補足：	mp3infp_Load()の後に呼び出してください
引数：	
		IN const char *szValueName	タグの種類を示す名前(表1を参照)
		IN const char *buf			タグ情報を示す文字列
戻値：	DWORD
		-1=失敗
		ERROR_SUCCESS=成功
対応：	Ver.2.43〜
*/
DWORD __stdcall mp3infp_SetValue(const char *szValueName,const char *buf);
typedef DWORD (WINAPI *LPMP3INFP_SETVALUE)(const char *szValueName,const char *buf);

/*=======================================================================================
名前：	mp3infp_Save
概要：	タグ情報を保存する
補足：	mp3infp_Load()の後に呼び出してください
引数：	IN const char *szFileName	対象ファイル名をフルパスで指定。
戻値：	DWORD 
		-1=失敗
		-2=2Gバイトを超えるファイルを扱うことはできません。(WAVファイルのみ)
		ERROR_SUCCESS=成功
		(その他)=Win32エラーコード (FormatMessageで文字列を取得できる)
対応：	Ver.2.43〜
*/
DWORD __stdcall mp3infp_Save(const char *szFileName);
typedef DWORD (WINAPI *LPMP3INFP_SAVE)(const char *szValueName);

/*=======================================================================================
名前：	mp3infp_mp3_MakeId3v1
概要：	ID3TAG V1を作成する
補足：	mp3infp_Load()の後に呼び出してください
		変更は直ちに反映されます
		mp3ファイルにのみ利用してください(wavファイルは対象外)
引数：	IN char *szFileName	対象ファイル名をフルパスで指定。
戻値：	DWORD 
		-1=失敗
		ERROR_SUCCESS=成功
		(その他)=Win32エラーコード (FormatMessageで文字列を取得できる)
対応：	Ver.2.43〜
*/
DWORD __stdcall mp3infp_mp3_MakeId3v1(const char *szFileName);
typedef DWORD (WINAPI *LPMP3INFP_MP3_MAKEID3V1)(const char *szValueName);

/*=======================================================================================
名前：	mp3infp_mp3_DelId3v1
概要：	ID3TAG V1を削除する
補足：	mp3infp_Load()の後に呼び出してください
		変更は直ちに反映されます
		mp3ファイルにのみ利用してください(wavファイルは対象外)
引数：	IN char *szFileName	対象ファイル名をフルパスで指定。
戻値：	DWORD 
		-1=失敗
		ERROR_SUCCESS=成功
		(その他)=Win32エラーコード (FormatMessageで文字列を取得できる)
対応：	Ver.2.43〜
*/
DWORD __stdcall mp3infp_mp3_DelId3v1(const char *szFileName);
typedef DWORD (WINAPI *LPMP3INFP_MP3_DELID3V1)(const char *szValueName);

/*=======================================================================================
名前：	mp3infp_mp3_MakeId3v2
概要：	ID3TAG V2を作成する
補足：	mp3infp_Load()の後に呼び出してください
		変更は直ちに反映されます
		mp3ファイルにのみ利用してください(wavファイルは対象外)
引数：	IN char *szFileName	対象ファイル名をフルパスで指定。
戻値：	DWORD 
		-1=失敗
		ERROR_SUCCESS=成功
		(その他)=Win32エラーコード (FormatMessageで文字列を取得できる)
対応：	Ver.2.43〜
*/
DWORD __stdcall mp3infp_mp3_MakeId3v2(const char *szFileName);
typedef DWORD (WINAPI *LPMP3INFP_MP3_MAKEID3V2)(const char *szValueName);

/*=======================================================================================
名前：	mp3infp_mp3_DelId3v2
概要：	ID3TAG V2を削除する
補足：	mp3infp_Load()の後に呼び出してください
		変更は直ちに反映されます
		mp3ファイルにのみ利用してください(wavファイルは対象外)
引数：	IN char *szFileName	対象ファイル名をフルパスで指定。
戻値：	DWORD 
		-1=失敗
		ERROR_SUCCESS=成功
		(その他)=Win32エラーコード (FormatMessageで文字列を取得できる)
対応：	Ver.2.43〜
*/
DWORD __stdcall mp3infp_mp3_DelId3v2(const char *szFileName);
typedef DWORD (WINAPI *LPMP3INFP_MP3_DELID3V2)(const char *szValueName);

/*=======================================================================================
名前：	mp3infp_mp3_MakeRMP
概要：	mp3形式からRMP形式に変換する
補足：	mp3infp_Load()の後に呼び出してください
		変更は直ちに反映されます
		mp3ファイルにのみ利用してください(wavファイルは対象外)
引数：	IN char *szFileName	対象ファイル名をフルパスで指定。
戻値：	DWORD 
		-1=失敗
		ERROR_SUCCESS=成功
		(その他)=Win32エラーコード (FormatMessageで文字列を取得できる)
対応：	Ver.2.43〜
*/
DWORD __stdcall mp3infp_mp3_MakeRMP(const char *szFileName);
typedef DWORD (WINAPI *LPMP3INFP_MP3_MAKERMP)(const char *szValueName);

/*=======================================================================================
名前：	mp3infp_mp3_DelRMP
概要：	RMP形式からmp3形式に変換する
補足：	mp3infp_Load()の後に呼び出してください
		変更は直ちに反映されます
		mp3ファイルにのみ利用してください(wavファイルは対象外)
引数：	IN char *szFileName	対象ファイル名をフルパスで指定。
戻値：	DWORD 
		-1=失敗
		ERROR_SUCCESS=成功
		(その他)=Win32エラーコード (FormatMessageで文字列を取得できる)
対応：	Ver.2.43〜
*/
DWORD __stdcall mp3infp_mp3_DelRMP(const char *szFileName);
typedef DWORD (WINAPI *LPMP3INFP_MP3_DELRMP)(const char *szValueName);

/*=======================================================================================
名前：	mp3infp_mp3_MakeApeTag
概要：	APE Tagを作成する
補足：	mp3infp_Load()の後に呼び出してください
		変更は直ちに反映されます
		mp3ファイルにのみ利用してください(wavファイルは対象外)
引数：	IN char *szFileName	対象ファイル名をフルパスで指定。
戻値：	DWORD 
		-1=失敗
		ERROR_SUCCESS=成功
		(その他)=Win32エラーコード (FormatMessageで文字列を取得できる)
対応：	Ver.2.47〜
*/
DWORD __stdcall mp3infp_mp3_MakeApeTag(const char *szFileName);
typedef DWORD (WINAPI *LPMP3INFP_MP3_MAKEAPETAG)(const char *szValueName);

/*=======================================================================================
名前：	mp3infp_mp3_DelApeTag
概要：	APE Tagを削除する
補足：	mp3infp_Load()の後に呼び出してください
		変更は直ちに反映されます
		mp3ファイルにのみ利用してください(wavファイルは対象外)
引数：	IN char *szFileName	対象ファイル名をフルパスで指定。
戻値：	DWORD 
		-1=失敗
		ERROR_SUCCESS=成功
		(その他)=Win32エラーコード (FormatMessageで文字列を取得できる)
対応：	Ver.2.47〜
*/
DWORD __stdcall mp3infp_mp3_DelApeTag(const char *szFileName);
typedef DWORD (WINAPI *LPMP3INFP_MP3_DELAPETAG)(const char *szValueName);

#if __cplusplus
}
#endif

#endif //_MP3INFP_EXPORT_FUNC_H
