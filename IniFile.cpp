#include "IniFile.h"

void IniFile::writeToIniFile(const QString& filePath, const QString& styleName, const QString& gameVariant, const QString& pieceStyle, const QString& engineOutput) {
	// Create a QSettings object for the INI file
	QSettings settings(filePath, QSettings::IniFormat);

	// Write values
	settings.beginGroup("General");
    settings.setValue("StyleName", styleName);
    settings.setValue("GameVariant", gameVariant);
    settings.setValue("PieceStyle", pieceStyle);
    settings.setValue("EngineOutput", engineOutput);
    settings.endGroup();

	// Sync the changes explicitly (optional)
	settings.sync();
}

QStringList IniFile::readFromIniFile(const QString& filePath) {
    // Create a QSettings object for the INI file
    QSettings settings(filePath, QSettings::IniFormat);

    // Read values from the "General" group
    settings.beginGroup("General");
    const QString styleName = settings.value("StyleName", QApplication::style()->name()).toString();
    const QString gameVariant = settings.value("GameVariant", "Chess").toString();
    const QString pieceStyle = settings.value("PieceStyle", "European").toString();
    const QString engineOutput = settings.value("EngineOutput", "Concise").toString();
    settings.endGroup();

    // Return values
    QStringList result;
    result << styleName << gameVariant << pieceStyle << engineOutput;
    return result;
}
