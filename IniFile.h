#pragma once

#include <QSettings>
#include <QApplication>
#include <qstyle.h>

class IniFile {
public:
    static void writeToIniFile(const QString& filePath, const QString& styleName, const QString& gameVariant,
                               const QString& pieceStyle, const QString& engineOutput);
    static QStringList readFromIniFile(const QString& filePath);
};
