#include "JudkinShogiBoard.h"

JudkinShogiBoard::JudkinShogiBoard()
{
	_width = 6;
	_height = 6;
	JudkinShogiBoard::Initialize();
}

JudkinShogiBoard::~JudkinShogiBoard()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_data[i][j] != nullptr)
			{
				delete _data[i][j];
			}
		}
	}
}

void JudkinShogiBoard::Initialize()
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
