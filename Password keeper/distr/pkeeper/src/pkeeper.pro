# ???? ?????? ? KDevelop ?????????? qmake.
# ------------------------------------------- 
# ?????????? ???????????? ???????? ???????? ???????: ./src
# ???? - ??????????:  ../bin/pkeeper

IMAGES += icons/close.png \
         icons/new.png \
         icons/open.png \
         icons/save.png \
         icons/delete.png \
         icons/delete_all.png \
         icons/tb_close.png \
         icons/tb_delete.png \
         icons/tb_new.png \
         icons/tb_open.png \
         icons/tb_save.png \
         icons/account.png \
         icons/icq.png \
         icons/irc.png \
         icons/mail.png \
         icons/system.png \
         icons/other.png \
         icons/edit.png \
         icons/tb_edit.png \
         icons/undo.png \
         icons/tb_undo.png \
         icons/redo.png \
         icons/tb_redo.png
          
HEADERS += mainform.h \
           newfield.h \
           createprofile.h \
           checkpass.h \
           changeprofile.h \
           rc4.h
           
SOURCES += mainform.cpp \
           newfield.cpp \
           main.cpp \
           createprofile.cpp \
           checkpass.cpp \
           changeprofile.cpp \
           md5.cpp \
           rc4.cpp 
           
TARGET = ../bin/pkeeper
