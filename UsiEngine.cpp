#include "UsiEngine.h"

UsiEngine::UsiEngine()
{
}

UsiEngine::~UsiEngine()
{
}

EngineProtocol UsiEngine::GetType()
{
	return USI;
}

void UsiEngine::StartGame(QString variant)
{
	_moves.clear();
	_process->write("usi\n");
	_process->write("usinewgame\n");
}

void UsiEngine::Move(int x1, int y1, int x2, int y2, char promotion)
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

QByteArray UsiEngine::AddMove(int x1, int y1, int x2, int y2, char promotion)
{
	QByteArray moveStr;
	if (x1 < 10)
	{
		moveStr.push_back(QString::number(x1)[0].toLatin1());
		moveStr.push_back(static_cast<char>(y1 + 97));
		moveStr.push_back(QString::number(x2)[0].toLatin1());
		moveStr.push_back(static_cast<char>(y2 + 97));
	}
	else
	{
		moveStr.push_back(x1);
		moveStr.push_back(y1);
		moveStr.push_back(x2);
		moveStr.push_back(y2);
	}
	if (promotion == '+')
	{
		moveStr.push_back(promotion);
	}
	_moves.push_back(moveStr);
	return moveStr;
}
