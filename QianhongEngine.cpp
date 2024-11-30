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
	moveStr.push_back('P');
	moveStr.push_back('L');
	moveStr.push_back('A');
	moveStr.push_back('Y');
	moveStr.push_back(' ');
	moveStr.push_back(x1 + 65);
	moveStr.push_back(y1 + '0');
	moveStr.push_back('-');
	moveStr.push_back(x2 + 65);
	moveStr.push_back(y2 + '0');
	_moves.push_back(moveStr);
	return moveStr;
}
