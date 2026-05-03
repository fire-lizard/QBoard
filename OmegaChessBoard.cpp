#include "OmegaChessBoard.h"

OmegaChessBoard::OmegaChessBoard()
{
    _width = 12;
    _height = 12;
    OmegaChessBoard::Initialize();
}

OmegaChessBoard::~OmegaChessBoard()
{
}

Board* OmegaChessBoard::Clone()
{
    OmegaChessBoard* cb = new OmegaChessBoard();
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

void OmegaChessBoard::Initialize()
{
    _moveCount = 0;
    _pgn = "";
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                SetData(i, j, new OmegaChessPiece(_initialSetup[j][i], j < 5 ? Black : White));
            }
            else
            {
                SetData(i, j, nullptr);
            }
        }
    }
}

Piece* OmegaChessBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
    return new OmegaChessPiece(pieceType, pieceColour);
}

void OmegaChessBoard::GetMoves(Piece* piece, int x, int y)
{
    _moves.clear();
    switch (piece->GetType())
    {
    case Champion:
        CheckMove(piece, x, y + 1);
        CheckMove(piece, x, y - 1);
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x - 1, y);
        CheckMove(piece, x + 2, y);
        CheckMove(piece, x - 2, y);
        CheckMove(piece, x, y + 2);
        CheckMove(piece, x, y - 2);
        CheckMove(piece, x + 2, y + 2);
        CheckMove(piece, x + 2, y - 2);
        CheckMove(piece, x - 2, y + 2);
        CheckMove(piece, x - 2, y - 2);
        break;
    case Wizard:
        CheckMove(piece, x + 1, y + 1);
        CheckMove(piece, x + 1, y - 1);
        CheckMove(piece, x - 1, y + 1);
        CheckMove(piece, x - 1, y - 1);
        CheckMove(piece, x + 1, y + 3);
        CheckMove(piece, x - 1, y + 3);
        CheckMove(piece, x + 3, y + 1);
        CheckMove(piece, x + 3, y - 1);
        CheckMove(piece, x - 3, y + 1);
        CheckMove(piece, x - 3, y - 1);
        CheckMove(piece, x + 1, y - 3);
        CheckMove(piece, x - 1, y - 3);
        break;
    case Pawn:
        if (piece->GetColour() == Black)
        {
            if (y == 2 && GetData(x, y + 1) == nullptr && GetData(x, y + 2) == nullptr && GetData(x, y + 3) == nullptr)
            {
                CheckMove(piece, x, y + 3);
            }
            if (y == 2 && GetData(x, y + 1) == nullptr && GetData(x, y + 2) == nullptr)
            {
                CheckMove(piece, x, y + 2);
            }
            if (y + 1 < _height && GetData(x, y + 1) == nullptr)
            {
                CheckMove(piece, x, y + 1);
            }
            if (y + 1 < _height && x + 1 < _width && GetData(x + 1, y + 1) != nullptr)
            {
                CheckMove(piece, x + 1, y + 1);
            }
            if (y + 1 < _height && x - 1 >= 0 && GetData(x - 1, y + 1) != nullptr)
            {
                CheckMove(piece, x - 1, y + 1);
            }
            // En passant
            if (_ep != "-")
            {
                const int letter = _ep[0] - 97;
                const int number = _ep[1] - 48;
                if (abs(x - letter) == 1 && y == number + 1)
                {
                    CheckMove(piece, letter, number + 2);
                }
            }
        }
        else
        {
            if (y == _height - 3 && GetData(x, y - 1) == nullptr && GetData(x, y - 2) == nullptr && GetData(x, y - 3) == nullptr)
            {
                CheckMove(piece, x, y - 3);
            }
            if (y == _height - 3 && GetData(x, y - 1) == nullptr && GetData(x, y - 2) == nullptr)
            {
                CheckMove(piece, x, y - 2);
            }
            if (y - 1 >= 0 && GetData(x, y - 1) == nullptr)
            {
                CheckMove(piece, x, y - 1);
            }
            if (y - 1 >= 0 && x + 1 < _width && GetData(x + 1, y - 1) != nullptr)
            {
                CheckMove(piece, x + 1, y - 1);
            }
            if (y - 1 >= 0 && x - 1 >= 0 && GetData(x - 1, y - 1) != nullptr)
            {
                CheckMove(piece, x - 1, y - 1);
            }
            // En passant
            if (_ep != "-")
            {
                const int letter = _ep[0] - 97;
                const int number = _ep[1] - 48;
                if (abs(x - letter) == 1 && y == number)
                {
                    CheckMove(piece, letter, number - 1);
                }
            }
        }
        break;
    default:
        ChessBoard::GetMoves(piece, x, y);
        break;
    }
}
