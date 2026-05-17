#include "JanggiBoard.h"

JanggiBoard::JanggiBoard()
{
    _width = 9;
    _height = 10;
    JanggiBoard::Initialize();
}

JanggiBoard::~JanggiBoard()
{
}

Board* JanggiBoard::Clone()
{
    JanggiBoard *cb = new JanggiBoard();
    for (int i = 0; i < GetWidth(); i++)
    {
        for (int j = 0; j < GetHeight(); j++)
        {
            const Piece *p = GetData(i, j);
            cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->Type, p->Colour) : nullptr);
        }
    }
    cb->SetMoveCount(_moveCount);
    return cb;
}

void JanggiBoard::Initialize()
{
    _moveCount = 0;
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                SetData(i, j, new Piece(_initialSetup[j][i], j < 5 ? Black : White));
            }
            else
            {
                SetData(i, j, nullptr);
            }
        }
    }
}

void JanggiBoard::GetMoves(Piece *piece, int x, int y)
{
    _moves.clear();
    switch (piece->Type)
    {
    case King:
    case Silver:
        if (x < 5)
            CheckMove(piece, x + 1, y);
        if ((piece->Colour == Black && y < 2) || piece->Colour == White)
            CheckMove(piece, x, y + 1);
        if ((piece->Colour == White && y > 7) || piece->Colour == Black)
            CheckMove(piece, x, y - 1);
        if (x > 3)
            CheckMove(piece, x - 1, y);
        if (x == 3 && y == 1 || x == 5 && y == 1 || x == 4 && y == 0 || x == 4 && y == 2 ||
            x == 3 && y == 8 || x == 5 && y == 8 || x == 4 && y == 9 || x == 4 && y == 7)
        {
        }
        else
        {
            if (x < 5 && (piece->Colour == Black && y < 2 || piece->Colour == White))
                CheckMove(piece, x + 1, y + 1);
            if (x < 5 && (piece->Colour == White && y > 7 || piece->Colour == Black))
                CheckMove(piece, x + 1, y - 1);
            if (x > 3 && (piece->Colour == Black && y < 2 || piece->Colour == White))
                CheckMove(piece, x - 1, y + 1);
            if (x > 3 && (piece->Colour == White && y > 7 || piece->Colour == Black))
                CheckMove(piece, x - 1, y - 1);
        }
        break;
    case Elephant:
        if (GetData(x, y + 1) == nullptr)
        {
            if (GetData(x + 1, y + 2) == nullptr)
                CheckMove(piece, x + 2, y + 3);
            if (GetData(x - 1, y + 2) == nullptr)
                CheckMove(piece, x - 2, y + 3);
        }
        if (GetData(x + 1, y) == nullptr)
        {
            if (GetData(x + 2, y + 1) == nullptr)
                CheckMove(piece, x + 3, y + 2);
            if (GetData(x + 2, y - 1) == nullptr)
                CheckMove(piece, x + 3, y - 2);
        }
        if (GetData(x - 1, y) == nullptr)
        {
            if (GetData(x - 2, y + 1) == nullptr)
                CheckMove(piece, x - 3, y + 2);
            if (GetData(x - 2, y - 1) == nullptr)
                CheckMove(piece, x - 3, y - 2);
        }
        if (GetData(x, y - 1) == nullptr)
        {
            if (GetData(x + 1, y - 2) == nullptr)
                CheckMove(piece, x + 2, y - 3);
            if (GetData(x - 1, y - 2) == nullptr)
                CheckMove(piece, x - 2, y - 3);
        }
        break;
    case Pawn:
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x - 1, y);
        if (piece->Colour == Black)
        {
            CheckMove(piece, x, y + 1);
            if (x == 4 && y == 8)
            {
                CheckMove(piece, x + 1, y + 1);
                CheckMove(piece, x - 1, y + 1);
            }
            else if (x == 3 && y == 7)
            {
                CheckMove(piece, x + 1, y + 1);
            }
            else if (x == 5 && y == 7)
            {
                CheckMove(piece, x - 1, y + 1);
            }
        }
        else
        {
            CheckMove(piece, x, y - 1);
            if (x == 4 && y == 1)
            {
                CheckMove(piece, x + 1, y - 1);
                CheckMove(piece, x - 1, y - 1);
            }
            else if (x == 3 && y == 2)
            {
                CheckMove(piece, x + 1, y - 1);
            }
            else if (x == 5 && y == 2)
            {
                CheckMove(piece, x - 1, y - 1);
            }
        }
        break;
    case Cannon:
        if (x == 3 && y == 2)
        {
            CheckCannonDirection(piece, x, y, SouthEast);
        }
        else if (x == 5 && y == 2)
        {
            CheckCannonDirection(piece, x, y, SouthWest);
        }
        else if (x == 3 && y == 7)
        {
            CheckCannonDirection(piece, x, y, NorthEast);
        }
        else if (x == 5 && y == 7)
        {
            CheckCannonDirection(piece, x, y, NorthWest);
        }
        else if (x == 3 && y == 0)
        {
            if (GetData(4, 1) != nullptr && GetData(4, 1)->Type != Cannon)
                CheckMove(piece, 5, 2);
        }
        else if (x == 5 && y == 0)
        {
            if (GetData(4, 1) != nullptr && GetData(4, 1)->Type != Cannon)
                CheckMove(piece, 3, 2);
        }
        else if (x == 3 && y == 9)
        {
            if (GetData(4, 8) != nullptr && GetData(4, 8)->Type != Cannon)
                CheckMove(piece, 5, 7);
        }
        else if (x == 5 && y == 9)
        {
            if (GetData(4, 8) != nullptr && GetData(4, 8)->Type != Cannon)
                CheckMove(piece, 3, 7);
        }
        CheckCannonDirection(piece, x, y, North);
        CheckCannonDirection(piece, x, y, East);
        CheckCannonDirection(piece, x, y, West);
        CheckCannonDirection(piece, x, y, South);
        break;
    case Rook:
        if (x == 3 && y == 2)
        {
            CheckDirection(piece, x, y, SouthEast);
        }
        else if (x == 5 && y == 2)
        {
            CheckDirection(piece, x, y, SouthWest);
        }
        else if (x == 3 && y == 7)
        {
            CheckDirection(piece, x, y, NorthEast);
        }
        else if (x == 5 && y == 7)
        {
            CheckDirection(piece, x, y, NorthWest);
        }
        else if (x == 3 && y == 0)
        {
            CheckDirection(piece, x, y, NorthEast, 2);
        }
        else if (x == 5 && y == 0)
        {
            CheckDirection(piece, x, y, NorthWest, 2);
        }
        else if (x == 3 && y == 9)
        {
            CheckDirection(piece, x, y, SouthEast, 2);
        }
        else if (x == 5 && y == 9)
        {
            CheckDirection(piece, x, y, SouthWest, 2);
        }
        CheckDirection(piece, x, y, North);
        CheckDirection(piece, x, y, East);
        CheckDirection(piece, x, y, West);
        CheckDirection(piece, x, y, South);
        break;
    default:
        XiangqiBoard::GetMoves(piece, x, y);
    }
}

void JanggiBoard::CheckCannonDirection(const Piece *piece, int x, int y, Direction direction)
{
    do
    {
        CheckDirectionInc(x, y, direction);
        if (GetData(x, y) != nullptr)
        {
            if (GetData(x, y)->Type == Cannon)
            {
                break;
            }
            do
            {
                CheckDirectionInc(x, y, direction);
                if (GetData(x, y) == nullptr)
                    CheckMove(piece, x, y);
            }
            while (GetData(x, y) == nullptr && InBounds(x, y, direction));
            if (CheckPosition(x, y) && GetData(x, y) != nullptr &&
                    GetData(x, y)->Colour != piece->Colour &&
                    GetData(x, y)->Type != Cannon)
            {
                CheckMove(piece, x, y);
            }
            break;
        }
    }
    while (InBounds(x, y, direction));
}
