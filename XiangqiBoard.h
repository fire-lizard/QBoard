#pragma once
#include <map>
#include "Board.h"

class XiangqiBoard : public Board
{
public:
	XiangqiBoard();
	~XiangqiBoard() override;
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
	void GetMoves(Piece *piece, int x, int y) override;
	bool Move(int oldX, int oldY, int newX, int newY) override;
	void WriteMove(PieceType pieceType, int x1, int y1, int x2, int y2);
	std::string GetWXF();

protected:

private:
	std::string _wxf;
	int _pieceFiles[5] = {-1, -1, -1, -1, -1};

	const std::map<PieceType, std::string> _pieceToWXF = {
		{Pawn, "P"},
		{Rook, "R"},
		{Knight, "H"},
		{Elephant, "E"},
		{King, "G"},
		{Silver, "A"},
		{Cannon, "C"}
	};

	void CheckCannonDirection(const Piece *piece, int x, int y, Direction direction);

	PieceType _initialSetup[10][9] = {
		{ Rook, Knight, Elephant, Silver, King, Silver, Elephant, Knight, Rook },
		{ None, None, None, None, None, None, None, None, None },
		{ None, Cannon, None, None, None, None, None, Cannon, None },
		{ Pawn, None, Pawn, None, Pawn, None, Pawn, None, Pawn },
		{ None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None },
		{ Pawn, None, Pawn, None, Pawn, None, Pawn, None, Pawn },
		{ None, Cannon, None, None, None, None, None, Cannon, None },
		{ None, None, None, None, None, None, None, None, None },
		{ Rook, Knight, Elephant, Silver, King, Silver, Elephant, Knight, Rook }
	};
};

