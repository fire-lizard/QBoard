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
    ChancellorChessBoard.cpp \
    CourierChessBoard.cpp \
    GothicChessBoard.cpp \
    GrandChessBoard.cpp \
    GrandeAcedrexBoard.cpp \
    HeianDaiShogiBoard.cpp \
    HeianShogiBoard.cpp \
    JanggiBoard.cpp \
    JanusChessBoard.cpp \
    KyotoShogiBoard.cpp \
    MicroShogiBoard.cpp \
    ModernChessBoard.cpp \
    OmegaChessBoard.cpp \
    ShatarBoard.cpp \
    ToriShogiBoard.cpp \
    EuroShogiBoard.cpp \
    WhaleShogiBoard.cpp \
    YariShogiBoard.cpp \
    graphicsmanager.cpp \
    mainwindow.cpp \
    Board.cpp \
    ChessBoard.cpp \
    ChessPiece.cpp \
    ChuShogiBoard.cpp \
    Piece.cpp \
    Logger.cpp \
    promotiondialog.cpp \
    settingsdialog.cpp \
    stringmanager.cpp \
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
    DaiShogiBoard.cpp \
    TenjikuShogiBoard.cpp \
    WaShogiBoard.cpp \
    WaShogiPiece.cpp \
    DaiDaiShogiBoard.cpp \
    MakaDaiDaiShogiBoard.cpp \
    KoShogiBoard.cpp \
    EngineOutputHandler.cpp \
    Communications.cpp \
    enginemanager.cpp \
    networkmanager.cpp \
    comboboxitemdelegate.cpp \
    newgamedialog.cpp \
    addenginedialog.cpp \
    zboard.cpp

HEADERS  += mainwindow.h \
    Board.h \
    CapablancaChessBoard.h \
    ChancellorChessBoard.h \
    ChessBoard.h \
    ChessPiece.h \
    ChuShogiBoard.h \
    Common.h \
    CourierChessBoard.h \
    GothicChessBoard.h \
    GrandChessBoard.h \
    GrandeAcedrexBoard.h \
    HeianDaiShogiBoard.h \
    HeianShogiBoard.h \
    JanggiBoard.h \
    JanusChessBoard.h \
    KyotoShogiBoard.h \
    MicroShogiBoard.h \
    ModernChessBoard.h \
    OmegaChessBoard.h \
    Piece.h \
    Logger.h \
    ShatarBoard.h \
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
    DaiShogiBoard.h \
    TenjikuShogiBoard.h \
    WaShogiBoard.h \
    WaShogiPiece.h \
    DaiDaiShogiBoard.h \
    MakaDaiDaiShogiBoard.h \
    KoShogiBoard.h \
    EngineOutputHandler.h \
    Communications.h \
    enginemanager.h \
    networkmanager.h \
    comboboxitemdelegate.h \
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
