#ifndef _MP3INFP_EXPORT_FUNC_H
#define _MP3INFP_EXPORT_FUNC_H

/*
��mp3infp API�̗��p�Edll�̍Ĕz�z�ɂ��ā@2002-09-16

1.API�𗘗p����O�ɕK�� mp3infp_GetVer() ���Ăяo���āA�K�v�ȃo�[�W�����𒲂ׂĂ�������
(�Â�mp3infp��mp3infp_GetVer()���T�|�[�g���Ă��Ȃ����߁A�G���g���|�C���g��NULL�`�F�b�N���K�v�ł�)
2.mp3infp.dll/mp3infpr.dll�̃t���[�\�t�g�ւ̓����͂����R�ɂǂ����B
�E���̏ꍇ�A���p�\�t�g�̃J�����gDir��mp3infp.dll��u���ė��p���܂�(system�Ƃ�windows�Ƃ��ɂ͒u���Ȃ��ł�������)
�E�h�L�������g�ɓ�������mp3infp�̃o�[�W�����Ȃǂ𖾋L���Ă�������
�Emp3infp��C���C�u������MFC���C�u�������X�^�e�B�b�N�����N���Ă邽�߁A�T�C�Y���傫���ł�
�E�J�����g��Windows�V�X�e��(mp3infp���C���X�g�[������Ă���dir)�̂ǂ����D�悵�ă��[�h����̂��A�悭�l���Đ݌v���Ă�������
*/

#if __cplusplus
extern "C"{
#endif

/*=======================================================================================
���O�F	mp3infp_GetVer
�T�v�F	mp3infp�̃o�[�W�������擾����
�����F	�Ȃ�
�ߒl�F	DWORD	�o�[�W������� 
			Ver.2.11	= 0x0211
���l�F	
�Ή��F	Ver2.11�`
*/
DWORD __stdcall mp3infp_GetVer();
typedef DWORD (WINAPI *LPMP3INFP_GETVER)();

/*=======================================================================================
���O�F	mp3infp_ViewProp
�T�v�F	mp3infp�ɑΉ������t�@�C���`���̃v���p�e�B���J��
�����F	�w��t�@�C���̃v���p�e�B��mp3infp�̃^�u���A�N�e�B�u�ɂ��ĊJ���܂�
�����F
		IN HWND hWnd		�e�E�C���h�E���w�肵�܂��B�����ꍇ��NULL�B
		IN char *szFileName	�Ώۃt�@�C�������t���p�X�Ŏw��B
		IN DWORD dwPage		�Emp3infp�̉��y�[�W�ڂ��A�N�e�B�u�ɂ��邩�w�肷��(0=ID3v1 / 1=ID3v2 / 2=RiffSIF)
							�E�^�O���܂܂Ȃ�mp3�̏ꍇ�̂ݗL��
							�E�^�O���܂ޏꍇ��ID3v2/RiffSIF/ID3v1�̏��Ō������āA�ŏ��Ɍ��������^�O���A�N�e�B�u�ɂ��܂�

�ߒl�F	BOOL ����=TRUE/���s=FALSE
�Ή��F	Ver2.00�`
*/
BOOL __stdcall mp3infp_ViewProp(HWND hWnd,char *szFileName,DWORD dwDummy);
typedef BOOL (WINAPI *LPMP3INFP_VIEWPROP)(HWND hWnd,char *szFileName,DWORD dwDummy);

/*=======================================================================================
���O�F	mp3infp_Load
�T�v�F	�^�O�������[�h����
�����F
		IN HWND hWnd		�Ăяo�����E�C���h�E���w�肵�܂��B�����ꍇ��NULL�B
		IN char *szFileName	�Ώۃt�@�C�������t���p�X�Ŏw��B
�ߒl�F	DWORD 
		-1=���[�h���s
		ERROR_SUCCESS=����
		(���̑�)=Win32�G���[�R�[�h (FormatMessage�ŕ�������擾�ł���)
�Ή��F	Ver2.26�`
*/
DWORD __stdcall mp3infp_Load(HWND hWnd,char *szFileName);
typedef DWORD (WINAPI *LPMP3INFP_LOAD)(HWND hWnd,char *szFileName);

/*=======================================================================================
////////////////////////////////////////////////////////////////////
�\1�@mp3infp_GetValue()/mp3infp_SetValue()��szValueName�Ɏw�肷�閼�O�ꗗ
////////////////////////////////////////////////////////////////////

	[MP3]				ID3v1		ID3v2		RiffSIF
	�t�H�[�}�b�g		"AFMT"		"AFMT"		"AFMT"	
	���t����			"TIME"		"TIME"		"TIME"
	�^�C�g��			"INAM_v1"	"INAM_v2"	"INAM_rmp"
	�A�[�e�B�X�g		"IART_v1"	"IART_v2"	"IART_rmp"
	�A���o��			"IPRD_v1"	"IPRD_v2"	"IPRD_rmp"
	�R�����g			"ICMT_v1"	"ICMT_v2"	"ICMT_rmp"
	�쐬��				"ICRD_v1"	"ICRD_v2"	"ICRD_rmp"
	�W������			"IGNR_v1"	"IGNR_v2"	"IGNR_rmp"
	(ID3v2/RiffSIF)
	���쌠							"ICOP_v2"	"ICOP_rmp"
	�\�t�g�E�F�A					"ISFT_v2"	"ISFT_rmp"
	(ID3v2)
	���							"COMP_v2"
	Orig.�A�[�e�B�X�g				"OART_v2"
	URL								"URL_v2"
	(RiffSIF)
	�\�[�X										"ISRC_rmp"
	�G���W�j�A									"IENG_rmp"
	(ID3v1/2)
	�g���b�N�ԍ�		"TRACK_v1"	"TRACK_v2"

	[WAV]
	�t�H�[�}�b�g		"AFMT"
	���t����			"TIME"
	�^�C�g��			"INAM"
	�^�C�g��			"ISBJ"
	�A�[�e�B�X�g		"IART"
	�A���o��			"IPRD"
	�R�����g			"ICMT"
	�쐬��				"ICRD"
	�W������			"IGNR"
	���쌠				"ICOP"
	�\�t�g�E�F�A		"ISFT"
	�\�[�X				"ISRC"
	�G���W�j�A			"IENG"

	[AVI]
	�����t�H�[�}�b�g	"AFMT"	
	�f���t�H�[�}�b�g	"VFMT"
	����				"TIME"
	�^�C�g��			"INAM"
	�^�C�g��			"ISBJ"
	�A�[�e�B�X�g		"IART"
	�R�����g			"ICMT"
	�쐬��				"ICRD"
	�W������			"IGNR"
	���쌠				"ICOP"
	�\�t�g�E�F�A		"ISFT"
	�\�[�X				"ISRC"
	�G���W�j�A			"IENG" 

	[VQF]
	�t�H�[�}�b�g		"AFMT"
	���t����			"TIME"
	�^�C�g��			"INAM"
	�A�[�e�B�X�g		"IART"
	�R�����g			"ICMT"
	���쌠				"ICOP"
	�ۑ���				"FILE"

	[WMA]
	�����t�H�[�}�b�g	"AFMT"
	�f���t�H�[�}�b�g	"VFMT"
	����				"TIME"
	�^�C�g��			"INAM"
	�g���b�N			"TRACK"
	�A�[�e�B�X�g		"IART"
	�A���o��			"IPRD"
	�R�����g			"ICMT"
	�쐬��				"ICRD"
	�W������			"IGNR"
	���쌠				"ICOP"
	URL(Album)			"URL1"
	URL(�֘A)			"URL2"

	[OGG]
	�t�H�[�}�b�g		"AFMT"
	���t����			"TIME"
	�^�C�g��			"INAM"
	�A�[�e�B�X�g		"IART"
	�A���o��			"IPRD"
	�R�����g			"ICMT"
	�쐬��				"ICRD"
	�W������			"IGNR"
	�g���b�N�ԍ�		"TRACK"
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
���O�F	mp3infp_GetType
�T�v�F	�t�@�C���̎�ނ��擾����
�⑫�F	mp3infp_Load()�̌�ɌĂяo���Ă�������
�����F	�Ȃ�
�ߒl�F	DWORD
#define MP3INFP_FILE_UNKNOWN	0x00
#define MP3INFP_FILE_MP3		0x01
#define MP3INFP_FILE_WAV		0x02
#define MP3INFP_FILE_AVI		0x03
#define MP3INFP_FILE_VQF		0x04
#define MP3INFP_FILE_WMA		0x05
#define MP3INFP_FILE_OGG		0x07
#define MP3INFP_FILE_APE		0x08
�Ή��F	Ver2.26�`
*/
DWORD __stdcall mp3infp_GetType();
typedef DWORD (WINAPI *LPMP3INFP_GETTYPE)();

/*=======================================================================================
���O�F	mp3infp_GetValue
�T�v�F	�^�O�����擾����
�⑫�F	mp3infp_Load()�̌�ɌĂяo���Ă�������
�����F	
		IN char *szValueName	�^�O�̎�ނ��������O(�\1���Q��)
		OUT char **buf			�^�O���������o�b�t�@�̃|�C���^���󂯎��|�C���^
�ߒl�F	BOOL ����=TRUE/���s=FALSE
�Ή��F	Ver2.26�`
*/
BOOL __stdcall mp3infp_GetValue(char *szValueName,char **buf);
typedef BOOL (WINAPI *LPMP3INFP_GETVALUE)(char *szValueName,char **buf);

#define MP3INFP_HAS_MP3_ID3V1	0x01
#define MP3INFP_HAS_MP3_ID3V2	0x02
#define MP3INFP_HAS_MP3_RIFFSIF	0x04
/*=======================================================================================
���O�F	mp3infp_mp3_GetTagType
�T�v�F	mp3�������Ă���^�O�̎�ނ��擾����
�⑫�F	mp3infp_Load()�̌�ɌĂяo���Ă�������
�����F	�Ȃ�
�ߒl�F	DWORD (OR)
#define MP3INFP_HAS_MP3_ID3V1	0x01
#define MP3INFP_HAS_MP3_ID3V2	0x02
#define MP3INFP_HAS_MP3_RIFFSIF	0x04
�Ή��F	Ver2.27�`
*/
DWORD __stdcall mp3infp_mp3_GetTagType();
typedef DWORD (WINAPI *LPMP3INFP_MP3_GETTAGTYPE)();

#if 0
/*=======================================================================================
���O�F	mp3infp_SetValue
�T�v�F	�^�O����ݒ肷��
�⑫�F	mp3infp_Load()�̌�ɌĂяo���Ă�������
�����F	
		IN char *szValueName	�^�O�̎�ނ��������O(�\1���Q��)
		OUT char *buf			�^�O���������o�b�t�@
		OUT DWORD len			����(�I�[��'\0'���܂�)
�ߒl�F	BOOL ����=TRUE/���s=FALSE
�Ή��F	������
*/
BOOL __stdcall mp3infp_SetValue(char *szValueName,char *buf,DWORD len);
typedef BOOL (WINAPI *LPMP3INFP_SETVALUE)(char *szValueName,char *buf,DWORD len);


BOOL __stdcall mp3infp_Save(HWND hWnd,char *szFileName);

//mp3
BOOL __stdcall mp3infp_mp3_MakeId3v1(HWND hWnd,char *szFileName);
BOOL __stdcall mp3infp_mp3_DelId3v1(HWND hWnd,char *szFileName);
BOOL __stdcall mp3infp_mp3_ConvId3v2(HWND hWnd,char *szFileName);
BOOL __stdcall mp3infp_mp3_ConvId3v2(HWND hWnd,char *szFileName);
BOOL __stdcall mp3infp_mp3_ConvRMP(HWND hWnd,char *szFileName);
BOOL __stdcall mp3infp_mp3_ConvRMP(HWND hWnd,char *szFileName);
#endif

#if __cplusplus
}
#endif

#endif //_MP3INFP_EXPORT_FUNC_H
