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
            cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
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
                _data[i][j] = new GothicChessPiece(_initialSetup[j][i], j < 5 ? Black : White);
            }
            else
            {
                _data[i][j] = nullptr;
            }
        }
    }
}
