#pragma once
#include <unordered_map>
#include "ShogiPiece.h"
#include "Common.h"

class ChuShogiPiece : public ShogiPiece
{
public:
	ChuShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~ChuShogiPiece() override;
	void Promote(PieceType pieceType = None) override;
	std::string StringCode() override;
	std::string KanjiStringCode() override;
	std::string GetKanjiImageFileName() override;
	std::string GetKanjiImageFileName2() override;
	virtual std::string GetMnemonicImageFileName() const;
	static PieceType FromStringCode(const std::string& code);

protected:
	static void replaceSubstring(std::string& str, const std::string& from, const std::string& to);
};
