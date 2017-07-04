#include "UsiEngine.h"

UsiEngine::UsiEngine()
{
}

UsiEngine::~UsiEngine()
{
}

EngineType UsiEngine::GetType()
{
	return USI;
}

void UsiEngine::Move(int x1, int y1, int x2, int y2, char promotion)
{
	_process->write("position startpos moves ", 24);
	for (int index = 0; index < _moves.size(); index++)
	{
		_process->write(_moves[index]);
		_process->write(" ", 1);
	}
	_process->write(AddMove(x1, y1, x2, y2, promotion));
	_process->write("\n", 1);
	_process->write("go movetime 1000\n", 17);
}

QByteArray UsiEngine::AddMove(int x1, int y1, int x2, int y2, char promotion)
{
	QByteArray moveStr;
	moveStr.push_back(QString::number(x1)[0].toLatin1());
	moveStr.push_back(char(y1 + 97));
	moveStr.push_back(QString::number(x2)[0].toLatin1());
	moveStr.push_back(char(y2 + 97));
	if (promotion == 'n' || promotion == 'b' || promotion == 'r' || promotion == 'q' || promotion == '+')
	{
		moveStr.push_back(promotion);
	}
	_moves.push_back(moveStr);
	return moveStr;
}
