#include "ToriShogiBoard.h"

ToriShogiBoard::ToriShogiBoard()
{
    _width = 7;
    _height = 7;
    ToriShogiBoard::Initialize();
}

ToriShogiBoard::~ToriShogiBoard()
{
}

void ToriShogiBoard::Initialize()
{
    _moveCount = 0;
    _capturedPieces.clear();
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                if (j != 3)
                    SetData(i, j, new ToriShogiPiece(_initialSetup[j][i], j < 3 ? Black : White));
                else
                    SetData(i, j, new ToriShogiPiece(_initialSetup[j][i], i < 3 ? Black : White));
            }
            else
            {
                SetData(i, j, nullptr);
            }
        }
    }
}

Board* ToriShogiBoard::Clone()
{
    ToriShogiBoard* cb = new ToriShogiBoard();
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

Piece* ToriShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
    return new ToriShogiPiece(pieceType, pieceColour);
}

void ToriShogiBoard::PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y)
{
    SetData(x, y, new ToriShogiPiece(pieceType, pieceColour));
}

void ToriShogiBoard::GetMoves(Piece* piece, int x, int y)
{
    _moves.clear();
    switch (piece->GetType())
    {
    case Falcon:
        CheckMove(piece, x + 1, y + 1);
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x + 1, y - 1);
        CheckMove(piece, x - 1, y + 1);
        CheckMove(piece, x - 1, y);
        CheckMove(piece, x - 1, y - 1);
        if (piece->GetColour() == Black)
        {
            CheckMove(piece, x, y + 1);
        }
        else
        {
            CheckMove(piece, x, y - 1);
        }
        break;
    case Crane:
        CheckMove(piece, x + 1, y + 1);
        CheckMove(piece, x + 1, y - 1);
        CheckMove(piece, x, y + 1);
        CheckMove(piece, x, y - 1);
        CheckMove(piece, x - 1, y + 1);
        CheckMove(piece, x - 1, y - 1);
        break;
    case Pheasant:
        if (piece->GetColour() == Black)
        {
            CheckMove(piece, x, y + 2);
            CheckMove(piece, x + 1, y - 1);
            CheckMove(piece, x - 1, y - 1);
        }
        else
        {
            CheckMove(piece, x, y - 2);
            CheckMove(piece, x + 1, y + 1);
            CheckMove(piece, x - 1, y + 1);
        }
        break;
    case LeftQuail:
        if (piece->GetColour() == White)
        {
            CheckDirection(piece, x, y, South);
            CheckDirection(piece, x, y, NorthEast);
            CheckMove(piece, x - 1, y + 1);
        }
        else
        {
            CheckDirection(piece, x, y, North);
            CheckDirection(piece, x, y, SouthEast);
            CheckMove(piece, x - 1, y - 1);
        }
        break;
    case RightQuail:
        if (piece->GetColour() == White)
        {
            CheckDirection(piece, x, y, South);
            CheckDirection(piece, x, y, NorthWest);
            CheckMove(piece, x + 1, y + 1);
        }
        else
        {
            CheckDirection(piece, x, y, North);
            CheckDirection(piece, x, y, SouthWest);
            CheckMove(piece, x + 1, y - 1);
        }
        break;
    case Eagle:
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x - 1, y);
        if (piece->GetColour() == White)
        {
            CheckDirection(piece, x, y, SouthWest);
            CheckDirection(piece, x, y, SouthEast);
            CheckMove(piece, x, y - 1);
            CheckMove(piece, x + 1, y + 1);
            CheckMove(piece, x - 1, y + 1);
            CheckMove(piece, x + 2, y + 2);
            CheckMove(piece, x - 2, y + 2);
        }
        else
        {
            CheckDirection(piece, x, y, NorthWest);
            CheckDirection(piece, x, y, NorthEast);
            CheckMove(piece, x, y + 1);
            CheckMove(piece, x + 1, y - 1);
            CheckMove(piece, x - 1, y - 1);
            CheckMove(piece, x + 2, y - 2);
            CheckMove(piece, x - 2, y - 2);
        }
        break;
    case Goose:
        if (piece->GetColour() == Black)
        {
            CheckMove(piece, x, y - 2);
            CheckMove(piece, x + 2, y + 2);
            CheckMove(piece, x - 2, y + 2);
        }
        else
        {
            CheckMove(piece, x, y + 2);
            CheckMove(piece, x + 2, y - 2);
            CheckMove(piece, x - 2, y - 2);
        }
        break;
    default:
        ShogiBoard::GetMoves(piece, x, y);
        break;
    }
}
