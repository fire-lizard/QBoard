#include "MiniShogiBoard.h"

MiniShogiBoard::MiniShogiBoard()
{
	_width = 5;
	_height = 5;
	MiniShogiBoard::Initialize();
}

MiniShogiBoard::~MiniShogiBoard()
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
