#include "EuroShogiBoard.h"

EuroShogiBoard::EuroShogiBoard()
{
    _width = 8;
    _height = 8;
    EuroShogiBoard::Initialize();
}

EuroShogiBoard::~EuroShogiBoard()
{
}

void EuroShogiBoard::Initialize()
{
    _moveCount = 0;
    _capturedPieces.clear();
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                SetData(i, j, new ShogiPiece(_initialSetup[j][i], j < 3 ? Black : White));
            }
            else
            {
                SetData(i, j, nullptr);
            }
        }
    }
}

Board* EuroShogiBoard::Clone()
{
    EuroShogiBoard *cb = new EuroShogiBoard();
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

void EuroShogiBoard::GetMoves(Piece *piece, int x, int y)
{
    _moves.clear();
    switch (piece->GetType())
    {
    case Knight:
        CheckMove(piece, x - 1, y);
        CheckMove(piece, x + 1, y);
        if (piece->GetColour() == Black)
        {
            CheckMove(piece, x - 1, y + 2);
            CheckMove(piece, x + 1, y + 2);
        }
        else
        {
            CheckMove(piece, x - 1, y - 2);
            CheckMove(piece, x + 1, y - 2);
        }
        break;
    default:
        ShogiBoard::GetMoves(piece, x, y);
        break;
    }
}
