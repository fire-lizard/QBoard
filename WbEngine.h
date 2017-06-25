#pragma once
#include "Engine.h"

class WbEngine : public Engine
{
public:
	WbEngine();
	virtual ~WbEngine();
	void StartGame(QString variant = "") override;
	void Move(int x1, int y1, int x2, int y2, char promotion = ' ') override;
};
