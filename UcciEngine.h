#pragma once
#include "UciEngine.h"

class UcciEngine : public UciEngine
{
public:
	UcciEngine();
	~UcciEngine() override;
	void SetFEN(std::string fen) override;
	EngineProtocol GetType() override;
	void StartGame(QString variant = "") override;
	QByteArray AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') override;
};

