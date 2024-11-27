#include "QianhongEngine.h"

QianhongEngine::QianhongEngine()
{
}

QianhongEngine::~QianhongEngine()
{
}

EngineProtocol QianhongEngine::GetType()
{
	return Qianhong;
}

void QianhongEngine::StartGame(QString variant)
{
}

void QianhongEngine::Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	_process->write(AddMove(x1, y1, x2, y2, promotion));
	_process->write("\n");
	_process->write("ai\n");
}

QByteArray QianhongEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	QByteArray moveStr;
	if (x1 < 10)
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
	_moves.push_back(moveStr);
	return moveStr;
}
