/*
 * The contents of this file are subject to the Mozilla Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 * 
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 * 
 * The Original Code is MPEG4IP.
 * 
 * The Initial Developer of the Original Code is Cisco Systems Inc.
 * Portions created by Cisco Systems Inc. are
 * Copyright (C) Cisco Systems Inc. 2001 - 2004.  All Rights Reserved.
 * 
 * 3GPP features implementation is based on 3GPP's TS26.234-v5.60,
 * and was contributed by Ximpo Group Ltd.
 *
 * Portions created by Ximpo Group Ltd. are
 * Copyright (C) Ximpo Group Ltd. 2003, 2004.  All Rights Reserved.
 *
 * Contributor(s): 
 *		Dave Mackie			dmackie@cisco.com
 *		Alix Marchandise-Franquet	alix@cisco.com
 *              Ximpo Group Ltd.                mp4v2@ximpo.com
 */

#ifndef __MP4_INCLUDED__
#define __MP4_INCLUDED__

/* include system and project specific headers */
#include "mpeg4ip.h"

#include <math.h>	/* to define float HUGE_VAL and/or NAN */
#ifndef NAN
#define NAN HUGE_VAL
#endif

#ifdef __cplusplus
/* exploit C++ ability of default values for function parameters */
#define DEFAULT(x)	=x
#else
#define DEFAULT(x)
#endif

/* MP4 API types */
typedef void*		MP4FileHandle;
typedef u_int32_t	MP4TrackId;
typedef u_int32_t	MP4SampleId;
typedef u_int64_t	MP4Timestamp;
typedef u_int64_t	MP4Duration;
typedef u_int32_t	MP4EditId;

/* Invalid values for API types */
#define MP4_INVALID_FILE_HANDLE	((MP4FileHandle)NULL)
#define MP4_INVALID_TRACK_ID	((MP4TrackId)0)
#define MP4_INVALID_SAMPLE_ID	((MP4SampleId)0)
#define MP4_INVALID_TIMESTAMP	((MP4Timestamp)-1)
#define MP4_INVALID_DURATION	((MP4Duration)-1)
#define MP4_INVALID_EDIT_ID		((MP4EditId)0)

/* Macros to test for API type validity */
#define MP4_IS_VALID_FILE_HANDLE(x)	((x) != MP4_INVALID_FILE_HANDLE) 
#define MP4_IS_VALID_TRACK_ID(x)	((x) != MP4_INVALID_TRACK_ID) 
#define MP4_IS_VALID_SAMPLE_ID(x)	((x) != MP4_INVALID_SAMPLE_ID) 
#define MP4_IS_VALID_TIMESTAMP(x)	((x) != MP4_INVALID_TIMESTAMP) 
#define MP4_IS_VALID_DURATION(x)	((x) != MP4_INVALID_DURATION) 
#define MP4_IS_VALID_EDIT_ID(x)		((x) != MP4_INVALID_EDIT_ID) 

/* MP4 verbosity levels - e.g. MP4SetVerbosity() */
#define MP4_DETAILS_ALL				0xFFFFFFFF
#define MP4_DETAILS_ERROR			0x00000001
#define MP4_DETAILS_WARNING			0x00000002
#define MP4_DETAILS_READ			0x00000004
#define MP4_DETAILS_WRITE			0x00000008
#define MP4_DETAILS_FIND			0x00000010
#define MP4_DETAILS_TABLE			0x00000020
#define MP4_DETAILS_SAMPLE			0x00000040
#define MP4_DETAILS_HINT			0x00000080
#define MP4_DETAILS_ISMA			0x00000100
#define MP4_DETAILS_EDIT			0x00000200

#define MP4_DETAILS_READ_ALL		\
	(MP4_DETAILS_READ | MP4_DETAILS_TABLE | MP4_DETAILS_SAMPLE)
#define MP4_DETAILS_WRITE_ALL		\
	(MP4_DETAILS_WRITE | MP4_DETAILS_TABLE | MP4_DETAILS_SAMPLE)

/*
 * MP4 Known track type names - e.g. MP4GetNumberOfTracks(type) 
 *
 * Note this first group of track types should be created 
 * via the MP4Add<Type>Track() functions, and not MP4AddTrack(type)
 */
#define MP4_OD_TRACK_TYPE		"odsm"
#define MP4_SCENE_TRACK_TYPE	"sdsm"
#define MP4_AUDIO_TRACK_TYPE	"soun"
#define MP4_VIDEO_TRACK_TYPE	"vide"
#define MP4_HINT_TRACK_TYPE		"hint"
/*
 * This second set of track types should be created 
 * via MP4AddSystemsTrack(type)
 */
#define MP4_CLOCK_TRACK_TYPE	"crsm"
#define MP4_MPEG7_TRACK_TYPE	"m7sm"
#define MP4_OCI_TRACK_TYPE		"ocsm"
#define MP4_IPMP_TRACK_TYPE		"ipsm"
#define MP4_MPEGJ_TRACK_TYPE	"mjsm"

#define MP4_IS_VIDEO_TRACK_TYPE(type) \
	(!strcasecmp(type, MP4_VIDEO_TRACK_TYPE))

#define MP4_IS_AUDIO_TRACK_TYPE(type) \
	(!strcasecmp(type, MP4_AUDIO_TRACK_TYPE))

#define MP4_IS_OD_TRACK_TYPE(type) \
	(!strcasecmp(type, MP4_OD_TRACK_TYPE))

#define MP4_IS_SCENE_TRACK_TYPE(type) \
	(!strcasecmp(type, MP4_SCENE_TRACK_TYPE))

#define MP4_IS_HINT_TRACK_TYPE(type) \
	(!strcasecmp(type, MP4_HINT_TRACK_TYPE))

#define MP4_IS_SYSTEMS_TRACK_TYPE(type) \
	(!strcasecmp(type, MP4_CLOCK_TRACK_TYPE) \
	|| !strcasecmp(type, MP4_MPEG7_TRACK_TYPE) \
	|| !strcasecmp(type, MP4_OCI_TRACK_TYPE) \
	|| !strcasecmp(type, MP4_IPMP_TRACK_TYPE) \
	|| !strcasecmp(type, MP4_MPEGJ_TRACK_TYPE))

/* MP4 Audio track types - see MP4AddAudioTrack()*/
#define MP4_INVALID_AUDIO_TYPE			0x00
#define MP4_MPEG1_AUDIO_TYPE			0x6B
#define MP4_MPEG2_AUDIO_TYPE			0x69
#define MP4_MP3_AUDIO_TYPE				MP4_MPEG2_AUDIO_TYPE
#define MP4_MPEG2_AAC_MAIN_AUDIO_TYPE	0x66
#define MP4_MPEG2_AAC_LC_AUDIO_TYPE		0x67
#define MP4_MPEG2_AAC_SSR_AUDIO_TYPE	0x68
#define MP4_MPEG2_AAC_AUDIO_TYPE		MP4_MPEG2_AAC_MAIN_AUDIO_TYPE
#define MP4_MPEG4_AUDIO_TYPE			0x40
#define MP4_PRIVATE_AUDIO_TYPE			0xC0
#define MP4_PCM16_LITTLE_ENDIAN_AUDIO_TYPE	0xE0	/* a private definition */
#define MP4_VORBIS_AUDIO_TYPE			0xE1	/* a private definition */
#define MP4_AC3_AUDIO_TYPE				0xE2	/* a private definition */
#define MP4_ALAW_AUDIO_TYPE				0xE3	/* a private definition */
#define MP4_ULAW_AUDIO_TYPE				0xE4	/* a private definition */
#define MP4_G723_AUDIO_TYPE                             0xE5    /* a private definition */
#define MP4_PCM16_BIG_ENDIAN_AUDIO_TYPE         0xE6 /* a private definition */

/* MP4 MPEG-4 Audio types from 14496-3 Table 1.5.1 */
#define MP4_MPEG4_INVALID_AUDIO_TYPE		0
#define MP4_MPEG4_AAC_MAIN_AUDIO_TYPE		1
#define MP4_MPEG4_AAC_LC_AUDIO_TYPE			2
#define MP4_MPEG4_AAC_SSR_AUDIO_TYPE		3
#define MP4_MPEG4_AAC_LTP_AUDIO_TYPE		4
#define MP4_MPEG4_AAC_SCALABLE_AUDIO_TYPE	6
#define MP4_MPEG4_CELP_AUDIO_TYPE			8
#define MP4_MPEG4_HVXC_AUDIO_TYPE			9
#define MP4_MPEG4_TTSI_AUDIO_TYPE			12
#define MP4_MPEG4_MAIN_SYNTHETIC_AUDIO_TYPE	13
#define MP4_MPEG4_WAVETABLE_AUDIO_TYPE		14
#define MP4_MPEG4_MIDI_AUDIO_TYPE			15
#define MP4_MPEG4_ALGORITHMIC_FX_AUDIO_TYPE	16

/* MP4 Audio type utilities following common usage */
#define MP4_IS_MP3_AUDIO_TYPE(type) \
	((type) == MP4_MPEG1_AUDIO_TYPE || (type) == MP4_MPEG2_AUDIO_TYPE) 

#define MP4_IS_MPEG2_AAC_AUDIO_TYPE(type) \
	(((type) >= MP4_MPEG2_AAC_MAIN_AUDIO_TYPE \
		&& (type) <= MP4_MPEG2_AAC_SSR_AUDIO_TYPE))

#define MP4_IS_MPEG4_AAC_AUDIO_TYPE(mpeg4Type) \
	(((mpeg4Type) >= MP4_MPEG4_AAC_MAIN_AUDIO_TYPE \
		&& (mpeg4Type) <= MP4_MPEG4_AAC_LTP_AUDIO_TYPE) \
	  || (mpeg4Type) == MP4_MPEG4_AAC_SCALABLE_AUDIO_TYPE \
          || (mpeg4Type) == 17)

#define MP4_IS_AAC_AUDIO_TYPE(type) \
	(MP4_IS_MPEG2_AAC_AUDIO_TYPE(type) \
	|| (type) == MP4_MPEG4_AUDIO_TYPE)

/* MP4 Video track types - see MP4AddVideoTrack() */
#define MP4_INVALID_VIDEO_TYPE			0x00
#define MP4_MPEG1_VIDEO_TYPE			0x6A
#define MP4_MPEG2_SIMPLE_VIDEO_TYPE		0x60
#define MP4_MPEG2_MAIN_VIDEO_TYPE		0x61
#define MP4_MPEG2_SNR_VIDEO_TYPE		0x62
#define MP4_MPEG2_SPATIAL_VIDEO_TYPE	0x63
#define MP4_MPEG2_HIGH_VIDEO_TYPE		0x64
#define MP4_MPEG2_442_VIDEO_TYPE		0x65
#define MP4_MPEG2_VIDEO_TYPE			MP4_MPEG2_MAIN_VIDEO_TYPE
#define MP4_MPEG4_VIDEO_TYPE			0x20
#define MP4_JPEG_VIDEO_TYPE				0x6C
#define MP4_PRIVATE_VIDEO_TYPE			0xD0
#define MP4_YUV12_VIDEO_TYPE			0xF0	/* a private definition */
#define MP4_H264_VIDEO_TYPE				0xF1	/* a private definition */
#define MP4_H263_VIDEO_TYPE				0xF2	/* a private definition */
#define MP4_H261_VIDEO_TYPE				0xF3	/* a private definition */

/* MP4 Video type utilities */
#define MP4_IS_MPEG1_VIDEO_TYPE(type) \
	((type) == MP4_MPEG1_VIDEO_TYPE)

#define MP4_IS_MPEG2_VIDEO_TYPE(type) \
	(((type) >= MP4_MPEG2_SIMPLE_VIDEO_TYPE \
		&& (type) <= MP4_MPEG2_442_VIDEO_TYPE) \
	  || MP4_IS_MPEG1_VIDEO_TYPE(type))

#define MP4_IS_MPEG4_VIDEO_TYPE(type) \
	((type) == MP4_MPEG4_VIDEO_TYPE)

/* Mpeg4 Visual Profile Defines - ISO/IEC 14496-2:2001/Amd.2:2002(E) */
#define MPEG4_SP_L1 (0x1)
#define MPEG4_SP_L2 (0x2)
#define MPEG4_SP_L3 (0x3)
#define MPEG4_SP_L0 (0x8)
#define MPEG4_SSP_L1 (0x11)
#define MPEG4_SSP_L2 (0x12)
#define MPEG4_CP_L1 (0x21)
#define MPEG4_CP_L2 (0x22)
#define MPEG4_MP_L2 (0x32)
#define MPEG4_MP_L3 (0x33)
#define MPEG4_MP_L4 (0x34)
#define MPEG4_NBP_L2 (0x42)
#define MPEG4_STP_L1 (0x51)
#define MPEG4_SFAP_L1 (0x61)
#define MPEG4_SFAP_L2 (0x62)
#define MPEG4_SFBAP_L1 (0x63)
#define MPEG4_SFBAP_L2 (0x64)
#define MPEG4_BATP_L1 (0x71)
#define MPEG4_BATP_L2 (0x72)
#define MPEG4_HP_L1 (0x81)
#define MPEG4_HP_L2 (0x82)
#define MPEG4_ARTSP_L1 (0x91)
#define MPEG4_ARTSP_L2 (0x92)
#define MPEG4_ARTSP_L3 (0x93)
#define MPEG4_ARTSP_L4 (0x94)
#define MPEG4_CSP_L1 (0xa1)
#define MPEG4_CSP_L2 (0xa2)
#define MPEG4_CSP_L3 (0xa3)
#define MPEG4_ACEP_L1 (0xb1)
#define MPEG4_ACEP_L2 (0xb2)
#define MPEG4_ACEP_L3 (0xb3)
#define MPEG4_ACEP_L4 (0xb4)
#define MPEG4_ACP_L1 (0xc1)
#define MPEG4_ACP_L2 (0xc2)
#define MPEG4_AST_L1 (0xd1)
#define MPEG4_AST_L2 (0xd2)
#define MPEG4_AST_L3 (0xd3)
#define MPEG4_S_STUDIO_P_L1 (0xe1)
#define MPEG4_S_STUDIO_P_L2 (0xe2)
#define MPEG4_S_STUDIO_P_L3 (0xe3)
#define MPEG4_S_STUDIO_P_L4 (0xe4)
#define MPEG4_C_STUDIO_P_L1 (0xe5)
#define MPEG4_C_STUDIO_P_L2 (0xe6)
#define MPEG4_C_STUDIO_P_L3 (0xe7)
#define MPEG4_C_STUDIO_P_L4 (0xe8)
#define MPEG4_ASP_L0 (0xF0)
#define MPEG4_ASP_L1 (0xF1)
#define MPEG4_ASP_L2 (0xF2)
#define MPEG4_ASP_L3 (0xF3)
#define MPEG4_ASP_L4 (0xF4)
#define MPEG4_ASP_L5 (0xF5)
#define MPEG4_ASP_L3B (0xF7)
#define MPEG4_FGSP_L0 (0xf8)
#define MPEG4_FGSP_L1 (0xf9)
#define MPEG4_FGSP_L2 (0xfa)
#define MPEG4_FGSP_L3 (0xfb)
#define MPEG4_FGSP_L4 (0xfc)
#define MPEG4_FGSP_L5 (0xfd)

/* MP4 API declarations */

#ifdef __cplusplus
extern "C" {
#endif

/* file operations */
#define MP4_CREATE_64BIT_DATA (0x01)
#define MP4_CREATE_64BIT_TIME (0x02) // Quicktime is not compatible with this
#define MP4_CREATE_64BIT (MP4_CREATE_64BIT_DATA | MP4_CREATE_64BIT_TIME)
#define MP4_CREATE_EXTENSIBLE_FORMAT (0x04)

#define _STEP_EXPORT_ extern "C" __declspec(dllexport) 

_STEP_EXPORT_ MP4FileHandle MP4Create(
	const char* fileName, 
	u_int32_t verbosity DEFAULT(0),
	u_int32_t flags DEFAULT(0));

_STEP_EXPORT_ MP4FileHandle MP4CreateEx(
		const char* fileName,
		u_int32_t verbosity DEFAULT(0),
		u_int32_t flags  DEFAULT(0),
		char* majorBrand DEFAULT(0),
		u_int32_t minorVersion DEFAULT(0),
		char** supportedBrands DEFAULT(0),
		u_int32_t supportedBrandsCount DEFAULT(0));

_STEP_EXPORT_ MP4FileHandle MP4Modify(
	const char* fileName, 
	u_int32_t verbosity DEFAULT(0),
	u_int32_t flags DEFAULT(0));

_STEP_EXPORT_ MP4FileHandle MP4Read(
	const char* fileName, 
	u_int32_t verbosity DEFAULT(0));

_STEP_EXPORT_ bool MP4Close(
	MP4FileHandle hFile);

_STEP_EXPORT_ bool MP4Optimize(
	const char* existingFileName, 
	const char* newFileName DEFAULT(NULL), 
	u_int32_t verbosity DEFAULT(0));

_STEP_EXPORT_ bool MP4Dump(
	MP4FileHandle hFile, 
	FILE* pDumpFile DEFAULT(NULL), 
	bool dumpImplicits DEFAULT(0));

_STEP_EXPORT_ char* MP4Info(
	MP4FileHandle hFile, 
	MP4TrackId trackId DEFAULT(MP4_INVALID_TRACK_ID));

_STEP_EXPORT_ char* MP4FileInfo(
	const char* fileName,
	MP4TrackId trackId DEFAULT(MP4_INVALID_TRACK_ID));

/* file properties */

/* specific file properties */

_STEP_EXPORT_ u_int32_t MP4GetVerbosity(MP4FileHandle hFile);

_STEP_EXPORT_ bool MP4SetVerbosity(MP4FileHandle hFile, u_int32_t verbosity);

_STEP_EXPORT_ MP4Duration MP4GetDuration(MP4FileHandle hFile);

_STEP_EXPORT_ u_int32_t MP4GetTimeScale(MP4FileHandle hFile);

_STEP_EXPORT_ bool MP4SetTimeScale(MP4FileHandle hFile, u_int32_t value);

_STEP_EXPORT_ u_int8_t MP4GetODProfileLevel(MP4FileHandle hFile);

_STEP_EXPORT_ bool MP4SetODProfileLevel(MP4FileHandle hFile, u_int8_t value);

_STEP_EXPORT_ u_int8_t MP4GetSceneProfileLevel(MP4FileHandle hFile);

_STEP_EXPORT_ bool MP4SetSceneProfileLevel(MP4FileHandle hFile, u_int8_t value);

_STEP_EXPORT_ u_int8_t MP4GetVideoProfileLevel(MP4FileHandle hFile);

_STEP_EXPORT_ bool MP4SetVideoProfileLevel(MP4FileHandle hFile, u_int8_t value);

_STEP_EXPORT_ u_int8_t MP4GetAudioProfileLevel(MP4FileHandle hFile);

_STEP_EXPORT_ bool MP4SetAudioProfileLevel(MP4FileHandle hFile, u_int8_t value);

_STEP_EXPORT_ u_int8_t MP4GetGraphicsProfileLevel(MP4FileHandle hFile);

_STEP_EXPORT_ bool MP4SetGraphicsProfileLevel(MP4FileHandle hFile, u_int8_t value);

/* generic file properties */

_STEP_EXPORT_ u_int64_t MP4GetIntegerProperty(
	MP4FileHandle hFile, 
	const char* propName);

_STEP_EXPORT_ bool MP4HaveTrackIntegerProperty(
	MP4FileHandle hFile, MP4TrackId trackId, 
	const char* propName);

_STEP_EXPORT_ float MP4GetFloatProperty(
	MP4FileHandle hFile, 
	const char* propName);

_STEP_EXPORT_ const char* MP4GetStringProperty(
	MP4FileHandle hFile, 
	const char* propName);

_STEP_EXPORT_ void MP4GetBytesProperty(
	MP4FileHandle hFile, 
	const char* propName,
	u_int8_t** ppValue, 
	u_int32_t* pValueSize);

_STEP_EXPORT_ bool MP4SetIntegerProperty(
	MP4FileHandle hFile, 
	const char* propName, 
	int64_t value);

_STEP_EXPORT_ bool MP4SetFloatProperty(
	MP4FileHandle hFile, 
	const char* propName, 
	float value);

_STEP_EXPORT_ bool MP4SetStringProperty(
	MP4FileHandle hFile, const char* propName, const char* value);

bool MP4SetBytesProperty(
	MP4FileHandle hFile, const char* propName, 
	const u_int8_t* pValue, u_int32_t valueSize);

/* track operations */

_STEP_EXPORT_ MP4TrackId MP4AddTrack(
	MP4FileHandle hFile, 
	const char* type);

_STEP_EXPORT_ MP4TrackId MP4AddSystemsTrack(
	MP4FileHandle hFile, 
	const char* type);

_STEP_EXPORT_ MP4TrackId MP4AddODTrack(
	MP4FileHandle hFile);

_STEP_EXPORT_ MP4TrackId MP4AddSceneTrack(
	MP4FileHandle hFile);

_STEP_EXPORT_ MP4TrackId MP4AddAudioTrack(
	MP4FileHandle hFile, 
	u_int32_t timeScale, 
	MP4Duration sampleDuration,
	u_int8_t audioType DEFAULT(MP4_MPEG4_AUDIO_TYPE));

_STEP_EXPORT_ typedef struct mp4v2_ismacryp_session_params {
  u_int32_t  scheme_type;
  u_int16_t  scheme_version;
  u_int8_t  key_ind_len;
  u_int8_t  iv_len;
  u_int8_t  selective_enc;
  char      *kms_uri;
} mp4v2_ismacrypParams;


_STEP_EXPORT_ MP4TrackId MP4AddEncAudioTrack(
	MP4FileHandle hFile, 
	u_int32_t timeScale, 
	MP4Duration sampleDuration,
        mp4v2_ismacrypParams *icPp,
	u_int8_t audioType DEFAULT(MP4_MPEG4_AUDIO_TYPE));
_STEP_EXPORT_ MP4TrackId MP4AddAmrAudioTrack(
		MP4FileHandle hFile,
		u_int32_t timeScale,
		u_int16_t modeSet,
		u_int8_t modeChangePeriod,
		u_int8_t framesPerSample,
		bool isAmrWB);

_STEP_EXPORT_ void MP4SetAmrVendor(
		MP4FileHandle hFile,
		MP4TrackId trackId,
		u_int32_t vendor);

_STEP_EXPORT_ void MP4SetAmrDecoderVersion(
		MP4FileHandle hFile,
		MP4TrackId trackId,
		u_int8_t decoderVersion);

_STEP_EXPORT_ void MP4SetAmrModeSet(
		MP4FileHandle hFile,
		MP4TrackId trackId,
		u_int16_t modeSet);

_STEP_EXPORT_ MP4TrackId MP4AddVideoTrack(
	MP4FileHandle hFile, 
	u_int32_t timeScale, 
	MP4Duration sampleDuration,
	u_int16_t width, 
	u_int16_t height,
	u_int8_t videoType DEFAULT(MP4_MPEG4_VIDEO_TYPE));

_STEP_EXPORT_ MP4TrackId MP4AddEncVideoTrack(
	MP4FileHandle hFile, 
	u_int32_t timeScale, 
	MP4Duration sampleDuration,
	u_int16_t width, 
	u_int16_t height,
        mp4v2_ismacrypParams *icPp,
	u_int8_t videoType DEFAULT(MP4_MPEG4_VIDEO_TYPE));

_STEP_EXPORT_ void MP4SetH263Vendor(
		MP4FileHandle hFile,
		MP4TrackId trackId,
		u_int32_t vendor);

_STEP_EXPORT_ void  MP4SetH263DecoderVersion(
		MP4FileHandle hFile,
		MP4TrackId trackId,
		u_int8_t decoderVersion);

_STEP_EXPORT_ void MP4SetH263Bitrates(
		MP4FileHandle hFile,
		MP4TrackId trackId,
		u_int32_t avgBitrate,
		u_int32_t maxBitrate);

_STEP_EXPORT_ MP4TrackId MP4AddH263VideoTrack(
		MP4FileHandle hFile,
		u_int32_t timeScale,
		MP4Duration sampleDuration,
		u_int16_t width,
		u_int16_t height,
		u_int8_t h263Level,
		u_int8_t h263Profile,
		u_int32_t avgBitrate,
		u_int32_t maxBitrate);

_STEP_EXPORT_ MP4TrackId MP4AddHintTrack(
	MP4FileHandle hFile, 
	MP4TrackId refTrackId);

_STEP_EXPORT_ MP4TrackId MP4CloneTrack(
	MP4FileHandle srcFile, 
	MP4TrackId srcTrackId,
	MP4FileHandle dstFile DEFAULT(MP4_INVALID_FILE_HANDLE),
	MP4TrackId dstHintTrackReferenceTrack DEFAULT(MP4_INVALID_TRACK_ID));

_STEP_EXPORT_ MP4TrackId MP4EncAndCloneTrack(
        MP4FileHandle srcFile,
        MP4TrackId srcTrackId,
        mp4v2_ismacrypParams *icPp,
        MP4FileHandle dstFile DEFAULT(MP4_INVALID_FILE_HANDLE),
        MP4TrackId dstHintTrackReferenceTrack DEFAULT(MP4_INVALID_TRACK_ID));

_STEP_EXPORT_ MP4TrackId MP4CopyTrack(
	MP4FileHandle srcFile, 
	MP4TrackId srcTrackId,
	MP4FileHandle dstFile DEFAULT(MP4_INVALID_FILE_HANDLE), 
	bool applyEdits DEFAULT(false),
	MP4TrackId dstHintTrackReferenceTrack DEFAULT(MP4_INVALID_TRACK_ID));

_STEP_EXPORT_ typedef u_int32_t (*encryptFunc_t)(u_int32_t, u_int32_t, u_int8_t*, u_int32_t*, u_int8_t **);

_STEP_EXPORT_ MP4TrackId MP4EncAndCopyTrack(
	MP4FileHandle srcFile, 
	MP4TrackId srcTrackId,
        mp4v2_ismacrypParams *icPp,
        encryptFunc_t encfcnp,
        u_int32_t encfcnparam1,
	MP4FileHandle dstFile DEFAULT(MP4_INVALID_FILE_HANDLE),
	bool applyEdits DEFAULT(false),
	MP4TrackId dstHintTrackReferenceTrack DEFAULT(MP4_INVALID_TRACK_ID));

_STEP_EXPORT_ bool MP4DeleteTrack(
	MP4FileHandle hFile, 
	MP4TrackId trackId);

_STEP_EXPORT_ u_int32_t MP4GetNumberOfTracks(
	MP4FileHandle hFile, 
	const char* type DEFAULT(NULL),
	u_int8_t subType DEFAULT(0));

_STEP_EXPORT_ MP4TrackId MP4FindTrackId(
	MP4FileHandle hFile, 
	u_int16_t index, 
	const char* type DEFAULT(NULL),
	u_int8_t subType DEFAULT(0));

_STEP_EXPORT_ u_int16_t MP4FindTrackIndex(
	MP4FileHandle hFile, 
	MP4TrackId trackId);

/* track properties */

/* specific track properties */

_STEP_EXPORT_ const char* MP4GetTrackType(
	MP4FileHandle hFile, 
	MP4TrackId trackId);

_STEP_EXPORT_ MP4Duration MP4GetTrackDuration(
	MP4FileHandle hFile, 
	MP4TrackId trackId);

_STEP_EXPORT_ u_int32_t MP4GetTrackTimeScale(
	MP4FileHandle hFile, 
	MP4TrackId trackId);

_STEP_EXPORT_ bool MP4SetTrackTimeScale(
	MP4FileHandle hFile, 
	MP4TrackId trackId, 
	u_int32_t value);

// Should not be used, replace with MP4GetTrackEsdsObjectTypeId
_STEP_EXPORT_ u_int8_t MP4GetTrackAudioType(
	MP4FileHandle hFile, 
	MP4TrackId trackId);

_STEP_EXPORT_ u_int8_t MP4GetTrackAudioMpeg4Type(
	MP4FileHandle hFile, 
	MP4TrackId trackId);

// Should not be used, replace with MP4GetTrackEsdsObjectTypeId
_STEP_EXPORT_ u_int8_t MP4GetTrackVideoType(
	MP4FileHandle hFile, 
	MP4TrackId trackId);

_STEP_EXPORT_ u_int8_t MP4GetTrackEsdsObjectTypeId(
	MP4FileHandle hFile, 
	MP4TrackId trackId);

/* returns MP4_INVALID_DURATION if track samples do not have a fixed duration */
_STEP_EXPORT_ MP4Duration MP4GetTrackFixedSampleDuration(
	MP4FileHandle hFile, 
	MP4TrackId trackId);

_STEP_EXPORT_ u_int32_t MP4GetTrackBitRate(
	MP4FileHandle hFile, 
	MP4TrackId trackId);

_STEP_EXPORT_ bool MP4GetTrackESConfiguration(
	MP4FileHandle hFile, 
	MP4TrackId trackId, 
	u_int8_t** ppConfig, 
	u_int32_t* pConfigSize);

_STEP_EXPORT_ bool MP4SetTrackESConfiguration(
	MP4FileHandle hFile, 
	MP4TrackId trackId, 
	const u_int8_t* pConfig, 
	u_int32_t configSize);

_STEP_EXPORT_ MP4SampleId MP4GetTrackNumberOfSamples(
	MP4FileHandle hFile, 
	MP4TrackId trackId);

_STEP_EXPORT_ u_int16_t MP4GetTrackVideoWidth(
	MP4FileHandle hFile, 
	MP4TrackId trackId);

_STEP_EXPORT_ u_int16_t MP4GetTrackVideoHeight(
	MP4FileHandle hFile, 
	MP4TrackId trackId);

_STEP_EXPORT_ float MP4GetTrackVideoFrameRate(
	MP4FileHandle hFile, 
	MP4TrackId trackId);

_STEP_EXPORT_ bool MP4IsIsmaCrypMediaTrack(
        MP4FileHandle hFile,
        MP4TrackId trackId);

/* generic track properties */

_STEP_EXPORT_ u_int64_t MP4GetTrackIntegerProperty(
	MP4FileHandle hFile, 
	MP4TrackId trackId, 
	const char* propName);

_STEP_EXPORT_ float MP4GetTrackFloatProperty(
	MP4FileHandle hFile, 
	MP4TrackId trackId, 
	const char* propName);

_STEP_EXPORT_ const char* MP4GetTrackStringProperty(
	MP4FileHandle hFile, 
	MP4TrackId trackId, 
	const char* propName);

_STEP_EXPORT_ void MP4GetTrackBytesProperty(
	MP4FileHandle hFile, 
	MP4TrackId trackId, 
	const char* propName,
	u_int8_t** ppValue, 
	u_int32_t* pValueSize);

_STEP_EXPORT_ bool MP4SetTrackIntegerProperty(
	MP4FileHandle hFile, 
	MP4TrackId trackId, 
	const char* propName, 
	int64_t value);

_STEP_EXPORT_ bool MP4SetTrackFloatProperty(
	MP4FileHandle hFile, 
	MP4TrackId trackId, 
	const char* propName, 
	float value);

_STEP_EXPORT_ bool MP4SetTrackStringProperty(
	MP4FileHandle hFile, 
	MP4TrackId trackId, 
	const char* propName, 
	const char* value);

_STEP_EXPORT_ bool MP4SetTrackBytesProperty(
	MP4FileHandle hFile, 
	MP4TrackId trackId, 
	const char* propName, 
	const u_int8_t* pValue, 
	u_int32_t valueSize);

/* sample operations */

_STEP_EXPORT_ bool MP4ReadSample(
	/* input parameters */
	MP4FileHandle hFile,
	MP4TrackId trackId, 
	MP4SampleId sampleId,
	/* input/output parameters */
	u_int8_t** ppBytes, 
	u_int32_t* pNumBytes, 
	/* output parameters */
	MP4Timestamp* pStartTime DEFAULT(NULL), 
	MP4Duration* pDuration DEFAULT(NULL),
	MP4Duration* pRenderingOffset DEFAULT(NULL), 
	bool* pIsSyncSample DEFAULT(NULL));

/* uses (unedited) time to specify sample instead of sample id */
_STEP_EXPORT_ bool MP4ReadSampleFromTime(
	/* input parameters */
	MP4FileHandle hFile,
	MP4TrackId trackId, 
	MP4Timestamp when,
	/* input/output parameters */
	u_int8_t** ppBytes, 
	u_int32_t* pNumBytes, 
	/* output parameters */
	MP4Timestamp* pStartTime DEFAULT(NULL), 
	MP4Duration* pDuration DEFAULT(NULL),
	MP4Duration* pRenderingOffset DEFAULT(NULL), 
	bool* pIsSyncSample DEFAULT(NULL));

_STEP_EXPORT_ bool MP4WriteSample(
	MP4FileHandle hFile,
	MP4TrackId trackId,
	const u_int8_t* pBytes, 
	u_int32_t numBytes,
	MP4Duration duration DEFAULT(MP4_INVALID_DURATION),
	MP4Duration renderingOffset DEFAULT(0), 
	bool isSyncSample DEFAULT(true));

_STEP_EXPORT_ bool MP4CopySample(
	MP4FileHandle srcFile,
	MP4TrackId srcTrackId, 
	MP4SampleId srcSampleId,
	MP4FileHandle dstFile DEFAULT(MP4_INVALID_FILE_HANDLE),
	MP4TrackId dstTrackId DEFAULT(MP4_INVALID_TRACK_ID),
	MP4Duration dstSampleDuration DEFAULT(MP4_INVALID_DURATION));

_STEP_EXPORT_ bool MP4EncAndCopySample(
	MP4FileHandle srcFile,
	MP4TrackId srcTrackId, 
	MP4SampleId srcSampleId,
        encryptFunc_t encfcnp,
        u_int32_t encfcnparam1,
	MP4FileHandle dstFile DEFAULT(MP4_INVALID_FILE_HANDLE),
	MP4TrackId dstTrackId DEFAULT(MP4_INVALID_TRACK_ID),
	MP4Duration dstSampleDuration DEFAULT(MP4_INVALID_DURATION));

/* Note this function is not yet implemented */
_STEP_EXPORT_ bool MP4ReferenceSample(
	MP4FileHandle srcFile,
	MP4TrackId srcTrackId, 
	MP4SampleId srcSampleId,
	MP4FileHandle dstFile,
	MP4TrackId dstTrackId,
	MP4Duration dstSampleDuration DEFAULT(MP4_INVALID_DURATION));

_STEP_EXPORT_ u_int32_t MP4GetSampleSize(
	MP4FileHandle hFile,
	MP4TrackId trackId, 
	MP4SampleId sampleId);

_STEP_EXPORT_ u_int32_t MP4GetTrackMaxSampleSize(
	MP4FileHandle hFile,
	MP4TrackId trackId); 

_STEP_EXPORT_ MP4SampleId MP4GetSampleIdFromTime(
	MP4FileHandle hFile,
	MP4TrackId trackId, 
	MP4Timestamp when, 
	bool wantSyncSample DEFAULT(false));

_STEP_EXPORT_ MP4Timestamp MP4GetSampleTime(
	MP4FileHandle hFile,
	MP4TrackId trackId, 
	MP4SampleId sampleId);

_STEP_EXPORT_ MP4Duration MP4GetSampleDuration(
	MP4FileHandle hFile,
	MP4TrackId trackId, 
	MP4SampleId sampleId);

_STEP_EXPORT_ MP4Duration MP4GetSampleRenderingOffset(
	MP4FileHandle hFile,
	MP4TrackId trackId, 
	MP4SampleId sampleId);

_STEP_EXPORT_ bool MP4SetSampleRenderingOffset(
	MP4FileHandle hFile,
	MP4TrackId trackId, 
	MP4SampleId sampleId,
	MP4Duration renderingOffset);

_STEP_EXPORT_ int8_t MP4GetSampleSync(
	MP4FileHandle hFile,
	MP4TrackId trackId, 
	MP4SampleId sampleId);

/* rtp hint track operations */

_STEP_EXPORT_ bool MP4GetHintTrackRtpPayload(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId,
	char** ppPayloadName DEFAULT(NULL),
	u_int8_t* pPayloadNumber DEFAULT(NULL),
	u_int16_t* pMaxPayloadSize DEFAULT(NULL),
	char **ppEncodingParams DEFAULT(NULL));

#define MP4_SET_DYNAMIC_PAYLOAD 0xff

_STEP_EXPORT_ bool MP4SetHintTrackRtpPayload(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId,
	const char* pPayloadName,
	u_int8_t* pPayloadNumber,
	u_int16_t maxPayloadSize DEFAULT(0),
	const char *encode_params DEFAULT(NULL),
	bool include_rtp_map DEFAULT(true),
	bool include_mpeg4_esid DEFAULT(true));

_STEP_EXPORT_ const char* MP4GetSessionSdp(
	MP4FileHandle hFile);

_STEP_EXPORT_ bool MP4SetSessionSdp(
	MP4FileHandle hFile,
	const char* sdpString);

_STEP_EXPORT_ bool MP4AppendSessionSdp(
	MP4FileHandle hFile,
	const char* sdpString);

_STEP_EXPORT_ const char* MP4GetHintTrackSdp(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId);

_STEP_EXPORT_ bool MP4SetHintTrackSdp(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId,
	const char* sdpString);

_STEP_EXPORT_ bool MP4AppendHintTrackSdp(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId,
	const char* sdpString);

_STEP_EXPORT_ MP4TrackId MP4GetHintTrackReferenceTrackId(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId);

_STEP_EXPORT_ bool MP4ReadRtpHint(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId,
	MP4SampleId hintSampleId,
	u_int16_t* pNumPackets DEFAULT(NULL));

_STEP_EXPORT_ u_int16_t MP4GetRtpHintNumberOfPackets(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId);

_STEP_EXPORT_ int8_t MP4GetRtpPacketBFrame(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId,
	u_int16_t packetIndex);

_STEP_EXPORT_ int32_t MP4GetRtpPacketTransmitOffset(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId,
	u_int16_t packetIndex);

_STEP_EXPORT_ bool MP4ReadRtpPacket(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId,
	u_int16_t packetIndex,
	u_int8_t** ppBytes, 
	u_int32_t* pNumBytes,
	u_int32_t ssrc DEFAULT(0),
	bool includeHeader DEFAULT(true),
	bool includePayload DEFAULT(true));

_STEP_EXPORT_ MP4Timestamp MP4GetRtpTimestampStart(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId);

_STEP_EXPORT_ bool MP4SetRtpTimestampStart(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId,
	MP4Timestamp rtpStart);

_STEP_EXPORT_ bool MP4AddRtpHint(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId);

_STEP_EXPORT_ bool MP4AddRtpVideoHint(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId,
	bool isBframe DEFAULT(false), 
	u_int32_t timestampOffset DEFAULT(0));

_STEP_EXPORT_ bool MP4AddRtpPacket(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId,
	bool setMbit DEFAULT(false),
	int32_t transmitOffset DEFAULT(0));

_STEP_EXPORT_ bool MP4AddRtpImmediateData(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId,
	const u_int8_t* pBytes,
	u_int32_t numBytes);

_STEP_EXPORT_ bool MP4AddRtpSampleData(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId,
	MP4SampleId sampleId,
	u_int32_t dataOffset,
	u_int32_t dataLength);

_STEP_EXPORT_ bool MP4AddRtpESConfigurationPacket(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId);

_STEP_EXPORT_ bool MP4WriteRtpHint(
	MP4FileHandle hFile,
	MP4TrackId hintTrackId,
	MP4Duration duration,
	bool isSyncSample DEFAULT(true));

/* 3GP specific utilities */

_STEP_EXPORT_ bool MP4Make3GPCompliant(
	const char* fileName,
	u_int32_t verbosity DEFAULT(0),
	char* majorBrand DEFAULT(0),
	u_int32_t minorVersion DEFAULT(0),
	char** supportedBrands DEFAULT(NULL),
	u_int32_t supportedBrandsCount DEFAULT(0),
	bool deleteIodsAtom DEFAULT(true));

/* ISMA specific utilities */

_STEP_EXPORT_ bool MP4MakeIsmaCompliant(const char* fileName, 
	u_int32_t verbosity DEFAULT(0),
	bool addIsmaComplianceSdp DEFAULT(true));

_STEP_EXPORT_ char* MP4MakeIsmaSdpIod(
	u_int8_t videoProfile,
	u_int32_t videoBitrate,
	u_int8_t* videoConfig,
	u_int32_t videoConfigLength,
	u_int8_t audioProfile,
	u_int32_t audioBitrate,
	u_int8_t* audioConfig,
	u_int32_t audioConfigLength,
	u_int32_t verbosity DEFAULT(0));

/* edit list */

/* NOTE this section of functionality 
 * has not yet been fully tested 
 */

_STEP_EXPORT_ MP4EditId MP4AddTrackEdit(
	MP4FileHandle hFile,
	MP4TrackId trackId,
	MP4EditId editId DEFAULT(MP4_INVALID_EDIT_ID),
	MP4Timestamp startTime DEFAULT(0),
	MP4Duration duration DEFAULT(0),
	bool dwell DEFAULT(false));

_STEP_EXPORT_ bool MP4DeleteTrackEdit(
	MP4FileHandle hFile,
	MP4TrackId trackId,
	MP4EditId editId);

_STEP_EXPORT_ u_int32_t MP4GetTrackNumberOfEdits(
	MP4FileHandle hFile,
	MP4TrackId trackId);

_STEP_EXPORT_ MP4Timestamp MP4GetTrackEditStart(
	MP4FileHandle hFile,
	MP4TrackId trackId,
	MP4EditId editId);

_STEP_EXPORT_ MP4Duration MP4GetTrackEditTotalDuration(
	MP4FileHandle hFile,
	MP4TrackId trackId,
	MP4EditId editId DEFAULT(MP4_INVALID_EDIT_ID));

_STEP_EXPORT_ MP4Timestamp MP4GetTrackEditMediaStart(
	MP4FileHandle hFile,
	MP4TrackId trackId,
	MP4EditId editId);

_STEP_EXPORT_ bool MP4SetTrackEditMediaStart(
	MP4FileHandle hFile,
	MP4TrackId trackId,
	MP4EditId editId,
	MP4Timestamp startTime);

_STEP_EXPORT_ MP4Duration MP4GetTrackEditDuration(
	MP4FileHandle hFile,
	MP4TrackId trackId,
	MP4EditId editId);

_STEP_EXPORT_ bool MP4SetTrackEditDuration(
	MP4FileHandle hFile,
	MP4TrackId trackId,
	MP4EditId editId,
	MP4Duration duration);

_STEP_EXPORT_ int8_t MP4GetTrackEditDwell(
	MP4FileHandle hFile,
	MP4TrackId trackId,
	MP4EditId editId);

_STEP_EXPORT_ bool MP4SetTrackEditDwell(
	MP4FileHandle hFile,
	MP4TrackId trackId,
	MP4EditId editId,
	bool dwell);

_STEP_EXPORT_ bool MP4ReadSampleFromEditTime(
	/* input parameters */
	MP4FileHandle hFile,
	MP4TrackId trackId, 
	MP4Timestamp when, 
	/* input/output parameters */
	u_int8_t** ppBytes, 
	u_int32_t* pNumBytes, 
	/* output parameters */
	MP4Timestamp* pStartTime DEFAULT(NULL), 
	MP4Duration* pDuration DEFAULT(NULL),
	MP4Duration* pRenderingOffset DEFAULT(NULL), 
	bool* pIsSyncSample DEFAULT(NULL));

_STEP_EXPORT_ MP4SampleId MP4GetSampleIdFromEditTime(
	MP4FileHandle hFile,
	MP4TrackId trackId, 
	MP4Timestamp when, 
	MP4Timestamp* pStartTime DEFAULT(NULL), 
	MP4Duration* pDuration DEFAULT(NULL));
/* iTunes metadata handling */
_STEP_EXPORT_ bool MP4MetadataDelete(MP4FileHandle hFile);
_STEP_EXPORT_ bool MP4GetMetadataByIndex(MP4FileHandle hFile, u_int32_t index,
			   const char** ppName,
			   u_int8_t** ppValue, u_int32_t* pValueSize);
_STEP_EXPORT_ bool MP4SetMetadataName(MP4FileHandle hFile, const char* value);
_STEP_EXPORT_ bool MP4GetMetadataName(MP4FileHandle hFile, char** value);
_STEP_EXPORT_ bool MP4SetMetadataArtist(MP4FileHandle hFile, const char* value);
_STEP_EXPORT_ bool MP4GetMetadataArtist(MP4FileHandle hFile, char** value);
_STEP_EXPORT_ bool MP4SetMetadataWriter(MP4FileHandle hFile, const char* value);
_STEP_EXPORT_ bool MP4GetMetadataWriter(MP4FileHandle hFile, char** value);
_STEP_EXPORT_ bool MP4SetMetadataComment(MP4FileHandle hFile, const char* value);
_STEP_EXPORT_ bool MP4GetMetadataComment(MP4FileHandle hFile, char** value);
_STEP_EXPORT_ bool MP4SetMetadataTool(MP4FileHandle hFile, const char* value);
_STEP_EXPORT_ bool MP4GetMetadataTool(MP4FileHandle hFile, char** value);
_STEP_EXPORT_ bool MP4SetMetadataYear(MP4FileHandle hFile, const char* value);
_STEP_EXPORT_ bool MP4GetMetadataYear(MP4FileHandle hFile, char** value);
_STEP_EXPORT_ bool MP4SetMetadataAlbum(MP4FileHandle hFile, const char* value);
_STEP_EXPORT_ bool MP4GetMetadataAlbum(MP4FileHandle hFile, char** value);
_STEP_EXPORT_ bool MP4SetMetadataTrack(MP4FileHandle hFile,
			 u_int16_t track, u_int16_t totalTracks);
_STEP_EXPORT_ bool MP4GetMetadataTrack(MP4FileHandle hFile,
			 u_int16_t* track, u_int16_t* totalTracks);
_STEP_EXPORT_ bool MP4SetMetadataDisk(MP4FileHandle hFile,
			u_int16_t disk, u_int16_t totalDisks);
_STEP_EXPORT_ bool MP4GetMetadataDisk(MP4FileHandle hFile,
			u_int16_t* disk, u_int16_t* totalDisks);
_STEP_EXPORT_ bool MP4SetMetadataGenre(MP4FileHandle hFile, const char *genre);
_STEP_EXPORT_ bool MP4GetMetadataGenre(MP4FileHandle hFile, char **genre);
_STEP_EXPORT_ bool MP4SetMetadataTempo(MP4FileHandle hFile, u_int16_t tempo);
_STEP_EXPORT_ bool MP4GetMetadataTempo(MP4FileHandle hFile, u_int16_t* tempo);
_STEP_EXPORT_ bool MP4SetMetadataCompilation(MP4FileHandle hFile, u_int8_t cpl);
_STEP_EXPORT_ bool MP4GetMetadataCompilation(MP4FileHandle hFile, u_int8_t* cpl);
_STEP_EXPORT_ bool MP4SetMetadataCoverArt(MP4FileHandle hFile,
			    u_int8_t *coverArt, u_int32_t size);
_STEP_EXPORT_ bool MP4GetMetadataCoverArt(MP4FileHandle hFile,
			    u_int8_t **coverArt, u_int32_t* size);
_STEP_EXPORT_ bool MP4SetMetadataFreeForm(MP4FileHandle hFile, char *name,
			    u_int8_t* pValue, u_int32_t valueSize);
_STEP_EXPORT_ bool MP4GetMetadataFreeForm(MP4FileHandle hFile, char *name,
			    u_int8_t** pValue, u_int32_t* valueSize);
_STEP_EXPORT_ bool MP4SetMetadataGroup(MP4FileHandle hFile, const char* value);
_STEP_EXPORT_ bool MP4GetMetadataGroup(MP4FileHandle hFile, char** value);
_STEP_EXPORT_ bool MP4SetMetadataAlbumArtist(MP4FileHandle hFile, const char* value); /* STEP */
_STEP_EXPORT_ bool MP4GetMetadataAlbumArtist(MP4FileHandle hFile, char** value); /* STEP */
 

/* time conversion utilties */

/* predefined values for timeScale parameter below */
#define MP4_SECONDS_TIME_SCALE		1
#define MP4_MILLISECONDS_TIME_SCALE 1000
#define MP4_MICROSECONDS_TIME_SCALE 1000000
#define MP4_NANOSECONDS_TIME_SCALE 	1000000000

#define MP4_SECS_TIME_SCALE 	MP4_SECONDS_TIME_SCALE
#define MP4_MSECS_TIME_SCALE	MP4_MILLISECONDS_TIME_SCALE
#define MP4_USECS_TIME_SCALE	MP4_MICROSECONDS_TIME_SCALE
#define MP4_NSECS_TIME_SCALE	MP4_NANOSECONDS_TIME_SCALE

_STEP_EXPORT_ u_int64_t MP4ConvertFromMovieDuration(
	MP4FileHandle hFile,
	MP4Duration duration,
	u_int32_t timeScale);

_STEP_EXPORT_ u_int64_t MP4ConvertFromTrackTimestamp(
	MP4FileHandle hFile,
	MP4TrackId trackId, 
	MP4Timestamp timeStamp,
	u_int32_t timeScale);

_STEP_EXPORT_ MP4Timestamp MP4ConvertToTrackTimestamp(
	MP4FileHandle hFile,
	MP4TrackId trackId, 
	u_int64_t timeStamp,
	u_int32_t timeScale);

_STEP_EXPORT_ u_int64_t MP4ConvertFromTrackDuration(
	MP4FileHandle hFile,
	MP4TrackId trackId, 
	MP4Duration duration,
	u_int32_t timeScale);

_STEP_EXPORT_ MP4Duration MP4ConvertToTrackDuration(
	MP4FileHandle hFile,
	MP4TrackId trackId, 
	u_int64_t duration,
	u_int32_t timeScale);

_STEP_EXPORT_ char* MP4BinaryToBase16(
	const u_int8_t* pData, 
	u_int32_t dataSize);

_STEP_EXPORT_ char* MP4BinaryToBase64(
	const u_int8_t* pData, 
	u_int32_t dataSize);

/*
 Add by haseta
  "Invalid Address specified to RtlValidateHeap"�΍�̂���
  http://www.codeguru.com/forum/showthread.php?p=1008218
 */
_STEP_EXPORT_ void MP4Free(void* p);


#ifdef __cplusplus
}
#endif

/* undefined our utlity macro to avoid conflicts */
#undef DEFAULT

#endif /* __MP4_INCLUDED__ */
