#include "MicroShogiBoard.h"

MicroShogiBoard::MicroShogiBoard()
{
    _width = 4;
    _height = 5;
    MicroShogiBoard::Initialize();
}

MicroShogiBoard::~MicroShogiBoard()
{
}

void MicroShogiBoard::Initialize()
{
    _capturedPieces.clear();
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                _data[i][j] = new MicroShogiPiece(_initialSetup[j][i], j < 2 ? Black : White);
            }
            else
            {
                _data[i][j] = nullptr;
            }
        }
    }
}

Board* MicroShogiBoard::Clone()
{
    MicroShogiBoard *cb = new MicroShogiBoard();
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
    return cb;
}

bool MicroShogiBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
{
    const PieceType destPieceType = _data[newX][newY] != nullptr ? _data[newX][newY]->GetType() : None;
    const bool result = ShogiVariantBoard::Move(oldX, oldY, newX, newY, cl);
    if (result && destPieceType != None)
    {
        _data[newX][newY]->Promote();
    }
    return result;
}

Piece* MicroShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
    return new MicroShogiPiece(pieceType, pieceColour);
}

void MicroShogiBoard::PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y)
{
    _data[x][y] = new MicroShogiPiece(pieceType, pieceColour);
}
