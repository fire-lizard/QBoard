#include "networkmanager.h"
#include "ui_networkmanager.h"

NetworkManager::NetworkManager(QWidget* parent) : QDialog(parent), ui(new Ui::NetworkManager)
{
	ui->setupUi(this);
}

NetworkManager::~NetworkManager()
{
	delete ui;
}
