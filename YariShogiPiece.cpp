#include "YariShogiPiece.h"

YariShogiPiece::YariShogiPiece(PieceType pieceType, PieceColour pieceColour) : ShogiPiece(pieceType, pieceColour)
{
}

YariShogiPiece::~YariShogiPiece()
{
}

void YariShogiPiece::Promote(PieceType pieceType)
{
    _isPromoted = true;
    switch (_pieceType)
    {
    case YariKnight:
        _pieceType = YariGold;
        break;
    case YariRook:
        _pieceType = Rook;
        break;
    case YariBishop:
        _pieceType = YariGold;
        break;
    case Pawn:
        _pieceType = YariSilver;
        break;
    default:
        break;
    }
}

std::string YariShogiPiece::StringCode()
{
    switch (_pieceType)
    {
    case YariKnight:
        return "N";
    case YariRook:
        return "Y";
    case YariBishop:
        return "B";
    case YariGold:
        return "G";
    case YariSilver:
        return "S";
    default:
        return ShogiPiece::StringCode();
    }
}

PieceType YariShogiPiece::FromStringCode(const std::string& code)
{
    static const std::unordered_map<std::string, PieceType> codeToPieceType = {
        {"N", YariKnight},
        {"Y", YariRook},
        {"B", YariBishop},
        {"G", YariGold},
        {"S", YariSilver}
    };

    const auto it = codeToPieceType.find(code);
    return it != codeToPieceType.end() ? it->second : ShogiPiece::FromStringCode(code);
}
