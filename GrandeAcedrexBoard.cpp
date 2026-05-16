#include "GrandeAcedrexBoard.h"

GrandeAcedrexBoard::GrandeAcedrexBoard()
{
    _width = 12;
    _height = 12;
    GrandeAcedrexBoard::Initialize();
}

GrandeAcedrexBoard::~GrandeAcedrexBoard()
{
}

Board* GrandeAcedrexBoard::Clone()
{
    GrandeAcedrexBoard* cb = new GrandeAcedrexBoard();
    for (int i = 0; i < GetWidth(); i++)
    {
        for (int j = 0; j < GetHeight(); j++)
        {
            const Piece* p = GetData(i, j);
            cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
        }
    }
    cb->SetMoveCount(_moveCount);
    return cb;
}

void GrandeAcedrexBoard::Initialize()
{
    _moveCount = 0;
    _pgn = "";
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                SetData(i, j, new ChessPiece(_initialSetup[j][i], j < 5 ? Black : White));
            }
            else
            {
                SetData(i, j, nullptr);
            }
        }
    }
}

Piece* GrandeAcedrexBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
    return new ChessPiece(pieceType, pieceColour);
}

void GrandeAcedrexBoard::Promote(int x, int y, PieceType pt)
{
    Promote(GetData(x, y), pt);
}

void GrandeAcedrexBoard::Promote(Piece *piece, PieceType pt)
{
    if (piece != nullptr)
    {
        piece->IsPromoted = true;
        piece->SetType(pt);
    }
}

void GrandeAcedrexBoard::GetMoves(Piece* piece, int x, int y)
{
    _moves.clear();
    switch (piece->GetType())
    {
    case King:
        CheckMove(piece, x + 1, y + 1);
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x + 1, y - 1);
        CheckMove(piece, x, y + 1);
        CheckMove(piece, x, y - 1);
        CheckMove(piece, x - 1, y + 1);
        CheckMove(piece, x - 1, y);
        CheckMove(piece, x - 1, y - 1);
        if (!dynamic_cast<ChessPiece*>(piece)->HasMoved())
        {
            CheckMove(piece, x + 2, y);
            CheckMove(piece, x - 2, y);
            if (piece->GetColour() == Black)
            {
                CheckMove(piece, x, y + 2);
                CheckMove(piece, x + 2, y + 2);
                CheckMove(piece, x - 2, y + 2);
            }
            else
            {
                CheckMove(piece, x, y - 2);
                CheckMove(piece, x + 2, y - 2);
                CheckMove(piece, x - 2, y - 2);
            }
        }
        break;
    case Aanca:
        CheckMove(piece, x + 1, y + 1);
        CheckMove(piece, x + 1, y - 1);
        CheckMove(piece, x - 1, y + 1);
        CheckMove(piece, x - 1, y - 1);
        if (GetData(x + 1, y + 1) == nullptr)
        {
            CheckDirection(piece, x + 1, y + 1, North);
            CheckDirection(piece, x + 1, y + 1, East);
        }
        if (GetData(x + 1, y - 1) == nullptr)
        {
            CheckDirection(piece, x + 1, y - 1, South);
            CheckDirection(piece, x + 1, y - 1, East);
        }
        if (GetData(x - 1, y + 1) == nullptr)
        {
            CheckDirection(piece, x - 1, y + 1, North);
            CheckDirection(piece, x - 1, y + 1, West);
        }
        if (GetData(x - 1, y - 1) == nullptr)
        {
            CheckDirection(piece, x - 1, y - 1, South);
            CheckDirection(piece, x - 1, y - 1, West);
        }
        break;
    case Giraffe:
        CheckMove(piece, x + 2, y + 3);
        CheckMove(piece, x - 2, y + 3);
        CheckMove(piece, x + 3, y + 2);
        CheckMove(piece, x + 3, y - 2);
        CheckMove(piece, x - 3, y + 2);
        CheckMove(piece, x - 3, y - 2);
        CheckMove(piece, x + 2, y - 3);
        CheckMove(piece, x - 2, y - 3);
        break;
    case Lion:
        CheckMove(piece, x + 1, y + 3);
        CheckMove(piece, x - 1, y + 3);
        CheckMove(piece, x + 3, y + 1);
        CheckMove(piece, x + 3, y - 1);
        CheckMove(piece, x - 3, y + 1);
        CheckMove(piece, x - 3, y - 1);
        CheckMove(piece, x + 1, y - 3);
        CheckMove(piece, x - 1, y - 3);
        CheckMove(piece, x - 3, y);
        CheckMove(piece, x + 3, y);
        CheckMove(piece, x, y - 3);
        CheckMove(piece, x, y + 3);
        break;
    case Crocodile:
        CheckDirection(piece, x, y, NorthEast);
        CheckDirection(piece, x, y, SouthEast);
        CheckDirection(piece, x, y, SouthWest);
        CheckDirection(piece, x, y, NorthWest);
        break;
    case Unicorn:
        if (GetData(x + 1, y + 2) == nullptr)
        {
            CheckMove(piece, x + 1, y + 2);
            CheckDirection(piece, x + 1, y + 2, NorthEast);
        }
        if (GetData(x - 1, y + 2) == nullptr)
        {
            CheckMove(piece, x - 1, y + 2);
            CheckDirection(piece, x - 1, y + 2, NorthWest);
        }
        if (GetData(x + 1, y - 2) == nullptr)
        {
            CheckMove(piece, x + 1, y - 2);
            CheckDirection(piece, x + 1, y - 2, SouthEast);
        }
        if (GetData(x - 1, y - 2) == nullptr)
        {
            CheckMove(piece, x - 1, y - 2);
            CheckDirection(piece, x - 1, y - 2, SouthWest);
        }
        if (GetData(x + 2, y + 1) == nullptr)
        {
            CheckMove(piece, x + 2, y + 1);
            CheckDirection(piece, x + 2, y + 1, NorthEast);
        }
        if (GetData(x + 2, y - 1) == nullptr)
        {
            CheckMove(piece, x + 2, y - 1);
            CheckDirection(piece, x + 2, y - 1, SouthEast);
        }
        if (GetData(x - 2, y + 1) == nullptr)
        {
            CheckMove(piece, x - 2, y + 1);
            CheckDirection(piece, x - 2, y + 1, NorthWest);
        }
        if (GetData(x - 2, y - 1) == nullptr)
        {
            CheckMove(piece, x - 2, y - 1);
            CheckDirection(piece, x - 2, y - 1, SouthWest);
        }
        break;
    default:
        ShatranjBoard::GetMoves(piece, x, y);
        break;
    }
}

bool GrandeAcedrexBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
{
    const bool result = ShatranjBoard::Move(oldX, oldY, newX, newY, cl);
    if (result)
    {
        dynamic_cast<ChessPiece*>(GetData(newX, newY))->Move();
    }
    return result;
}

std::string GrandeAcedrexBoard::GetStringCode(int x, int y) const
{
    if (GetData(x, y) == nullptr) return "";
    PieceType pieceType = GetData(x, y)->GetType();
    switch (pieceType)
    {
    case King:
        return "K";
    case Aanca:
        return "A";
    case Rook:
        return "R";
    case Crocodile:
        return "C";
    case Giraffe:
        return "G";
    case Unicorn:
        return "U";
    case Lion:
        return "L";
    case Pawn:
        return "P";
    default:
        return Board::GetStringCode(x, y);
    }
}
