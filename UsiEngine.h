#pragma once
#include "UciEngine.h"

class UsiEngine : public UciEngine
{
public:
	UsiEngine();
	~UsiEngine() override;
	EngineProtocol GetType() override;
	void Move() override;
	void StartGame(QString variant = "") override;
	void Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') override;
	QByteArray AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') override;
};

