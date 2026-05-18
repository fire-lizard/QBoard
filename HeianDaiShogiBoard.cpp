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
                SetData(i, j, Piece(_initialSetup[j][i], j < 5 ? Black : White));
            }
            else
            {
                SetData(i, j, std::nullopt);
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
            const std::optional<Piece> p = GetData(i, j);
            cb->SetData(i, j, p != std::nullopt ? cb->CreatePiece(p->Type, p->Colour) : std::nullopt);
        }
    }
    cb->SetMoveCount(_moveCount);
    return cb;
}

void HeianDaiShogiBoard::Promote(std::optional<Piece>& piece, PieceType pt)
{
    if (piece != std::nullopt)
    {
        piece->IsPromoted = true;
        piece->Type = Gold;
    }
}

void HeianDaiShogiBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
    _moves.clear();
    switch (piece->Type)
    {
    case SideMover:
        CheckDirection(piece, x, y, East);
        CheckDirection(piece, x, y, West);
        if (piece->Colour == Black)
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
        if (piece->Colour == Black)
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
