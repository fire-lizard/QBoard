#pragma once
#include <string>
#include "Common.h"

class StringManager
{
public:
    static std::string PieceType2Description(GameVariant gameVariant, PieceType pieceType);
    static PieceType Description2PieceType(GameVariant gameVariant, const std::string& description);
private:
    static std::string PieceType2Description(PieceType pieceType);
    static std::string KoShogiPieceType2Description(PieceType pieceType);
    static PieceType Description2PieceType(const std::string& description);
    static PieceType KoShogiDescription2PieceType(const std::string& description);
};
