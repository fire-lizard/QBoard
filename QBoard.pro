#-------------------------------------------------
#
# Project created by QtCreator 2017-06-13T19:07:43
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QBoard
TEMPLATE = app

win32:RC_ICONS += toolbar/QBoard.ico
macx-clang {
    ICON = toolbar/QBoard.icns
}

SOURCES += main.cpp\
    CapablancaChessBoard.cpp \
    GothicChessBoard.cpp \
    GothicChessPiece.cpp \
    GrandChessBoard.cpp \
    HeianDaiShogiBoard.cpp \
    HeianShogiBoard.cpp \
    HeianShogiPiece.cpp \
    JanusChessBoard.cpp \
    KyotoShogiBoard.cpp \
    KyotoShogiPiece.cpp \
    MicroShogiBoard.cpp \
    MicroShogiPiece.cpp \
    ToriShogiPiece.cpp \
    ToriShogiBoard.cpp \
    EuroShogiBoard.cpp \
    WhaleShogiBoard.cpp \
    WhaleShogiPiece.cpp \
    YariShogiBoard.cpp \
    YariShogiPiece.cpp \
    mainwindow.cpp \
    Board.cpp \
    ChessBoard.cpp \
    ChessPiece.cpp \
    ChuShogiBoard.cpp \
    ChuShogiPiece.cpp \
    Piece.cpp \
    KanjiPiece.cpp \
    Logger.cpp \
    promotiondialog.cpp \
    gothicpromotiondialog.cpp \
    januspromotiondialog.cpp \
    settingsdialog.cpp \
    variantdialog.cpp \
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
    TenjikuShogiBoard.cpp \
    TenjikuShogiPiece.cpp \
    WaShogiBoard.cpp \
    WaShogiPiece.cpp \
    DaiDaiShogiBoard.cpp \
    DaiDaiShogiPiece.cpp \
    MakaDaiDaiShogiBoard.cpp \
    MakaDaiDaiShogiPiece.cpp \
    KoShogiBoard.cpp \
    KoShogiPiece.cpp \
    EngineOutputHandler.cpp \
    Communications.cpp \
    enginemanager.cpp \
    networkmanager.cpp \
    comboboxitemdelegate.cpp \
    newgamedialog.cpp \
    addenginedialog.cpp

HEADERS  += mainwindow.h \
    Board.h \
    CapablancaChessBoard.h \
    ChessBoard.h \
    ChessPiece.h \
    ChuShogiBoard.h \
    ChuShogiPiece.h \
    Common.h \
    GothicChessBoard.h \
    GothicChessPiece.h \
    GrandChessBoard.h \
    HeianDaiShogiBoard.h \
    HeianShogiBoard.h \
    HeianShogiPiece.h \
    JanusChessBoard.h \
    KyotoShogiBoard.h \
    KyotoShogiPiece.h \
    MicroShogiBoard.h \
    MicroShogiPiece.h \
    Piece.h \
    KanjiPiece.h \
    Logger.h \
    ToriShogiPiece.h \
    ToriShogiBoard.h \
    EuroShogiBoard.h \
    WhaleShogiBoard.h \
    WhaleShogiPiece.h \
    YariShogiBoard.h \
    YariShogiPiece.h \
    promotiondialog.h \
    gothicpromotiondialog.h \
    januspromotiondialog.h \
    settingsdialog.h \
    variantdialog.h \
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
    TenjikuShogiBoard.h \
    TenjikuShogiPiece.h \
    WaShogiBoard.h \
    WaShogiPiece.h \
    DaiDaiShogiBoard.h \
    DaiDaiShogiPiece.h \
    MakaDaiDaiShogiBoard.h \
    MakaDaiDaiShogiPiece.h \
    KoShogiBoard.h \
    KoShogiPiece.h \
    EngineOutputHandler.h \
    Communications.h \
    enginemanager.h \
    networkmanager.h \
    comboboxitemdelegate.h \
    newgamedialog.h \
    addenginedialog.h

FORMS    += mainwindow.ui \
    promotiondialog.ui \
    gothicpromotiondialog.ui \
    januspromotiondialog.ui \
    settingsdialog.ui \
    enginemanager.ui \
    networkmanager.ui \
    newgamedialog.ui \
    addenginedialog.ui \
    variantdialog.ui

RESOURCES += \
    resources.qrc
