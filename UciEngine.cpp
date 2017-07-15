#include "UciEngine.h"

UciEngine::UciEngine()
{
}

UciEngine::~UciEngine()
{
}

EngineType UciEngine::GetType()
{
	return UCI;
}

void UciEngine::StartGame(QString variant)
{
	_moves.clear();
	_process->write("uci\n");
	_process->write("ucinewgame\n");
}

void UciEngine::Move(int x1, int y1, int x2, int y2, char promotion)
{
	_process->write("position startpos moves ");
	for (int index = 0; index < _moves.size(); index++)
	{
		_process->write(_moves[index]);
		_process->write(" ");
	}
	_process->write(AddMove(x1, y1, x2, y2, promotion));
	_process->write("\n");
	_process->write("go movetime 1000\n");
}

QByteArray UciEngine::AddMove(int x1, int y1, int x2, int y2, char promotion)
{
	QByteArray moveStr;
	if (y1 < 10)
	{
		moveStr.push_back(char(x1 + 97));
		moveStr.push_back(QString::number(y1)[0].toLatin1());
		moveStr.push_back(char(x2 + 97));
		moveStr.push_back(QString::number(y2)[0].toLatin1());
	}
	else
	{
		moveStr.push_back(x1);
		moveStr.push_back(y1);
		moveStr.push_back(x2);
		moveStr.push_back(y2);
	}
	if (promotion == 'n' || promotion == 'b' || promotion == 'r' || promotion == 'q' || promotion == '+')
	{
		moveStr.push_back(promotion);
	}
	_moves.push_back(moveStr);
	return moveStr;
}
