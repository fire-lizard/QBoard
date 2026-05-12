#pragma once
#include <QString>
#include <QPainter>
#include <QPixmap>
#include "Common.h"
#include "KanjiPiece.h"
#include "ChuShogiPiece.h"
#include "MakrukPiece.h"

class GraphicsManager
{
public:
    static void DrawPiece(QPainter& painter, Piece *p, GameVariant gameVariant, PieceStyle pieceStyle, int w, int h, int i, int j);

private:
    static QString GetResourcePrefix(GameVariant gameVariant, PieceStyle pieceStyle);
    static QString GetImageFileName(GameVariant gameVariant, PieceStyle pieceStyle, Piece *p);
    static QString GetImageFileName(PieceColour pieceColour, PieceType pieceType, bool isPromoted);
    static QString GetMakrukImageFileName(PieceColour pieceColour, PieceType pieceType, PieceType basePieceType, bool isPromoted);
    static QString GetXiangqiImageFileName(PieceColour pieceColour, PieceType pieceType);
    static QString GetKanjiImageFileName(PieceColour pieceColour, PieceType pieceType, bool isPromoted);
    static QString GetKanjiImageFileName2(PieceColour pieceColour, PieceType pieceType, bool isPromoted);
    static QString GetWhaleShogiImageFileName(PieceColour pieceColour, PieceType pieceType);
    static QString GetYariShogiImageFileName(PieceColour pieceColour, PieceType pieceType);
};
