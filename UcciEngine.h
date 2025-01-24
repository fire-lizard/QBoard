#pragma once
#include "UciEngine.h"

class UcciEngine : public UciEngine
{
public:
	UcciEngine();
	~UcciEngine() override;
	EngineProtocol GetType() override;
	void StartGame(QString variant = "") override;
	void Move() override;
	void Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') override;
	QByteArray AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') override;
};

