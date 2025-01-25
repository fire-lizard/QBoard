#include "Logger.h"

void Logger::writeToLog(const QString& message, const LogLevel level)
{
    const QString settingsDir = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
    const QString logFileName = settingsDir + "/QBoard.log";
    QFile logFile(logFileName);

    // Open the file in append mode
    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Failed to open log file:" << logFileName;
        return;
    }

    QTextStream logStream(&logFile);

    // Format the log message with a timestamp
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString levelStr;
    switch (level)
    {
    Warning:
        levelStr = "WARNING";
        break;
    Error:
        levelStr = "ERROR";
        break;
    default:
        levelStr = "INFO";
        break;
    }
    logStream << "[" << timestamp << "] [" << levelStr << "] " << message << "\n";

    logFile.close();
}