#-------------------------------------------------
#
# Project created by QtCreator 2017-06-13T19:07:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QBoard
TEMPLATE = app

win32:RC_ICONS += toolbar/QBoard.ico
macx-clang {
    ICON = toolbar/QBoard.icns
}

SOURCES += main.cpp\
        mainwindow.cpp \
    Board.cpp \
    ChessBoard.cpp \
    ChessPiece.cpp \
    ChuShogiBoard.cpp \
    ChuShogiPiece.cpp \
    Piece.cpp \
    promotiondialog.cpp \
    settingsdialog.cpp \
    vboard.cpp \
    IniFile.cpp \
    ShogiVariantBoard.cpp \
    ShogiBoard.cpp \
    ShogiPiece.cpp \
    XiangqiBoard.cpp \
    XiangqiPiece.cpp \
    Engine.cpp \
    UciEngine.cpp \
    WbEngine.cpp \
    QianhongEngine.cpp \
    UcciEngine.cpp \
    UsiEngine.cpp \
    ChuShogiEngine.cpp \
    MiniShogiBoard.cpp \
    enginemanager.cpp \
    comboboxitemdelegate.cpp \
    newgamedialog.cpp \
    addenginedialog.cpp \
    PGN.cpp \
    WXF.cpp \
    PSN.cpp \
    CSA.cpp \
    KIF.cpp

HEADERS  += mainwindow.h \
    Board.h \
    ChessBoard.h \
    ChessPiece.h \
    ChuShogiBoard.h \
    ChuShogiPiece.h \
    Common.h \
    Piece.h \
    promotiondialog.h \
    settingsdialog.h \
    vboard.h \
    IniFile.h \
    ShogiVariantBoard.h \
    ShogiBoard.h \
    ShogiPiece.h \
    XiangqiBoard.h \
    XiangqiPiece.h \
    Engine.h \
    UciEngine.h \
    WbEngine.h \
    QianhongEngine.h \
    UcciEngine.h \
    UsiEngine.h \
    ChuShogiEngine.h \
    MiniShogiBoard.h \
    enginemanager.h \
    comboboxitemdelegate.h \
    newgamedialog.h \
    addenginedialog.h \
    PGN.h \
    WXF.h \
    PSN.h \
    CSA.h \
    KIF.h

FORMS    += mainwindow.ui \
    promotiondialog.ui \
    settingsdialog.ui \
    enginemanager.ui \
    newgamedialog.ui \
    addenginedialog.ui

RESOURCES += \
    resources.qrc
