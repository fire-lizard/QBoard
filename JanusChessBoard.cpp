#include "JanusChessBoard.h"

JanusChessBoard::JanusChessBoard()
{
    _width = 10;
    _height = 8;
    JanusChessBoard::Initialize();
}

JanusChessBoard::~JanusChessBoard()
{
}

Board* JanusChessBoard::Clone()
{
    JanusChessBoard *cb = new JanusChessBoard();
    for (int i = 0; i < GetWidth(); i++)
    {
        for (int j = 0; j < GetHeight(); j++)
        {
            const Piece *p = GetData(i, j);
            cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->Type, p->Colour) : nullptr);
        }
    }
    cb->SetMoveCount(_moveCount);
    cb->SetHalfMoveCount(_halfMoveCount);
    cb->SetCastling(GetCastling());
    cb->SetEnPassant(_ep);
    return cb;
}

void JanusChessBoard::Initialize()
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
                SetData(i, j, new Piece(_initialSetup[j][i], j < 5 ? Black : White));
            }
            else
            {
                SetData(i, j, nullptr);
            }
        }
    }
}

void JanusChessBoard::GetMoves(Piece *piece, int x, int y)
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
            if (GetData(0, y) != nullptr)
            {
                const Piece* cp = GetData(0, y);
                if (!cp->HasMoved && cp->Type == Rook && GetData(1, y) == nullptr && GetData(2, y) == nullptr && GetData(3, y) == nullptr)
                {
                    if ((piece->Colour == White && _wqc == true) || (piece->Colour == Black && _bqc == true))
                    {
                        _moves.emplace_back(0, y);
                    }
                }
            }
            if (GetData(9, y) != nullptr)
            {
                const Piece* cp = GetData(9, y);
                if (!cp->HasMoved && cp->Type == Rook && GetData(5, y) == nullptr && GetData(6, y) == nullptr && GetData(7, y) == nullptr && GetData(8, y) == nullptr)
                {
                    if ((piece->Colour == White && _wkc == true) || (piece->Colour == Black && _bkc == true))
                    {
                        _moves.emplace_back(9, y);
                    }
                }
            }
        }
        break;
    default:
        CapablancaChessBoard::GetMoves(piece, x, y);
        break;
    }
}
