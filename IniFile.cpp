#include "IniFile.h"

void IniFile::writeToIniFile(const QString& filePath, const QString& styleName, const QString& gameVariant, const QString& pieceStyle, 
    const QString& engineOutput, bool highlightMoves, bool highlightShoots, bool highlightAttackers, bool highlightDefenders, bool highlightLastMoves) {
	// Create a QSettings object for the INI file
	QSettings settings(filePath, QSettings::IniFormat);

	// Write values
	settings.beginGroup("General");
    settings.setValue("StyleName", styleName);
    settings.setValue("GameVariant", gameVariant);
    settings.setValue("PieceStyle", pieceStyle);
    settings.setValue("EngineOutput", engineOutput);
    settings.setValue("HighlightMoves", highlightMoves);
    settings.setValue("HighlightShoots", highlightShoots);
    settings.setValue("HighlightAttackers", highlightAttackers);
    settings.setValue("HighlightDefenders", highlightDefenders);
    settings.setValue("HighlightLastMoves", highlightLastMoves);
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
    settings.endGroup();

    // Return values
    QStringList result;
    result << styleName << gameVariant << pieceStyle << engineOutput << QVariant(highlightMoves).toString();
    result << QVariant(highlightShoots).toString() << QVariant(highlightAttackers).toString();
	result << QVariant(highlightDefenders).toString() << QVariant(highlightLastMoves).toString();
    return result;
}
