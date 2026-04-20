#include "KyotoShogiPiece.h"

KyotoShogiPiece::KyotoShogiPiece(PieceType pieceType, PieceColour pieceColour) : ShogiPiece(pieceType, pieceColour)
{
}

KyotoShogiPiece::~KyotoShogiPiece()
{
}

void KyotoShogiPiece::Promote(PieceType pieceType)
{
    switch (_pieceType)
    {
    case Rook:
        _pieceType = Pawn;
        break;
    case Bishop:
        _pieceType = Silver;
        break;
    case Tokin:
        _pieceType = Lance;
        break;
    case Lance:
        _pieceType = Tokin;
        break;
    case Silver:
        _pieceType = Bishop;
        break;
    case Knight:
        _pieceType = Gold;
        break;
    case Gold:
        _pieceType = Knight;
        break;
    case Pawn:
        _pieceType = Rook;
        break;
    default:
        break;
    }
}

std::string KyotoShogiPiece::GetImageFileName() const
{
    const std::string colour = _pieceColour == White ? "B" : "W";
    switch (_pieceType)
    {
    case King:
        return "King_" + colour + ".png";
    case Rook:
        return "Rook_" + colour + ".png";
    case Bishop:
        return "Bishop_" + colour + ".png";
    case Lance:
        return "Lance_" + colour + ".png";
    case Gold:
        return "Gold_" + colour + ".png";
    case Tokin:
        return "Tokin_" + colour + ".png";
    case Silver:
        return "Silver_" + colour + ".png";
    case Pawn:
        return "Pawn_" + colour + ".png";
    case Knight:
        return "Knight_" + colour + ".png";
    default:
        return "";
    }
}

std::string KyotoShogiPiece::GetKanjiImageFileName()
{
    const std::string colour = _pieceColour == White ? "B" : "W";
    switch (_pieceType)
    {
    case King:
        return "King_F" + colour + ".png";
    case Rook:
        return "Rook_F" + colour + ".png";
    case Bishop:
        return "Bishop_F" + colour + ".png";
    case Lance:
        return "Lance_F" + colour + ".png";
    case Gold:
        return "Gold_F" + colour + ".png";
    case Tokin:
        return "Tokin_F" + colour + ".png";
    case Silver:
        return "Silver_F" + colour + ".png";
    case Pawn:
        return "Pawn_F" + colour + ".png";
    case Knight:
        return "Knight_F" + colour + ".png";
    default:
        return "";
    }
}

std::string KyotoShogiPiece::GetKanjiImageFileName2()
{
    const std::string colour = _pieceColour == White ? "B" : "W";
    switch (_pieceType)
    {
    case King:
        return "King_I" + colour + ".png";
    case Rook:
        return "Rook_I" + colour + ".png";
    case Bishop:
        return "Bishop_I" + colour + ".png";
    case Lance:
        return "Lance_I" + colour + ".png";
    case Gold:
        return "Gold_I" + colour + ".png";
    case Tokin:
        return "Tokin_I" + colour + ".png";
    case Silver:
        return "Silver_I" + colour + ".png";
    case Pawn:
        return "Pawn_I" + colour + ".png";
    case Knight:
        return "Knight_I" + colour + ".png";
    default:
        return "";
    }
}
