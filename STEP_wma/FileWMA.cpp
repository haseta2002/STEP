//
//  Microsoft Windows Media Technologies
//  Copyright (C) Microsoft Corporation, 1999 - 2001.  All rights reserved.
//

#include "stdafx.h"
#include <TCHAR.h>
#include <stdio.h>
#include <string.h>
#include "wmsdk.h"
#include "FileWMA.h"

#ifndef SAFE_RELEASE

#define SAFE_RELEASE( x )  \
    if( NULL != x )        \
    {                      \
        x->Release( );     \
        x = NULL;          \
    }

#endif // SAFE_RELEASE

//
// List of all the ID3v2 Tag's Attribute names
//
LPCWSTR ID3TagDefs[] =
{
	L"WM/AlbumTitle", // This is same as the global variable g_wszWMAlbumTitle
	L"WM/GenreID",    // This is same as the global variable g_wszWMGenreID
	L"Author",        // This is same as the global variable g_wszWMAuthor
	L"WM/Track",      // This is same as the global variable g_wszWMTrack
	L"WM/TrackNumber",// WMP9
	L"Title",         // This is same as the global variable g_wszWMTitle
	L"WM/Year",       // This is same as the global variable g_wszWMYear
	L"Description",   // This is same as the global variable g_wszWMDescription
	L"WM/GenreID",
	L"WM/Genre",
	L"Copyright",
	L"Is_Protected",
	L"Duration",
	L"WM/PromotionURL",
	L"WM/AlbumCoverURL",
	L"WM/OriginalArtist",
	L"WM/Composer",		// WMP9
	L"WM/Publisher",	// WMP9
	L"WM/AlbumArtist",	// WMP9
	NULL,
} ;

bool LoadAttributeFileWMA(FILE_INFO *pFileMP3)
{
	HRESULT hr = S_OK;

	LPWSTR	pwszInFile = NULL;
	hr = ConvertMBtoWC(GetFullPath(pFileMP3), &pwszInFile);
	if (FAILED(hr)) return(false);

	CoInitialize(NULL);

    IWMMetadataEditor* pEditor      = NULL;
#ifndef USE_WMSDK9
    IWMHeaderInfo*     pHeaderInfo  = NULL;
#else
    IWMHeaderInfo3*    pHeaderInfo  = NULL;
#endif
	BOOL	bIsProtected = FALSE;

	do {
		// Lets create a Metadata Editor.
		hr = WMCreateEditor(&pEditor);
		if (FAILED(hr)) {
			TRACE( _T( "Could not create Metadata Editor (hr=0x%08x).\n" ), hr );
			break ;
		}

		hr = pEditor->Open(pwszInFile);
		if (FAILED(hr)) {
			TRACE( _T( "Could not open outfile %ws (hr=0x%08x).\n" ), pwszInFile, hr );
			break ;
		}

#ifndef USE_WMSDK9
		hr = pEditor->QueryInterface( IID_IWMHeaderInfo, ( void ** ) &pHeaderInfo );
#else
		hr = pEditor->QueryInterface( IID_IWMHeaderInfo3, ( void ** ) &pHeaderInfo );
#endif
		if (FAILED(hr)) {
			TRACE( _T( "Could not QI for IWMHeaderInfo (hr=0x%08x).\n" ), hr );
			break ;
		}

		for (int i = 0; ID3TagDefs[i] != NULL; i++) {
			hr = LoadHeaderAttribute(pHeaderInfo, ID3TagDefs[i], pFileMP3, &bIsProtected);
			if (FAILED(hr)) break;
		}

		hr = pEditor->Close();
		if (FAILED(hr)) {
			TRACE( _T( "Could not close the file %ws (hr=0x%08x).\n" ), pwszInFile, hr) ;
			break;
		}
	}
	while(FALSE);

	SAFE_RELEASE( pHeaderInfo ) ;
	SAFE_RELEASE( pEditor ) ;

	CoUninitialize();

	delete[] pwszInFile;
	pwszInFile = NULL;

	extern bool GetValues_mp3infp(FILE_INFO *pFileMP3);
	GetValues_mp3infp(pFileMP3);

	if (bIsProtected) {
		CString fmt = GetAudioFormat(pFileMP3);
		fmt += ", DRM";
		SetAudioFormat(pFileMP3, fmt);
	}
//	return(bIsProtected ? false : true);
	if (FAILED(hr)) {
		return false;
	} else {
		return true;
	}
}

bool WriteAttributeFileWMA(FILE_INFO *pFileMP3)
{
	HRESULT hr = S_OK;

	LPWSTR	pwszInFile = NULL;
	hr = ConvertMBtoWC((LPCSTR)GetFullPath(pFileMP3), &pwszInFile);
	if (FAILED(hr)) return(false);

	CoInitialize(NULL);

	IWMMetadataEditor* pEditor      = NULL;
#ifndef USE_WMSDK9
    IWMHeaderInfo*     pHeaderInfo  = NULL;
#else
    IWMHeaderInfo3*    pHeaderInfo  = NULL;
#endif

	do {
		//
		// Lets create a Metadata Editor.
		//
		hr = WMCreateEditor( &pEditor );
		if (FAILED(hr)) {
			TRACE( _T( "Could not create Metadata Editor (hr=0x%08x).\n" ), hr );
			break ;
		}

		hr = pEditor->Open( pwszInFile ) ;
		if (FAILED(hr)) {
			TRACE( _T( "Could not open the file %ws (hr=0x%08x).\n" ), pwszInFile, hr );
			break ;
		}

#ifndef USE_WMSDK9
		hr = pEditor->QueryInterface( IID_IWMHeaderInfo, ( void ** ) &pHeaderInfo );
#else
		hr = pEditor->QueryInterface( IID_IWMHeaderInfo3, ( void ** ) &pHeaderInfo );
#endif
		if (FAILED(hr)) {
			TRACE( _T( "Could not QI for IWMHeaderInfo (hr=0x%08x).\n" ), hr );
			break ;
		}
		// タグ情報の出力
		//if (GetBTrackNumber(pFileMP3) > 0 && GetBTrackNumber(pFileMP3) < 0xff) {
		//	WriteAttributeDWORD(pHeaderInfo, L"WM/Track", GetBTrackNumber(pFileMP3) - 1);
		//	WriteAttributeDWORD(pHeaderInfo, L"WM/TrackNumber", GetBTrackNumber(pFileMP3));
		if (strlen(GetTrackNumberSI(pFileMP3)) > 0 && atoi(GetTrackNumberSI(pFileMP3)) > 0) {
			WriteAttributeDWORD(pHeaderInfo, L"WM/Track", atoi(GetTrackNumberSI(pFileMP3)) - 1);
			WriteAttributeDWORD(pHeaderInfo, L"WM/TrackNumber", atoi(GetTrackNumberSI(pFileMP3)));
		} else {
			/**//* ↓で追加した削除処理を使わなくても良いようなのでここで削除 2006.09.27 */
			WriteAttributeStr(pHeaderInfo, L"WM/Track", ""); // アトリビュートを消すのはどうするんだ？
			WriteAttributeStr(pHeaderInfo, L"WM/TrackNumber", ""); // アトリビュートを消すのはどうするんだ？
			WriteAttributeStr(pHeaderInfo, L"ID3/Track", ""); // アトリビュートを消すのはどうするんだ？
			WriteAttributeStr(pHeaderInfo, L"ID3/TRK", ""); // アトリビュートを消すのはどうするんだ？
			WriteAttributeStr(pHeaderInfo, L"ID3/TRCK", ""); // アトリビュートを消すのはどうするんだ？
			/**/
			// ↓に削除処理を追加
		}
		WriteAttributeStr(pHeaderInfo, L"WM/AlbumTitle", GetAlbumNameSI(pFileMP3));
		WriteAttributeStr(pHeaderInfo, L"Author"       , GetArtistNameSI(pFileMP3), TRUE);
		WriteAttributeStr(pHeaderInfo, L"Copyright"    , GetCopyrightSI(pFileMP3));
		WriteAttributeStr(pHeaderInfo, L"Title"        , GetTrackNameSI(pFileMP3));
		WriteAttributeStr(pHeaderInfo, L"Description"  , GetCommentSI(pFileMP3));
		WriteAttributeStr(pHeaderInfo, L"WM/Year"      , GetYearSI(pFileMP3));
		WriteAttributeStr(pHeaderInfo, L"WM/Genre"     , GetGenreSI(pFileMP3), TRUE);
		WriteAttributeStr(pHeaderInfo, L"WM/GenreID"   , GetGenreSI(pFileMP3), TRUE);
		WriteAttributeStr(pHeaderInfo, L"WM/PromotionURL", GetURLSI(pFileMP3), TRUE);
		WriteAttributeStr(pHeaderInfo, L"WM/AlbumCoverURL", GetOther(pFileMP3), TRUE);
		WriteAttributeStr(pHeaderInfo, L"WM/OriginalArtist", GetOrigArtistSI(pFileMP3));
		WriteAttributeStr(pHeaderInfo, L"WM/Composer"  , GetComposerSI(pFileMP3), TRUE);
		WriteAttributeStr(pHeaderInfo, L"WM/AlbumArtist"  , GetKeywordSI(pFileMP3), TRUE);
		WriteAttributeStr(pHeaderInfo, L"WM/Publisher"  , GetEngineerSI(pFileMP3), TRUE); // WMP9

		hr = pEditor->Flush();
		if (FAILED(hr)) {
			TRACE( _T( "Flush failed (hr=0x%08x).\n" ), hr) ;
			break;
		}

		hr = pEditor->Close();
		if (FAILED(hr)) {
			TRACE( _T( "Could not close the file %ws (hr=0x%08x).\n" ), pwszInFile, hr) ;
			break;
		}
	}
	while( FALSE ) ;

	SAFE_RELEASE( pHeaderInfo ) ;
	SAFE_RELEASE( pEditor ) ;

#ifdef __IWMHeaderInfo3_FWD_DEFINED__ /* Conspiracy3 202 */
#if 0 // WriteAttributeStr()で削除されるのでここではやる必要なし
	// トラック番号アトリビュートを削除
	IWMHeaderInfo3*    pHeaderInfo3 = NULL;
	do {
		HRESULT hr = S_OK;
		hr = WMCreateEditor( &pEditor );
		if (FAILED(hr)) {
			TRACE( _T( "Could not create Metadata Editor (hr=0x%08x).\n" ), hr );
			break ;
		}

		hr = pEditor->Open( pwszInFile ) ;
		if (FAILED(hr)) {
			TRACE( _T( "Could not open the file %ws (hr=0x%08x).\n" ), pwszInFile, hr );
			break ;
		}

		hr = pEditor->QueryInterface( IID_IWMHeaderInfo3, ( void ** ) &pHeaderInfo3 );
		if (FAILED(hr)) {
			TRACE( _T( "Could not QI for IWMHeaderInfo3 (hr=0x%08x).\n" ), hr );
			break ;
		}
		// タグ情報の出力
		//if (GetBTrackNumber(pFileMP3) > 0 && GetBTrackNumber(pFileMP3) < 0xff) {
		if (strlen(GetTrackNumberSI(pFileMP3)) > 0 && atoi(GetTrackNumberSI(pFileMP3)) > 0) {
		} else {
			WORD wLangIndex = 0;
			WORD wIndices[1];
			WORD wCount = 1;
			if (pHeaderInfo3->GetAttributeIndices(STREAM_NUM, L"WM/Track", &wLangIndex, wIndices, &wCount) == S_OK && wCount > 0) {
				pHeaderInfo3->DeleteAttribute(STREAM_NUM, wIndices[0]);
			}
			wCount = 1;
			if (pHeaderInfo3->GetAttributeIndices(STREAM_NUM, L"WM/TrackNumber", &wLangIndex, wIndices, &wCount) == S_OK && wCount > 0) {
				pHeaderInfo3->DeleteAttribute(STREAM_NUM, wIndices[0]);
			}
			wCount = 1;
			if (pHeaderInfo3->GetAttributeIndices(STREAM_NUM, L"ID3/Track", &wLangIndex, wIndices, &wCount) == S_OK && wCount > 0) {
				pHeaderInfo3->DeleteAttribute(STREAM_NUM, wIndices[0]);
			}
			wCount = 1;
			if (pHeaderInfo3->GetAttributeIndices(STREAM_NUM, L"ID3/TRK", &wLangIndex, wIndices, &wCount) == S_OK && wCount > 0) {
				pHeaderInfo3->DeleteAttribute(STREAM_NUM, wIndices[0]);
			}
			wCount = 1;
			if (pHeaderInfo3->GetAttributeIndices(STREAM_NUM, L"ID3/TRCK", &wLangIndex, wIndices, &wCount) == S_OK && wCount > 0) {
				pHeaderInfo3->DeleteAttribute(STREAM_NUM, wIndices[0]);
			}
		}
		hr = pEditor->Flush();
		if (FAILED(hr)) {
			TRACE( _T( "Flush failed (hr=0x%08x).\n" ), hr) ;
			break;
		}

		hr = pEditor->Close();
		if (FAILED(hr)) {
			TRACE( _T( "Could not close the file %ws (hr=0x%08x).\n" ), pwszInFile, hr) ;
			break;
		}
	}
	while( FALSE ) ;
	SAFE_RELEASE( pHeaderInfo3 ) ;
	SAFE_RELEASE( pEditor ) ;
#endif
#else
	#warning Undefined symbol <IWMHeaderInfo3>
#endif

	CoUninitialize();

	delete[] pwszInFile;
	pwszInFile = NULL;

	return(FAILED(hr) ? false : true);
}
