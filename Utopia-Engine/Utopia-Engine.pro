QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    activation_dialog.cpp \
    backpack_panel.cpp \
    battle_dialog.cpp \
    connection_dialog.cpp \
    dice.cpp \
    exploration_dialog.cpp \
    exploration_panel.cpp \
    game_controller.cpp \
    main.cpp \
    mainwindow.cpp \
    panel.cpp \
    worktable_panel.cpp

HEADERS += \
    activation_dialog.h \
    backpack_panel.h \
    battle_dialog.h \
    connection_dialog.h \
    dice.h \
    exploration_dialog.h \
    exploration_panel.h \
    game_controller.h \
    mainwindow.h \
    panel.h \
    worktable_panel.h

FORMS += \
    activation_dialog.ui \
    backpack_panel.ui \
    battle_dialog.ui \
    connection_dialog.ui \
    exploration_dialog.ui \
    exploration_panel.ui \
    mainwindow.ui \
    worktable_panel.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
