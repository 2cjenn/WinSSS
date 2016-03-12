# Microsoft Developer Studio Project File - Name="sss" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=sss - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sss.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sss.mak" CFG="sss - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sss - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "sss - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sss - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib glu32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "sss - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "sss - Win32 Release"
# Name "sss - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Model_Contact.cpp
# End Source File
# Begin Source File

SOURCE=.\Model_Cyclic.cpp
# End Source File
# Begin Source File

SOURCE=.\Model_EP.cpp
# End Source File
# Begin Source File

SOURCE=.\Model_GH.cpp
# End Source File
# Begin Source File

SOURCE=.\Model_LVoter.cpp
# End Source File
# Begin Source File

SOURCE=.\Model_MultiContact.cpp
# End Source File
# Begin Source File

SOURCE=.\Model_RSP.cpp
# End Source File
# Begin Source File

SOURCE=.\ModelTemplate.cpp
# End Source File
# Begin Source File

SOURCE=.\MyRand.cpp
# End Source File
# Begin Source File

SOURCE=.\ParaDlg_Contact.cpp
# End Source File
# Begin Source File

SOURCE=.\ParaDlg_Cyclic.cpp
# End Source File
# Begin Source File

SOURCE=.\ParaDlg_Ep.cpp
# End Source File
# Begin Source File

SOURCE=.\ParaDlg_GH.cpp
# End Source File
# Begin Source File

SOURCE=.\ParaDlg_MultiCont.cpp
# End Source File
# Begin Source File

SOURCE=.\ParaDlg_RSP.cpp
# End Source File
# Begin Source File

SOURCE=.\ParaDlg_Voter.cpp
# End Source File
# Begin Source File

SOURCE=.\SpatialWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\sss.cpp
# End Source File
# Begin Source File

SOURCE=.\sss.rc
# End Source File
# Begin Source File

SOURCE=.\sssDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\sssWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Model_Contact.h
# End Source File
# Begin Source File

SOURCE=.\Model_Cyclic.h
# End Source File
# Begin Source File

SOURCE=.\Model_EP.h
# End Source File
# Begin Source File

SOURCE=.\Model_GH.h
# End Source File
# Begin Source File

SOURCE=.\Model_LVoter.h
# End Source File
# Begin Source File

SOURCE=.\Model_MultiContact.h
# End Source File
# Begin Source File

SOURCE=.\Model_RSP.h
# End Source File
# Begin Source File

SOURCE=.\ModelTemplate.h
# End Source File
# Begin Source File

SOURCE=.\MyRand.h
# End Source File
# Begin Source File

SOURCE=.\ParaDlg_Contact.h
# End Source File
# Begin Source File

SOURCE=.\ParaDlg_Cyclic.h
# End Source File
# Begin Source File

SOURCE=.\ParaDlg_Ep.h
# End Source File
# Begin Source File

SOURCE=.\ParaDlg_GH.h
# End Source File
# Begin Source File

SOURCE=.\ParaDlg_MultiCont.h
# End Source File
# Begin Source File

SOURCE=.\ParaDlg_RSP.h
# End Source File
# Begin Source File

SOURCE=.\ParaDlg_Voter.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SpatialWnd.h
# End Source File
# Begin Source File

SOURCE=.\sss.h
# End Source File
# Begin Source File

SOURCE=.\sssDlg.h
# End Source File
# Begin Source File

SOURCE=.\sssWnd.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\sss.ico
# End Source File
# Begin Source File

SOURCE=.\res\sss.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
