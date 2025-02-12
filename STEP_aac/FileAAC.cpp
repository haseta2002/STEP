#include "stdafx.h"
#include "FileAAC.h"
#include "mp4.h"

typedef struct {
	char* name;
	char* value;
	u_int32_t size;
} MetaData;

bool UTF8toSJIS(const char* UTF8, char** SJIS)
{
	unsigned char* data;
	char* buff;
	int size1, size2;
	size1 = MultiByteToWideChar(CP_UTF8, 0, UTF8, -1, 0, 0);
	size1 = size1*sizeof(WCHAR);
	data = (unsigned char*)malloc(size1);
	if(data) {
		MultiByteToWideChar(CP_UTF8, 0, UTF8, -1, (unsigned short*)data,size1/sizeof(WCHAR));

		size2 = WideCharToMultiByte(CP_ACP, 0, (const unsigned short *)data, size1/sizeof(WCHAR),0,0,NULL,NULL);
		size2++;
		buff = (char*)malloc(size2);
		if (buff) {
			WideCharToMultiByte(CP_ACP, 0, (const unsigned short *)data, size1/sizeof(WCHAR), buff, size2, NULL, NULL);
			buff[size2-1] = '\0';
			*SJIS = buff;
		} else {
			*SJIS = NULL;
		}
		delete data;
	}
	return *SJIS != NULL;
}

bool SJIStoUTF8(const char* SJIS, char** UTF8)
{
	unsigned char* data;
	char* buff;
	int size1, size2;
	size1 = MultiByteToWideChar(CP_ACP, 0, SJIS, -1, 0, 0);
	size1 = size1*sizeof(WCHAR);
	data = (unsigned char*)malloc(size1);
	if(data) {
		MultiByteToWideChar(CP_ACP, 0, SJIS, -1, (unsigned short*)data,size1/sizeof(WCHAR));

		size2 = WideCharToMultiByte(CP_UTF8, 0, (const unsigned short *)data, size1/sizeof(WCHAR),0,0,NULL,NULL);
		size2++;
		buff = (char*)malloc(size2);
		if (buff) {
			WideCharToMultiByte(CP_UTF8, 0, (const unsigned short *)data, size1/sizeof(WCHAR), buff, size2, NULL, NULL);
			buff[size2-1] = '\0';
			*UTF8 = buff;
		} else {
			*UTF8 = NULL;
		}
		delete data;
	}
	return *UTF8 != NULL && strlen(*UTF8) > 0;
}

bool LoadFileAAC(FILE_INFO *pFile)
{
    MP4FileHandle h = MP4Read(GetFullPath(pFile), 0);
    if (h == MP4_INVALID_FILE_HANDLE) {
		return false;
	}
	char* value;
	char* buff;
	u_int16_t no, total;
	if (MP4GetMetadataName(h, &value) == true) {
		if (UTF8toSJIS(value, &buff) == true) {
			SetTrackNameSI(pFile, buff);
			free(buff);
		}
	}
	if (MP4GetMetadataArtist(h, &value) == true) {
		if (UTF8toSJIS(value, &buff) == true) {
			SetArtistNameSI(pFile, buff);
			free(buff);
		}
	}
	if (MP4GetMetadataWriter(h, &value) == true) {
		if (UTF8toSJIS(value, &buff) == true) {
			SetComposerSI(pFile, buff);
			free(buff);
		}
	}
	if (MP4GetMetadataComment(h, &value) == true) {
		if (UTF8toSJIS(value, &buff) == true) {
			SetCommentSI(pFile, buff);
			free(buff);
		}
	}
	if (MP4GetMetadataTool(h, &value) == true) {
		if (UTF8toSJIS(value, &buff) == true) {
			SetSoftwareSI(pFile, buff);
			free(buff);
		}
	}
	if (MP4GetMetadataYear(h, &value) == true) {
		if (UTF8toSJIS(value, &buff) == true) {
			SetYearSI(pFile, buff);
			free(buff);
		}
	}
	if (MP4GetMetadataAlbum(h, &value) == true) {
		if (UTF8toSJIS(value, &buff) == true) {
			SetAlbumNameSI(pFile, buff);
			free(buff);
		}
	}
	if (MP4GetMetadataTrack(h, &no, &total) == true) {
		char trackNo[10];
		if (total > 0) {
			sprintf(trackNo, "%d/%d", no, total);
		} else {
			sprintf(trackNo, "%d", no);
		}
		SetTrackNumberSI(pFile, trackNo);
	}
	if (MP4GetMetadataGenre(h, &value) == true) { /* 取得できるようにmp4v2.dllを変更 */
		if (UTF8toSJIS(value, &buff) == true) {
			SetGenreSI(pFile, buff);
			free(buff);
		}
	}
	if (MP4GetMetadataGroup(h, &value) == true) { /* 取得できるようにmp4v2.dllに追加 */
		if (UTF8toSJIS(value, &buff) == true) {
			SetKeywordSI(pFile, buff);
			free(buff);
		}
	}
	if (MP4GetMetadataAlbumArtist(h, &value) == true) { /* 取得できるようにmp4v2.dllに追加 */
		if (UTF8toSJIS(value, &buff) == true) {
			SetAlbumArtistSI(pFile, buff);
			free(buff);
		}
	}
	CString strOther = "";
	if (MP4GetMetadataDisk(h, &no, &total) == true) {
		char diskNo[10];
		if (total > 0 && no > 0) {
			sprintf(diskNo, "%d/%d", no, total);
		} else if (no > 0) {
			sprintf(diskNo, "%d", no);
		} else {
			diskNo[0] = '\0';
		}
		/* STEP 045 */
		SetDiskNumberSI(pFile, diskNo);
		/*
		if (diskNo[0] != '\0') {
			strOther += "DiskNo ";
			strOther += diskNo;
		}
		*/
	}
	{
		u_int16_t tempo;
		if (MP4GetMetadataTempo(h, &tempo) == true) {
			if (tempo > 0) {
				char buff[10];
				sprintf(buff, " %dBPM", tempo);
				strOther += buff;
			}
		}
	}
	{
		u_int8_t cpl;
		if (MP4GetMetadataCompilation(h, &cpl) == true) {
			if (cpl == 1) {
				/* STEP 049 */
				SetCompilationSI(pFile, "1");
				//strOther += " ｺﾝﾋﾟﾚｰｼｮﾝの一部";
			}
		}
	}
	/*{
		const char* name;
		u_int8_t* value;
		u_int32_t size;
		u_int32_t index = 0;
		while (MP4GetMetadataByIndex(h,index, &name, &value, &size) == true) {
			value[size] = '\0';
			if (strcmp(name, "ｩgrp") == 0) {
				if (UTF8toSJIS((char*)value, &buff) == true) {
					SetKeywordSI(pFile, buff);
					free(buff);
				}
			}
			index++;
		}
	}*/
	//MP4TrackId trackId = MP4FindTrackId(pFile, 0, MP4_AUDIO_TRACK_TYPE);
	//SetAudioFormat(pFile, MP4Info(h));
	// mp4info.cpp PrintAudioInfo()
	MP4TrackId trackId = MP4FindTrackId(h, 0);
	static const char* mpeg4AudioNames[] = {
		"MPEG-4 AAC main",
		"MPEG-4 AAC LC", 
		"MPEG-4 AAC SSR",
		"MPEG-4 AAC LTP",
		NULL,
		"MPEG-4 AAC Scalable",
		"MPEG-4 TwinVQ",
		"MPEG-4 CELP",
		"MPEG-4 HVXC",
		NULL, NULL,
		"MPEG-4 TTSI",
		"MPEG-4 Main Synthetic",
		"MPEG-4 Wavetable Syn",
		"MPEG-4 General MIDI",
		"MPEG-4 Algo Syn and Audio FX",
		"MPEG-4 ER AAC LC",
		NULL,
		"MPEG-4 ER AAC LTP",
		"MPEG-4 ER AAC Scalable",
		"MPEG-4 ER TwinVQ",
		"MPEG-4 ER BSAC",
		"MPEG-4 ER ACC LD",
		"MPEG-4 ER CELP",
		"MPEG-4 ER HVXC",
		"MPEG-4 ER HILN",
		"MPEG-4 ER Parametric",
	};
	static u_int8_t mpegAudioTypes[] = {
		MP4_MPEG2_AAC_MAIN_AUDIO_TYPE,	// 0x66
		MP4_MPEG2_AAC_LC_AUDIO_TYPE,	// 0x67
		MP4_MPEG2_AAC_SSR_AUDIO_TYPE,	// 0x68
		MP4_MPEG2_AUDIO_TYPE,			// 0x69
		MP4_MPEG1_AUDIO_TYPE,			// 0x6B
		MP4_PCM16_LITTLE_ENDIAN_AUDIO_TYPE,
		MP4_VORBIS_AUDIO_TYPE,
		MP4_ALAW_AUDIO_TYPE,
		MP4_ULAW_AUDIO_TYPE,
		MP4_G723_AUDIO_TYPE,
		MP4_PCM16_BIG_ENDIAN_AUDIO_TYPE,
	};
	static const char* mpegAudioNames[] = {
		"MPEG-2 AAC Main",
		"MPEG-2 AAC LC",
		"MPEG-2 AAC SSR",
		"MPEG-2 Audio (13818-3)",
		"MPEG-1 Audio (11172-3)",
		"PCM16 (little endian)",
		"Vorbis",
		"G.711 aLaw",
		"G.711 uLaw",
		"G.723.1",
		"PCM16 (big endian)",
	};
	static u_int8_t numMpegAudioTypes = 
		sizeof(mpegAudioTypes) / sizeof(u_int8_t);

	u_int8_t type =
		MP4GetTrackEsdsObjectTypeId(h, trackId);
	const char* typeName = "Unknown";

	if (type == MP4_MPEG4_AUDIO_TYPE) {
	  u_int8_t* pAacConfig = NULL;
	  u_int32_t aacConfigLength;

	  MP4GetTrackESConfiguration(h, 
				     trackId,
				     &pAacConfig,
				     &aacConfigLength);

	  if (pAacConfig != NULL && aacConfigLength >= 2) {
	    type = (pAacConfig[0] >> 3) & 0x1f;
	    if (type == 0 || type == 5 || type == 10 || type == 11 ||
		type == 18 || type >= 28) {
	      typeName = "MPEG-4";
	    } else {
	        typeName = mpeg4AudioNames[type - 1];
	    }
	    MP4Free(pAacConfig);
	  } else {
	    typeName = "MPEG-4";
	  }
	} else {
		for (u_int8_t i = 0; i < numMpegAudioTypes; i++) {
			if (type == mpegAudioTypes[i]) {
				typeName = mpegAudioNames[i];
				break;
			}
		}
	}

	u_int32_t timeScale =
		MP4GetTrackTimeScale(h, trackId);

	MP4Duration trackDuration =
		MP4GetTrackDuration(h, trackId);

	double msDuration =
		UINT64_TO_DOUBLE(MP4ConvertFromTrackDuration(h, trackId, 
			trackDuration, MP4_MSECS_TIME_SCALE));

	u_int32_t avgBitRate =
		MP4GetTrackBitRate(h, trackId);

	/*{
		double durationMSecs = msDuration / 1000;
		//if (trackDuration % timeScale != 0) {
		//	durationMSecs += 1;
		//}

		MP4SampleId sampleId = 1;
		MP4SampleId numSamples = 
			MP4GetTrackNumberOfSamples(h, trackId);
		double sampleSize = 0;
		for (; sampleId <= numSamples; sampleId++) {
			if (MP4GetSampleSize(h, trackId, sampleId) > 0) {
				sampleSize += (MP4GetSampleSize(h, trackId, sampleId) * 8.0);
			}
		}
		avgBitRate = (u_int32_t)(sampleSize / durationMSecs);
	}*/
	// type duration avgBitrate samplingFrequency
	char format[256];
	sprintf(format, "%s %ukbps %uHz", typeName, (avgBitRate + 500) / 1000, timeScale);
	SetAudioFormat(pFile, format);
	SetPlayTime(pFile, (int)(msDuration / 1000.0));
	/*
    if (MP4IsIsmaCrypMediaTrack(h, trackId)) {
	sprintf(sInfo,	
		"%u\taudio\tenca - %s, %.3f secs, %u kbps, %u Hz\n", 
		trackId, 
		typeName, 
		msDuration / 1000.0, 
		(avgBitRate + 500) / 1000, 
		timeScale);
        else
	sprintf(sInfo,	
		"%u\taudio\t%s, %.3f secs, %u kbps, %u Hz\n", 
		trackId, 
		typeName, 
		msDuration / 1000.0, 
		(avgBitRate + 500) / 1000, 
		timeScale);
	*/

	SetOther(pFile, strOther);

	MP4Close(h);
	return true;
}

bool WriteFileAAC(FILE_INFO *pFile)
{
	/*
		size = MultiByteToWideChar(CP_ACP, 0, value, -1, 0, 0);
		size = size*sizeof(WCHAR)+3;
		data = (unsigned char*)malloc(size);
		if(data) {
			MultiByteToWideChar(CP_ACP, 0, value, -1, (unsigned short*)data,size/sizeof(WCHAR));
		}
	*/
    MP4FileHandle h = MP4Read(GetFullPath(pFile), 0/*MP4_DETAILS_ALL*/);
    if (h == MP4_INVALID_FILE_HANDLE) {
      return false;
    }

	u_int32_t index = 0;
	CPtrArray tag;
	typedef struct {
		char* name;
		char* value;
		u_int32_t size;
	} MetaData;
	const char* name;
	u_int8_t* value;
	u_int32_t size;
	while (MP4GetMetadataByIndex(h,index, &name, &value, &size) == true) {
		if (!stricmp(name, "trkn") || !stricmp(name, "tracknumber") ||
			!stricmp(name, "disk") || !stricmp(name, "disknumber") ||	/* STEP 045 */
			!stricmp(name, "cpil") ||	/* STEP 049 */
			//!stricmp(name, "tmxpo") ||
			!stricmp(name, "ｩART") ||
			!stricmp(name, "ｩwrt") ||
			!stricmp(name, "ｩnam") ||
			!stricmp(name, "ｩalb") ||
			!stricmp(name, "ｩday") || !stricmp(name, "year") ||
			!stricmp(name, "ｩcmt") ||
			!stricmp(name, "ｩtoo") ||
			!stricmp(name, "ｩgrp") ||
			!stricmp(name, "aART") ||
			!stricmp(name, "ｩgen")) {
			index++;
			continue;
		}
		MetaData* meta = new MetaData;
		meta->name = (char*)malloc(strlen(name)+1);
		strcpy(meta->name, name);
		meta->value = (char*)malloc(size + 1);
		memcpy(meta->value, value, size);
		meta->value[size] = '\0';
		meta->size = size;
		tag.Add(meta);
		index++;
	}
	if (MP4GetMetadataCoverArt(h, &value, &size) == true) {
		MetaData* meta = new MetaData;
		meta->name = (char*)malloc(strlen("covr")+1);
		strcpy(meta->name, "covr");
		meta->value = (char*)malloc(size + 1);
		memcpy(meta->value, value, size);
		meta->value[size] = '\0';
		meta->size = size;
		tag.Add(meta);
		index++;
	}
	
	MP4Close(h);
    h = MP4Modify(GetFullPath(pFile), 0/*MP4_DETAILS_ALL*/, 0);
    if (h == MP4_INVALID_FILE_HANDLE) {
      return false;
    }
	MP4MetadataDelete(h);

	char* buff;
	{
		unsigned __int16 trkn = 0, tot = 0;
		int t1 = 0, t2 = 0;
		LPCTSTR strTrackNo = GetTrackNumberSI(pFile);
		if (strstr(strTrackNo, "/") != NULL) {
			sscanf(strTrackNo, "%d/%d", &t1, &t2);
			trkn = t1, tot = t2;
		} else {
			sscanf(strTrackNo, "%d", &t1);
			trkn = t1;
		}
		if (trkn > 0) {
			MP4SetMetadataTrack(h, trkn, tot);
		}
	}
	{
		if (SJIStoUTF8(GetArtistNameSI(pFile), &buff) == true) { 
			MP4SetMetadataArtist(h, buff);
			free(buff);
		}
	}
	{
		if (SJIStoUTF8(GetComposerSI(pFile), &buff) == true) { 
			MP4SetMetadataWriter(h, buff);
			free(buff);
		}
	}
	{
		if (SJIStoUTF8(GetTrackNameSI(pFile), &buff) == true) { 
			MP4SetMetadataName(h, buff);
			free(buff);
		}
	}
	{
		if (SJIStoUTF8(GetAlbumNameSI(pFile), &buff) == true) { 
			MP4SetMetadataAlbum(h, buff);
			free(buff);
		}
	}
	{
		if (SJIStoUTF8(GetYearSI(pFile), &buff) == true) { 
			MP4SetMetadataYear(h, buff);
			free(buff);
		}
	}
	{
		if (SJIStoUTF8(GetCommentSI(pFile), &buff) == true) { 
			MP4SetMetadataComment(h, buff);
			free(buff);
		}
	}
	{
		if (SJIStoUTF8(GetGenreSI(pFile), &buff) == true) { 
			MP4SetMetadataGenre(h, buff);
			free(buff);
		}
	}
	{
		if (SJIStoUTF8(GetSoftwareSI(pFile), &buff) == true) { 
			MP4SetMetadataTool(h, buff);
			free(buff);
		}
	}
	{
		if (SJIStoUTF8(GetKeywordSI(pFile), &buff) == true) { 
			MP4SetMetadataGroup(h, buff);
			free(buff);
		}
	}
	{
		if (SJIStoUTF8(GetAlbumArtistSI(pFile), &buff) == true) { 
			MP4SetMetadataAlbumArtist(h, buff);
			free(buff);
		}
	}
	{ /* STEP 045 */
		unsigned __int16 disk, tot;
		int t1 = 0, t2 = 0;
		LPCTSTR strDiskNo = GetDiskNumberSI(pFile);
		if (strstr(strDiskNo, "/") != NULL) {
			sscanf(strDiskNo, "%d/%d", &t1, &t2);
			disk = t1, tot = t2;
		} else {
			sscanf(strDiskNo, "%d", &t1);
			disk = t1;
		}
		if (disk > 0) {
			MP4SetMetadataDisk(h, disk, tot);
		}
	}
	{ /* STEP 049 */
			unsigned __int8 cpil = atoi(GetCompilationSI(pFile));
			if (cpil != 0) {
				MP4SetMetadataCompilation(h, cpil);
			}
	}
	/*
	{
		if (SJIStoUTF8(GetGenreSI(pFile), &buff) == true) { 
			MP4SetMetadataGenre(h, buff);
			free(buff);
		}
	}
	*/

	for (int i=0;i<tag.GetSize();i++) {
		MetaData* meta = (MetaData*)tag.GetAt(i);
		if (false) {
		}
		else if (!stricmp(meta->name, "disk") || !stricmp(meta->name, "disknumber"))
		{ /* STEP 045 */
			/*
			unsigned __int16 disk = 0, tot = 0;
			disk = meta->value[2] << 8 | (meta->value[3] & 0xff);
			tot = meta->value[4] << 8 | (meta->value[5] & 0xff);
			if (disk > 0) {
				MP4SetMetadataDisk(h, disk, tot);
			}
			*/
		}
		else if (!stricmp(meta->name, "cpil"))
		{ /* STEP 049 */
			/*
			unsigned __int8 cpil = meta->value[0];
			if (cpil != 0) {
				MP4SetMetadataCompilation(h, cpil);
			}
			*/
		}
		else if (!stricmp(meta->name, "tmpo"))
		{
			unsigned __int16 tempo = meta->value[0] << 8 | (meta->value[1] & 0xff);
			if (tempo != 0) {
				MP4SetMetadataTempo(h, tempo);
			}
		}
		/*
		else if (!stricmp(meta->name, "ｩART"))
		else if (!stricmp(meta->name, "ｩwrt"))
		else if (!stricmp(meta->name, "ｩnam"))
		else if (!stricmp(meta->name, "ｩalb"))
		else if (!stricmp(meta->name, "ｩday") || !stricmp(meta->name, "year"))
		else if (!stricmp(meta->name, "ｩcmt"))
		else if (!stricmp(meta->name, "ｩgen"))
		else if (!stricmp(meta->name, "ｩtoo"))
		else if (!stricmp(meta->name, "ｩgrp"))
		else if (!stricmp(meta->name, "ｩgen"))
		*/
		else if (!stricmp(meta->name, "covr"))
		{
			MP4SetMetadataCoverArt(h, (u_int8_t*)meta->value, meta->size);
		}
		else
		{
			MP4SetMetadataFreeForm(h, meta->name, (u_int8_t*)meta->value, meta->size);
		}

		free(meta->name);
		free(meta->value);
		delete meta;
	}
	MP4Close(h);
	MP4Optimize(GetFullPath(pFile), NULL, 0/*MP4_DETAILS_ALL*/);

	return true;
}
