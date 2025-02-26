#pragma once
#include <unordered_map>
#include "Common.h"
#include "KanjiPiece.h"

class WaShogiPiece : public KanjiPiece
{
public:
	WaShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~WaShogiPiece() override;
	void Promote(PieceType pieceType = None) override;
	std::string StringCode() override;
	std::string KanjiStringCode() override;
	std::string GetImageFileName() const override;
	std::string GetKanjiImageFileName() override;
	std::string GetKanjiImageFileName2() override;
	std::string Description() const;
	static PieceType FromStringCode(const std::string& code);
	static std::string PieceType2Description(PieceType pieceType);
	static PieceType Description2PieceType(const std::string& description);
};

