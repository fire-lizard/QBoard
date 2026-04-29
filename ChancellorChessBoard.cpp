#include "ChancellorChessBoard.h"

ChancellorChessBoard::ChancellorChessBoard()
{
    _width = 9;
    _height = 9;
    ChancellorChessBoard::Initialize();
}

ChancellorChessBoard::~ChancellorChessBoard()
{
}

Board* ChancellorChessBoard::Clone()
{
    ChancellorChessBoard *cb = new ChancellorChessBoard();
    for (int i = 0; i < GetWidth(); i++)
    {
        for (int j = 0; j < GetHeight(); j++)
        {
            const Piece *p = GetData(i, j);
            cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
        }
    }
    cb->SetMoveCount(_moveCount);
    cb->SetHalfMoveCount(_halfMoveCount);
    cb->SetCastling(GetCastling());
    cb->SetEnPassant(_ep);
    return cb;
}

void ChancellorChessBoard::Initialize()
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
                SetData(i, j, new GothicChessPiece(_initialSetup[j][i], j < 5 ? Black : White));
            }
            else
            {
                SetData(i, j, nullptr);
            }
        }
    }
}

void ChancellorChessBoard::GetMoves(Piece *piece, int x, int y)
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
            if (GetData(0, y) != nullptr)
            {
                const ChessPiece* cp = dynamic_cast<ChessPiece*>(GetData(0, y));
                if (!cp->HasMoved() && cp->GetType() == Rook && GetData(1, y) == nullptr && GetData(2, y) == nullptr && GetData(3, y) == nullptr)
                {
                    if ((piece->GetColour() == White && _wqc == true) || (piece->GetColour() == Black && _bqc == true))
                    {
                        _moves.emplace_back(0, y);
                    }
                }
            }
            if (GetData(_width - 1, y) != nullptr)
            {
                const ChessPiece* cp = dynamic_cast<ChessPiece*>(GetData(_width - 1, y));
                if (!cp->HasMoved() && cp->GetType() == Rook && GetData(5, y) == nullptr && GetData(6, y) == nullptr)
                {
                    if ((piece->GetColour() == White && _wkc == true) || (piece->GetColour() == Black && _bkc == true))
                    {
                        _moves.emplace_back(_width - 1, y);
                    }
                }
            }
        }
        break;
    case Pawn:
        if (piece->GetColour() == Black)
        {
            if (y == 1 && GetData(x, y + 1) == nullptr && GetData(x, y + 2) == nullptr)
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
                if (abs(x - letter) == 1 && y == number + 2)
                {
                    CheckMove(piece, letter, number + 3);
                }
            }
        }
        else
        {
            if (y == _height - 2 && GetData(x, y - 1) == nullptr && GetData(x, y - 2) == nullptr)
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
        CapablancaChessBoard::GetMoves(piece, x, y);
        break;
    }
}

bool ChancellorChessBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
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
            _ep.append(oldY == _height - 3 ? "7" : "3");
        }
        else if (pieceType == Pawn && _ep != "-")
        {
            const char letter = newX + 97;
            const int number = _ep[1] - 48;
            if (letter == _ep[0] &&	((pieceColour == White && newY == number - 1) || (pieceColour == Black && newY == number + 3)))
            {
                const Piece* p = pieceColour == White ? GetData(newX, number) : GetData(newX, number + 2);
                if (p != nullptr && p->GetType() == Pawn && p->GetColour() != pieceColour)
                {
                    delete p;
                    if (pieceColour == White)
                    {
                        SetData(newX, number, nullptr);
                    }
                    else
                    {
                        SetData(newX, number + 2, nullptr);
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
