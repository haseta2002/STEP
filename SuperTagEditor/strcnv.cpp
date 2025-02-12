#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "imm.h"

#ifndef iskanji
#define iskanji(c)		((c) >= 0x81 && (c) <= 0x9f || (c) >= 0xe0 && (c) <= 0xfc)
#endif

enum	{CONV_SUJI=1, CONV_ALPHA=2, CONV_KATA=4, CONV_KIGOU=8, CONV_ALL=15};

#ifdef __cplusplus
extern "C" {
#endif

extern	int conv_han2zens(unsigned char *, const unsigned char *, int);
extern	int conv_zen2hans(unsigned char *, const unsigned char *, int);
extern	void conv_kata2hira(unsigned char *);
extern	void conv_kata_erase_dakuon(unsigned char *);
extern	void conv_hira2kata(unsigned char *);
extern	void conv_upper(unsigned char *);
extern	void conv_lower(unsigned char *);
extern	void conv_first_upper(unsigned char *, const char *, const char *, bool);
//extern	DWORD conv_kan2hira(HWND, unsigned char *, DWORD);
//extern	void conv_romaji(HWND hwnd, unsigned char *str, unsigned char *sRomaji);
#ifdef __cplusplus
}
#endif

unsigned short han2zen(int c, int flag)
{
	if (c <= 0x19 || (c >= 0x80 && c <= 0xa0) || c >= 0xe0) {
		return c;					// §ä¢è`
	}
	if (flag & CONV_ALPHA) {
		if (c >= 'A' && c <= 'Z') return(0x8260U + (c - 'A'));	// på¶
		if (c >= 'a' && c <= 'z') return(0x8281U + (c - 'a'));	// p¬¶
	}
	if (flag & CONV_SUJI) {
		if (c >= '0' && c <= '9') return(0x824FU + (c - '0'));	// 
	}

	int		i;
	static const unsigned char *s1 = (const unsigned char *)
		/* 0123456789ABCDEF		        OPQRSTUVWX`abcde */
		  "   ,. :;?!Þß   "		/* 212X:@@ABCDEFGHIJKLMN */
		  /* STEP 016 *///" ¤¡,.¥:;?!Þß   "		/* 212X:@@ABCDEFGHIJKLMN */
		  /* BeachMonster 102 *///"^~_         °- /"	/* 213X:OPQRSTUVWXYZ[\]^ */
		  /* Baja 169 *///"^~_          - /"	/* 213X:OPQRSTUVWXYZ[\]^ */
		  "^~_            /"	/* 213X:OPQRSTUVWXYZ[\]^ */
		  "   |  `\' \"()  []"	/* 214X:_`abcdefghijklmn */
		  "{}          +-   "	/* 215X:opqrstuvwxyz{|}~7F */
		  /* STEP 016 *///"{}    ¢£    +-   "	/* 215X:opqrstuvwxyz{|}~7F */
		  " = <>          \\"	/* 216X: */
		  "$  %#&*@        ";	/* 217X:   */
	static const unsigned char *s2 = (const unsigned char *)
		/* 0123456789ABCDEF		        OPQRSTUVWX`abcde */
		  "§±¨²©³ª´«µ¶Þ·Þ¸"		/* 252X:@@ABCDEFGHIJKLMN */
		  "Þ¹ÞºÞ»Þ¼Þ½Þ¾Þ¿ÞÀ"	/* 253X:OPQRSTUVWXYZ[\]^ */
		  "ÞÁÞ¯ÂÞÃÞÄÞÅÆÇÈÉÊ"	/* 254X:_`abcdefghijklmn */
		  "ÞßËÞßÌÞßÍÞßÎÞßÏÐ "	/* 255X:opqrstuvwxyz{|}~7F */
		  "ÑÒÓ¬Ô­Õ®Ö×ØÙÚÛ Ü"	/* 256X: */
		  "  ¦Ý";				/* 257X: */
	static const unsigned char *s3 = (const unsigned char *) /* BeachMonster 102 */
		/* 0123456789ABCDEF		        OPQRSTUVWX`abcde */
		  "                "	/* 212X:@@ABCDEFGHIJKLMN */
		  "            °   "	/* 213X:OPQRSTUVWXYZ[\]^ */
		  "                "	/* 214X:_`abcdefghijklmn */
		  "                "	/* 215X:opqrstuvwxyz{|}~7F */
		  "                "	/* 216X: */
		  "                ";	/* 217X:   */
		 ;
	static const unsigned char *s4 = (const unsigned char *) /* STEP 016 */
		/* 0123456789ABCDEF		        OPQRSTUVWX`abcde */
		  "  ¤¡  ¥         "	/* 212X:@@ABCDEFGHIJKLMN */
		  "                "	/* 213X:OPQRSTUVWXYZ[\]^ */
		  "                "	/* 214X:_`abcdefghijklmn */
		  "      ¢£        "	/* 215X:opqrstuvwxyz{|}~7F */
		  "                "	/* 216X: */
		  "                ";	/* 217X:   */
		 ;
	if (flag & CONV_KIGOU) {
		for (i = 0; s1[i]; i++) if (c == s1[i]) return(0x8140U+i);	// L
	}
	if (flag & CONV_KATA) {
		for (i = 0; s2[i]; i++) if (c == s2[i]) return(0x8340U+i);	// J^Ji
	}
	if (flag & CONV_KATA) { /* BeachMonster 102 */
		for (i = 0; s3[i]; i++) if (c == s3[i]) return(0x8140U+i-1/* STEP 016*/);	// L¾¯ÇJ^Jiµ¢
	}
	extern bool g_bZenHanKigouKana; /* STEP 016 */
	if ((!g_bZenHanKigouKana && flag & CONV_KIGOU) 
		|| (g_bZenHanKigouKana && flag & CONV_KATA)) { /* STEP 016 */
		for (i = 0; s4[i]; i++) if (c == s4[i]) return(0x8140U+i-1);
	}
	return(c);
}

int conv_han2zens(unsigned char *zen, const unsigned char *han, int flag)
{
	int		i;
	int		pzen = 0;		// SpÊu
	int		l = strlen((const char *)han);
	zen[0] = '\0';

	for (i = 0; i < l; i++, pzen++, zen[pzen] = '\0') {
		if (han[i] == ' ') {		// ó
			if (flag & CONV_KIGOU) {
				zen[pzen] = 0x81U;
				pzen++;
				zen[pzen] = 0x40U;
			} else {
				zen[pzen] = ' ';
			}
			continue;
		}

		if (iskanji(han[i])) {		// ¿
			zen[pzen] = han[i];
			pzen++;
			i++;
			zen[pzen] = han[i];
			continue;
		}

		if (flag & CONV_KATA) {
			unsigned int	x;
			static const unsigned char *s1 = (const unsigned char *)
			/* 0123456789ABCDEF		        OPQRSTUVWX`abcde */
			             "¶ · ¸"	/* 252X:@@ABCDEFGHIJKLMN */
			  " ¹ º » ¼ ½ ¾ ¿ À"	/* 253X:OPQRSTUVWXYZ[\]^ */
			  " Á ¯Â Ã Ä ÅÆÇÈÉÊ"	/* 254X:_`abcdefghijklmn */
			  "  Ë  Ì  Í  Î";		/* 255X:opqrstuvwxyz{|     */
			static const unsigned char *s2 = (const unsigned char *)
			/* 0123456789ABCDEF		        OPQRSTUVWX`abcde */
			                 "Ê"	/* 254X:                              n */
			  "  Ë  Ì  Í  Î";		/* 255X:opqrstuvwxyz{|     */

			// [³Þ] => [] ÌÏ·
			if (han[i] == (unsigned char)'³' && han[i+1] == (unsigned char)'Þ') {
				zen[pzen] = 0x83U;
				pzen++;
				i++;
				zen[pzen] = 0x94U;
				goto cont;
			}

			// ÷¹ÌÏ·
			for (x = 0; s1[x]; x++) {
				if (han[i] == s1[x] && han[i+1] == (unsigned char)'Þ') {
					zen[pzen] = 0x83U;
					pzen++;
					i++;
					zen[pzen] = 0x4BU + x;
					goto cont;
				}
			}

			// ¼÷¹ÌÏ·
			for (x = 0; s2[x]; x++) {
				if (han[i] == s2[x] && han[i+1] == (unsigned char)'ß') {
					// ¼÷¹
					zen[pzen] = 0x83U;
					pzen++;
					i++;
					zen[pzen] = 0x70U + x;
					goto cont;
				}
			}
		}

		// »Ì¼ÌÏ·
		{
			unsigned short z = han2zen(han[i], flag);
			if (z >= 0x100) {
				zen[pzen] = (unsigned char)(z >> 8);
				pzen++;
				zen[pzen] = (unsigned char)z;
			} else {
				zen[pzen] = (unsigned char)z;
			}
		}
cont:	;
	}

	return(pzen);
}

unsigned short zen2han(unsigned short c, int flag)
{
	if (c <= 0x100) return(c);				// ñ¿
	if (flag & CONV_ALPHA) {
		if (c == 0x8140U) return(' ');			// ó
		if (c >= 0x8260U && c <= 0x8279U) {		// `|y
			return('A' + (c - 0x8260U));
		}
		if (c >= 0x8281U && c <= 0x829AU) {		// |
			return('a' + (c - 0x8281U));
		}
	}
	if (flag & CONV_SUJI) {
		if (c >= 0x824FU && c <= 0x8258U) {		// O|X
			return('0' + (c - 0x824FU));
		}
	}

	int		i;
	if (flag & CONV_KIGOU) {
		// ÈñÅ"`"ð"-"ÉµÄéÌ©o¦ÄÈ¢ÌÅí 041018
		static const unsigned char *han = (const unsigned char *)
			",.:;?!Þß^~_-/|`\'\"()[]{}+-=<>\\$%#&*@"; /* BeachMonster 102 *//* STEP 016 */
		static const unsigned char *zen = (const unsigned char *)
			"CDFGHIJKOPQ|^bMfhijmnop{|\0"; /* BeachMonster 102 *//* STEP 016 */
		for (i = 0; zen[i+1]; i+=2) {
			if (c == ((zen[i] << 8) | zen[i+1])) return(han[i/2]);
		}
		extern bool g_bZenHanKigouKana; /* STEP 016 */
		if (!g_bZenHanKigouKana) { /* STEP 016 */
			static const unsigned char *han2 = (const unsigned char *)
				"¥¤¡¢£";
			static const unsigned char *zen2 = (const unsigned char *)
				"EABuv\0";
			for (i = 0; zen2[i+1]; i+=2) {
				if (c == ((zen2[i] << 8) | zen2[i+1])) return(han2[i/2]);
			}
		}
	}
	if (flag & CONV_KATA) {
		static const unsigned char *han = (const unsigned char *)
			"§±¨²©³ª´«µ¶·¸¹º»¼½¾¿ÀÁ¯ÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓ¬Ô­Õ®Ö×ØÙÚÛÜ¦Ý°";
		static const unsigned char *kata = (const unsigned char *)
			"@ABCDEFGHIJLNPRTVXZ\^`bcegijklm"
			"nqtwz}~[\0";
		// J^Ji
		for (i = 0; kata[i+1]; i+=2) {
			if (c == ((kata[i] << 8) | kata[i+1])) return(han[i/2]);
		}
		extern bool g_bZenHanKigouKana; /* STEP 016 */
		if (g_bZenHanKigouKana) { /* STEP 016 */
			static const unsigned char *han2 = (const unsigned char *)
				"¥¤¡¢£";
			static const unsigned char *kata2 = (const unsigned char *)
				"EABuv\0";
			for (i = 0; kata2[i+1]; i+=2) {
				if (c == ((kata2[i] << 8) | kata2[i+1])) return(han2[i/2]);
			}
		}
	}
#if 0
	if (flag & CONV_KATA) {
		static const unsigned char *han = (const unsigned char *)
			"§±¨²©³ª´«µ¶·¸¹º»¼½¾¿ÀÁ¯ÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓ¬Ô­Õ®Ö×ØÙÚÛÜ¦Ý";
		static const unsigned char *hira = (const unsigned char *)
			" ¡¢£¤¥¦§¨©«­¯±³µ·¹»½¿ÁÂÄÆÈÉÊËÌ"
			"ÍÐÓÖÙÜÝÞßàáâãäåæçèéêëíðñ\0";
		// ÐçªÈ
		for (i = 0; hira[i+1]; i+=2) {
			if (c == ((hira[i] << 8) | hira[i+1])) return(han[i/2]);
		}
	}
#endif

	// Ï·Å«È©Á½
	return(c);
}

int conv_zen2hans(unsigned char *han, const unsigned char *zen, int flag)
{
	int		i;
	int		phan = 0;		// ¼pÊu
	int		l = strlen((const char *)zen);
	han[0] = '\0';

	for (i = 0; i < l; i++, phan++, han[phan] = '\0') {
		if (!iskanji(zen[i])) {		// ñ¿
			han[phan] = zen[i];
			continue;				// ³Ï·
		}

		if (flag & CONV_KATA) {
			int		j;
			static const unsigned char *k1 = (const unsigned char *)"KMOQSUWY[]_adfhorux{\0";
			static const unsigned char *h1 = (const unsigned char *)"ª¬®°²´¶¸º¼¾ÀÃÅÇÎÑÔ×Ú\0\0\0";
			static const unsigned char *k2 = (const unsigned char *)"psvy|\0";
			static const unsigned char *h2 = (const unsigned char *)"ÏÒÕØÛ\0";
			// ÷¹ÌÏ·
			for (j = 0; k1[j+1]; j+=2) {
#if 1
				if (zen[i] == k1[j] && zen[i+1] == k1[j+1]) {	// J^Ji
#else
				if ((zen[i] == k1[j] && zen[i+1] == k1[j+1])	// J^Ji
				||  (zen[i] == h1[j] && zen[i+1] == h1[j+1])) {	// ÐçªÈ
#endif
					static const unsigned char *h = (const unsigned char *)"¶·¸¹º»¼½¾¿ÀÁÂÃÄÊËÌÍÎ³";
					han[phan] = h[j/2];
					phan++;
					han[phan] = (unsigned char)'Þ';
					i++;
					goto cont;
				}
			}

			// ¼÷¹ÌÏ·
			for (j = 0; k2[j+1]; j+=2) {
#if 1
				if (zen[i] == k2[j] && zen[i+1] == k2[j+1]) {	// J^Ji
#else
				if ((zen[i] == k2[j] && zen[i+1] == k2[j+1])	// J^Ji
				||  (zen[i] == h2[j] && zen[i+1] == h2[j+1])) {	// ÐçªÈ
#endif
					static const unsigned char *h = (const unsigned char *)"ÊËÌÍÎ";
					han[phan] = h[j/2];
					phan++;
					han[phan] = (unsigned char)'ß';
					i++;
					goto cont;
				}
			}
		}

		// »Ì¼ÌÏ·
		{
			unsigned short c;
			c = zen2han((zen[i] << 8) | zen[i+1], flag);
			i++;
			if (c >= 0x100) {
				han[phan] = (unsigned char)(c >> 8);
				phan++;
				han[phan] = (unsigned char)c;
			} else {
				han[phan] = (unsigned char)c;
			}
		}

cont:	;
	}

	return(phan);
}

static const unsigned char *kata = (const unsigned char *)
	"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]"
	"^_`abcdefghijklmnopqrstuvwxyz{|"
	"}~";
static const unsigned char *hira = (const unsigned char *)
	" ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼"
	"½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛ"
	"ÜÝÞßàáâãäåæçèéêëìíðñ";
static const unsigned char *alphaS = (const unsigned char *)
	"fOPQRSTUVWX" /* STEP 026 */;
static const unsigned char *alphaL = (const unsigned char *)
	"`abcdefghijklmnopqrstuvwxyfOPQRSTUVWX" /* STEP 026 */;

static const unsigned char *kata_dakuon = (const unsigned char *) /* FunnyCorn 179 */
	"@ABCDEFGHIJJLLNNPPRRTTVVXXZZ\\"
	"^^``bcceeggijklmnnnqqqtttwwwzzz"
	"}~";

void conv_table(const unsigned char *before, const unsigned char *after, unsigned char *str)
{
	while(*str != '\0') {
		if (iskanji(*str)) {		// ¿
			for (int i = 0; before[i]; i+=2) {
				if (before[i] == str[0] && before[i+1] == str[1]) {
					str[0] = after[i];
					str[1] = after[i+1];
					break;
				}
			}
			str++;
		}
		str++;
	}
}
// [J^Ji]Ì÷¹A¼÷¹ðÈ­·
void conv_kata_erase_dakuon(unsigned char *str)
{
	conv_table(kata, kata_dakuon, str);
}
// [J^Ji]=>[ÐçªÈ]ÉÏ·
void conv_kata2hira(unsigned char *str)
{
	conv_table(kata, hira, str);
}

// [ÐçªÈ]=>[J^Ji]ÉÏ·
void conv_hira2kata(unsigned char *str)
{
	conv_table(hira, kata, str);
}

// [¬¶]=>[å¶]ÉÏ·
void conv_upper(unsigned char *str)
{
	_mbsupr(str);
	conv_table(alphaS, alphaL, str);
}

// [å¶]=>[¬¶]ÉÏ·
void conv_lower(unsigned char *str)
{
	_mbslwr(str);
	conv_table(alphaL, alphaS, str);
}

void lower_suffix_word(unsigned char *str, int len, CString suffixs) /* STEP 026*/
{
	CString strZWord((LPCTSTR)str, len);
	CString strWord;
	conv_zen2hans((unsigned char *)strWord.GetBuffer(len*2+1), (const unsigned char *)(const char *)strZWord, CONV_ALL);
	strWord.ReleaseBuffer();
	strWord.MakeLower();
	while (1) {
		CString suffix = suffixs.SpanExcluding(",");
		if (suffix == strWord) {
			if (iskanji(*str)) {		// ¿
				for (int i = 0; alphaS[i]; i+=2) {
					if ((alphaS[i] == str[0] && alphaS[i+1] == str[1])
					||  (alphaL[i] == str[0] && alphaL[i+1] == str[1])) {
						str[0] = alphaS[i];
						str[1] = alphaS[i+1];
						break;
					}
				}
			} else {
				*str = tolower(*str);
			}
			return;
		}
		suffixs.TrimLeft(suffix);
		suffixs.TrimLeft(',');
		if (suffixs.GetLength() == 0) {
			return;
		}
	}
}

bool isSentenceSeparate(unsigned char* str, int len, CString separator) /* STEP 026 */
{
	CString strZWord((LPCTSTR)str, len);
	CString strChar;
	conv_zen2hans((unsigned char *)strChar.GetBuffer(2+1), (const unsigned char *)(const char *)strZWord, CONV_ALL);
	strChar.ReleaseBuffer();
	for (int i=0;i<separator.GetLength();i++) {
		unsigned char c = separator.GetAt(i);
		if (iskanji(c)) {		// ¿
			char	kanji[3];
			kanji[0] = separator.GetAt(i);
			kanji[1] = separator.GetAt(i+1);
			kanji[2] = '\0';
			if (strChar == kanji) {
				return true;
			}
		} else {
			if (strChar == separator.GetAt(i)) {
				return true;
			}
		}
	}
	return false;
}

// PêÌP¶ÚÌÝA[¬¶]=>[å¶]ÉÏ·
void conv_first_upper(unsigned char *str, const char *suffixs /* STEP 026 */, const char* separator /* STEP 026 */, bool bUseSuffix /* STEP 026 */)
{
	bool	bFirst = true;
	unsigned char*	pFirstPos = NULL; /* STEP 026 */
	unsigned char*	pEndPos = NULL; /* STEP 026 */
	bool	bFirstWord = true; /* STEP 026 */
	while(TRUE/* STEP 026 *str != '\0'*/) {
		if (iskanji(*str)) {		// ¿
			for (int i = 0; alphaS[i]; i+=2) {
				if ((alphaS[i] == str[0] && alphaS[i+1] == str[1])
				||  (alphaL[i] == str[0] && alphaL[i+1] == str[1])) {
					if (bFirst) {
						str[0] = alphaL[i];
						str[1] = alphaL[i+1];
						pFirstPos = str; /* STEP 026 */
					}
					bFirst = false;
					break;
				}
			}
			if (alphaS[i] == '\0') {	// PêÌæØè
				pEndPos = str-1; /* STEP 026 */
				if (pFirstPos != NULL && pEndPos != NULL && !bFirstWord && bUseSuffix) { /* STEP 026 */
					lower_suffix_word(pFirstPos, pEndPos - pFirstPos + 1, suffixs);
				}
				pFirstPos = NULL; /* STEP 026 */
				pEndPos = NULL; /* STEP 026 */
				if (!bFirst) bFirstWord = FALSE; /* STEP 026 */
				if (bUseSuffix) { /* STEP 026 */
					if (isSentenceSeparate(str, 2, separator)) {
						bFirstWord = TRUE;
					}
				}
				bFirst = true;
			}
			if (*str == '\0')	break; /* STEP 026 */
			str++;
		} else {					// ñ¿
			if ((*str >= 'a' && *str <= 'z')
			||  (*str >= 'A' && *str <= 'Z')
			||  (*str >= '0' && *str <= '9') /* STEP 026 2005.12.02 */
			||  (*str == '\'')) {
				if (bFirst) {
					*str = toupper(*str);
					bFirst = false;
					pFirstPos = str; /* STEP 026 */
				}
			} else {
				// PêÌæØè
				pEndPos = str-1;
				if (pFirstPos != NULL && pEndPos != NULL && !bFirstWord && bUseSuffix) { /* STEP 026 */
					lower_suffix_word(pFirstPos, pEndPos - pFirstPos + 1, suffixs);
				}
				pFirstPos = NULL; /* STEP 026 */
				pEndPos = NULL; /* STEP 026 */
				if (!bFirst) bFirstWord = FALSE; /* STEP 026 */
				if (bUseSuffix) { /* STEP 026 */
					if (isSentenceSeparate(str, 1, separator)) {
						bFirstWord = TRUE;
					}
				}
				if (*str == '\n') {
					bFirstWord = TRUE;
				}
				bFirst = true;
			}
		}
		if (*str == '\0')	break; /* STEP 026 */
		str++;
	}
}

bool isKigou(char ch) {
	static const unsigned char *s1 = (const unsigned char *)
		/* 0123456789ABCDEF		        OPQRSTUVWX`abcde */
		  "   ,. :;?!Þß   "		/* 212X:@@ABCDEFGHIJKLMN */
		  "^~_            /"	/* 213X:OPQRSTUVWXYZ[\]^ */
		  "   |  `\' \"()  []"	/* 214X:_`abcdefghijklmn */
		  "{}          +-   "	/* 215X:opqrstuvwxyz{|}~7F */
		  /* STEP 016 *///"{}    ¢£    +-   "	/* 215X:opqrstuvwxyz{|}~7F */
		  " = <>          \\"	/* 216X: */
		  "$  %#&*@        ";	/* 217X:   */
	for (int i=0;s1[i]!='\0';i++) {
		if (ch == s1[i]) {
			return true;
		}
	}
	return false;
}

unsigned char* fixed_upper_lower(unsigned char *str/*, int len*/, CStringArray& fixedWords) /* STEP 040*/
{
	CString strZWord((LPCTSTR)str/*, len*/);
	CString strWord;
	conv_zen2hans((unsigned char *)strWord.GetBuffer(strlen((char*)str)+1/*len*2+1*/), (const unsigned char *)(const char *)strZWord, CONV_ALL);
	strWord.ReleaseBuffer();
	strWord.MakeLower();
	for (int i=0;i<fixedWords.GetSize();i++) {
		CString fixed = fixedWords.GetAt(i);
		CString strFixZWord(fixed);
		CString strFixWord;
		conv_zen2hans((unsigned char *)strFixWord.GetBuffer(strFixZWord.GetLength()+1), (const unsigned char *)(const char *)strFixZWord, CONV_ALL);
		strFixWord.ReleaseBuffer();
		fixed = strFixWord;
		fixed.MakeLower();
//		if (fixed == strWord) {
		if (strWord.Find(fixed, 0) == 0 && (strWord == fixed || (strWord.GetLength() >= fixed.GetLength() && isKigou(strWord.GetAt(strlen(fixed)))) )) {
			unsigned char* pos = str;
			for (int j=0;j<fixed.GetLength();j++) {
				if (iskanji(*pos)) {		// ¿
					for (int k = 0; alphaS[k]; k+=2) {
						if ((alphaS[k] == pos[0] && alphaS[k+1] == pos[1])
						||  (alphaL[k] == pos[0] && alphaL[k+1] == pos[1])) {
							if (isupper(strFixWord.GetAt(j))) {
								pos[0] = alphaL[k];
								pos[1] = alphaL[k+1];
							} else {
								pos[0] = alphaS[k];
								pos[1] = alphaS[k+1];
							}
							break;
						}
					}
					pos += 2;
				} else {
					*pos = strFixWord.GetAt(j);
					pos++;
				}
			}
			return pos;
		}
	}
	return NULL;
}

void conv_fixed_upper_lower(unsigned char *str, CStringArray& fixedWords) /* STEP 040 */
{
	unsigned char* current = str;
	bool bConv = false;
	while (TRUE) {
		if ((current = fixed_upper_lower(str, fixedWords))) {
			bConv = true;
			str = current;
		} else {
			bConv = false;
			current = str;
		}
		if (*str == '\0')	break;
		if (bConv)	continue;
		//if (iskanji(*str)) {		// ¿
		//	str++;
		//}
		//str++;
		bool bBreak;
		if (current == str)	{
			bBreak = TRUE;
		}
		while(TRUE) {
			if (*str == '\0')	break;
			if (iskanji(*str)) {		// ¿
				for (int i = 0; alphaS[i]; i+=2) {
					if ((alphaS[i] == str[0] && alphaS[i+1] == str[1])
					||  (alphaL[i] == str[0] && alphaL[i+1] == str[1])) {
						break;
					}
				}
				if (alphaS[i] == '\0') {	// PêÌæØè
					str += 2;
					continue;
				} else {
					if (!bBreak) {
						break;
					}
					str += 2;
				}
			} else {					// ñ¿
				if ((*str >= 'a' && *str <= 'z')
				||  (*str >= 'A' && *str <= 'Z')
				||  (*str >= '0' && *str <= '9')
				||  (*str == '\'')) {
					if (!bBreak) {
						break;
					}
					str++;
				} else {
					str++;
					if (bBreak) {
						break;
					}
					continue;
				}
			}
		}
	}

/*
	bool	bFirst = true;
	unsigned char*	pFirstPos = str;
	unsigned char*	pEndPos = NULL;
	while(TRUE) {
		if ((*str == ' ' && *str == '\t')
		||  (*str == '\r' && *str == '\n')
		|| (strncmp((const char*)str, "@", 2) == 0)
		|| (*str == '\0')) {
			// PêÌæØè
			pEndPos = str-1;
			fixed_upper_lower(pFirstPos, pEndPos - pFirstPos + 1, fixedWords);
			pFirstPos = NULL;
			pEndPos = NULL;
			bFirst = true;
		} else {
			if (bFirst) {
				bFirst = false;
				pFirstPos = str;
			}
		}
		if (*str == '\0')	break;
		str++;
	}
*/
}


#if 0
DWORD conv_kan2hira(HWND hWnd, unsigned char * str, DWORD dwSize)
{
	// MS-IME2000ÅÍ¤Ü­®¢½ªAATOK16ÅÍ¾ßBPêPÊÅ êÎÅ«é...
	HIMC himc = ::ImmGetContext(hWnd);
	DWORD dwRet = ::ImmGetConversionList(
					 ::GetKeyboardLayout(0), himc,
					 (const char *)str, NULL, 0,
					 GCL_REVERSECONVERSION);

	// ÇÝ¼¼i[ÌæðmÛ 
	CANDIDATELIST *lpCand;
	lpCand = (CANDIDATELIST *)malloc(dwRet);
	// ÇÝ¼¼ðæ¾
	dwRet = ::ImmGetConversionList(
					 ::GetKeyboardLayout(0), himc,
					 (const char*)str, lpCand, dwRet,
					 GCL_REVERSECONVERSION);
	if (dwRet > 0 && lpCand->dwCount > 0) {
		char *work = (char*)lpCand + lpCand->dwOffset[0];
		if (strlen(work) >= dwSize) return dwRet;
		strcpy((char*)str, work);

		/*
		for (unsigned int i = 0; i< lpCand->dwCount; i++)
		{
			TRACE("%s", (LPBYTE)lpCand + lpCand->dwOffset[i]);
		}
		*/
	}

	free(lpCand);
	::ImmReleaseContext(hWnd, himc);
	return 0;
}

void conv_romaji(HWND hwnd, unsigned char *str, unsigned char *sRomaji)
{
	static const char *romaji[] = {
		"«á", "KYA", "«ã", "KYU", "«å", "KYO",
		"µá", "SHA", "µã", "SHU", "µå", "SHO",
		"¿á", "CHA", "¿ã", "CHU", "¿å", "CHO",
		"Éá", "NYA", "Éã", "NYU", "Éå", "NYO",
		"Ðá", "HYA", "Ðã", "HYU", "Ðå", "HYO",
		"Ýá", "MYA", "Ýã", "MYU", "Ýå", "MYO",
		"èá", "RYA", "èã", "RYU", "èå", "RYO",
		"¬á", "GYA", "¬ã", "GYU", "¬å", "GYO",
		"¶á", "JA", "¶ã", "JU", "¶å", "JO",
		"Ñá", "BYA", "Ñã", "BYU", "Ñå", "BYO",
		"Òá", "PYA", "Òã", "PYU", "Òå", "PYO",

		"©", "KA", "«", "KI", "­", "KU", "¯", "KE", "±", "KO",
		"³", "SA", "µ", "SHI", "·", "SU", "¹", "SE", "»", "SO",
		"½", "TA", "¿", "CHI", "Â", "TSU", "Ä", "TE", "Æ", "TO",
		"È", "NA", "É", "NI", "Ê", "NU", "Ë", "NE", "Ì", "NO",
		"Í", "HA", "Ð", "HI", "Ó", "FU", "Ö", "HE", "Ù", "HO",
		"Ü", "MA", "Ý", "MI", "Þ", "MU", "ß", "ME", "à", "MO",
		"â", "YA", "ä", "YU", "æ", "YO",
		"ç", "RA", "è", "RI", "é", "RU", "ê", "RE", "ë", "RO",
		"í", "WA",
		"ª", "GA", "¬", "GI", "®", "GU", "°", "GE", "²", "GO",
		"´", "ZA", "¶", "JI", "¸", "ZU", "º", "ZE", "¼", "ZO",
		"¾", "DA", "À", "JI", "Ã", "ZU", "Å", "DE", "Ç", "DO",
		"Î", "BA", "Ñ", "BI", "Ô", "BU", "×", "BE", "Ú", "BO",
		"Ï", "PA", "Ò", "PI", "Õ", "PU", "Ø", "PE", "Û", "PO",

		" ", "A", "¢", "I", "¤", "U", "¦", "E", "¨", "O",
		"ð", "O", "ñ", "N",
		"[", "",
		NULL, NULL,
	};

	CString	strWork, strRep;
	int		nPos;
	int nRomaji = 0;

	strWork = str;
	/*
	while (romaji[nRomaji*2] != NULL) {
		while((nPos = strWork.Find(romaji[nRomaji*2])) != -1) {
			int		nLenOrg = strWork.GetLength();
			int		nLenKey = strlen(romaji[nRomaji*2]);
			strRep = romaji[nRomaji*2+1];
			conv_lower((unsigned char *)strRep.GetBuffer(0));
			strRep.ReleaseBuffer();
			strWork.Format("%s%s%s", strWork.Left(nPos), strRep, strWork.Right(nLenOrg-(nPos+nLenKey)));
		}
		nRomaji++;
	}

	for (int i=0;;i++) {
		strWork.ReleaseBuffer();
		DWORD dwSize = strWork.GetLength()*(i+2)+20;
		if (conv_kan2hira(hwnd, (unsigned char *)strWork.GetBuffer(dwSize), dwSize) == 0)
			break;
	}
	strWork.ReleaseBuffer();
	*/

	nRomaji = 0;
	while (romaji[nRomaji*2] != NULL) {
		while((nPos = strWork.Find(romaji[nRomaji*2])) != -1) {
			int		nLenOrg = strWork.GetLength();
			int		nLenKey = strlen(romaji[nRomaji*2]);
			strRep = romaji[nRomaji*2+1];
			conv_lower((unsigned char *)strRep.GetBuffer(0));
			strRep.ReleaseBuffer();
			conv_first_upper((unsigned char *)strRep.GetBuffer(0));
			strRep.ReleaseBuffer();
			strWork.Format("%s%s%s", strWork.Left(nPos), strRep, strWork.Right(nLenOrg-(nPos+nLenKey)));
		}
		nRomaji++;
	}

	conv_zen2hans((unsigned char *)strRep.GetBuffer(strWork.GetLength()*2+1), (const unsigned char *)(const char *)strWork, CONV_ALL);
	strWork.ReleaseBuffer();
	strRep.ReleaseBuffer();
	strcpy((char*)sRomaji, strRep);
}
#endif


#if 0
void main(void)
{
	unsigned char	buffer[1024];
	unsigned char	buffer2[1024];
	const unsigned char *s1 =
		/* 0123456789ABCDEF		        OPQRSTUVWX`abcde */
		  "0123456789\n"		 /*       OPQRSTUVWX`abcde */
		  "abcdefghijklmnopqrstuvwxyz\n"	/*	        OPQRSTUVWX`abcde */
		  "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n"	/*	        OPQRSTUVWX`abcde */
		  " ¤¡,.¥:;?!Þß"	/* 212X:@@ABCDEFGHIJKLMN */
		  "^_-/ß"	/* 213X:OPQRSTUVWXYZ[\]^ */
		  " ~ |  `\' \"()  []\n"	/* 214X:_`abcdefghijklmn */
		  "{}¢£+-"	/* 215X:opqrstuvwxyz{|}~7F */
		  "=<>\\"	/* 216X: */
		  "$%#&*@\n"	/* 217X:   */
		   "§±¨²©³ª´«µ¶Þ·Þ¸Þ"	/* 252X:@@ABCDEFGHIJKLMN */
		  "¹ÞºÞ»Þ¼Þ½Þ¾Þ¿ÞÀÞ\n"	/* 253X:OPQRSTUVWXYZ[\]^ */
		  "ÁÞ¯ÂÞÃÞÄÞÅÆÇÈÉÊÞ"	/* 254X:_`abcdefghijklmn */
		  "ÊßËÞËßÌÞÌßÍÞÍßÎÞÎßÏÐ\n"	/* 255X:opqrstuvwxyz{|}~7F */
		  "ÑÒÓ¬Ô­Õ®Ö×ØÙÚÛÜ"	/* 256X: */
		  "¦Ý";				/* 257X: */
	
	han2zens(buffer, s1, CONV_ALL);
	zen2hans(buffer2, buffer, CONV_ALL);

	printf("%s\n\n", buffer);
//	printf("%s\n", buffer2);

	kata2hira(buffer);
	printf("%s\n", buffer);

	hira2kata(buffer);
	printf("%s\n", buffer);
}
#endif
