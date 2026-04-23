#include "GrandeAcedrexPiece.h"

GrandeAcedrexPiece::GrandeAcedrexPiece(PieceType pieceType, PieceColour pieceColour) : ChessPiece(pieceType, pieceColour)
{
}

GrandeAcedrexPiece::~GrandeAcedrexPiece()
{
}

void GrandeAcedrexPiece::Promote(PieceType pieceType)
{
    _isPromoted = true;
    _pieceType = pieceType;
}

std::string GrandeAcedrexPiece::StringCode()
{
    switch (_pieceType)
    {
    case King:
        return "K";
    case Aanca:
        return "A";
    case Rook:
        return "R";
    case Bishop:
        return "C";
    case Giraffe:
        return "G";
    case Unicorn:
        return "U";
    case Lion:
        return "L";
    case Pawn:
        return "P";
    default:
        return "";
    }
}

PieceType GrandeAcedrexPiece::FromStringCode(const std::string& code)
{
    static const std::unordered_map<std::string, PieceType> codeToPieceType = {
        {"K", King},
        {"A", Aanca},
        {"R", Rook},
        {"C", Bishop},
        {"G", Giraffe},
        {"U", Unicorn},
        {"L", Lion},
        {"P", Pawn}
    };

    const auto it = codeToPieceType.find(code);
    return it != codeToPieceType.end() ? it->second : None;
}

std::string GrandeAcedrexPiece::PieceType2Description(PieceType pieceType)
{
    switch (pieceType)
    {
    case Aanca: return "Aanca";
    case Bishop: return "Crocodile";
    case Giraffe: return "Giraffe";
    default: return Piece::PieceType2Description(pieceType);
    }
}

PieceType GrandeAcedrexPiece::Description2PieceType(const std::string& description)
{
    if (description == "Aanca")      return Aanca;
    if (description == "Crocodile")  return Bishop;
    if (description == "Giraffe")    return Giraffe;
    return Piece::Description2PieceType(description);
}

std::string GrandeAcedrexPiece::GetImageFileName() const
{
    const std::string colour = _pieceColour == White ? "White" : "Black";
    switch (_pieceType)
    {
    case Aanca:
        return colour + "Hawk.png";
    case Giraffe:
        return colour + "Camel.png";
    default:
        return ChessPiece::GetImageFileName();
    }
}
