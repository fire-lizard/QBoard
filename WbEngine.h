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
};
