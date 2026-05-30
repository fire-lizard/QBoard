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
            const std::optional<Piece> p = GetData(i, j);
            cb->SetData(i, j, p != std::nullopt ? std::make_optional<Piece>(p->Type, p->Colour) : std::nullopt);
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
                SetData(i, j, Piece(_initialSetup[j][i], j < 4 ? Black : White));
            }
            else
            {
                SetData(i, j, std::nullopt);
            }
        }
    }
}

void ShatarBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
    _moves.clear();
    switch (piece->Type)
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
    case Bishop:
        CheckDirection(piece, x, y, NorthEast);
        CheckDirection(piece, x, y, NorthWest);
        CheckDirection(piece, x, y, SouthEast);
        CheckDirection(piece, x, y, SouthWest);
        break;
    case Knight:
        if (GetData(x + 1, y + 2) == std::nullopt || GetData(x + 1, y + 2)->Type != King) CheckMove(piece, x + 1, y + 2);
        if (GetData(x - 1, y + 2) == std::nullopt || GetData(x - 1, y + 2)->Type != King) CheckMove(piece, x - 1, y + 2);
        if (GetData(x + 2, y + 1) == std::nullopt || GetData(x + 2, y + 1)->Type != King) CheckMove(piece, x + 2, y + 1);
        if (GetData(x + 2, y - 1) == std::nullopt || GetData(x + 2, y - 1)->Type != King) CheckMove(piece, x + 2, y - 1);
        if (GetData(x - 2, y + 1) == std::nullopt || GetData(x - 2, y + 1)->Type != King) CheckMove(piece, x - 2, y + 1);
        if (GetData(x - 2, y - 1) == std::nullopt || GetData(x - 2, y - 1)->Type != King) CheckMove(piece, x - 2, y - 1);
        if (GetData(x + 1, y - 2) == std::nullopt || GetData(x + 1, y - 2)->Type != King) CheckMove(piece, x + 1, y - 2);
        if (GetData(x - 1, y - 2) == std::nullopt || GetData(x - 1, y - 2)->Type != King) CheckMove(piece, x - 1, y - 2);
        break;
    case Pawn:
        if (piece->Colour == Black)
        {
            if (y + 1 < _height && GetData(x, y + 1) == std::nullopt)
            {
                CheckMove(piece, x, y + 1);
            }
            if (y + 1 < _height && x + 1 < _width && GetData(x + 1, y + 1) != std::nullopt)
            {
                CheckMove(piece, x + 1, y + 1);
            }
            if (y + 1 < _height && x - 1 >= 0 && GetData(x - 1, y + 1) != std::nullopt)
            {
                CheckMove(piece, x - 1, y + 1);
            }
        }
        else
        {
            if (y - 1 >= 0 && GetData(x, y - 1) == std::nullopt)
            {
                CheckMove(piece, x, y - 1);
            }
            if (y - 1 >= 0 && x + 1 < _width && GetData(x + 1, y - 1) != std::nullopt)
            {
                CheckMove(piece, x + 1, y - 1);
            }
            if (y - 1 >= 0 && x - 1 >= 0 && GetData(x - 1, y - 1) != std::nullopt)
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
