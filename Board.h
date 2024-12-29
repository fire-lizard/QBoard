#pragma once
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
#include "Piece.h"

class Board
{
public:
	virtual ~Board();
	virtual void Initialize() = 0;
	virtual Board* Clone() = 0;
	virtual Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) = 0;
	virtual void GetMoves(Piece *piece, int x, int y) = 0;
    void RemoveMove(int x, int y);
	std::vector<std::tuple<int, int, int, int>> GetAllMoves(PieceColour pieceColour);
	virtual bool Move(int oldX, int oldY, int newX, int newY);
	std::vector<std::pair<int, int>> Moves() const;
	Piece* GetData(int x, int y) const;
	void SetData(int x, int y, Piece *p);
	int GetWidth() const;
	int GetHeight() const;
	bool CheckPosition(int x, int y) const;

protected:
	void CheckMove(const Piece *piece, int x, int y);
	void CheckDirection(const Piece *piece, int x, int y, Direction direction);
	bool CheckDirectionAux(int x, int y, Direction direction) const;
	static void CheckDirectionInc(int &x, int &y, Direction direction);

	std::vector<std::pair<int, int>> _moves;
	int _width = -1;
	int _height = -1;
	int _moveCount = 0;
	Piece* _data[12][12];

private:
};
