#include "KyotoShogiBoard.h"

KyotoShogiBoard::KyotoShogiBoard()
{
    _width = 5;
    _height = 5;
    KyotoShogiBoard::Initialize();
}

KyotoShogiBoard::~KyotoShogiBoard()
{
}

void KyotoShogiBoard::Initialize()
{
    _moveCount = 0;
    _capturedPieces.clear();
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                SetData(i, j, Piece(_initialSetup[j][i], j < 2 ? Black : White));
            }
            else
            {
                SetData(i, j, std::nullopt);
            }
        }
    }
}

Board* KyotoShogiBoard::Clone()
{
    KyotoShogiBoard *cb = new KyotoShogiBoard();
    for (int i = 0; i < GetWidth(); i++)
    {
        for (int j = 0; j < GetHeight(); j++)
        {
            const std::optional<Piece> p = GetData(i, j);
            cb->SetData(i, j, p != std::nullopt ? cb->CreatePiece(p->Type, p->Colour) : std::nullopt);
        }
    }
    for (const auto& capturedPiece: _capturedPieces)
    {
        cb->AddCapturedPiece(capturedPiece.second, capturedPiece.first);
    }
    cb->SetMoveCount(_moveCount);
    return cb;
}

void KyotoShogiBoard::Promote(std::optional<Piece>& piece, PieceType pt)
{
    if (piece != std::nullopt)
    {
        PieceType pieceType = None;
        switch (piece->Type)
        {
        case Rook:
            pieceType = Pawn;
            break;
        case Bishop:
            pieceType = Silver;
            break;
        case Tokin:
            pieceType = Lance;
            break;
        case Lance:
            pieceType = Tokin;
            break;
        case Silver:
            pieceType = Bishop;
            break;
        case Knight:
            pieceType = Gold;
            break;
        case Gold:
            pieceType = Knight;
            break;
        case Pawn:
            pieceType = Rook;
            break;
        default:
            break;
        }
        if (pieceType != None)
        {
            piece->Type = pieceType;
        }
    }
}
