#-------------------------------------------------
#
# Project created by QtCreator 2017-06-13T19:07:43
#
#-------------------------------------------------

QT       += widgets core gui network

CONFIG   += c++20

TARGET = QBoard
TEMPLATE = app

win32:RC_ICONS += toolbar/QBoard.ico
macx-clang {
    ICON = toolbar/QBoard.icns
}

SOURCES += main.cpp\
    PieceStorage.cpp \
    CapablancaChessBoard.cpp \
    ChancellorChessBoard.cpp \
    CourierChessBoard.cpp \
    GothicChessBoard.cpp \
    GrandChessBoard.cpp \
    MusketeerChessBoard.cpp \
    GrandeAcedrexBoard.cpp \
    HeianDaiShogiBoard.cpp \
    HeianShogiBoard.cpp \
    JanggiBoard.cpp \
    JanusChessBoard.cpp \
    KyotoShogiBoard.cpp \
    MicroShogiBoard.cpp \
    ModernChessBoard.cpp \
    NightriderChessBoard.cpp \
    OmegaChessBoard.cpp \
    ShatarBoard.cpp \
    SittuyinBoard.cpp \
    ToriShogiBoard.cpp \
    EuroShogiBoard.cpp \
    WhaleShogiBoard.cpp \
    YariShogiBoard.cpp \
    graphicsmanager.cpp \
    mainwindow.cpp \
    Board.cpp \
    ChessBoard.cpp \
    ChuShogiBoard.cpp \
    Logger.cpp \
    promotiondialog.cpp \
    settingsdialog.cpp \
    stringmanager.cpp \
    variantdialog.cpp \
    vboard.cpp \
    IniFile.cpp \
    ShogiBoard.cpp \
    XiangqiBoard.cpp \
    Engine.cpp \
    UciEngine.cpp \
    WbEngine.cpp \
    QianhongEngine.cpp \
    UcciEngine.cpp \
    UsiEngine.cpp \
    MiniShogiBoard.cpp \
    JudkinShogiBoard.cpp \
    ShatranjBoard.cpp \
    MakrukBoard.cpp \
    DaiShogiBoard.cpp \
    TenjikuShogiBoard.cpp \
    WaShogiBoard.cpp \
    DaiDaiShogiBoard.cpp \
    MakaDaiDaiShogiBoard.cpp \
    KoShogiBoard.cpp \
    EngineOutputHandler.cpp \
    Communications.cpp \
    enginemanager.cpp \
    networkmanager.cpp \
    newgamedialog.cpp \
    addenginedialog.cpp \
    zboard.cpp

HEADERS  += mainwindow.h \
    Board.h \
    CapablancaChessBoard.h \
    ChancellorChessBoard.h \
    ChessBoard.h \
    ChuShogiBoard.h \
    Common.h \
    PieceStorage.h \
    CourierChessBoard.h \
    GothicChessBoard.h \
    GrandChessBoard.h \
    MusketeerChessBoard.h \
    GrandeAcedrexBoard.h \
    HeianDaiShogiBoard.h \
    HeianShogiBoard.h \
    JanggiBoard.h \
    JanusChessBoard.h \
    KyotoShogiBoard.h \
    MicroShogiBoard.h \
    ModernChessBoard.h \
    NightriderChessBoard.h \
    OmegaChessBoard.h \
    Logger.h \
    ShatarBoard.h \
    SittuyinBoard.h \
    ToriShogiBoard.h \
    EuroShogiBoard.h \
    WhaleShogiBoard.h \
    YariShogiBoard.h \
    graphicsmanager.h \
    promotiondialog.h \
    settingsdialog.h \
    stringmanager.h \
    variantdialog.h \
    vboard.h \
    IniFile.h \
    ShogiBoard.h \
    XiangqiBoard.h \
    Engine.h \
    UciEngine.h \
    WbEngine.h \
    QianhongEngine.h \
    UcciEngine.h \
    UsiEngine.h \
    MiniShogiBoard.h \
    JudkinShogiBoard.h \
    ShatranjBoard.h \
    MakrukBoard.h \
    DaiShogiBoard.h \
    TenjikuShogiBoard.h \
    WaShogiBoard.h \
    DaiDaiShogiBoard.h \
    MakaDaiDaiShogiBoard.h \
    KoShogiBoard.h \
    EngineOutputHandler.h \
    Communications.h \
    enginemanager.h \
    networkmanager.h \
    newgamedialog.h \
    addenginedialog.h \
    zboard.h

FORMS    += mainwindow.ui \
    promotiondialog.ui \
    settingsdialog.ui \
    enginemanager.ui \
    networkmanager.ui \
    newgamedialog.ui \
    addenginedialog.ui \
    variantdialog.ui

RESOURCES += \
    resources.qrc
