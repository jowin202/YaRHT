QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GUI/connectionlabel.cpp \
    GUI/encounterwidget.cpp \
    GUI/pokemonwidget.cpp \
    GUI/textbrowserdialog.cpp \
    ROM/gbaencounter.cpp \
    ROM/gbamap.cpp \
    ROM/gbaoffsetfinder.cpp \
    ROM/gbapalette.cpp \
    ROM/gbapokemon.cpp \
    ROM/gbarom.cpp \
    GUI/hexspin.cpp \
    ROM/gbatileset.cpp \
    ROM/gbatrainer.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    GUI/connectionlabel.h \
    GUI/encounterwidget.h \
    GUI/pokemonwidget.h \
    GUI/textbrowserdialog.h \
    ROM/gbaencounter.h \
    ROM/gbamap.h \
    ROM/gbaoffsetfinder.h \
    ROM/gbapalette.h \
    ROM/gbapokemon.h \
    ROM/gbarom.h \
    GUI/hexspin.h \
    ROM/gbatileset.h \
    ROM/gbatrainer.h \
    mainwindow.h

FORMS += \
    GUI/encounterwidget.ui \
    GUI/pokemonwidget.ui \
    GUI/textbrowserdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
