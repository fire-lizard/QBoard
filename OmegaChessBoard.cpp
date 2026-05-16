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
    const PieceColour pieceColour = y < 6 ? White : Black;
    const bool fpa = (fp != nullptr) && (fp->GetType() == Pawn) && (fp->GetColour() == pieceColour);
    const bool spa = (sp != nullptr) && (sp->GetType() == Pawn) && (sp->GetColour() == pieceColour);
    return fpa || spa;
}

void OmegaChessBoard::GetMoves(Piece* piece, int x, int y)
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
        // Check castling
        if (!dynamic_cast<ChessPiece*>(piece)->HasMoved())
        {
            if (GetData(2, y) != nullptr)
            {
                const ChessPiece* cp = dynamic_cast<ChessPiece*>(GetData(2, y));
                if (!cp->HasMoved() && cp->GetType() == Rook && GetData(3, y) == nullptr && GetData(4, y) == nullptr && GetData(5, y) == nullptr)
                {
                    if ((piece->GetColour() == White && _wqc == true) || (piece->GetColour() == Black && _bqc == true))
                    {
                        _moves.emplace_back(2, y);
                    }
                }
            }
            if (GetData(_width - 3, y) != nullptr)
            {
                const ChessPiece* cp = dynamic_cast<ChessPiece*>(GetData(_width - 3, y));
                if (!cp->HasMoved() && cp->GetType() == Rook && GetData(7, y) == nullptr && GetData(8, y) == nullptr)
                {
                    if ((piece->GetColour() == White && _wkc == true) || (piece->GetColour() == Black && _bkc == true))
                    {
                        _moves.emplace_back(_width - 3, y);
                    }
                }
            }
        }
        break;
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
    if (result && GetData(newX, newY) != nullptr)
    {
        dynamic_cast<ChessPiece*>(GetData(newX, newY))->Move();
        // Castling
        if (pieceType == Rook)
        {
            if (oldX == 2 && oldY == _height - 2)
            {
                _wqc = false;
            }
            else if (oldX == _width - 3 && oldY == _height - 2)
            {
                _wkc = false;
            }
            else if (oldX == 2 && oldY == 1)
            {
                _bqc = false;
            }
            else if (oldX == _width - 3 && oldY == 1)
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
            if (newX == 2 && newY == _height - 2)
            {
                _wqc = false;
            }
            else if (newX == _width - 3 && newY == _height - 2)
            {
                _wkc = false;
            }
            else if (newX == 2 && newY == 1)
            {
                _bqc = false;
            }
            else if (newX == _width - 3 && newY == 1)
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
            _ep.append(oldY == _height - 3 ? "6" : "4");
        }
        else if (pieceType == Pawn && abs(oldY - newY) == 3 && EnemyPawnsAround(newX, newY))
        {
            _ep = "";
            const char letter = newX + 97;
            _ep.push_back(letter);
            _ep.append(oldY == _height - 3 ? "5" : "5");
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

std::string OmegaChessBoard::GetStringCode(int x, int y) const
{
    if (GetData(x, y) == nullptr) return "";
    PieceType pieceType = GetData(x, y)->GetType();
    switch (pieceType)
    {
    case Champion:
        return "C";
    case Wizard:
        return "W";
    default:
        return Board::GetStringCode(x, y);
    }
}
