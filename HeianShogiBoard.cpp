#include "HeianShogiBoard.h"

HeianShogiBoard::HeianShogiBoard()
{
    _width = 9;
    _height = 8;
    HeianShogiBoard::Initialize();
}

HeianShogiBoard::~HeianShogiBoard()
{
}

void HeianShogiBoard::Initialize()
{
    _capturedPieces.clear();
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                _data[i][j] = new ShogiPiece(_initialSetup[j][i], j < 5 ? Black : White);
            }
            else
            {
                _data[i][j] = nullptr;
            }
        }
    }
}

Board* HeianShogiBoard::Clone()
{
    HeianShogiBoard *cb = new HeianShogiBoard();
    for (int i = 0; i < GetWidth(); i++)
    {
        for (int j = 0; j < GetHeight(); j++)
        {
            const Piece *p = GetData(i, j);
            cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
        }
    }
    cb->SetMoveCount(_moveCount);
    return cb;
}
