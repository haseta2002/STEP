# Microsoft Developer Studio Project File - Name="SuperTagEditor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SuperTagEditor - Win32 PublicDebug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "SuperTagEditor.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "SuperTagEditor.mak" CFG="SuperTagEditor - Win32 PublicDebug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "SuperTagEditor - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "SuperTagEditor - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE "SuperTagEditor - Win32 PublicRelease" ("Win32 (x86) Application" 用)
!MESSAGE "SuperTagEditor - Win32 PublicDebug" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/STEP/SuperTagEditor", DAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SuperTagEditor - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".\id3v2" /I "D:\WMSDK\WMFSDK\include" /I ".\ogg\include" /I "..\STEP_SDK" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "SUPORT_DRAGDROP" /D "RECONVERT_ID3V2" /D "FLICKERFREE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 htmlhelp.lib imm32.lib /nologo /subsystem:windows /machine:I386 /libpath:"D:\WMSDK\WMFSDK\lib"

!ELSEIF  "$(CFG)" == "SuperTagEditor - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\STEP_SDK" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "SUPORT_DRAGDROP" /D "RECONVERT_ID3V2" /D "FLICKERFREE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 htmlhelp.lib imm32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"D:\WMSDK\WMFSDK\lib"

!ELSEIF  "$(CFG)" == "SuperTagEditor - Win32 PublicRelease"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SuperTagEditor___Win32_PublicRelease"
# PROP BASE Intermediate_Dir "SuperTagEditor___Win32_PublicRelease"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "PublicRelease"
# PROP Intermediate_Dir "PublicRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I ".\id3v2" /I "D:\WMSDK\WMFSDK\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "SUPORT_DRAGDROP" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".\id3v2" /I "D:\WMSDK\WMFSDK\include" /I ".\ogg\include" /I "..\STEP_SDK" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "SUPORT_DRAGDROP" /D "FLICKERFREE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wmstub.lib wmvcore.lib vbmp3.lib htmlhelp.lib ape/MACLib.lib /nologo /subsystem:windows /machine:I386 /libpath:"D:\WMSDK\WMFSDK\lib"
# ADD LINK32 htmlhelp.lib imm32.lib /nologo /subsystem:windows /machine:I386 /libpath:"D:\WMSDK\WMFSDK\lib"

!ELSEIF  "$(CFG)" == "SuperTagEditor - Win32 PublicDebug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SuperTagEditor___Win32_PublicDebug"
# PROP BASE Intermediate_Dir "SuperTagEditor___Win32_PublicDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "PublicDebug"
# PROP Intermediate_Dir "PublicDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I ".\id3v2" /I "D:\WMSDK\WMFSDK\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "SUPORT_DRAGDROP" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I ".\id3v2" /I "D:\WMSDK\WMFSDK\include" /I ".\ogg\include" /I "..\STEP_SDK" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "SUPORT_DRAGDROP" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wmstub.lib wmvcore.lib vbmp3.lib htmlhelp.lib ape/MACLib.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"D:\WMSDK\WMFSDK\lib"
# ADD LINK32 htmlhelp.lib imm32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"D:\WMSDK\WMFSDK\lib"

!ENDIF 

# Begin Target

# Name "SuperTagEditor - Win32 Release"
# Name "SuperTagEditor - Win32 Debug"
# Name "SuperTagEditor - Win32 PublicRelease"
# Name "SuperTagEditor - Win32 PublicDebug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\mp3infp\call_mp3infp.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboInListView.cpp
# End Source File
# Begin Source File

SOURCE=.\DkToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAddNumber.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAddUserGenre.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCommonProg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDeleteChar.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFavorites.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFileNameChange.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFileOverWrite.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFileOverWrite2.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFixedString.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFixedUpperLower.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgListSort.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLoadPlayList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNameChange.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPluginSetup.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgReplaceWord.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTeikei.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTeikeiPaste.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUnifyChar.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUserConvFormartTag2Tag.cpp
# End Source File
# Begin Source File

SOURCE=.\DoubleZeroString.cpp
# End Source File
# Begin Source File

SOURCE=.\FileMP3.cpp
# End Source File
# Begin Source File

SOURCE=.\HeaderCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\HistoryComboEx.cpp
# End Source File
# Begin Source File

SOURCE=.\dde\kbdde.cpp
# End Source File
# Begin Source File

SOURCE=.\ListEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MyFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MyFileDialogPlaylist.cpp
# End Source File
# Begin Source File

SOURCE=.\MyRecentFileList.cpp
# End Source File
# Begin Source File

SOURCE=.\MySuperGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\OXToolTipCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\INI\Profile.cpp
# End Source File
# Begin Source File

SOURCE=.\Regexp.cpp
# End Source File
# Begin Source File

SOURCE=.\SHBrowseForFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\strcnv.cpp
# End Source File
# Begin Source File

SOURCE=.\SuperGridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\SuperTagEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\SuperTagEditor.rc
# End Source File
# Begin Source File

SOURCE=.\SuperTagEditorDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SuperTagEditorView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ape\All.h
# End Source File
# Begin Source File

SOURCE=.\ape\APEInfo.h
# End Source File
# Begin Source File

SOURCE=.\ape\APETag.h
# End Source File
# Begin Source File

SOURCE=.\AutoBuildCount.h
# End Source File
# Begin Source File

SOURCE=.\ID3v2\classID.h
# End Source File
# Begin Source File

SOURCE=.\ComboInListView.h
# End Source File
# Begin Source File

SOURCE=.\DkToolBar.h
# End Source File
# Begin Source File

SOURCE=.\DlgAddNumber.h
# End Source File
# Begin Source File

SOURCE=.\DlgAddUserGenre.h
# End Source File
# Begin Source File

SOURCE=.\DlgCommonProg.h
# End Source File
# Begin Source File

SOURCE=.\DlgDeleteChar.h
# End Source File
# Begin Source File

SOURCE=.\DlgFavorites.h
# End Source File
# Begin Source File

SOURCE=.\DlgFileNameChange.h
# End Source File
# Begin Source File

SOURCE=.\DlgFileOverWrite.h
# End Source File
# Begin Source File

SOURCE=.\DlgFileOverWrite2.h
# End Source File
# Begin Source File

SOURCE=.\DlgFixedString.h
# End Source File
# Begin Source File

SOURCE=.\DlgFixedUpperLower.h
# End Source File
# Begin Source File

SOURCE=.\DlgListSort.h
# End Source File
# Begin Source File

SOURCE=.\DlgLoadPlayList.h
# End Source File
# Begin Source File

SOURCE=.\DlgNameChange.h
# End Source File
# Begin Source File

SOURCE=.\DlgPluginSetup.h
# End Source File
# Begin Source File

SOURCE=.\DlgReplaceWord.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetCheck.h
# End Source File
# Begin Source File

SOURCE=.\DlgTeikei.h
# End Source File
# Begin Source File

SOURCE=.\DlgTeikeiPaste.h
# End Source File
# Begin Source File

SOURCE=.\DlgUnifyChar.h
# End Source File
# Begin Source File

SOURCE=.\DlgUserConvFormartTag2Tag.h
# End Source File
# Begin Source File

SOURCE=.\DoubleZeroString.h
# End Source File
# Begin Source File

SOURCE=.\FileMP3.h
# End Source File
# Begin Source File

SOURCE=.\HeaderCtrlEx.h
# End Source File
# Begin Source File

SOURCE=.\HistoryComboEx.h
# End Source File
# Begin Source File

SOURCE=.\ape\IO.h
# End Source File
# Begin Source File

SOURCE=.\dde\kbdde.h
# End Source File
# Begin Source File

SOURCE=.\ListEditCtrl.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MyFileDialog.h
# End Source File
# Begin Source File

SOURCE=.\MyFileDialogPlaylist.h
# End Source File
# Begin Source File

SOURCE=.\MyRecentFileList.h
# End Source File
# Begin Source File

SOURCE=.\MySuperGrid.h
# End Source File
# Begin Source File

SOURCE=.\OXDllExt.h
# End Source File
# Begin Source File

SOURCE=.\OXToolTipCtrl.h
# End Source File
# Begin Source File

SOURCE=.\INI\Profile.h
# End Source File
# Begin Source File

SOURCE=.\Regexp.h
# End Source File
# Begin Source File

SOURCE=.\Registry.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\scmpx.h
# End Source File
# Begin Source File

SOURCE=.\SHBrowseForFolder.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SuperGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\SuperTagEditor.h
# End Source File
# Begin Source File

SOURCE=.\SuperTagEditorDoc.h
# End Source File
# Begin Source File

SOURCE=.\SuperTagEditorView.h
# End Source File
# Begin Source File

SOURCE=.\winamp.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\check.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\folders.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\subitems.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SuperTagEditor.ico
# End Source File
# Begin Source File

SOURCE=.\res\SuperTagEditor.rc2
# End Source File
# Begin Source File

SOURCE=.\res\SuperTagEditorDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tree.bmp
# End Source File
# End Group
# Begin Group "オプション設定関連"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DlgConv.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgConv.h
# End Source File
# Begin Source File

SOURCE=.\DlgConvFormatEx.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgConvFormatEx.h
# End Source File
# Begin Source File

SOURCE=.\DlgCopyFormat.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCopyFormat.h
# End Source File
# Begin Source File

SOURCE=.\DlgDefaultValue.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDefaultValue.h
# End Source File
# Begin Source File

SOURCE=.\DlgEditShowColumn.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditShowColumn.h
# End Source File
# Begin Source File

SOURCE=.\DlgEnvConf.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEnvConf.h
# End Source File
# Begin Source File

SOURCE=.\DlgEnvironment.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEnvironment.h
# End Source File
# Begin Source File

SOURCE=.\DlgEnvPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEnvPlayer.h
# End Source File
# Begin Source File

SOURCE=.\DlgEnvSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEnvSheet.h
# End Source File
# Begin Source File

SOURCE=.\DlgFileNameMaxCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFileNameMaxCheck.h
# End Source File
# Begin Source File

SOURCE=.\DlgFolderSync.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFolderSync.h
# End Source File
# Begin Source File

SOURCE=.\DlgKeyConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgKeyConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgLyricFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLyricFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgMoveFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMoveFolder.h
# End Source File
# Begin Source File

SOURCE=.\DlgReplaceFileName.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgReplaceFileName.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetClassification.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetClassification.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetupGenre.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetupGenre.h
# End Source File
# Begin Source File

SOURCE=.\DlgUserConvFormat.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUserConvFormat.h
# End Source File
# Begin Source File

SOURCE=.\DlgWriteForm.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWriteForm.h
# End Source File
# Begin Source File

SOURCE=.\OptionPage\OptionListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionPage\OptionListBox.h
# End Source File
# Begin Source File

SOURCE=.\OptionPage\OptionPage.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionPage\OptionPage.h
# End Source File
# Begin Source File

SOURCE=.\OptionPage\OptionPageStaticText.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionPage\OptionPageStaticText.h
# End Source File
# Begin Source File

SOURCE=.\OptionPage\OptionSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionPage\OptionSheet.h
# End Source File
# Begin Source File

SOURCE=.\OptionPage\SMLDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionPage\SMLDoc.h
# End Source File
# Begin Source File

SOURCE=.\OptionPage\SMLStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionPage\SMLStatic.h
# End Source File
# End Group
# Begin Group "HELP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Help\history.html
# End Source File
# Begin Source File

SOURCE=.\Help\index.html
# End Source File
# Begin Source File

SOURCE=.\Help\schedule.html
# End Source File
# End Group
# Begin Group "Plugin"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Plugin.cpp
# End Source File
# Begin Source File

SOURCE=.\Plugin.h
# End Source File
# Begin Source File

SOURCE=.\STEP_api.cpp
# End Source File
# Begin Source File

SOURCE=..\STEP_SDK\STEP_api.h
# End Source File
# Begin Source File

SOURCE=..\STEP_SDK\STEP_API.txt
# End Source File
# Begin Source File

SOURCE=..\STEP_SDK\STEPlugin.cpp
# End Source File
# Begin Source File

SOURCE=..\STEP_SDK\STEPlugin.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\STEP.txt
# End Source File
# Begin Source File

SOURCE=.\SuperTagEditor.reg
# End Source File
# Begin Source File

SOURCE=..\var_list.txt
# End Source File
# Begin Source File

SOURCE=..\var_list2.txt
# End Source File
# End Target
# End Project
