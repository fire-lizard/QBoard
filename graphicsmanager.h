#pragma once
#include <QString>
#include <QPainter>
#include <QPixmap>
#include "Common.h"
#include "KanjiPiece.h"
#include "ChuShogiPiece.h"
#include "MakrukPiece.h"
#include "stringmanager.h"

class GraphicsManager
{
public:
    static void DrawPiece(QPainter& painter, Piece *p, GameVariant gameVariant, PieceStyle pieceStyle, int w, int h, int i, int j);

private:
    static QString GetResourcePrefix(GameVariant gameVariant, PieceStyle pieceStyle);
    static QString GetImageFileName(GameVariant gameVariant, PieceStyle pieceStyle, PieceColour pieceColour, PieceType pieceType, bool isPromoted);
    static QString GetImageFileName(PieceColour pieceColour, PieceType pieceType, bool isPromoted);
    static QString GetMakrukImageFileName(PieceColour pieceColour, PieceType pieceType, bool isPromoted);
    static QString GetXiangqiImageFileName(PieceColour pieceColour, PieceType pieceType);
    static QString GetShogiImageFileName(PieceColour pieceColour, PieceType pieceType, bool isPromoted);
    static QString GetMnemonicImageFileName(PieceColour pieceColour, PieceType pieceType, bool isPromoted);
    static QString GetKanjiImageFileName(PieceColour pieceColour, PieceType pieceType, bool isPromoted);
    static QString GetKanjiImageFileName2(PieceColour pieceColour, PieceType pieceType, bool isPromoted);
    static QString GetKanjiImageFileName3(PieceColour pieceColour, PieceType pieceType, bool isPromoted);
    static QString GetKoShogiImageFileName(PieceStyle pieceStyle, PieceColour pieceColour, PieceType pieceType, bool isPromoted);
    static QString GetKyotoShogiImageFileName(PieceStyle pieceStyle, PieceColour pieceColour, PieceType pieceType);
    static QString GetTenjikuShogiImageFileName(PieceColour pieceColour, PieceType pieceType, bool isPromoted);
    static QString GetToriShogiImageFileName(PieceStyle pieceStyle, PieceColour pieceColour, PieceType pieceType);
    static QString GetWaShogiImageFileName(PieceStyle pieceStyle, PieceColour pieceColour, PieceType pieceType, bool isPromoted);
    static QString GetWhaleShogiImageFileName(PieceColour pieceColour, PieceType pieceType);
    static QString GetYariShogiImageFileName(PieceColour pieceColour, PieceType pieceType);
};
