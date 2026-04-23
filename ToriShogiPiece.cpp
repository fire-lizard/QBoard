#include "ToriShogiPiece.h"

ToriShogiPiece::ToriShogiPiece(PieceType pieceType, PieceColour pieceColour) : KanjiPiece(pieceType, pieceColour)
{
}

ToriShogiPiece::~ToriShogiPiece()
{
}

void ToriShogiPiece::Promote(PieceType pieceType)
{
    _isPromoted = true;
    switch (_pieceType)
    {
    case Falcon:
        _pieceType = Eagle;
        break;
    case Pawn:
        _pieceType = Goose;
        break;
    default:
        break;
    }
}

std::string ToriShogiPiece::StringCode()
{
    switch (_pieceType)
    {
    case King:
        return "K";
    case Falcon:
        return "F";
    case Eagle:
        return "+F";
    case Crane:
        return "C";
    case Pheasant:
        return "P";
    case LeftQuail:
        return "L";
    case RightQuail:
        return "R";
    case Pawn:
        return "S";
    case Goose:
        return "+S";
    default:
        return "";
    }
}

PieceType ToriShogiPiece::FromStringCode(const std::string& code)
{
    static const std::unordered_map<std::string, PieceType> codeToPieceType = {
        {"K", King},
        {"F", Falcon},
        {"+F", Eagle},
        {"C", Crane},
        {"P", Pheasant},
        {"L", LeftQuail},
        {"R", RightQuail},
        {"S", Pawn},
        {"+S", Goose}
    };

    const auto it = codeToPieceType.find(code);
    return it != codeToPieceType.end() ? it->second : None;
}

std::string ToriShogiPiece::PieceType2Description(PieceType pieceType)
{
    switch (pieceType)
    {
    case King: return "Phoenix";
    case Falcon: return "Falcon";
    case Eagle: return "Eagle";
    case Crane: return "Crane";
    case Pheasant: return "Pheasant";
    case LeftQuail: return "Left Quail";
    case RightQuail: return "Right Quail";
    case Pawn: return "Swallow";
    case Goose: return "Goose";
    default: return "";
    }
}

PieceType ToriShogiPiece::Description2PieceType(const std::string& description)
{
    if (description == "Phoenix")     return King;
    if (description == "Falcon")      return Falcon;
    if (description == "Eagle")       return Eagle;
    if (description == "Crane")       return Crane;
    if (description == "Pheasant")    return Pheasant;
    if (description == "Left Quail")  return LeftQuail;
    if (description == "Right Quail") return RightQuail;
    if (description == "Swallow")     return Pawn;
    if (description == "Goose")       return Goose;
    return None;
}

std::string ToriShogiPiece::KanjiStringCode()
{
    switch (_pieceType)
    {
    case King:
        return "鵬";
    case Falcon:
        return "鷹";
    case Eagle:
        return "鵰";
    case Crane:
        return "鶴";
    case Pheasant:
        return "雉";
    case LeftQuail:
    case RightQuail:
        return "鶉";
    case Pawn:
        return "燕";
    case Goose:
        return "鴈";
    default:
        return "";
    }
}

std::string ToriShogiPiece::GetImageFileName() const
{
    std::string colour = _pieceColour == White ? "B" : "W";
    switch (_pieceType)
    {
    case King:
        return colour + "Phoenix.png";
    case Falcon:
        return colour + "Falcon.png";
    case Eagle:
        return colour + "Eagle.png";
    case Crane:
        return colour + "Crane.png";
    case Pheasant:
        return colour + "Pheasant.png";
    case LeftQuail:
        return colour + "LQuail.png";
    case RightQuail:
        return colour + "RQuail.png";
    case Pawn:
        return colour + "Swallow.png";
    case Goose:
        return colour + "Goose.png";
    default:
        return "";
    }
}

std::string ToriShogiPiece::GetKanjiImageFileName()
{
    std::string colour = _pieceColour == White ? "B" : "W";
    switch (_pieceType)
    {
    case King:
        return colour + "PhoenixJ.png";
    case Falcon:
        return colour + "FalconJ.png";
    case Eagle:
        return colour + "EagleJ.png";
    case Crane:
        return colour + "CraneJ.png";
    case Pheasant:
        return colour + "PheasantJ.png";
    case LeftQuail:
        return colour + "LQuailJ.png";
    case RightQuail:
        return colour + "RQuailJ.png";
    case Pawn:
        return colour + "SwallowJ.png";
    case Goose:
        return colour + "GooseJ.png";
    default:
        return "";
    }
}

std::string ToriShogiPiece::GetKanjiImageFileName2()
{
    std::string colour = _pieceColour == White ? "" : "Flip";
    switch (_pieceType)
    {
    case King:
        return "DaPeng" + colour + ".png";
    case Falcon:
        return "Hawk" + colour + ".png";
    case Eagle:
        return "MountainHawkP" + colour + ".png";
    case Crane:
        return "Crane" + colour + ".png";
    case Pheasant:
        return "Pheasant" + colour + ".png";
    case LeftQuail:
        return "L-Quail" + colour + ".png";
    case RightQuail:
        return "R-Quail" + colour + ".png";
    case Pawn:
        return "Swallow" + colour + ".png";
    case Goose:
        return "WildGooseP" + colour + ".png";
    default:
        return "";
    }
}
