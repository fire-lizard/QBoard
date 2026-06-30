#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Common.h"

class StringManager
{
public:
    static std::string PieceType2Description(GameVariant gameVariant, PieceType pieceType);
    static std::string PieceType2KanjiCode(GameVariant gameVariant, PieceType pieceType, PieceColour pieceColour);
    static std::string PieceType2GHCode(GameVariant gameVariant, PieceType pieceType, PieceType basePieceType);
    static PieceType Description2PieceType(GameVariant gameVariant, const std::string& description);
    static PieceType StringCode2PieceType(GameVariant gameVariant, const std::string& stringCode);
    static std::string PieceType2Description(PieceType pieceType);
    static std::string KoShogiPieceType2Description(PieceType pieceType);
    static std::string ToriShogiPieceType2Description(PieceType pieceType);
    static std::string WaShogiPieceType2Description(PieceType pieceType);
    static std::string WhaleShogiPieceType2Description(PieceType pieceType);
    static std::pair<std::unordered_map<PieceType, std::string>, std::vector<PieceType>> GetOrderData(GameVariant gameVariant);
private:
    static PieceType Description2PieceType(const std::string& description);
    static PieceType KoShogiDescription2PieceType(const std::string& description);
    static PieceType ToriShogiDescription2PieceType(const std::string& description);
    static PieceType WaShogiDescription2PieceType(const std::string& description);
    static PieceType WhaleShogiDescription2PieceType(const std::string& description);
};
