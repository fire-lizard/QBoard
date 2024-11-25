#pragma once
#include "Engine.h"

class UciEngine : public Engine
{
public:
	UciEngine();
	~UciEngine() override;
	EngineProtocol GetType() override;
	void StartGame(QString variant = "") override;
	void Move(int x1, int y1, int x2, int y2, char promotion = ' ') override;
	QByteArray AddMove(int x1, int y1, int x2, int y2, char promotion = ' ') override;
};
