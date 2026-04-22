#include "IniFile.h"

void IniFile::writeToIniFile(const QString& filePath, const ConfigRecord& configRecord) {
	// Create a QSettings object for the INI file
	QSettings settings(filePath, QSettings::IniFormat);

	// Write values
	settings.beginGroup("General");
    settings.setValue("StyleName", configRecord.styleName);
    settings.setValue("GameVariant", configRecord.gameVariant);
    settings.setValue("PieceStyle", configRecord.pieceStyle);
    settings.setValue("EngineOutput", configRecord.engineOutput);
    settings.setValue("HighlightMoves", configRecord.highlightMoves);
    settings.setValue("HighlightShoots", configRecord.highlightShoots);
    settings.setValue("HighlightAttackers", configRecord.highlightAttackers);
    settings.setValue("HighlightDefenders", configRecord.highlightDefenders);
    settings.setValue("HighlightLastMoves", configRecord.highlightLastMoves);
    settings.setValue("TimerState", configRecord.timerState);
    settings.setValue("EngineDepth", configRecord.engineDepth);
    settings.endGroup();

	// Sync the changes explicitly (optional)
	settings.sync();
}

QStringList IniFile::readFromIniFile(const QString& filePath) {
    // Create a QSettings object for the INI file
    QSettings settings(filePath, QSettings::IniFormat);

    // Read values from the "General" group
    settings.beginGroup("General");
    const QString styleName = settings.value("StyleName", "").toString();
    const QString gameVariant = settings.value("GameVariant", "Chess").toString();
    const QString pieceStyle = settings.value("PieceStyle", "European").toString();
    const QString engineOutput = settings.value("EngineOutput", "Concise").toString();
    const bool highlightMoves = settings.value("HighlightMoves", true).toBool();
    const bool highlightShoots = settings.value("HighlightShoots", true).toBool();
    const bool highlightAttackers = settings.value("HighlightAttackers", true).toBool();
    const bool highlightDefenders = settings.value("HighlightDefenders", true).toBool();
    const bool highlightLastMoves = settings.value("HighlightLastMoves", true).toBool();
    const bool timerState = settings.value("TimerState", true).toBool();
    const int  engineDepth = settings.value("EngineDepth", 10).toInt();
    settings.endGroup();

    // Return values
    QStringList result;
    result << styleName << gameVariant << pieceStyle << engineOutput << QVariant(highlightMoves).toString();
    result << QVariant(highlightShoots).toString() << QVariant(highlightAttackers).toString();
	result << QVariant(highlightDefenders).toString() << QVariant(highlightLastMoves).toString();
    result << QVariant(timerState).toString() << QVariant(engineDepth).toString();
    return result;
}
