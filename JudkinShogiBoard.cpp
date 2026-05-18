#include "JudkinShogiBoard.h"

JudkinShogiBoard::JudkinShogiBoard()
{
	_width = 6;
	_height = 6;
	JudkinShogiBoard::Initialize();
}

JudkinShogiBoard::~JudkinShogiBoard()
{
}

void JudkinShogiBoard::Initialize()
{
    _moveCount = 0;
    _capturedPieces.clear();
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
                SetData(i, j, Piece(_initialSetup[j][i], j < 2 ? Black : White));
			}
			else
			{
				SetData(i, j, std::nullopt);
			}
		}
	}
}

Board* JudkinShogiBoard::Clone()
{
    JudkinShogiBoard *cb = new JudkinShogiBoard();
    for (int i = 0; i < GetWidth(); i++)
    {
        for (int j = 0; j < GetHeight(); j++)
        {
            const std::optional<Piece> p = GetData(i, j);
            cb->SetData(i, j, p != std::nullopt ? cb->CreatePiece(p->Type, p->Colour) : std::nullopt);
        }
    }
    for (const auto& capturedPiece: _capturedPieces)
    {
        cb->AddCapturedPiece(capturedPiece.second, capturedPiece.first);
    }
    cb->SetMoveCount(_moveCount);
    return cb;
}
