#pragma once
#include <string>
#include <vector>
#include <optional>
#include <algorithm>
#include <utility>
#include <tuple>
#include "Common.h"

struct Piece
{
    Piece(PieceType pieceType, PieceColour pieceColour)
    {
        BaseType = pieceType;
        Type = pieceType;
        Colour = pieceColour;
        IsPromoted = false;
        HasMoved = false;
    }
    PieceType BaseType;
    PieceType Type;
    PieceColour Colour;
    bool IsPromoted;
    bool HasMoved;
};

class Board
{
public:
	virtual ~Board();
	virtual void Initialize() = 0;
	virtual Board* Clone() = 0;
    virtual void Promote(int x, int y, PieceType pt = None) = 0;
    virtual void GetMoves(const std::optional<Piece>& piece, int x, int y) = 0;
    virtual bool Move(int oldX, int oldY, int newX, int newY, bool cl = true);
    virtual std::string GetStringCode(int x, int y) const;
    void Clear();
	void RemoveMove(int x, int y);
	void RemoveMoves();
	std::optional<Piece> CreatePiece(PieceType pieceType, PieceColour pieceColour);
    std::vector<std::tuple<int, int, int, int>> GetAllMoves(PieceColour pieceColour);
	std::vector<std::pair<int, int>> Moves() const;
    std::pair<int, int> GetPieceLocation(PieceType pieceType, PieceColour pieceColour) const;
	std::optional<Piece> GetData(int x, int y) const;
	void SetData(int x, int y, const std::optional<Piece>& p);
    std::string GetFEN() const;
	void SetFEN(std::string fen);
	int GetWidth() const;
	int GetHeight() const;
	int MoveCount() const;
	void SetMoveCount(int moveCount);
	bool CheckPosition(int x, int y) const;
	bool HasPiece(PieceType pieceType, PieceColour pieceColour) const;
	std::vector<std::pair<int, int>> GetAttackers(int x, int y);
	std::vector<std::pair<int, int>> GetDefenders(int x, int y);
	bool IsMovePossible(int x, int y);
	bool operator == (const std::string& fen) const;
	bool operator != (const std::string& fen) const;

protected:
	void CheckMove(const std::optional<Piece>& piece, int x, int y);
	void CheckDirection(const std::optional<Piece>& piece, int x, int y, Direction direction);
	void CheckDirection(const std::optional<Piece>& piece, int x, int y, Direction direction, int count);
	bool InBounds(int x, int y, Direction direction) const;
	static void CheckDirectionInc(int &x, int &y, Direction direction);

	std::string _fen;
	std::vector<std::pair<int, int>> _moves;
	int _width = -1;
	int _height = -1;
	int _moveCount = 0;
	std::optional<Piece> _data[19][19];
};
