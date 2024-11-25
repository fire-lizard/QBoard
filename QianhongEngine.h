#pragma once
#include "Engine.h"

class QianhongEngine : public Engine
{
public:
	QianhongEngine();
	~QianhongEngine() override;
	EngineProtocol GetType() override;
	void StartGame(QString variant = "") override;
	void Move(int x1, int y1, int x2, int y2, char promotion = ' ') override;
	QByteArray AddMove(int x1, int y1, int x2, int y2, char promotion = ' ') override;
};

