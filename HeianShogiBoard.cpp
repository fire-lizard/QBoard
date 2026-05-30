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
    _moveCount = 0;
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                SetData(i, j, Piece(_initialSetup[j][i], j < 5 ? Black : White));
            }
            else
            {
                SetData(i, j, std::nullopt);
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
            const std::optional<Piece> p = GetData(i, j);
            cb->SetData(i, j, p != std::nullopt ? std::make_optional<Piece>(p->Type, p->Colour) : std::nullopt);
        }
    }
    cb->SetMoveCount(_moveCount);
    return cb;
}
