#pragma once
#include <QProcess>
#include <QFileInfo>
#include <QTextEdit>
#include "Common.h"

constexpr signed char operator "" _c(unsigned long long arg) noexcept
{
	return static_cast<signed char>(arg);
}

class Engine
{
public:
	Engine();
	virtual ~Engine();
	virtual QProcess* RunProcess(QObject *parentObject, const QString& engineExe);
	void Quit() const;
	bool IsActive() const;
	void SetActive(bool val);
	QTextEdit* GetTextEdit();
	void SetTextEdit(QTextEdit* textEdit);
	void WriteToProcess(QByteArray buf);
	virtual void SetFEN(std::string fen);
	virtual EngineProtocol GetType() = 0;
	virtual void StartGame(QString variant = "") = 0;
	virtual void Move() = 0;
	virtual void Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') = 0;
	virtual QByteArray AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') = 0;

protected:
	mutable std::unique_ptr<QProcess> _process = nullptr;
	QTextEdit *_textEdit;
	bool _isActive = false;
	std::vector<QByteArray> _moves;
	std::string _fen;

private:
};
