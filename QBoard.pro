#-------------------------------------------------
#
# Project created by QtCreator 2017-06-13T19:07:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QBoard
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Board.cpp \
    ChessBoard.cpp \
    ChessPiece.cpp \
    ChuShogiBoard.cpp \
    ChuShogiPiece.cpp \
    Piece.cpp \
    settingsdialog.cpp \
    vboard.cpp \
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
    MiniShogiBoard.cpp

HEADERS  += mainwindow.h \
    Board.h \
    ChessBoard.h \
    ChessPiece.h \
    ChuShogiBoard.h \
    ChuShogiPiece.h \
    Common.h \
    Piece.h \
    settingsdialog.h \
    vboard.h \
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
    MiniShogiBoard.h

FORMS    += mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    resources.qrc
