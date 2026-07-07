#pragma once
#include <tuple>
#include <QDialog>
#include <QMessageBox>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "addenginedialog.h"
#include "Common.h"

namespace Ui {
	class EngineManager;
}

namespace {
	using Pair = QPair<GameVariant, QString>;

	const QList<Pair>& variantMap()
	{
		static const QList<Pair> _variantMap = {
			{Chess,           "Chess"},
			{CapablancaChess, "Capablanca Chess"},
			{GothicChess,     "Gothic Chess"},
			{JanusChess,      "Janus Chess"},
			{ChancellorChess, "Chancellor Chess"},
			{ModernChess,     "Modern Chess"},
			{GrandChess,      "Grand Chess"},
			{OmegaChess,      "Omega Chess"},
			{NightriderChess, "Nightrider Chess"},
			{MusketeerChess,  "Musketeer Chess"},
			{CourierChess,    "Courier Chess"},
			{GrandeAcedrex,   "Grande Acedrex"},
			{Xiangqi,         "Xiangqi"},
			{Janggi,          "Janggi"},
			{Shatranj,        "Shatranj"},
			{Shatar,          "Shatar"},
			{Makruk,          "Makruk"},
			{Sittuyin,        "Sittuyin"},
			{Shogi,           "Shogi"},
			{MicroShogi,      "Micro Shogi"},
			{KyotoShogi,      "Kyoto Shogi"},
			{MiniShogi,       "Mini Shogi"},
			{JudkinShogi,     "Judkins Shogi"},
			{WhaleShogi,      "Whale Shogi"},
			{ToriShogi,       "Tori Shogi"},
			{EuroShogi,       "Euro Shogi"},
			{YariShogi,       "Yari Shogi"},
			{HeianShogi,      "Heian Shogi"},
			{ShoShogi,        "Sho Shogi"},
			{WaShogi,         "Wa Shogi"},
			{CrazyWa,         "CrazyWa"},
			{ChuShogi,        "Chu Shogi"},
			{HeianDaiShogi,   "Heian Dai Shogi"},
			{DaiShogi,        "Dai Shogi"},
			{TenjikuShogi,    "Tenjiku Shogi"},
			{DaiDaiShogi,     "Dai Dai Shogi"},
			{MakaDaiDaiShogi, "Maka Dai Dai Shogi"},
			{KoShogi,         "Ko Shogi"}
		};
		return _variantMap;
	}

	const QList<Pair>& engineMap()
	{
		static const QList<Pair> _engineMap = {
		{Chess,             "normal"},
		{CapablancaChess,   "capablanca"},
		{GothicChess,       "gothic"},
		{JanusChess,        "janus"},
		{ChancellorChess,   "chancellor"},
		{ModernChess,       "modern"},
		{GrandChess,        "grand"},
		{OmegaChess,        "omega"},
		{NightriderChess,   "nightrider"},
		{MusketeerChess,    "musketeer"},
		{CourierChess,      "courier"},
		{GrandeAcedrex,     "grande-acedrex"},

		{Xiangqi,           "xiangqi"},
		{Janggi,            "janggi"},
		{Shatranj,          "shatranj"},
		{Shatar,            "shatar"},
		{Makruk,            "makruk"},
		{Sittuyin,          "sittuyin"},

		{Shogi,             "shogi"},
		{MicroShogi,        "micro_shogi"},
		{KyotoShogi,        "5x5+4_shogi"},
		{MiniShogi,         "5x5+5_shogi"},
		{JudkinShogi,       "6x6+6_shogi"},
		{WhaleShogi,        "whale_shogi"},
		{ToriShogi,         "7x7+6_shogi"},
		{EuroShogi,         "8x8+5_shogi"},
		{YariShogi,         "yarishogi"},
		{HeianShogi,        "heian_shogi"},
		{ShoShogi,          "sho"},
		{WaShogi,           "washogi"},
		{CrazyWa,           "crazywa"},
		{ChuShogi,          "chu"},
		{HeianDaiShogi,     "heian_dai_shogi"},
		{DaiShogi,          "dai"},
		{TenjikuShogi,      "tenjiku"},
		{DaiDaiShogi,       "daidai"},
		{MakaDaiDaiShogi,   "maka"},
		{KoShogi,           "ko"}
		};
		return _engineMap;
	}
}

class EngineManager : public QDialog
{
	Q_OBJECT

public:
	explicit EngineManager(QWidget* parent = nullptr);
	~EngineManager() override;
	QTableWidget* GetEngineTable() const;
	void SetImageInCell(int row, int col, const QString& imagePath) const;
	static QString GameVariantToString(GameVariant gameVariant);
	static GameVariant StringToGameVariant(const QString& variantName);
	static EngineProtocol StringToEngineProtocol(const QString& str);
	static QString GameVariantToShortString(GameVariant gameVariant);
	static std::optional<GameVariant> ShortStringToGameVariant(const QString& variantName);

private slots:
	void on_toolButton_clicked();

	void on_toolButton_2_clicked();

	void on_toolButton_3_clicked();

	void on_buttonBox_accepted();

	void on_buttonBox_rejected();

	void on_engineTable_cellDoubleClicked(int row, int column);

private:
	Ui::EngineManager* ui;
};
