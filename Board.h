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
	virtual bool Move(int oldX, int oldY, int newX, int newY);
	void Clear();
	void RemoveMove(int x, int y);
	std::vector<std::tuple<int, int, int, int>> GetAllMoves(PieceColour pieceColour);
	std::vector<std::pair<int, int>> Moves() const;
	Piece* GetData(int x, int y) const;
	void SetData(int x, int y, Piece *p);
	std::string GetFEN();
	void SetFEN(std::string fen);
	int GetWidth() const;
	int GetHeight() const;
	int MoveCount();
	bool CheckPosition(int x, int y) const;
	void GetAttackers(int x, int y, std::vector<std::pair<int, int>>& vec);
	void GetDefenders(int x, int y, std::vector<std::pair<int, int>>& vec);
	bool operator == (const PieceType other[16][16]) const;

protected:
	void CheckMove(const Piece *piece, int x, int y);
	void CheckDirection(const Piece *piece, int x, int y, Direction direction);
	bool CheckDirectionAux(int x, int y, Direction direction) const;
	static void CheckDirectionInc(int &x, int &y, Direction direction);

	std::string _fen;
	std::vector<std::pair<int, int>> _moves;
	int _width = -1;
	int _height = -1;
	int _moveCount = 0;
	Piece* _data[16][16];

private:
};
