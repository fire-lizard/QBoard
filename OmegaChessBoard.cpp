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
    _halfMoveCount = 0;
    _pgn = "";
    _wkc = true;
    _wqc = true;
    _bkc = true;
    _bqc = true;
    _ep = "-";
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

bool OmegaChessBoard::EnemyPawnsAround(int x, int y) const
{
    const Piece *fp = x > 0 ? GetData(x - 1, y) : nullptr;
    const Piece *sp = x < _width - 1 ? GetData(x + 1, y) : nullptr;
    const PieceColour pieceColour = y == 3 ? White : Black;
    const bool fpa = (fp != nullptr) && (fp->GetType() == Pawn) && (fp->GetColour() == pieceColour);
    const bool spa = (sp != nullptr) && (sp->GetType() == Pawn) && (sp->GetColour() == pieceColour);
    return fpa || spa;
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

bool OmegaChessBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
{
    const PieceType pieceType = GetData(oldX, oldY)->GetType();
    const PieceColour pieceColour = GetData(oldX, oldY)->GetColour();
    const PieceType destPieceType = GetData(newX, newY) != nullptr ? GetData(newX, newY)->GetType() : None;
    const bool result = Board::Move(oldX, oldY, newX, newY, cl);
    if (result)
    {
        dynamic_cast<ChessPiece*>(GetData(newX, newY))->Move();
        // Castling
        if (pieceType == Rook)
        {
            if (oldX == 0 && oldY == _height - 1)
            {
                _wqc = false;
            }
            else if (oldX == _width - 1 && oldY == _height - 1)
            {
                _wkc = false;
            }
            else if (oldX == 0 && oldY == 0)
            {
                _bqc = false;
            }
            else if (oldX == _width - 1 && oldY == 0)
            {
                _bkc = false;
            }
        }
        else if (pieceType == King)
        {
            if (pieceColour == White)
            {
                _wqc = false;
                _wkc = false;
            }
            else
            {
                _bqc = false;
                _bkc = false;
            }
        }
        if (destPieceType == Rook)
        {
            if (newX == 0 && newY == _height - 1)
            {
                _wqc = false;
            }
            else if (newX == _width - 1 && newY == _height - 1)
            {
                _wkc = false;
            }
            else if (newX == 0 && newY == 0)
            {
                _bqc = false;
            }
            else if (newX == _width - 1 && newY == 0)
            {
                _bkc = false;
            }
        }
        // En passant
        if (pieceType == Pawn && abs(oldY - newY) == 2 && EnemyPawnsAround(newX, newY))
        {
            _ep = "";
            const char letter = newX + 97;
            _ep.push_back(letter);
            _ep.append(oldY == _height - 3 ? "6" : "3");
        }
        else if (pieceType == Pawn && _ep != "-")
        {
            const char letter = newX + 97;
            const int number = _ep[1] - 48;
            if (letter == _ep[0] &&	((pieceColour == White && newY == number - 1) || (pieceColour == Black && newY == number + 2)))
            {
                const Piece* p = pieceColour == White ? GetData(newX, number) : GetData(newX, number + 1);
                if (p != nullptr && p->GetType() == Pawn && p->GetColour() != pieceColour)
                {
                    delete p;
                    if (pieceColour == White)
                    {
                        SetData(newX, number, nullptr);
                    }
                    else
                    {
                        SetData(newX, number + 1, nullptr);
                    }
                }
            }
            _ep = "-";
        }
        else
        {
            _ep = "-";
        }
        if (pieceType == Pawn || destPieceType != None)
        {
            _halfMoveCount = 0;
        }
        else
        {
            _halfMoveCount++;
        }
    }
    return result;
}
