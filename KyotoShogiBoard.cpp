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
                SetData(i, j, new KyotoShogiPiece(_initialSetup[j][i], j < 2 ? Black : White));
            }
            else
            {
                SetData(i, j, nullptr);
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
            const Piece *p = GetData(i, j);
            cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
        }
    }
    for (const auto& capturedPiece: _capturedPieces)
    {
        cb->AddCapturedPiece(capturedPiece.second, capturedPiece.first);
    }
    cb->SetMoveCount(_moveCount);
    return cb;
}

Piece* KyotoShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
    return new KyotoShogiPiece(pieceType, pieceColour);
}

void KyotoShogiBoard::PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y)
{
    SetData(x, y, new KyotoShogiPiece(pieceType, pieceColour));
}

void KyotoShogiBoard::Promote(int x, int y, PieceType pt)
{
    if (GetData(x, y) != nullptr)
    {
        PieceType pieceType = None;
        switch (GetData(x, y)->GetType())
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
            GetData(x, y)->SetType(pieceType);
        }
    }
}
