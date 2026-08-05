#include "KyotoShogiBoard.h"

KyotoShogiBoard::KyotoShogiBoard()
{
    _width = 5;
    _height = 5;
    KyotoShogiBoard::Initialize();
}

KyotoShogiBoard::~KyotoShogiBoard()
{
}

void KyotoShogiBoard::Initialize()
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

Board* KyotoShogiBoard::Clone()
{
    KyotoShogiBoard *cb = new KyotoShogiBoard();
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

PieceType KyotoFlip(PieceType pieceType)
{
    switch (pieceType)
    {
    case Rook:
        return Pawn;
    case Bishop:
        return Silver;
    case Tokin:
        return Lance;
    case Lance:
        return Tokin;
    case Silver:
        return Bishop;
    case Knight:
        return Gold;
    case Gold:
        return Knight;
    case Pawn:
        return Rook;
    default:
        return None;
    }
}

void KyotoShogiBoard::Promote(int x, int y, PieceType pt)
{
    if (GetData(x, y) != std::nullopt)
    {
        const PieceType pieceType = KyotoFlip(_data[x][y]->Type);
        if (pieceType != None)
        {
            _data[x][y]->Type = pieceType;
        }
    }
}

// Kyoto's tokin needs a letter of its own. Board::GetStringCode writes it as "+P", which the engines
// read as the tokin's own other face (a rook), and which the drop relay truncates to a bare '+'.
std::string KyotoShogiBoard::GetStringCode(int x, int y) const
{
    if (GetData(x, y) != std::nullopt && GetData(x, y)->Type == Tokin) return "T";
    return ShogiBoard::GetStringCode(x, y);
}
