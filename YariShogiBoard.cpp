#include "YariShogiBoard.h"

YariShogiBoard::YariShogiBoard()
{
    _width = 7;
    _height = 9;
    ShogiBoard::Initialize();
}

YariShogiBoard::~YariShogiBoard()
{
}

void YariShogiBoard::Initialize()
{
    _moveCount = 0;
    _capturedPieces.clear();
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                _data[i][j] = new YariShogiPiece(_initialSetup[j][i], j < 5 ? Black : White);
            }
            else
            {
                _data[i][j] = nullptr;
            }
        }
    }
}

Board* YariShogiBoard::Clone()
{
    YariShogiBoard *cb = new YariShogiBoard();
    for (int i = 0; i < GetWidth(); i++)
    {
        for (int j = 0; j < GetHeight(); j++)
        {
            const Piece *p = GetData(i, j);
            cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
        }
    }
    for (const auto& capturedPiece: _capturedPieces)
    {
        cb->AddCapturedPiece(capturedPiece.second, capturedPiece.first);
    }
    cb->SetMoveCount(_moveCount);
    return cb;
}

Piece* YariShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
    return new YariShogiPiece(pieceType, pieceColour);
}

void YariShogiBoard::PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y)
{
    _data[x][y] = new YariShogiPiece(pieceType, pieceColour);
}

void YariShogiBoard::GetMoves(Piece *piece, int x, int y)
{
    _moves.clear();
    switch (piece->GetType())
    {
    case YariRook:
        CheckDirection(piece, x, y, East);
        CheckDirection(piece, x, y, West);
        if (piece->GetColour() == Black)
        {
            CheckDirection(piece, x, y, North);
        }
        else
        {
            CheckDirection(piece, x, y, South);
        }
        break;
    case YariGold:
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x - 1, y);
        if (piece->GetColour() == Black)
        {
            CheckDirection(piece, x, y, North);
            CheckMove(piece, x, y + 1);
            CheckMove(piece, x - 1, y + 1);
            CheckMove(piece, x + 1, y + 1);
        }
        else
        {
            CheckDirection(piece, x, y, South);
            CheckMove(piece, x, y - 1);
            CheckMove(piece, x - 1, y - 1);
            CheckMove(piece, x + 1, y - 1);
        }
        break;
    case YariSilver:
        if (piece->GetColour() == Black)
        {
            CheckDirection(piece, x, y, North);
            CheckMove(piece, x, y + 1);
            CheckMove(piece, x - 1, y + 1);
            CheckMove(piece, x + 1, y + 1);
        }
        else
        {
            CheckDirection(piece, x, y, South);
            CheckMove(piece, x, y - 1);
            CheckMove(piece, x - 1, y - 1);
            CheckMove(piece, x + 1, y - 1);
        }
        break;
    case YariBishop:
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x - 1, y);
        if (piece->GetColour() == Black)
        {
            CheckDirection(piece, x, y, North);
        }
        else
        {
            CheckDirection(piece, x, y, South);
        }
        break;
    case YariKnight:
        if (piece->GetColour() == Black)
        {
            CheckDirection(piece, x, y, North);
            CheckMove(piece, x - 1, y + 2);
            CheckMove(piece, x + 1, y + 2);
        }
        else
        {
            CheckDirection(piece, x, y, South);
            CheckMove(piece, x - 1, y - 2);
            CheckMove(piece, x + 1, y - 2);
        }
        break;
    default:
        ShogiBoard::GetMoves(piece, x, y);
        break;
    }
}
