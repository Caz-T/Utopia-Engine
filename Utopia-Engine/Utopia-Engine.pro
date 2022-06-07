QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    activation_dialog.cpp \
    battle_dialog.cpp \
    dice.cpp \
    exploration_dialog.cpp \
    exploration_panel.cpp \
    final_activation_dialog.cpp \
    game_controller.cpp \
    link_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    panel.cpp \
    recharge_tool_dialog.cpp \
    worktable_panel.cpp

HEADERS += \
    activation_dialog.h \
    battle_dialog.h \
    constants.h \
    dice.h \
    exploration_dialog.h \
    exploration_panel.h \
    final_activation_dialog.h \
    game_controller.h \
    link_dialog.h \
    mainwindow.h \
    panel.h \
    recharge_tool_dialog.h \
    worktable_panel.h

FORMS += \
    activation_dialog.ui \
    battle_dialog.ui \
    exploration_dialog.ui \
    exploration_panel.ui \
    final_activation_dialog.ui \
    link_dialog.ui \
    mainwindow.ui \
    recharge_tool_dialog.ui \
    worktable_panel.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
