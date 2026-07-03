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
            const std::optional<Piece> p = GetData(i, j);
            cb->SetData(i, j, p != std::nullopt ? std::make_optional<Piece>(p->Type, p->Colour) : std::nullopt);
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
                SetData(i, j, Piece(_initialSetup[j][i], j < 5 ? Black : White));
            }
            else
            {
                SetData(i, j, std::nullopt);
            }
        }
    }
}

bool OmegaChessBoard::EnemyPawnsAround(int x, int y) const
{
    const std::optional<Piece> fp = x > 0 ? GetData(x - 1, y) : std::nullopt;
    const std::optional<Piece> sp = x < _width - 1 ? GetData(x + 1, y) : std::nullopt;
    const PieceColour pieceColour = y < 6 ? White : Black;
    const bool fpa = (fp != std::nullopt) && (fp->Type == Pawn) && (fp->Colour == pieceColour);
    const bool spa = (sp != std::nullopt) && (sp->Type == Pawn) && (sp->Colour == pieceColour);
    return fpa || spa;
}

void OmegaChessBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
    _moves.clear();
    switch (piece->Type)
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
        if (!piece->HasMoved)
        {
            if (GetData(2, y) != std::nullopt)
            {
                const std::optional<Piece> cp = GetData(2, y);
                if (!cp->HasMoved && cp->Type == Rook && GetData(3, y) == std::nullopt && GetData(4, y) == std::nullopt && GetData(5, y) == std::nullopt)
                {
                    if ((piece->Colour == White && _wqc == true) || (piece->Colour == Black && _bqc == true))
                    {
                        _moves.emplace_back(2, y);
                    }
                }
            }
            if (GetData(_width - 3, y) != std::nullopt)
            {
                const std::optional<Piece> cp = GetData(_width - 3, y);
                if (!cp->HasMoved && cp->Type == Rook && GetData(7, y) == std::nullopt && GetData(8, y) == std::nullopt)
                {
                    if ((piece->Colour == White && _wkc == true) || (piece->Colour == Black && _bkc == true))
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
        if (piece->Colour == Black)
        {
            if (y == 2 && GetData(x, y + 1) == std::nullopt && GetData(x, y + 2) == std::nullopt && GetData(x, y + 3) == std::nullopt)
            {
                CheckMove(piece, x, y + 3);
            }
            if (y == 2 && GetData(x, y + 1) == std::nullopt && GetData(x, y + 2) == std::nullopt)
            {
                CheckMove(piece, x, y + 2);
            }
            if (y + 1 < _height && GetData(x, y + 1) == std::nullopt)
            {
                CheckMove(piece, x, y + 1);
            }
            if (y + 1 < _height && x + 1 < _width && GetData(x + 1, y + 1) != std::nullopt)
            {
                CheckMove(piece, x + 1, y + 1);
            }
            if (y + 1 < _height && x - 1 >= 0 && GetData(x - 1, y + 1) != std::nullopt)
            {
                CheckMove(piece, x - 1, y + 1);
            }
            // En passant
            if (_ep != "-")
            {
                GetEnPassantMoves(piece.value(), x, y);
            }
        }
        else
        {
            if (y == _height - 3 && GetData(x, y - 1) == std::nullopt && GetData(x, y - 2) == std::nullopt && GetData(x, y - 3) == std::nullopt)
            {
                CheckMove(piece, x, y - 3);
            }
            if (y == _height - 3 && GetData(x, y - 1) == std::nullopt && GetData(x, y - 2) == std::nullopt)
            {
                CheckMove(piece, x, y - 2);
            }
            if (y - 1 >= 0 && GetData(x, y - 1) == std::nullopt)
            {
                CheckMove(piece, x, y - 1);
            }
            if (y - 1 >= 0 && x + 1 < _width && GetData(x + 1, y - 1) != std::nullopt)
            {
                CheckMove(piece, x + 1, y - 1);
            }
            if (y - 1 >= 0 && x - 1 >= 0 && GetData(x - 1, y - 1) != std::nullopt)
            {
                CheckMove(piece, x - 1, y - 1);
            }
            // En passant
            if (_ep != "-")
            {
                GetEnPassantMoves(piece.value(), x, y);
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
    const PieceType pieceType = GetData(oldX, oldY)->Type;
    const PieceColour pieceColour = GetData(oldX, oldY)->Colour;
    const PieceType destPieceType = GetData(newX, newY) != std::nullopt ? GetData(newX, newY)->Type : None;
    const bool result = ChessBoard::Move(oldX, oldY, newX, newY, cl);
    if (result && GetData(newX, newY) != std::nullopt)
    {
        _data[newX][newY]->HasMoved = true;
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
            _ep.append(oldY == 2 ? "8" : "5");
        }
        else if (pieceType == Pawn && abs(oldY - newY) == 3 && EnemyPawnsAround(newX, newY))
        {
            _ep = "";
            const char letter = newX + 97;
            _ep.push_back(letter);
            _ep.append(oldY == 2 ? "7" : "6");
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
    if (GetData(x, y) == std::nullopt) return "";
    PieceType pieceType = GetData(x, y)->Type;
    switch (pieceType)
    {
    case Champion:
        return "C";
    case Wizard:
        return "W";
    default:
        return ChessBoard::GetStringCode(x, y);
    }
}
