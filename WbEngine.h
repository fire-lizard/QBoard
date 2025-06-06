#pragma once
#include "Engine.h"
#include "Board.h"

class WbEngine : public Engine
{
public:
	WbEngine();
	~WbEngine() override;
	void SetFEN(std::string fen) override;
	void SetMemory(int memorySize);
	EngineProtocol GetType() override;
	void StartGame(QString variant = "") override;
	void Move() override;
	void Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') override;
	void Move(signed char x1, signed char y1, signed char x2, signed char y2, signed char x3, signed char y3);
	void Move(signed char x1, signed char y1, signed char x2, signed char y2, signed char x3, signed char y3, signed char x4, signed char y4);
	QByteArray AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') override;
	QByteArray AddMove(signed char x1, signed char y1, signed char x2, signed char y2, signed char x3, signed char y3);
	QByteArray AddMove(signed char x1, signed char y1, signed char x2, signed char y2, signed char x3, signed char y3, signed char x4, signed char y4);
	void SetOption(const std::string& name, bool value);
	bool GetOption(const std::string& name) const;
	void Edit(const Board* board) const;

private:
	bool _memory = false;
	int _memorySize = 80;
	bool _usermove = false;
	bool _setboard = false;
};
