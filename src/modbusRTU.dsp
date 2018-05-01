# Microsoft Developer Studio Project File - Name="modbusRTU" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=modbusRTU - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "modbusRTU.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "modbusRTU.mak" CFG="modbusRTU - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "modbusRTU - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "modbusRTU - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "modbusRTU - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W3 /O1 /I "." /I "$(QTDIR)\include" /I "H:\modbusRTU" /I "D:\Qt\3.2.1\mkspecs\win32-msvc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /D "QT_NO_DEBUG" /FD -Zm200 /c
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 "qt-mt321.lib" "qtmain.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "imm32.lib" "winmm.lib" "wsock32.lib" "winspool.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "imm32.lib" "winmm.lib" "wsock32.lib" "winspool.lib" "opengl32.lib" "glu32.lib" "delayimp.lib" delayimp.lib /nologo /subsystem:windows /machine:IX86 /libpath:"$(QTDIR)\lib" /DELAYLOAD:comdlg32.dll /DELAYLOAD:oleaut32.dll /DELAYLOAD:winmm.dll /DELAYLOAD:wsock32.dll /DELAYLOAD:winspool.dll

!ELSEIF  "$(CFG)" == "modbusRTU - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W3 /Gm /Zi /Od /I "." /I "$(QTDIR)\include" /I "H:\modbusRTU" /I "D:\Qt\3.2.1\mkspecs\win32-msvc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /FR /FD /GZ -Zm200 /c
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 "qt-mt321.lib" "qtmain.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "imm32.lib" "winmm.lib" "wsock32.lib" "winspool.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "imm32.lib" "winmm.lib" "wsock32.lib" "winspool.lib" "opengl32.lib" "glu32.lib" "delayimp.lib" /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept /libpath:"$(QTDIR)\lib"

!ENDIF 

# Begin Target

# Name "modbusRTU - Win32 Release"
# Name "modbusRTU - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=comm.cpp
# End Source File
# Begin Source File

SOURCE=ctdrive.cpp
# End Source File
# Begin Source File

SOURCE=ctsocket.cpp
# End Source File
# Begin Source File

SOURCE=domparser.cpp
# End Source File
# Begin Source File

SOURCE=main.cpp
# End Source File
# Begin Source File

SOURCE=Modbus.cpp
# End Source File
# Begin Source File

SOURCE=qextserialbase.cpp
# End Source File
# Begin Source File

SOURCE=qextserialport.cpp
# End Source File
# Begin Source File

SOURCE=ramrt.cpp
# End Source File
# Begin Source File

SOURCE=serial.cpp
# End Source File
# Begin Source File

SOURCE=trayicon.cpp
# End Source File
# Begin Source File

SOURCE=trayicon_win.cpp
# End Source File
# Begin Source File

SOURCE=win_qextserialport.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=comm.h
# End Source File
# Begin Source File

SOURCE=ctdrive.h

!IF  "$(CFG)" == "modbusRTU - Win32 Release"

USERDEP__CTDRI="$(QTDIR)\bin\moc.exe"	
# Begin Custom Build - Moc'ing ctdrive.h...
InputPath=ctdrive.h

"moc_ctdrive.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc ctdrive.h -o moc_ctdrive.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "modbusRTU - Win32 Debug"

USERDEP__CTDRI="$(QTDIR)\bin\moc.exe"	
# Begin Custom Build - Moc'ing ctdrive.h...
InputPath=ctdrive.h

"moc_ctdrive.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc ctdrive.h -o moc_ctdrive.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ctsocket.h

!IF  "$(CFG)" == "modbusRTU - Win32 Release"

USERDEP__CTSOC="$(QTDIR)\bin\moc.exe"	
# Begin Custom Build - Moc'ing ctsocket.h...
InputPath=ctsocket.h

"moc_ctsocket.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc ctsocket.h -o moc_ctsocket.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "modbusRTU - Win32 Debug"

USERDEP__CTSOC="$(QTDIR)\bin\moc.exe"	
# Begin Custom Build - Moc'ing ctsocket.h...
InputPath=ctsocket.h

"moc_ctsocket.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc ctsocket.h -o moc_ctsocket.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=domparser.h
# End Source File
# Begin Source File

SOURCE=Modbus.h
# End Source File
# Begin Source File

SOURCE=os.h
# End Source File
# Begin Source File

SOURCE=qextserialbase.h
# End Source File
# Begin Source File

SOURCE=qextserialport.h
# End Source File
# Begin Source File

SOURCE=ramrt.h
# End Source File
# Begin Source File

SOURCE=serial.h
# End Source File
# Begin Source File

SOURCE=trayicon.h

!IF  "$(CFG)" == "modbusRTU - Win32 Release"

USERDEP__TRAYI="$(QTDIR)\bin\moc.exe"	
# Begin Custom Build - Moc'ing trayicon.h...
InputPath=trayicon.h

"moc_trayicon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc trayicon.h -o moc_trayicon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "modbusRTU - Win32 Debug"

USERDEP__TRAYI="$(QTDIR)\bin\moc.exe"	
# Begin Custom Build - Moc'ing trayicon.h...
InputPath=trayicon.h

"moc_trayicon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc trayicon.h -o moc_trayicon.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=win_qextserialport.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Generated"

# PROP Default_Filter ""
# Begin Source File

SOURCE=moc_ctdrive.cpp
# End Source File
# Begin Source File

SOURCE=moc_ctsocket.cpp
# End Source File
# Begin Source File

SOURCE=moc_trayicon.cpp
# End Source File
# End Group
# End Target
# End Project
