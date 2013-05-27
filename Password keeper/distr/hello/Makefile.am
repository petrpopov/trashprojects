
CC       = gcc
CXX      = g++
LEX      = flex
YACC     = yacc
CFLAGS   = -pipe -Wall -W -O2 -mcpu=pentium4  -DQT_NO_DEBUG
CXXFLAGS = -pipe -Wall -W -O2 -mcpu=pentium4  -DQT_NO_DEBUG
LEXFLAGS = 
YACCFLAGS= -d
INCPATH  = -I$(QTDIR)/mkspecs/linux-g++ -I. -I. -I$(QTDIR)/include
LINK     = g++
LFLAGS   = 
LIBS     = $(SUBLIBS) -L$(QTDIR)/lib -L/usr/X11R6/lib -lqt -lXext -lX11 -lm
AR       = ar cqs
RANLIB   = 
MOC      = $(QTDIR)/bin/moc
UIC      = $(QTDIR)/bin/uic
QMAKE    = qmake
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f
COPY_FILE= $(COPY)
COPY_DIR = $(COPY) -r
INSTALL_FILE= $(COPY_FILE)
INSTALL_DIR = $(COPY_DIR)
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rmdir
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p

####### Output directory

OBJECTS_DIR = ./

####### Files

SOURCES = hello.cpp
OBJECTS = hello.o
FORMS = 
UICDECLS = 
UICIMPLS = 
SRCMOC   = 
OBJMOC = 
DIST	   = hello.pro
QMAKE_TARGET = hello
DESTDIR  = 
TARGET   = hello

first: all
####### Implicit rules

SUFFIXES= .c .o .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules

all: Makefile.am $(TARGET)

$(TARGET):  $(UICDECLS) $(OBJECTS) $(OBJMOC)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(OBJCOMP) $(LIBS)

mocables: $(SRCMOC)
uicables: $(UICDECLS) $(UICIMPLS)

$(MOC): 
	( cd $(QTDIR)/src/moc && $(MAKE) )

Makefile.am: hello.pro  /usr/qt/3/mkspecs/linux-g++/qmake.conf 
	$(QMAKE) -o Makefile.am hello.pro
qmake: 
	@$(QMAKE) -o Makefile.am hello.pro

dist: 
	@mkdir -p .tmp/hello && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/hello/ && ( cd `dirname .tmp/hello` && $(TAR) hello.tar hello && $(GZIP) hello.tar ) && $(MOVE) `dirname .tmp/hello`/hello.tar.gz . && $(DEL_FILE) -r .tmp/hello

mocclean:

uiclean:

yaccclean:
lexclean:
clean:
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) $(TARGET)


FORCE:

####### Compile

hello.o: hello.cpp 

####### Install

install:  

uninstall:  

