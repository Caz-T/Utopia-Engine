QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    activation_dialog.cpp \
    connection_dialog.cpp \
    exploration.cpp \
    exploration_dialog.cpp \
    game_controller.cpp \
    main.cpp \
    mainwindow.cpp \
    worktable.cpp

HEADERS += \
    activation_dialog.h \
    connection_dialog.h \
    exploration.h \
    exploration_dialog.h \
    game_controller.h \
    mainwindow.h \
    worktable.h

FORMS += \
    activation_dialog.ui \
    connection_dialog.ui \
    exploration.ui \
    exploration_dialog.ui \
    mainwindow.ui \
    worktable.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
