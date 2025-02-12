// Tag_Ape.h: CTag_Ape クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Tag_Ape_H__6C5D4E96_2B7C_4333_A4F8_3CF81D10E6F5__INCLUDED_)
#define AFX_Tag_Ape_H__6C5D4E96_2B7C_4333_A4F8_3CF81D10E6F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)
#include <map>
#include <list>
using namespace std;

/*
Memo:
ID3tag->Ape tagの順でロードする
セーブするとApe tagのみが書き込まれる
*/

class CTag_Ape  
{
public:
	CTag_Ape(BOOL bScmpxGenre = TRUE);
	virtual ~CTag_Ape();
	void	Release();
	BOOL	IsEnable(){return m_bHasApetag;};
	BOOL	HasId3tag(){return m_bHasId3tag;};
//	void	SetId3tag(BOOL val){m_bHasId3tag = val;};
	BOOL	HasApetag(){return m_bHasApetag;};
//	void	SetApetag(BOOL val){m_bHasApetag = val;};
	int		GetApeVersion(){return m_apeVersion;};
	void	SetDonotsaveId3v1(BOOL val){m_bDoNotSaveId3v1 = val;};
	BOOL	GetDonotsaveId3v1(){return m_bDoNotSaveId3v1;};
//	long	GenreString2Num(const char *szGenre);
//	CString GenreNum2String(unsigned char cGenre);
//	void	SetScmpxGenre(BOOL bSwitch);

	BOOL	SetComment(const char *name,const char *value);
	BOOL	GetComment(const char *name,CString &strValue);
	void	GetCommentNames(CStringArray &strArray);

	DWORD	Load(const char *szFileName);
	DWORD	Save(const char *szFileName);
	DWORD	DelTag(const char *szFileName);
	DWORD	MakeTag(const char *szFileName);

	static const int CTag_Ape::CURRENT_APE_TAG_VERSION;
	static const char *CTag_Ape::APE_TAG_FIELD_TITLE;
	static const char *CTag_Ape::APE_TAG_FIELD_ARTIST;
	static const char *CTag_Ape::APE_TAG_FIELD_ALBUM;
	static const char *CTag_Ape::APE_TAG_FIELD_COMMENT;
	static const char *CTag_Ape::APE_TAG_FIELD_YEAR;
	static const char *CTag_Ape::APE_TAG_FIELD_TRACK;
	static const char *CTag_Ape::APE_TAG_FIELD_GENRE;

private:
	void _GetId3tagString(char *szTag);
//	DWORD _MakeId3Tag(const char *szFileName);
//	DWORD _MakeApeTag(const char *szFileName);
	DWORD _LoadId3Tag(const char *szFileName);
	DWORD _LoadApeTagV1(HANDLE hFile);
	DWORD _LoadApeTagV2(HANDLE hFile);
	DWORD _SaveId3TagV1(const char *szFileName);
	DWORD _SaveApeTagV2(const char *szFileName);
//	DWORD _SaveId3V1(HANDLE hFile);
	DWORD _DelTag(const char *szFileName);

#pragma pack(1)
	typedef struct _ID3_TAG
	{
		char TagHeader[3];
		char Title[30];
		char Artist[30];
		char Album[30];
		char Year[4];
		char Comment[29];
		unsigned char Track;
		unsigned char Genre;
	}ID3_TAG;
	typedef struct _APE_TAG_FOOTER
	{
		char id[8];		// "APETAGEX"
		int version;		// タグバージョン
		int size;			// このフッタを含むタグサイズ
		int fields;			// タグに含まれるフィールド数
		int flags;			// フラグ
		char reserved[8];	// 予約
	}APE_TAG_FOOTER;
#pragma pack()
	ID3_TAG m_id3tag;
	APE_TAG_FOOTER m_footer;
	BOOL m_bHasId3tag;
	BOOL m_bHasApetag;
	BOOL m_bScmpxGenre;		//SCMPX拡張ジャンルを使用する
	int m_apeVersion;
	BOOL m_bDoNotSaveId3v1;	// ID3v1を保存しない

	map<CString,CString> m_comments;

public:
	BOOL isApetagV1() { return (m_footer.version < 2000) ? TRUE : FALSE; }; // Add STEP

};

#endif // !defined(AFX_Tag_Ape_H__6C5D4E96_2B7C_4333_A4F8_3CF81D10E6F5__INCLUDED_)
