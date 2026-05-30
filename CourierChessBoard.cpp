#include "CourierChessBoard.h"

CourierChessBoard::CourierChessBoard()
{
    _width = 12;
    _height = 8;
    CourierChessBoard::Initialize();
}

CourierChessBoard::~CourierChessBoard()
{
}

Board* CourierChessBoard::Clone()
{
    CourierChessBoard* cb = new CourierChessBoard();
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

void CourierChessBoard::Initialize()
{
    _moveCount = 0;
    _pgn = "";
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

void CourierChessBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
    _moves.clear();
    switch (piece->Type)
    {
    case Sage:
        CheckMove(piece, x + 1, y + 1);
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x + 1, y - 1);
        CheckMove(piece, x, y + 1);
        CheckMove(piece, x, y - 1);
        CheckMove(piece, x - 1, y + 1);
        CheckMove(piece, x - 1, y);
        CheckMove(piece, x - 1, y - 1);
        break;
    case Schleich:
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x - 1, y);
        CheckMove(piece, x, y + 1);
        CheckMove(piece, x, y - 1);
        break;
    case Courier:
        CheckDirection(piece, x, y, NorthEast);
        CheckDirection(piece, x, y, SouthEast);
        CheckDirection(piece, x, y, SouthWest);
        CheckDirection(piece, x, y, NorthWest);
        break;
    default:
        ShatranjBoard::GetMoves(piece, x, y);
        break;
    }
}

std::string CourierChessBoard::GetStringCode(int x, int y) const
{
    if (GetData(x, y) == std::nullopt) return "";
    PieceType pieceType = GetData(x, y)->Type;
    switch (pieceType)
    {
    case Bishop:
        return "E";
    case Courier:
        return "B";
    case Schleich:
        return "W";
    case Sage:
        return "M";
    case Queen:
        return "F";
    default:
        return Board::GetStringCode(x, y);
    }
}
