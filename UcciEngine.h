#pragma once
#include "UciEngine.h"

class UcciEngine : public UciEngine
{
public:
	UcciEngine();
	virtual ~UcciEngine();
	EngineType GetType() override;
	void StartGame(QString variant = "") override;
	void Move(int x1, int y1, int x2, int y2, char promotion = ' ') override;
	QByteArray AddMove(int x1, int y1, int x2, int y2, char promotion = ' ') override;
};

