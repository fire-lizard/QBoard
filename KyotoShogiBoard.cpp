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
