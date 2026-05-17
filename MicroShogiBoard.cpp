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
    _moveCount = 0;
    _capturedPieces.clear();
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                SetData(i, j, new Piece(_initialSetup[j][i], j < 2 ? Black : White));
            }
            else
            {
                SetData(i, j, nullptr);
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
            cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->Type, p->Colour) : nullptr);
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
    const PieceType destPieceType = GetData(newX, newY) != nullptr ? GetData(newX, newY)->Type : None;
    const bool result = ShogiVariantBoard::Move(oldX, oldY, newX, newY, cl);
    if (result && destPieceType != None)
    {
        Promote(newX, newY, None);
    }
    return result;
}

void MicroShogiBoard::Promote(int x, int y, PieceType pt)
{
    Promote(GetData(x, y), pt);
}

void MicroShogiBoard::Promote(Piece *piece, PieceType pt)
{
    if (piece != nullptr)
    {
        PieceType pieceType = None;
        switch (piece->Type)
        {
        case Rook:
            pieceType = Gold;
            break;
        case Bishop:
            pieceType = Tokin;
            break;
        case Tokin:
            pieceType = Bishop;
            break;
        case Lance:
            pieceType = Silver;
            break;
        case Silver:
            pieceType = Lance;
            break;
        case Knight:
            pieceType = Pawn;
            break;
        case Gold:
            pieceType = Rook;
            break;
        case Pawn:
            pieceType = Knight;
            break;
        default:
            break;
        }
        if (pieceType != None)
        {
            piece->Type = pieceType;
        }
    }
}
