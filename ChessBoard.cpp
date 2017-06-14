#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
    _width = 8;
    _height = 8;
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                _data[i][j] = new ChessPiece(_initialSetup[j][i], j < 5 ? Black : White);
            }
        }
    }
}

ChessBoard::~ChessBoard()
{
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_data[i][j] != nullptr)
            {
                delete _data[i][j];
            }
        }
    }
}

void ChessBoard::GetMoves(Piece *piece, int x, int y)
{
    _moves.clear();
    switch (piece->GetType())
    {
case King:
    CheckKingMove(piece, x + 1, y + 1);
    CheckKingMove(piece, x + 1, y);
    CheckKingMove(piece, x + 1, y - 1);
    CheckKingMove(piece, x, y + 1);
    CheckKingMove(piece, x, y - 1);
    CheckKingMove(piece, x - 1, y + 1);
    CheckKingMove(piece, x - 1, y);
    CheckKingMove(piece, x - 1, y - 1);
    break;
case Queen:
    CheckDirection(piece, x, y, North);
    CheckDirection(piece, x, y, NorthEast);
    CheckDirection(piece, x, y, East);
    CheckDirection(piece, x, y, SouthEast);
    CheckDirection(piece, x, y, South);
    CheckDirection(piece, x, y, SouthWest);
    CheckDirection(piece, x, y, West);
    CheckDirection(piece, x, y, NorthWest);
    break;
case Rook:
    CheckDirection(piece, x, y, North);
    CheckDirection(piece, x, y, East);
    CheckDirection(piece, x, y, West);
    CheckDirection(piece, x, y, South);
    break;
case Bishop:
    CheckDirection(piece, x, y, NorthEast);
    CheckDirection(piece, x, y, SouthEast);
    CheckDirection(piece, x, y, SouthWest);
    CheckDirection(piece, x, y, NorthWest);
    break;
case Pawn:
    if (piece->GetColour() == Black)
    {
        if (y + 1 < _height && _data[x][y + 1] == nullptr)
        {
            CheckMove(piece, x, y + 1);
        }
        if (y + 1 < _height && x + 1 < _width && _data[x + 1][y + 1] != nullptr)
        {
            CheckMove(piece, x + 1, y + 1);
        }
        if (y + 1 < _height && x - 1 > 0 && _data[x - 1][y + 1] != nullptr)
        {
            CheckMove(piece, x - 1, y + 1);
        }
    }
    else
    {
        if (y - 1 >= 0 && _data[x][y - 1] == nullptr)
        {
            CheckMove(piece, x, y - 1);
        }
        if (y - 1 >= 0 && x + 1 < _width && _data[x + 1][y - 1] != nullptr)
        {
            CheckMove(piece, x + 1, y - 1);
        }
        if (y - 1 >= 0 && x - 1 > 0 && _data[x - 1][y - 1] != nullptr)
        {
            CheckMove(piece, x - 1, y - 1);
        }
    }
    break;
case WhiteHorse:
    CheckMove(piece, x + 1, y + 2);
    CheckMove(piece, x - 1, y + 2);
    CheckMove(piece, x + 2, y + 1);
    CheckMove(piece, x + 2, y - 1);
    CheckMove(piece, x - 2, y + 1);
    CheckMove(piece, x - 2, y - 1);
    CheckMove(piece, x + 1, y - 2);
    CheckMove(piece, x - 1, y - 2);
    break;
default:
    break;
    }
}
