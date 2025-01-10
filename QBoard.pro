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
    KanjiPiece.cpp \
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
    MiniShogiBoard.cpp \
    JudkinShogiBoard.cpp \
    ShatranjBoard.cpp \
    ShatranjPiece.cpp \
    MakrukBoard.cpp \
    MakrukPiece.cpp \
    DaiShogiBoard.cpp \
    DaiShogiPiece.cpp \
    enginemanager.cpp \
    comboboxitemdelegate.cpp \
    newgamedialog.cpp \
    addenginedialog.cpp

HEADERS  += mainwindow.h \
    Board.h \
    ChessBoard.h \
    ChessPiece.h \
    ChuShogiBoard.h \
    ChuShogiPiece.h \
    Common.h \
    Piece.h \
    KanjiPiece.h \
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
    MiniShogiBoard.h \
    JudkinShogiBoard.h \
    ShatranjBoard.h \
    ShatranjPiece.h \
    MakrukBoard.h \
    MakrukPiece.h \
    DaiShogiBoard.h \
    DaiShogiPiece.h \
    enginemanager.h \
    comboboxitemdelegate.h \
    newgamedialog.h \
    addenginedialog.h

FORMS    += mainwindow.ui \
    promotiondialog.ui \
    settingsdialog.ui \
    enginemanager.ui \
    newgamedialog.ui \
    addenginedialog.ui

RESOURCES += \
    resources.qrc
