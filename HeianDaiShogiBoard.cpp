#include "HeianDaiShogiBoard.h"

HeianDaiShogiBoard::HeianDaiShogiBoard()
{
    _width = 13;
    _height = 13;
    HeianDaiShogiBoard::Initialize();
}

HeianDaiShogiBoard::~HeianDaiShogiBoard()
{
}

void HeianDaiShogiBoard::Initialize()
{
    _moveCount = 0;
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                _data[i][j] = new HeianShogiPiece(_initialSetup[j][i], j < 5 ? Black : White);
            }
            else
            {
                _data[i][j] = nullptr;
            }
        }
    }
}

Board* HeianDaiShogiBoard::Clone()
{
    HeianDaiShogiBoard *cb = new HeianDaiShogiBoard();
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

Piece* HeianDaiShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
    return new HeianShogiPiece(pieceType, pieceColour);
}

void HeianDaiShogiBoard::GetMoves(Piece* piece, int x, int y)
{
    _moves.clear();
    switch (piece->GetType())
    {
    case SideMover:
        CheckDirection(piece, x, y, East);
        CheckDirection(piece, x, y, West);
        if (piece->GetColour() == Black)
        {
            CheckMove(piece, x, y + 1);
        }
        else
        {
            CheckMove(piece, x, y - 1);
        }
        break;
    case FlyingDragon:
        CheckDirection(piece, x, y, SouthWest);
        CheckDirection(piece, x, y, NorthWest);
        CheckDirection(piece, x, y, SouthEast);
        CheckDirection(piece, x, y, NorthEast);
        break;
    case Copper:
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x - 1, y);
        CheckMove(piece, x, y + 1);
        CheckMove(piece, x, y - 1);
        break;
    case Iron:
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x - 1, y);
        if (piece->GetColour() == Black)
        {
            CheckMove(piece, x, y + 1);
            CheckMove(piece, x - 1, y + 1);
            CheckMove(piece, x + 1, y + 1);
        }
        else
        {
            CheckMove(piece, x, y - 1);
            CheckMove(piece, x - 1, y - 1);
            CheckMove(piece, x + 1, y - 1);
        }
        break;
    case Tiger:
        CheckMove(piece, x + 1, y + 1);
        CheckMove(piece, x + 1, y - 1);
        CheckMove(piece, x - 1, y + 1);
        CheckMove(piece, x - 1, y - 1);
        break;
    default:
        DaiShogiBoard::GetMoves(piece, x, y);
        break;
    }
}
