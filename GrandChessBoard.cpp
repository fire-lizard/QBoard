#include "GrandChessBoard.h"

GrandChessBoard::GrandChessBoard()
{
    _width = 10;
    _height = 10;
    GrandChessBoard::Initialize();
}

GrandChessBoard::~GrandChessBoard()
{
}

Board* GrandChessBoard::Clone()
{
    GrandChessBoard *cb = new GrandChessBoard();
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
    cb->SetHalfMoveCount(_halfMoveCount);
    cb->SetCastling("-");
    cb->SetEnPassant(_ep);
    return cb;
}

void GrandChessBoard::Initialize()
{
    _moveCount = 0;
    _halfMoveCount = 0;
    _pgn = "";
    _wkc = false;
    _wqc = false;
    _bkc = false;
    _bqc = false;
    _ep = "-";
    _capturedPieces.clear();
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

void GrandChessBoard::GetMoves(Piece *piece, int x, int y)
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
        break;
    case Pawn:
        if (piece->GetColour() == Black)
        {
            if (y == 2 && GetData(x, y + 1) == nullptr && GetData(x, y + 2) == nullptr)
            {
                CheckMove(piece, x, y + 2);
            }
            if (y + 1 < _height - 1 && GetData(x, y + 1) == nullptr)
            {
                CheckMove(piece, x, y + 1);
            }
            if (y + 1 < _height - 1 && x + 1 < _width && GetData(x + 1, y + 1) != nullptr)
            {
                CheckMove(piece, x + 1, y + 1);
            }
            if (y + 1 < _height - 1 && x - 1 >= 0 && GetData(x - 1, y + 1) != nullptr)
            {
                CheckMove(piece, x - 1, y + 1);
            }
            // Unlike standard chess, a pawn may be promoted only to a captured piece of the same colour
            // Pawn can still give check to the King on tenth rank
            if (y == _height - 2 && x + 1 < _width && GetData(x + 1, y + 1) != nullptr && GetData(x + 1, y + 1)->GetType() == King)
            {
                CheckMove(piece, x + 1, y + 1);
            }
            if (y == _height - 2 && x - 1 >= 0 && GetData(x - 1, y + 1) != nullptr && GetData(x - 1, y + 1)->GetType() == King)
            {
                CheckMove(piece, x - 1, y + 1);
            }
            if (y == _height - 2 && !GetCapturedPieces(White).empty())
            {
                if (GetData(x, y + 1) == nullptr)
                {
                    CheckMove(piece, x, y + 1);
                }
                if (x + 1 < _width && GetData(x + 1, y + 1) != nullptr)
                {
                    CheckMove(piece, x + 1, y + 1);
                }
                if (x - 1 >= 0 && GetData(x - 1, y + 1) != nullptr)
                {
                    CheckMove(piece, x - 1, y + 1);
                }
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
            if (y == 7 && GetData(x, y - 1) == nullptr && GetData(x, y - 2) == nullptr)
            {
                CheckMove(piece, x, y - 2);
            }
            if (y - 1 >= 1 && GetData(x, y - 1) == nullptr)
            {
                CheckMove(piece, x, y - 1);
            }
            if (y - 1 >= 1 && x + 1 < _width && GetData(x + 1, y - 1) != nullptr)
            {
                CheckMove(piece, x + 1, y - 1);
            }
            if (y - 1 >= 1 && x - 1 >= 0 && GetData(x - 1, y - 1) != nullptr)
            {
                CheckMove(piece, x - 1, y - 1);
            }
            // Unlike standard chess, a pawn may be promoted only to a captured piece of the same colour
            // Pawn can still give check to the King on tenth rank
            if (y == 1 && x + 1 < _width && GetData(x + 1, y - 1) != nullptr && GetData(x + 1, y - 1)->GetType() == King)
            {
                CheckMove(piece, x + 1, y - 1);
            }
            if (y == 1 && x - 1 >= 0 && GetData(x - 1, y - 1) != nullptr && GetData(x - 1, y - 1)->GetType() == King)
            {
                CheckMove(piece, x - 1, y - 1);
            }
            if (y == 1 && !GetCapturedPieces(Black).empty())
            {
                if (GetData(x, y - 1) == nullptr)
                {
                    CheckMove(piece, x, y - 1);
                }
                if (x + 1 < _width && GetData(x + 1, y - 1) != nullptr)
                {
                    CheckMove(piece, x + 1, y - 1);
                }
                if (x - 1 >= 0 && GetData(x - 1, y - 1) != nullptr)
                {
                    CheckMove(piece, x - 1, y - 1);
                }
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

bool GrandChessBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
{
    const PieceType pieceType = GetData(oldX, oldY)->GetType();
    const PieceColour pieceColour = GetData(oldX, oldY)->GetColour();
    const PieceType destPieceType = GetData(newX, newY) != nullptr ? GetData(newX, newY)->GetType() : None;
    const bool result = Board::Move(oldX, oldY, newX, newY, cl);
    if (result)
    {
        if (destPieceType != None && destPieceType != Pawn)
        {
            _capturedPieces.emplace_back(pieceColour, destPieceType);
        }
        dynamic_cast<ChessPiece*>(GetData(newX, newY))->Move();
        // En passant
        if (pieceType == Pawn && abs(oldY - newY) == 2 && EnemyPawnsAround(newX, newY))
        {
            _ep = "";
            const char letter = newX + 97;
            _ep.push_back(letter);
            _ep.append(oldY == 6 ? "7" : "4");
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

bool GrandChessBoard::EnemyPawnsAround(int x, int y) const
{
    const Piece *fp = x > 0 ? GetData(x - 1, y) : nullptr;
    const Piece *sp = x < _width - 1 ? GetData(x + 1, y) : nullptr;
    const PieceColour pieceColour = y == 4 ? White : Black;
    const bool fpa = (fp != nullptr) && (fp->GetType() == Pawn) && (fp->GetColour() == pieceColour);
    const bool spa = (sp != nullptr) && (sp->GetType() == Pawn) && (sp->GetColour() == pieceColour);
    return fpa || spa;
}

std::vector<PieceType> GrandChessBoard::GetCapturedPieces(PieceColour pieceColour)
{
    std::vector<PieceType> result;
    for (auto& capturedPiece : _capturedPieces)
    {
        if (capturedPiece.first == pieceColour)
        {
            result.emplace_back(capturedPiece.second);
        }
    }
    return result;
}

void GrandChessBoard::AddCapturedPiece(PieceType p, PieceColour pieceColour)
{
    _capturedPieces.emplace_back(pieceColour, p);
}

void GrandChessBoard::RemoveCapturedPiece(PieceType p, PieceColour pieceColour)
{
    for (size_t index = 0; index < _capturedPieces.size(); index++)
    {
        if (_capturedPieces[index].first == pieceColour && _capturedPieces[index].second == p)
        {
            _capturedPieces.erase(_capturedPieces.begin() + index);
            break;
        }
    }
}
