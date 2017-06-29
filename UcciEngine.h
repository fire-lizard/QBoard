#pragma once
#include "Engine.h"

class UcciEngine : public Engine
{
public:
	UcciEngine();
	virtual ~UcciEngine();
	EngineType GetType() override;
	void StartGame(QString variant = "") override;
	void Move(int x1, int y1, int x2, int y2, char promotion = ' ') override;
};

