#############################################################################
# Makefile for building: fractal
# Generated by qmake (1.07a) (Qt 3.3.3) on: Fri Oct 21 21:09:57 2005
# Project:  fractal.pro
# Template: app
# Command: $(QMAKE) -o Makefile fractal.pro
#############################################################################

####### Compiler, tools and options

CC		=	cl
CXX		=	cl
LEX		= flex
YACC		= byacc
CFLAGS	=	-nologo -Zm200 -W3 -MD -O1  -DUNICODE -DWIN32 -DQT_DLL -DQT_THREAD_SUPPORT -DQT_NO_DEBUG
CXXFLAGS	=	-nologo -Zm200 -W3 -w34100 -w34189 -MD -O1  -DUNICODE -DWIN32 -DQT_DLL -DQT_THREAD_SUPPORT -DQT_NO_DEBUG
LEXFLAGS	=
YACCFLAGS	=-d
INCPATH	=	 -I"." -I"$(QTDIR)\include" -I"F:\fractal" -I"F:\Qt\3.3.3\mkspecs\win32-msvc.net"
LINK	=	link
LFLAGS	=	/NOLOGO /DELAYLOAD:comdlg32.dll /DELAYLOAD:oleaut32.dll /DELAYLOAD:winmm.dll /DELAYLOAD:wsock32.dll /DELAYLOAD:winspool.dll /SUBSYSTEM:WINDOWS /LIBPATH:"$(QTDIR)\lib"
LIBS	=	 "qt-mt333.lib" "qtmain.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "imm32.lib" "winmm.lib" "wsock32.lib" "winspool.lib" "delayimp.lib" "opengl32.lib" "glu32.lib"
MOC		=	$(QTDIR)\bin\moc.exe
UIC		=	$(QTDIR)\bin\uic.exe
QMAKE		=	qmake
IDC		=	$(QTDIR)\bin\idc.exe
IDL		=	midl
ZIP		=	zip -r -9
COPY_FILE	=       copy
COPY_DIR	=       copy
DEL_FILE	=       del
DEL_DIR	=       rmdir
MOVE		=       move
CHK_DIR_EXISTS =	if not exist
MKDIR		=	mkdir
INSTALL_FILE= $(COPY_FILE)
INSTALL_DIR = $(COPY_DIR)

####### Files

HEADERS =	itdialog.h \
		mainform.h
SOURCES =	itdialog.cpp \
		main.cpp \
		mainform.cpp
OBJECTS =	itdialog.obj \
		main.obj \
		mainform.obj
FORMS =	
UICDECLS =	
UICIMPLS =	
SRCMOC	=	moc_itdialog.cpp \
		moc_mainform.cpp
OBJMOC	=	moc_itdialog.obj \
		moc_mainform.obj
DIST	=	
TARGET	=	fractal.exe

####### Implicit rules

.SUFFIXES: .c .cpp .cc .cxx .C

{.}.cpp{}.obj::
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -Fo @<<
	$<
<<

{.}.cc{}.obj::
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -Fo @<<
	$<
<<

{.}.cxx{}.obj::
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -Fo @<<
	$<
<<

{.}.C{}.obj::
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -Fo @<<
	$<
<<

{.}.c{}.obj::
	$(CC) -c $(CFLAGS) $(INCPATH) -Fo @<<
	$<
<<

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	$(LINK) $(LFLAGS) /OUT:$(TARGET) @<< 
	  $(OBJECTS) $(OBJMOC) $(LIBS)
<<


mocables: $(SRCMOC)
uicables: $(UICIMPLS) $(UICDECLS)

Makefile: fractal.pro  F:\Qt\3.3.3\mkspecs\win32-msvc.net\qmake.conf ..\Qt\3.3.3\lib\qtmain.prl
	$(QMAKE) -o Makefile fractal.pro
qmake: 
	@$(QMAKE) -o Makefile fractal.pro

dist:
	$(ZIP) fractal.zip $(SOURCES) $(HEADERS) $(DIST) $(FORMS) F:/fractal/fractal.pro ..\Qt\3.3.3\lib\qtmain.prl  

uiclean:
mocclean:
	-$(DEL_FILE) moc_itdialog.cpp
	-$(DEL_FILE) moc_mainform.cpp
	-$(DEL_FILE) moc_itdialog.obj
	-$(DEL_FILE) moc_mainform.obj
clean: uiclean mocclean
	-$(DEL_FILE) itdialog.obj
	-$(DEL_FILE) main.obj
	-$(DEL_FILE) mainform.obj



FORCE:

distclean: clean
	-$(DEL_FILE) $(TARGET)

####### Compile

itdialog.obj: itdialog.cpp  \
		itdialog.h \
		

main.obj: main.cpp  \
		mainform.h \
		

mainform.obj: mainform.cpp  \
		mainform.h \
		itdialog.h \
		

moc_itdialog.obj: moc_itdialog.cpp  itdialog.h 

moc_mainform.obj: moc_mainform.cpp  mainform.h 

moc_itdialog.cpp: $(MOC) itdialog.h
	$(MOC) itdialog.h -o moc_itdialog.cpp

moc_mainform.cpp: $(MOC) mainform.h
	$(MOC) mainform.h -o moc_mainform.cpp

####### Install

install:  

uninstall:  

