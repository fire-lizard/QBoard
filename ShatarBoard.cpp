#include "ShatarBoard.h"

ShatarBoard::ShatarBoard()
{
    _width = 8;
    _height = 8;
    ShatranjBoard::Initialize();
}

ShatarBoard::~ShatarBoard()
{
}

Board* ShatarBoard::Clone()
{
    ShatarBoard* cb = new ShatarBoard();
    for (int i = 0; i < GetWidth(); i++)
    {
        for (int j = 0; j < GetHeight(); j++)
        {
            const Piece* p = GetData(i, j);
            cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
        }
    }
    cb->SetMoveCount(_moveCount);
    return cb;
}

void ShatarBoard::Initialize()
{
    _moveCount = 0;
    _pgn = "";
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                SetData(i, j, new ShatranjPiece(_initialSetup[j][i], j < 5 ? Black : White));
            }
            else
            {
                SetData(i, j, nullptr);
            }
        }
    }
}

void ShatarBoard::GetMoves(Piece* piece, int x, int y)
{
    _moves.clear();
    switch (piece->GetType())
    {
    case Queen:
        CheckMove(piece, x + 1, y + 1);
        CheckMove(piece, x + 1, y - 1);
        CheckMove(piece, x - 1, y + 1);
        CheckMove(piece, x - 1, y - 1);
        CheckDirection(piece, x, y, North);
        CheckDirection(piece, x, y, East);
        CheckDirection(piece, x, y, West);
        CheckDirection(piece, x, y, South);
        break;
    case Knight:
        if (GetData(x + 1, y + 2) == nullptr || GetData(x + 1, y + 2)->GetType() != King) CheckMove(piece, x + 1, y + 2);
        if (GetData(x - 1, y + 2) == nullptr || GetData(x - 1, y + 2)->GetType() != King) CheckMove(piece, x - 1, y + 2);
        if (GetData(x + 2, y + 1) == nullptr || GetData(x + 2, y + 1)->GetType() != King) CheckMove(piece, x + 2, y + 1);
        if (GetData(x + 2, y - 1) == nullptr || GetData(x + 2, y - 1)->GetType() != King) CheckMove(piece, x + 2, y - 1);
        if (GetData(x - 2, y + 1) == nullptr || GetData(x - 2, y + 1)->GetType() != King) CheckMove(piece, x - 2, y + 1);
        if (GetData(x - 2, y - 1) == nullptr || GetData(x - 2, y - 1)->GetType() != King) CheckMove(piece, x - 2, y - 1);
        if (GetData(x + 1, y - 2) == nullptr || GetData(x + 1, y - 2)->GetType() != King) CheckMove(piece, x + 1, y - 2);
        if (GetData(x - 1, y - 2) == nullptr || GetData(x - 1, y - 2)->GetType() != King) CheckMove(piece, x - 1, y - 2);
        break;
    case Pawn:
        if (piece->GetColour() == Black)
        {
            if (x == 3 && y == 1 && GetData(x, y + 1) == nullptr && GetData(x, y + 2) == nullptr)
            {
                CheckMove(piece, x, y + 2);
            }
            if (y + 1 < _height && GetData(x, y + 1) == nullptr)
            {
                CheckMove(piece, x, y + 1);
            }
            if (y + 1 < _height && x + 1 < _width && GetData(x + 1, y + 1) != nullptr)
            {
                CheckMove(piece, x + 1, y + 1);
            }
            if (y + 1 < _height && x - 1 >= 0 && GetData(x - 1, y + 1) != nullptr)
            {
                CheckMove(piece, x - 1, y + 1);
            }
        }
        else
        {
            if (x == 4 && y == _height - 2 && GetData(x, y - 1) == nullptr && GetData(x, y - 2) == nullptr)
            {
                CheckMove(piece, x, y - 2);
            }
            if (y - 1 >= 0 && GetData(x, y - 1) == nullptr)
            {
                CheckMove(piece, x, y - 1);
            }
            if (y - 1 >= 0 && x + 1 < _width && GetData(x + 1, y - 1) != nullptr)
            {
                CheckMove(piece, x + 1, y - 1);
            }
            if (y - 1 >= 0 && x - 1 >= 0 && GetData(x - 1, y - 1) != nullptr)
            {
                CheckMove(piece, x - 1, y - 1);
            }
        }
        break;
    default:
        ShatranjBoard::GetMoves(piece, x, y);
        break;
    }
}
