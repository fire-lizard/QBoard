#include "UciEngine.h"

UciEngine::UciEngine()
{
	_fen = CHESSFEN;
}

UciEngine::~UciEngine()
{
}

EngineProtocol UciEngine::GetType()
{
	return UCI;
}

void UciEngine::StartGame(QString variant)
{
	_moves.clear();
	_process->write("uci\n");
	_process->write("isready\n");
	_process->write("ucinewgame\n");
}

void UciEngine::Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	_process->write(QByteArray::fromStdString("position fen " + _fen + " moves "));
	for (auto& _move : _moves)
	{
		_process->write(_move);
		_process->write(" ");
    }
	_process->write(AddMove(x1, y1, x2, y2, promotion));
	_process->write("\n");
	_process->write("go depth 10\n");
}

QByteArray UciEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	QByteArray moveStr;
	if (y1 < 10)
	{
		moveStr.push_back(static_cast<char>(x1 + 97));
		moveStr.push_back(QString::number(y1)[0].toLatin1());
		moveStr.push_back(static_cast<char>(x2 + 97));
		moveStr.push_back(QString::number(y2)[0].toLatin1());
	}
	else
	{
		moveStr.push_back(x1);
		moveStr.push_back(y1);
		moveStr.push_back(x2);
		moveStr.push_back(y2);
	}
	if (promotion == 'n' || promotion == 'b' || promotion == 'r' || promotion == 'q')
	{
		moveStr.push_back(promotion);
	}
	_moves.push_back(moveStr);
	return moveStr;
}
