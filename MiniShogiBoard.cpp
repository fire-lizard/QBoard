#include "MiniShogiBoard.h"

MiniShogiBoard::MiniShogiBoard()
{
	_width = 5;
	_height = 5;
	MiniShogiBoard::Initialize();
}

MiniShogiBoard::~MiniShogiBoard()
{
}

void MiniShogiBoard::Initialize()
{
	_capturedPieces.clear();
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				_data[i][j] = new ShogiPiece(_initialSetup[j][i], j < 2 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
			}
		}
	}
}

Board* MiniShogiBoard::Clone()
{
    MiniShogiBoard *cb = new MiniShogiBoard();
    for (int i = 0; i < GetWidth(); i++)
    {
        for (int j = 0; j < GetHeight(); j++)
        {
            const Piece *p = GetData(i, j);
            cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
        }
    }
    for (const auto& capturedPiece: _capturedPieces)
    {
        cb->AddCapturedPiece(capturedPiece.second, capturedPiece.first);
    }
    cb->SetMoveCount(_moveCount);
    return cb;
}
