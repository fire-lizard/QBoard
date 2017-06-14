#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <utility>
#include "Piece.h"

using namespace std;

class Board
{
    public:
        virtual ~Board();
        virtual void GetMoves(Piece *piece, int x, int y) = 0;
        vector<pair<int,int>> GetAllMoves(PieceColour colour);
        virtual bool Move(int oldX, int oldY, int newX, int newY);
        vector<pair<int,int>> Moves() const;
        Piece* GetData(int x, int y);
        int GetWidth() const;
        int GetHeight() const;

    protected:
        void CheckMove(Piece *piece, int x, int y);
        void CheckKingMove(Piece *piece, int x, int y);
        void CheckDirection(Piece *piece, int x, int y, Direction direction);
        bool CheckDirectionAux(int x, int y, Direction direction) const;
		static void CheckDirectionInc(int &x, int &y, Direction direction);

        vector<pair<int,int>> _moves;
        vector<pair<int,int>> _opponentMoves;
        int _width;
        int _height;
        Piece* _data[12][12];

    private:
};

#endif // BOARD_H
