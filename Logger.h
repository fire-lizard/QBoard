#pragma once
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDateTime>
#include <QDebug>

enum class LogLevel {Info, Warning, Error};

class Logger
{
public:
	static void writeToLog(const QString& message, const LogLevel level = LogLevel::Info);
};

