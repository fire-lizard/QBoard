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
                SetData(i, j, Piece(_initialSetup[j][i], j < 2 ? Black : White));
            }
            else
            {
                SetData(i, j, std::nullopt);
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
            const std::optional<Piece> p = GetData(i, j);
            cb->SetData(i, j, p != std::nullopt ? std::make_optional<Piece>(p->Type, p->Colour) : std::nullopt);
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
    const PieceType destPieceType = GetData(newX, newY) != std::nullopt ? GetData(newX, newY)->Type : None;
    const bool result = ShogiVariantBoard::Move(oldX, oldY, newX, newY, cl);
    if (result && destPieceType != None)
    {
        Promote(newX, newY);
    }
    return result;
}

void MicroShogiBoard::Promote(int x, int y, PieceType pt)
{
    if (_data[x][y] != std::nullopt)
    {
        PieceType pieceType = None;
        switch (_data[x][y]->Type)
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
            _data[x][y]->Type = pieceType;
        }
    }
}
