#pragma once
#include <unordered_map>
#include "KanjiPiece.h"

class ToriShogiPiece : public KanjiPiece
{
public:
    ToriShogiPiece(PieceType pieceType, PieceColour pieceColour);
    ~ToriShogiPiece() override;
    void Promote(PieceType pieceType = None) override;
    std::string StringCode() override;
    std::string KanjiStringCode() override;
    std::string GetImageFileName() const override;
    std::string GetKanjiImageFileName() override;
    std::string GetKanjiImageFileName2() override;
    std::string Description() const;
    static PieceType FromStringCode(const std::string& code);
    static std::string ToStringCode(PieceType piece);
    static std::string PieceType2Description(PieceType pieceType);
    static PieceType Description2PieceType(const std::string& description);
};
