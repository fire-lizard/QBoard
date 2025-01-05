#pragma once
#include "Engine.h"

class WbEngine : public Engine
{
public:
	WbEngine();
	~WbEngine() override;
	EngineProtocol GetType() override;
	void StartGame(QString variant = "") override;
	void Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') override;
	QByteArray AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') override;
	QByteArray AddMove(signed char x1, signed char y1, signed char x2, signed char y2, signed char x3, signed char y3);
	void SetOption(const std::string& name, bool value);

private:
	bool _setboard = false;
	bool _memory = false;
	int _memorySize = 80;
	bool _memorySet = false;
	bool _usermove = false;
};
