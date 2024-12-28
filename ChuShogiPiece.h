#pragma once
#include "ShogiPiece.h"
#include "Common.h"

class ChuShogiPiece : public ShogiPiece
{
public:
	ChuShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~ChuShogiPiece() override;
	void Promote(PieceType pieceType = None) override;
	void MoveOnce();
	void EndMove();
	bool HasMovedOnce() const;
	std::string StringCode() override;
	std::string AsianStringCode() override;
	std::string GetJapaneseImageFileName() override;

protected:
	static void replaceSubstring(std::string& str, const std::string& from, const std::string& to);

private:
	bool _hasMovedOnce;
};
