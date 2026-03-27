#include "WhaleShogiPiece.h"

WhaleShogiPiece::WhaleShogiPiece(PieceType pieceType, PieceColour pieceColour) : Piece(pieceType, pieceColour)
{
}

WhaleShogiPiece::~WhaleShogiPiece()
{
}

void WhaleShogiPiece::Promote(PieceType pieceType)
{
}

std::string WhaleShogiPiece::StringCode()
{
    switch (_pieceType)
    {
    case King:
        return "W";
    case GreyWhale:
        return "G";
    case Porpoise:
        return "P";
    case DragonKing:
        return "K";
    case Narwhal:
        return "N";
    case Humpback:
        return "H";
    case BlueWhale:
        return "B";
    case Pawn:
        return "D";
    default:
        return "";
    }
}

PieceType WhaleShogiPiece::FromStringCode(const std::string& code)
{
    static const std::unordered_map<std::string, PieceType> codeToPieceType = {
        {"W", King},
        {"G", GreyWhale},
        {"P", Porpoise},
        {"K", DragonKing},
        {"N", Narwhal},
        {"H", Humpback},
        {"B", BlueWhale},
        {"D", Pawn}
    };

    const auto it = codeToPieceType.find(code);
    return it != codeToPieceType.end() ? it->second : None;
}

std::string WhaleShogiPiece::ToStringCode(PieceType piece)
{
    static const std::unordered_map<PieceType, std::string> pieceTypeToCode = {
    { King,           "W" },
    { GreyWhale,      "G" },
    { Porpoise,       "P" },
    { DragonKing,     "K" },
    { Narwhal,        "N" },
    { Humpback,       "H" },
    { BlueWhale,      "B" },
    { Pawn,           "D" }
    };

    const auto it = pieceTypeToCode.find(piece);
    return it != pieceTypeToCode.end() ? it->second : "";
}

std::string WhaleShogiPiece::Description() const
{
    return PieceType2Description(_pieceType);
}

std::string WhaleShogiPiece::PieceType2Description(PieceType pieceType)
{
    switch (pieceType)
    {
    case King: return "White Whale";
    case GreyWhale: return "Grey Whale";
    case Porpoise: return "Porpoise";
    case DragonKing: return "Killer Whale";
    case Narwhal: return "Narwhal";
    case Humpback: return "Humpback";
    case BlueWhale: return "Blue Whale";
    case Pawn: return "Dolphin";
    default: return "";
    }
}

PieceType WhaleShogiPiece::Description2PieceType(const std::string& description)
{
    if (description == "White Whale")  return King;
    if (description == "Grey Whale")   return GreyWhale;
    if (description == "Porpoise")     return Porpoise;
    if (description == "Killer Whale") return DragonKing;
    if (description == "Narwhal")      return Narwhal;
    if (description == "Humpback")     return Humpback;
    if (description == "Blue Whale")   return BlueWhale;
    if (description == "Dolphin")      return Pawn;
    return None;
}

std::string WhaleShogiPiece::GetImageFileName() const
{
    std::string colour = _pieceColour == White ? "B" : "W";
    switch (_pieceType)
    {
    case King:
        return colour + "WhWhale.png";
    case GreyWhale:
        return colour + "GrWhale.png";
    case Porpoise:
        return colour + "Porpoise.png";
    case DragonKing:
        return colour + "KWhale.png";
    case Narwhal:
        return colour + "Narwhal.png";
    case Humpback:
        return colour + "HBwhale.png";
    case BlueWhale:
        return colour + "BWhale.png";
    case Pawn:
        return colour + "Dolphin.png";
    default:
        return "";
    }
}
