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

std::string YariShogiPiece::PieceType2Description(PieceType pieceType)
{
    switch (pieceType)
    {
    case YariKnight: return "Yari Knight";
    case YariRook: return "Yari Rook";
    case YariBishop: return "Yari Bishop";
    case YariGold: return "Yari Gold";
    case YariSilver: return "Yari Silver";
    default: return Piece::PieceType2Description(pieceType);
    }
}

PieceType YariShogiPiece::Description2PieceType(const std::string& description)
{
    if (description == "Yari Knight")    return YariKnight;
    if (description == "Yari Rook")      return YariRook;
    if (description == "Yari Bishop")    return YariBishop;
    if (description == "Yari Gold")      return YariGold;
    if (description == "Yari Silver")    return YariSilver;
    return Piece::Description2PieceType(description);
}
