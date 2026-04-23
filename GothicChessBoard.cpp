#include "GothicChessBoard.h"

GothicChessBoard::GothicChessBoard()
{
    _width = 10;
    _height = 8;
    GothicChessBoard::Initialize();
}

GothicChessBoard::~GothicChessBoard()
{
}

Board* GothicChessBoard::Clone()
{
    GothicChessBoard *cb = new GothicChessBoard();
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

void GothicChessBoard::Initialize()
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
