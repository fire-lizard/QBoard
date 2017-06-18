#ifndef CHUSHOGIBOARD_H
#define CHUSHOGIBOARD_H
#include "Board.h"
#include "ChuShogiPiece.h"

using namespace std;

class ChuShogiBoard : public Board
{
public:
	ChuShogiBoard();
	virtual ~ChuShogiBoard();
	void Initialize() override;
	void GetMoves(Piece *piece, int x, int y) override;

protected:

private:

	PieceType _initialSetup[12][12] = {
	{Lance, FerociousLeopard, Copper, Silver, Gold, King, Elephant, Gold, Silver, Copper, FerociousLeopard, Lance},
	{Cannon, None, Bishop, None, BlindTiger, Kylin, Phoenix, BlindTiger, None, Bishop, None, Cannon},
	{SideMover, VerticalMover, Rook, DragonHorse, DragonKing, Lion, Queen, DragonKing, DragonHorse, Rook, VerticalMover, SideMover},
	{Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
	{None, None, None, Cobra, None, None, None, None, Cobra, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, Cobra, None, None, None, None, Cobra, None, None, None},
	{Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
	{SideMover, VerticalMover, Rook, DragonHorse, DragonKing, Lion, Queen, DragonKing, DragonHorse, Rook, VerticalMover, SideMover},
	{Cannon, None, Bishop, None, BlindTiger, Kylin, Phoenix, BlindTiger, None, Bishop, None, Cannon},
	{Lance, FerociousLeopard, Copper, Silver, Gold, King, Elephant, Gold, Silver, Copper, FerociousLeopard, Lance}
	};
};

#endif // CHUSHOGIBOARD_H
