#include "WhaleShogiBoard.h"

WhaleShogiBoard::WhaleShogiBoard()
{
    _width = 6;
    _height = 6;
    WhaleShogiBoard::Initialize();
}

WhaleShogiBoard::~WhaleShogiBoard()
{
}

void WhaleShogiBoard::Initialize()
{
    _moveCount = 0;
    _capturedPieces.clear();
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                _data[i][j] = new WhaleShogiPiece(_initialSetup[j][i], j < 3 ? Black : White);
            }
            else
            {
                _data[i][j] = nullptr;
            }
        }
    }
}

Board* WhaleShogiBoard::Clone()
{
    WhaleShogiBoard* cb = new WhaleShogiBoard();
    for (int i = 0; i < GetWidth(); i++)
    {
        for (int j = 0; j < GetHeight(); j++)
        {
            const Piece* p = GetData(i, j);
            cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
        }
    }
    for (const auto& capturedPiece : _capturedPieces)
    {
        cb->AddCapturedPiece(capturedPiece.second, capturedPiece.first);
    }
    cb->SetMoveCount(_moveCount);
    return cb;
}

Piece* WhaleShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
    return new WhaleShogiPiece(pieceType, pieceColour);
}

void WhaleShogiBoard::PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y)
{
    _data[x][y] = new WhaleShogiPiece(pieceType, pieceColour);
}

void WhaleShogiBoard::GetMoves(Piece* piece, int x, int y)
{
    _moves.clear();
    switch (piece->GetType())
    {
    case GreyWhale:
        if (piece->GetColour() == Black)
        {
            CheckDirection(piece, x, y, North);
            CheckDirection(piece, x, y, SouthEast);
            CheckDirection(piece, x, y, SouthWest);
        }
        else
        {
            CheckDirection(piece, x, y, South);
            CheckDirection(piece, x, y, NorthEast);
            CheckDirection(piece, x, y, NorthWest);
        }
        break;
    case Porpoise:
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x - 1, y);
        break;
    case Narwhal:
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x - 1, y);
        if (piece->GetColour() == Black)
        {
            CheckMove(piece, x, y - 1);
            CheckMove(piece, x, y + 2);
        }
        else
        {
            CheckMove(piece, x, y + 1);
            CheckMove(piece, x, y - 2);
        }
        break;
    case Humpback:
        CheckMove(piece, x + 1, y + 1);
        CheckMove(piece, x + 1, y - 1);
        CheckMove(piece, x - 1, y + 1);
        CheckMove(piece, x - 1, y - 1);
        if (piece->GetColour() == Black)
        {
            CheckMove(piece, x, y - 1);
        }
        else
        {
            CheckMove(piece, x, y + 1);
        }
        break;
    case BlueWhale:
        CheckMove(piece, x, y + 1);
        CheckMove(piece, x, y - 1);
        if (piece->GetColour() == Black)
        {
            CheckMove(piece, x - 1, y + 1);
            CheckMove(piece, x + 1, y + 1);
        }
        else
        {
            CheckMove(piece, x - 1, y - 1);
            CheckMove(piece, x + 1, y - 1);
        }
        break;
    case Pawn:
        if (piece->GetColour() == Black)
        {
            CheckMove(piece, x, y + 1);
            if (y == _height - 1)
            {
                CheckDirection(piece, x, y, SouthEast);
                CheckDirection(piece, x, y, SouthWest);
            }
        }
        else
        {
            CheckMove(piece, x, y - 1);
            if (y == 0)
            {
                CheckDirection(piece, x, y, NorthEast);
                CheckDirection(piece, x, y, NorthWest);
            }
        }
        break;
    default:
        ShogiBoard::GetMoves(piece, x, y);
        break;
    }
}
