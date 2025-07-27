#include "networkmanager.h"
#include "ui_networkmanager.h"

NetworkManager::NetworkManager(QWidget* parent) : QDialog(parent), ui(new Ui::NetworkManager)
{
	ui->setupUi(this);
	ui->local_host->setText(Communications::preferred_host_address(QAbstractSocket::IPv4Protocol).toString());
	ui->local_scope_id->setEnabled(false);
	ui->remote_host->setText(QHostAddress(QHostAddress::LocalHost).toString());
	ui->remote_scope_id->setEnabled(false);

	connect(ui->connect,
		SIGNAL(clicked()),
		this,
		SLOT(slot_connect()));
	connect(ui->disconnect,
		SIGNAL(clicked()),
		this,
		SLOT(slot_disconnect()));
	connect(ui->listen,
		SIGNAL(clicked()),
		this,
		SLOT(slot_listen()));
	connect(ui->local,
		SIGNAL(toggled(bool)),
		this,
		SLOT(slot_local(bool)));
	connect(ui->local_ipv4,
		SIGNAL(clicked()),
		this,
		SLOT(slot_protocol_changed()));
	connect(ui->local_ipv6,
		SIGNAL(clicked()),
		this,
		SLOT(slot_protocol_changed()));
	connect(ui->remote,
		SIGNAL(toggled(bool)),
		this,
		SLOT(slot_remote(bool)));
	connect(ui->remote_ipv4,
		SIGNAL(clicked()),
		this,
		SLOT(slot_protocol_changed()));
	connect(ui->remote_ipv6,
		SIGNAL(clicked()),
		this,
		SLOT(slot_protocol_changed()));
	ui->remote_gb->setEnabled(false);
}

NetworkManager::~NetworkManager()
{
	delete ui;
}

void NetworkManager::SetCommunications(Communications* _communications)
{
	_comm = _communications;

	if (_comm)
	{
		connect(_comm,
			SIGNAL(connected_to_client()),
			this,
			SLOT(slot_connected_to_client()));
		connect(_comm,
			SIGNAL(disconnected_from_client()),
			this,
			SLOT(slot_disconnected_from_client()));
	}
}

QHostAddress NetworkManager::get_listening_address() const
{
	QHostAddress address;

	if (ui->local_ipv4->isChecked())
		address.setAddress(ui->local_host->text().trimmed());
	else
	{
		address.setAddress(ui->local_host->text().trimmed());
		address.setScopeId(ui->local_scope_id->text().trimmed());
	}

	return address;
}

QLineEdit* NetworkManager::get_allowed_host_field() const
{
	return ui->allowed_host;
}

QLineEdit* NetworkManager::get_local_host_field() const
{
	return ui->local_host;
}

QLineEdit* NetworkManager::get_remote_host_field() const
{
	return ui->remote_host;
}

QLineEdit* NetworkManager::get_remote_scope_id_field() const
{
	return ui->remote_scope_id;
}

QSpinBox* NetworkManager::get_local_port_field() const
{
	return ui->local_port;
}

QSpinBox* NetworkManager::get_remote_port_field() const
{
	return ui->remote_port;
}

void NetworkManager::reset() const
{
	_comm ? _comm->disconnect_remotely(), _comm->stop_listening() : (void)0;
	ui->allowed_host->clear();
	ui->color->setCurrentIndex(0);
	ui->connect->setText(tr("&Connect"));
	ui->listen->setText(tr("&Listen"));
	ui->local->setChecked(true);
	ui->local_host->setReadOnly(false);
	ui->local_host->setText(Communications::preferred_host_address(QAbstractSocket::IPv4Protocol).toString());
	ui->local_ipv4->setChecked(true);
	ui->local_ipv4->setEnabled(true);
	ui->local_ipv6->setEnabled(true);
	ui->local_port->setReadOnly(false);
	ui->local_port->setValue(4710);
	ui->local_scope_id->clear();
	ui->local_scope_id->setEnabled(false);
	ui->local_scope_id->setReadOnly(false);
	ui->remote_host->setReadOnly(false);
	ui->remote_host->setText(QHostAddress(QHostAddress::LocalHost).toString());
	ui->remote_ipv4->setChecked(true);
	ui->remote_ipv4->setEnabled(true);
	ui->remote_ipv6->setEnabled(true);
	ui->remote_port->setReadOnly(false);
	ui->remote_port->setValue(4710);
	ui->remote_scope_id->clear();
	ui->remote_scope_id->setEnabled(false);
	ui->remote_scope_id->setReadOnly(false);
}

void NetworkManager::slot_connect() const
{
	if (_comm)
	{
		if (_comm->is_connected_remotely())
			_comm->disconnect_remotely();
		else
			_comm->connect_remotely();
	}
}

void NetworkManager::slot_connected_to_client() const
{
	ui->connect->setText(tr("&Disconnect"));
	ui->remote_host->setReadOnly(true);
	ui->remote_ipv4->setEnabled(false);
	ui->remote_ipv6->setEnabled(false);
	ui->remote_port->setReadOnly(true);
	ui->remote_scope_id->setReadOnly(true);
}

void NetworkManager::slot_disconnect() const
{
	if (_comm)
		_comm->disconnect_remotely();
}

void NetworkManager::slot_disconnected_from_client() const
{
	ui->connect->setText(tr("&Connect"));
	ui->remote_host->setReadOnly(false);
	ui->remote_ipv4->setEnabled(true);
	ui->remote_ipv6->setEnabled(true);
	ui->remote_port->setReadOnly(false);
	ui->remote_scope_id->setReadOnly(false);
}

void NetworkManager::slot_listen() const
{
	auto state = false;

	if (_comm && ui->listen == sender())
	{
		if (_comm->is_listening())
			_comm->stop_listening();
		else
			_comm->set_listen();

		state = _comm->is_listening();
	}

	ui->local_host->setReadOnly(state);
	ui->local_ipv4->setEnabled(!state);
	ui->local_ipv6->setEnabled(!state);
	ui->local_port->setReadOnly(state);

	if (ui->local_ipv6->isChecked())
		ui->local_scope_id->setReadOnly(state);

	if (state)
		ui->listen->setText(tr("&Stop Listening"));
	else
		ui->listen->setText(tr("&Listen"));
}

void NetworkManager::slot_local(bool state) const
{
	if (state)
	{
		if (_comm)
			_comm->disconnect_remotely();

		slot_disconnected_from_client();
		ui->local_gb->setEnabled(true);
		ui->remote->blockSignals(true);
		ui->remote->setChecked(false);
		ui->remote->blockSignals(false);
		ui->remote_gb->setEnabled(false);
	}
	else
	{
		ui->local->blockSignals(true);
		ui->local->setChecked(true);
		ui->local->blockSignals(false);
	}
}

void NetworkManager::slot_protocol_changed() const
{
	if (sender() == ui->local_ipv4)
	{
		const auto preferred_host_address(Communications::preferred_host_address(QAbstractSocket::IPv4Protocol));

		ui->allowed_host->clear();
		ui->local_host->setText(preferred_host_address.toString());
		ui->local_scope_id->clear();
		ui->local_scope_id->setEnabled(false);
	}
	else if (sender() == ui->local_ipv6)
	{
		auto const preferred_host_address(Communications::preferred_host_address(QAbstractSocket::IPv6Protocol));

		ui->allowed_host->clear();
		ui->local_host->setText(preferred_host_address.toString());
		ui->local_scope_id->setEnabled(true);
		ui->local_scope_id->setText(preferred_host_address.scopeId());
	}
	else if (sender() == ui->remote_ipv4)
	{
		ui->remote_host->setText
		(QHostAddress(QHostAddress::LocalHost).toString());
		ui->remote_scope_id->clear();
		ui->remote_scope_id->setEnabled(false);
	}
	else if (sender() == ui->remote_ipv6)
	{
		ui->remote_host->setText
		(QHostAddress(QHostAddress::LocalHostIPv6).toString());
		ui->remote_scope_id->setText
		(QHostAddress(QHostAddress::LocalHostIPv6).scopeId());
		ui->remote_scope_id->setEnabled(true);
	}
}

void NetworkManager::slot_remote(bool state) const
{
	if (state)
	{
		if (_comm)
		{
			_comm->disconnect_remotely();
			_comm->stop_listening();
		}

		slot_disconnected_from_client();
		slot_listen();
		ui->local->blockSignals(true);
		ui->local->setChecked(false);
		ui->local->blockSignals(false);
		ui->local_gb->setEnabled(false);
		ui->remote_gb->setEnabled(true);
	}
	else
	{
		ui->remote->blockSignals(true);
		ui->remote->setChecked(true);
		ui->remote->blockSignals(false);
	}
}

void NetworkManager::stop() const
{
	ui->connect->setText(tr("&Connect"));
	ui->listen->setText(tr("&Listen"));
}
