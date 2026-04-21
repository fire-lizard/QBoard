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

std::string YariShogiPiece::ToStringCode(PieceType piece)
{
    static const std::unordered_map<PieceType, std::string> pieceTypeToCode = {
        {YariKnight, "N"},
        {YariRook, "Y"},
        {YariBishop, "B"},
        {YariGold, "G"},
        {YariSilver, "S"}
    };

    const auto it = pieceTypeToCode.find(piece);
    return it != pieceTypeToCode.end() ? it->second : ShogiPiece::ToStringCode(piece);
}

std::string YariShogiPiece::Description() const
{
    return PieceType2Description(_pieceType);
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

std::string YariShogiPiece::GetImageFileName() const
{
    std::string colour = _pieceColour == White ? "" : "Flip";
    switch (_pieceType)
    {
    case King:
        return "King" + colour + ".png";
    case Rook:
        return "RookP" + colour + ".png";
    case Pawn:
        return "Pawn" + colour + ".png";
    case YariKnight:
        return "Knight" + colour + ".png";
    case YariRook:
        return "Rook" + colour + ".png";
    case YariBishop:
        return "Bishop" + colour + ".png";
    case YariGold:
        return "Gold" + colour + ".png";
    case YariSilver:
        return "Silver" + colour + ".png";
    default:
        return "";
    }
}
