# ???? ?????? ? KDevelop ?????????? qmake.
# ------------------------------------------- 
# ?????????? ???????????? ???????? ???????? ???????: ./src
# ???? - ??????????:  ../bin/gameclient

IMAGES += images/new.png \
          images/open.png \
          images/save.png \
          images/create.png \
          images/find.png \
          images/icon.png \
          images/check.png \
          images/help.png \
	  images/back.png \
	  images/fwd.png \
	  images/exit.png \
	  images/home.png \
	  images/gear.png
HEADERS += mainform.h \
           creategame.h \
           findgame.h \
           addserver.h \
           mynetworkobject.h \
           gamedialog.h \
           helpbrowser.h \
	   checker.h \
	   cleardialog.h
SOURCES += mainform.cpp \
           main.cpp \
           creategame.cpp \
           findgame.cpp \
           addserver.cpp \
           gamedialog.cpp \
           helpbrowser.cpp \
	   cleardialog.cpp
#TARGET=../bin/gameclient
