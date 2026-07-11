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

void WbEngine::SetEngineDepth(int engineDepth)
{
    _engineDepth = engineDepth;
    if (_process != nullptr && _process->processId() > 0 && _process->state() != QProcess::ProcessState::NotRunning && _useEngineDepth)
    {
        WriteToProcess("sd " + QByteArray::number(_engineDepth) + "\n");
    }
}

void WbEngine::SetEngineTime(int engineTime)
{
	_engineTime = engineTime;
	if (_process != nullptr && _process->processId() > 0 && _process->state() != QProcess::ProcessState::NotRunning && _useEngineTime)
	{
		WriteToProcess("st " + QByteArray::number(_engineTime) + "\n");
	}
}

void WbEngine::SetFEN(std::string fen)
{
	_fen = std::move(fen);
	if (_setboard)
	{
		WriteToProcess(QByteArray::fromStdString("setboard " + _fen + "\n"));
	}
	_moves.clear();
}

void WbEngine::Edit(const Board* board) const
{
	PieceColour pieceColour = White;
	WriteToProcess("edit\n");
	WriteToProcess("#\n");
	for (int j = 0; j < board->GetHeight(); j++)
	{
		for (int i = 0; i < board->GetWidth(); i++)
		{
			std::optional<Piece> p = board->GetData(i, j);
			if (p != std::nullopt)
			{
				const char letter = i + 97;
				const int number = board->GetHeight() - j;
                const PieceColour newPieceColour = p->Colour;
				std::string str;
				if (newPieceColour != pieceColour)
				{
					WriteToProcess("c\n");
					pieceColour = newPieceColour;
				}
                str += board->GetStringCode(i, j);
				str.push_back(letter);
				str += std::to_string(number);
				str.push_back('\n');
				WriteToProcess(QByteArray::fromStdString(str));
			}
		}
	}
	WriteToProcess(".\n");
}

void WbEngine::StartGame(QString variant)
{
	_moves.clear();
    WriteToProcess("xboard\n");
    WriteToProcess("protover 2\n");
	WriteToProcess("new\n");
	if (variant != "")
	{
        const QString str = "variant " + variant + "\n";
        WriteToProcess(str.toLatin1());
	}
	if (_useEngineDepth)
	{
		WriteToProcess("sd " + QByteArray::number(_engineDepth) + "\n");
	}
	if (_useEngineTime)
	{
		WriteToProcess("st " + QByteArray::number(_engineTime) + "\n");
	}
}

void WbEngine::SetMemory(int memorySize)
{
	const QString memoryStr = "memory " + QString::number(_memorySize) + "\n";
	WriteToProcess(memoryStr.toLatin1());
	_memorySize = memorySize;
}

void WbEngine::Move()
{
	_textEdit->setText("");
	WriteToProcess("go\n");
}

void WbEngine::Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	_textEdit->setText("");
    WriteToProcess(AddMove(x1, y1, x2, y2, promotion) + "\n");
}

void WbEngine::DoubleMove(signed char x1, signed char y1, signed char x2, signed char y2, signed char x3, signed char y3)
{
	_textEdit->setText("");
    WriteToProcess(AddMove(x1, y1, x2, y2, x3, y3) + "\n");
}

void WbEngine::TripleMove(signed char x1, signed char y1, signed char x2, signed char y2, signed char x3, signed char y3, signed char x4, signed char y4)
{
	_textEdit->setText("");
    WriteToProcess(AddMove(x1, y1, x2, y2, x3, y3, x4, y4) + "\n");
}

void WbEngine::SendString(const QByteArray& str) const
{
	WriteToProcess(str + "\n");
}

QByteArray WbEngine::AddMove(QByteArray moveStr)
{
	if (_usermove)
	{
		moveStr = "usermove " + moveStr;
	}
	_moves.push_back(moveStr);
	return moveStr;
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
	else if (x1 == x2 && y1 == y2)
	{
		moveStr += "@@@@";
	}
	else if (y1 <= 25 || y2 <= 25)
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
    if (promotion == 'n' || promotion == 'b' || promotion == 'r' || promotion == 'q' ||
		promotion == 'j' || promotion == 'f' || promotion == 'a' || promotion == 'c' ||
		promotion == 'w' || promotion == 'm' || promotion == 'M' || promotion == '+')
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
	if (y1 <= 25 || y2 <= 25)
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
	if (y2 <= 25 || y3 <= 25)
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

QByteArray WbEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, signed char x3, signed char y3, signed char x4, signed char y4)
{
	QByteArray moveStr;
	moveStr += "usermove ";
	if (y1 <= 25 || y2 <= 25)
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
	if (y2 <= 25 || y3 <= 25)
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
	moveStr.push_back(',');
	if (y3 <= 25 || y4 <= 25)
	{
		moveStr.push_back(static_cast<char>(x3 < 30 ? x3 + 97 : x3));
		moveStr.push_back(QString::number(y3)[0].toLatin1());
		if (y3 >= 10) moveStr.push_back(QString::number(y3)[1].toLatin1());
		moveStr.push_back(static_cast<char>(x4 < 30 ? x4 + 97 : x4));
		moveStr.push_back(QString::number(y4)[0].toLatin1());
		if (y4 >= 10) moveStr.push_back(QString::number(y4)[1].toLatin1());
	}
	else
	{
		moveStr.push_back(x3);
		moveStr.push_back(y3);
		moveStr.push_back(x4);
		moveStr.push_back(y4);
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

bool WbEngine::GetOption(const std::string& name) const
{
	if (name == "setboard") return _setboard;
	if (name == "memory") return _memory;
	if (name == "usermove") return _usermove;
	return false;
}
