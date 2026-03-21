#include "CapablancaChessBoard.h"

CapablancaChessBoard::CapablancaChessBoard()
{
    _width = 10;
    _height = 8;
    CapablancaChessBoard::Initialize();
}

CapablancaChessBoard::~CapablancaChessBoard()
{
}

Board* CapablancaChessBoard::Clone()
{
    CapablancaChessBoard *cb = new CapablancaChessBoard();
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

void CapablancaChessBoard::Initialize()
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
                _data[i][j] = new GothicChessPiece(_initialSetup[j][i], j < 5 ? Black : White);
            }
            else
            {
                _data[i][j] = nullptr;
            }
        }
    }
}

Piece* CapablancaChessBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
    return new GothicChessPiece(pieceType, pieceColour);
}

void CapablancaChessBoard::GetMoves(Piece *piece, int x, int y)
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
            if (_data[0][y] != nullptr)
            {
                const ChessPiece* cp = dynamic_cast<ChessPiece*>(_data[0][y]);
                if (!cp->HasMoved() && cp->GetType() == Rook && _data[1][y] == nullptr && _data[2][y] == nullptr && _data[3][y] == nullptr && _data[4][y] == nullptr)
                {
                    if ((piece->GetColour() == White && _wqc == true) || (piece->GetColour() == Black && _bqc == true))
                    {
                        _moves.emplace_back(0, y);
                    }
                }
            }
            if (_data[9][y] != nullptr)
            {
                const ChessPiece* cp = dynamic_cast<ChessPiece*>(_data[9][y]);
                if (!cp->HasMoved() && cp->GetType() == Rook && _data[6][y] == nullptr && _data[7][y] == nullptr && _data[8][y] == nullptr)
                {
                    if ((piece->GetColour() == White && _wkc == true) || (piece->GetColour() == Black && _bkc == true))
                    {
                        _moves.emplace_back(9, y);
                    }
                }
            }
        }
        break;
    case Archbishop:
        CheckMove(piece, x + 1, y + 2);
        CheckMove(piece, x - 1, y + 2);
        CheckMove(piece, x + 2, y + 1);
        CheckMove(piece, x + 2, y - 1);
        CheckMove(piece, x - 2, y + 1);
        CheckMove(piece, x - 2, y - 1);
        CheckMove(piece, x + 1, y - 2);
        CheckMove(piece, x - 1, y - 2);
        CheckDirection(piece, x, y, NorthEast);
        CheckDirection(piece, x, y, SouthEast);
        CheckDirection(piece, x, y, SouthWest);
        CheckDirection(piece, x, y, NorthWest);
        break;
    case Chancellor:
        CheckMove(piece, x + 1, y + 2);
        CheckMove(piece, x - 1, y + 2);
        CheckMove(piece, x + 2, y + 1);
        CheckMove(piece, x + 2, y - 1);
        CheckMove(piece, x - 2, y + 1);
        CheckMove(piece, x - 2, y - 1);
        CheckMove(piece, x + 1, y - 2);
        CheckMove(piece, x - 1, y - 2);
        CheckDirection(piece, x, y, North);
        CheckDirection(piece, x, y, East);
        CheckDirection(piece, x, y, South);
        CheckDirection(piece, x, y, West);
        break;
    default:
        ChessBoard::GetMoves(piece, x, y);
        break;
    }
}
