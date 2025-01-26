#include "WbEngine.h"

WbEngine::WbEngine()
{
}

WbEngine::~WbEngine()
{
	Quit();
}

EngineProtocol WbEngine::GetType()
{
	return XBoard;
}

void WbEngine::SetFEN(std::string fen)
{
	if (_setboard)
	{
		WriteToProcess(QByteArray::fromStdString("setboard " + fen + "\n"));
	}
	_fen = std::move(fen);
}

void WbEngine::Edit(const Board* board)
{
	PieceColour pieceColour = White;
	WriteToProcess("edit\n");
	//WriteToProcess("#\n");
	for (int j = 0; j < board->GetHeight(); j++)
	{
		for (int i = 0; i < board->GetWidth(); i++)
		{
			Piece* p = board->GetData(i, j);
			char letter = i + 97;
			int number = board->GetHeight() - j;
			std::string str;
			if (p != nullptr)
			{
				PieceColour newPieceColour = p->GetColour();
				if (newPieceColour != pieceColour)
				{
					WriteToProcess("c\n");
					pieceColour = newPieceColour;
				}
				str += p->StringCode();
			}
			else
			{
				str += "x";
			}
			str.push_back(letter);
			str += std::to_string(number);
			str.push_back('\n');
			WriteToProcess(QByteArray::fromStdString(str));
		}
	}
	WriteToProcess(".\n");
}

void WbEngine::StartGame(QString variant)
{
	_moves.clear();
	WriteToProcess("xboard\n");
	WriteToProcess("protover\n");
	WriteToProcess("new\n");
	if (variant != "")
	{
		const QString str = "variant " + variant + "\n";
		WriteToProcess(str.toLatin1());
	}
}

void WbEngine::Move()
{
	if (_memory && !_memorySet)
	{
		const QString memoryStr = "memory " + QString::number(_memorySize) + "\n";
		WriteToProcess(memoryStr.toLatin1());
		_memorySet = true;
	}
	WriteToProcess("go\n");
}

void WbEngine::Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	_textEdit->setText("");
	if (_memory && !_memorySet)
	{
		const QString memoryStr = "memory " + QString::number(_memorySize) + "\n";
		WriteToProcess(memoryStr.toLatin1());
		_memorySet = true;
	}
	WriteToProcess(AddMove(x1, y1, x2, y2, promotion));
	WriteToProcess("\n");
}

void WbEngine::Move(signed char x1, signed char y1, signed char x2, signed char y2, signed char x3, signed char y3)
{
	_textEdit->setText("");
	WriteToProcess(AddMove(x1, y1, x2, y2, x3, y3));
	WriteToProcess("\n");
}

QByteArray WbEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	QByteArray moveStr;
	if (_usermove)
	{
		moveStr += "usermove ";
	}
	if (y1 == '@')
	{
		moveStr.push_back(x1);
		moveStr.push_back(y1);
		moveStr.push_back(static_cast<char>(x2 + 97));
		moveStr.push_back(QString::number(y2)[0].toLatin1());
	}
	else if (y1 <= 16 || y2 <= 16)
	{
		moveStr.push_back(static_cast<char>(x1 < 30 ? x1 + 97 : x1));
		moveStr.push_back(QString::number(y1)[0].toLatin1());
		if (y1 >= 10) moveStr.push_back(QString::number(y1)[1].toLatin1());
		moveStr.push_back(static_cast<char>(x2 < 30 ? x2 + 97 : x2));
		moveStr.push_back(QString::number(y2)[0].toLatin1());
		if (y2 >= 10) moveStr.push_back(QString::number(y2)[1].toLatin1());
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

QByteArray WbEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, signed char x3, signed char y3)
{
	QByteArray moveStr;
	moveStr += "usermove ";
	if (y1 <= 16 || y2 <= 16)
	{
		moveStr.push_back(static_cast<char>(x1 < 30 ? x1 + 97 : x1));
		moveStr.push_back(QString::number(y1)[0].toLatin1());
		if (y1 >= 10) moveStr.push_back(QString::number(y1)[1].toLatin1());
		moveStr.push_back(static_cast<char>(x2 < 30 ? x2 + 97 : x2));
		moveStr.push_back(QString::number(y2)[0].toLatin1());
		if (y2 >= 10) moveStr.push_back(QString::number(y2)[1].toLatin1());
	}
	else
	{
		moveStr.push_back(x1);
		moveStr.push_back(y1);
		moveStr.push_back(x2);
		moveStr.push_back(y2);
	}
	moveStr.push_back(',');
	if (y2 <= 16 || y3 <= 16)
	{
		moveStr.push_back(static_cast<char>(x2 < 30 ? x2 + 97 : x2));
		moveStr.push_back(QString::number(y2)[0].toLatin1());
		if (y2 >= 10) moveStr.push_back(QString::number(y2)[1].toLatin1());
		moveStr.push_back(static_cast<char>(x3 < 30 ? x3 + 97 : x3));
		moveStr.push_back(QString::number(y3)[0].toLatin1());
		if (y3 >= 10) moveStr.push_back(QString::number(y3)[1].toLatin1());
	}
	else
	{
		moveStr.push_back(x2);
		moveStr.push_back(y2);
		moveStr.push_back(x3);
		moveStr.push_back(y3);
	}
	_moves.push_back(moveStr);
	return moveStr;
}

void WbEngine::SetOption(const std::string& name, bool value)
{
	if (name == "setboard") _setboard = value;
	if (name == "memory") _memory = value;
	if (name == "usermove") _usermove = value;
}

bool WbEngine::GetOption(const std::string& name)
{
	if (name == "setboard") return _setboard;
	if (name == "memory") return _memory;
	if (name == "usermove") return _usermove;
	return false;
}