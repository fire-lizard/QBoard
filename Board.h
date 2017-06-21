#pragma once
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
#include "Piece.h"

using namespace std;

class Board
{
public:
	virtual ~Board();
	virtual void Initialize() = 0;
	virtual Board* Clone() = 0;
	virtual Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted = false) = 0;
	virtual void GetMoves(Piece *piece, int x, int y) = 0;
	void RemoveMove(int x, int y);
	vector<tuple<int, int, int, int>> GetAllMoves(PieceColour pieceColour);
	virtual bool Move(int oldX, int oldY, int newX, int newY);
	vector<pair<int, int>> Moves() const;
	Piece* GetData(int x, int y);
	void SetData(int x, int y, Piece *p);
	int GetWidth() const;
	int GetHeight() const;

protected:
	void CheckMove(Piece *piece, int x, int y);
	void CheckDirection(Piece *piece, int x, int y, Direction direction);
	bool CheckDirectionAux(int x, int y, Direction direction) const;
	static void CheckDirectionInc(int &x, int &y, Direction direction);

	vector<pair<int, int>> _moves;
	int _width;
	int _height;
	Piece* _data[12][12];

private:
};
