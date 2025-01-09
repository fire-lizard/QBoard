#include "UsiEngine.h"

UsiEngine::UsiEngine()
{
	_fen = SHOGIFEN;
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
	_process->write("isready\n");
	_process->write("usinewgame\n");
}

void UsiEngine::Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
    _process->write("position startpos moves ");
	for (auto& _move : _moves)
	{
		_process->write(_move);
		_process->write(" ");
    }
	_process->write(AddMove(x1, y1, x2, y2, promotion));
	_process->write("\n");
	_process->write("go depth 10\n");
}

QByteArray UsiEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	QByteArray moveStr;
	if (y1 == '*')
	{
		moveStr.push_back(x1);
		moveStr.push_back(y1);
		moveStr.push_back(QString::number(x2)[0].toLatin1());
		moveStr.push_back(static_cast<char>(y2 + 97));
	}
	else if (x1 < 10)
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
