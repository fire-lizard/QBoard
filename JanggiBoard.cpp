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
            cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
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
                SetData(i, j, new XiangqiPiece(_initialSetup[j][i], j < 5 ? Black : White));
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
    switch (piece->GetType())
    {
    case King:
    case Silver:
        if (x < 5)
            CheckMove(piece, x + 1, y);
        if ((piece->GetColour() == Black && y < 2) || piece->GetColour() == White)
            CheckMove(piece, x, y + 1);
        if ((piece->GetColour() == White && y > 7) || piece->GetColour() == Black)
            CheckMove(piece, x, y - 1);
        if (x > 3)
            CheckMove(piece, x - 1, y);
        if ((x < 5 && (piece->GetColour() == Black && y < 2)) || piece->GetColour() == White)
            CheckMove(piece, x + 1, y + 1);
        if ((x < 5 && (piece->GetColour() == White && y > 7)) || piece->GetColour() == Black)
            CheckMove(piece, x + 1, y - 1);
        if ((x > 3 && (piece->GetColour() == Black && y < 2)) || piece->GetColour() == White)
            CheckMove(piece, x - 1, y + 1);
        if ((x > 3 && (piece->GetColour() == White && y > 7)) || piece->GetColour() == Black)
            CheckMove(piece, x - 1, y - 1);
        break;
    case Elephant:
        if ((piece->GetColour() == White) || piece->GetColour() == Black)
        {
            if (GetData(x - 1, y - 1) == nullptr)
                CheckMove(piece, x - 2, y - 2);
            if (GetData(x + 1, y - 1) == nullptr)
                CheckMove(piece, x + 2, y - 2);
        }
        if ((piece->GetColour() == Black) || piece->GetColour() == White)
        {
            if (GetData(x - 1, y + 1) == nullptr)
                CheckMove(piece, x - 2, y + 2);
            if (GetData(x + 1, y + 1) == nullptr)
                CheckMove(piece, x + 2, y + 2);
        }
        break;
    case Pawn:
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x - 1, y);
        if (piece->GetColour() == Black)
        {
            CheckMove(piece, x, y + 1);
        }
        else
        {
            CheckMove(piece, x, y - 1);
        }
        break;
    case Cannon:
        CheckCannonDirection(piece, x, y, North);
        CheckCannonDirection(piece, x, y, East);
        CheckCannonDirection(piece, x, y, West);
        CheckCannonDirection(piece, x, y, South);
        break;
    default:
        XiangqiBoard::GetMoves(piece, x, y);
    }
}
