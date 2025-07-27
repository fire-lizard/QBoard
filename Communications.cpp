#include "Communications.h"
#include "networkmanager.h"
#include "vboard.h"

NetworkManager* m_gui = nullptr;
VBoard* m_vboard = nullptr;

Communications::Communications() :QObject()
{
    qRegisterMetaType<QProcess::ExitStatus>("QProcess::ExitStatus");
    connect(&m_listening_socket,
        SIGNAL(newConnection()),
        this,
        SLOT(slot_accept_connection()));
}

void Communications::SetGui(QDialog* gui)
{
    m_gui = dynamic_cast<NetworkManager*>(gui);
}

void Communications::SetVBoard(QWidget* vboard)
{
    m_vboard = dynamic_cast<VBoard*>(vboard);
}

QByteArray Communications::hmac(const QByteArray& data, const QByteArray& k)
{
    auto key(k);
    static constexpr int s_block_length = 576 / CHAR_BIT;

    if (key.length() > s_block_length)
        key = shax(key);

    if (key.length() < s_block_length)
        key.append(QByteArray(s_block_length - key.length(), 0));

    QByteArray const ipad(s_block_length, 0x36);
    QByteArray const opad(s_block_length, 0x5c);
    QByteArray left(s_block_length, 0);

    for (int i = 0; i < s_block_length; i++)
        left[i] = static_cast<char>(key.at(i) ^ opad.at(i));

    QByteArray right(s_block_length, 0);

    for (int i = 0; i < s_block_length; i++)
        right[i] = static_cast<char>(ipad.at(i) ^ key.at(i));

    return shax(left.append(shax(right.append(data))));
}

QByteArray Communications::shax(const QByteArray& data)
{
    QCryptographicHash sha(QCryptographicHash::Sha3_512);

    sha.addData(data);
    return sha.result();
}

QByteArray Communications::xor_arrays(const QByteArray& a, const QByteArray& b) const
{
    QByteArray bytes(qMin(a.length(), b.length()), 0);

    for (int i = 0; i < bytes.length(); i++)
        bytes[i] = static_cast<char>(a[i] ^ b[i]);

    return bytes;
}

QHostAddress Communications::preferred_host_address
(const QAbstractSocket::NetworkLayerProtocol protocol)
{
    foreach(const auto& interface, QNetworkInterface::allInterfaces())
        if (!(interface.flags() & QNetworkInterface::IsLoopBack))
            if (interface.flags() & QNetworkInterface::IsUp)
            {
                foreach(const auto& address, interface.addressEntries())
                    if (address.ip().protocol() == protocol)
                        return address.ip();
            }

    if (protocol == QAbstractSocket::IPv4Protocol)
        return {QHostAddress::LocalHost};
    else
        return {QHostAddress::LocalHostIPv6};
}

bool Communications::is_connected_remotely() const
{
    if (m_client_connection)
        return m_client_connection->state() == QAbstractSocket::ConnectedState;
    else
        return false;
}

bool Communications::is_listening() const
{
    return m_listening_socket.isListening();
}

bool Communications::is_ready() const
{
    return is_connected_remotely();
}

bool Communications::memcmp(const QByteArray& a, const QByteArray& b) const
{
    auto const length = qMax(a.length(), b.length());
    quint64 rc = 0;

    for (int i = 0; i < length; i++)
        rc |= (i < a.length() ? static_cast<quint64>(a.at(i)) : 0ULL) ^
        (i < b.length() ? static_cast<quint64>(b.at(i)) : 0ULL);

    return rc == 0;
}

void Communications::connect_remotely()
{
    QHostAddress address("");
    quint16 remote_port = 0;
    QString scope_id("");

    if (m_gui)
    {
        if (m_gui->get_remote_host_field())
            address = QHostAddress(m_gui->get_remote_host_field()->text().trimmed());

        if (m_gui->get_remote_port_field())
            remote_port = static_cast<quint16>(m_gui->get_remote_port_field()->text().trimmed().toInt());

        if (m_gui->get_remote_scope_id_field())
            scope_id = m_gui->get_remote_scope_id_field()->text().trimmed();
    }

    if (!scope_id.isEmpty())
        address.setScopeId(scope_id);

    if (m_client_connection)
    {
        m_client_connection->abort();
        m_client_connection->deleteLater();
    }

    m_client_connection = new QTcpSocket(this);
    connect(m_client_connection,
        SIGNAL(connected()),
        this,
        SIGNAL(connected_to_client()));
    connect(m_client_connection,
        SIGNAL(connected()),
        this,
        SLOT(slot_client_connected()));
    connect(m_client_connection,
        SIGNAL(disconnected()),
        this,
        SIGNAL(disconnected_from_client()));
    connect(m_client_connection,
        SIGNAL(disconnected()),
        this,
        SLOT(slot_client_disconnected()));
#if (QT_VERSION < QT_VERSION_CHECK(5, 15, 0))
    connect(m_client_connection,
        SIGNAL(error(QAbstractSocket::SocketError)),
        m_client_connection,
        SIGNAL(disconnected()));
#else
    connect(m_client_connection,
        SIGNAL(errorOccurred(QAbstractSocket::SocketError)),
        m_client_connection,
        SIGNAL(disconnected()));
    connect(m_client_connection,
        SIGNAL(errorOccurred(QAbstractSocket::SocketError)),
        this,
        SLOT(slot_disconnected(QAbstractSocket::SocketError)));
#endif
    connect(m_client_connection,
        SIGNAL(readyRead()),
        this,
        SLOT(slot_update_board()));
    m_client_connection->connectToHost(address, remote_port);
}

void Communications::disconnect_remotely() const
{
    if (m_client_connection)
    {
        m_client_connection->abort();
        m_client_connection->deleteLater();
    }

    if (m_vboard)
    {
        m_vboard->GetBoard()->Initialize();
    }
}

void Communications::initialize()
{
    if (m_gui &&
        m_gui->get_allowed_host_field())
        m_gui->get_allowed_host_field()->clear();

    if (m_gui &&
        m_gui->get_local_host_field())
        m_gui->get_local_host_field()->setText(preferred_host_address(QAbstractSocket::IPv4Protocol).toString());

    m_listening_socket.close();
    prepare_connection_status();
}

void Communications::prepare_connection_status() const
{
    if (m_vboard)
    {
        if (m_client_connection &&
            m_client_connection->state() == QAbstractSocket::ConnectedState)
            m_vboard->GetStatusBar()->showMessage(tr("Status: Peer %1:%2 Connected").arg(m_client_connection->peerAddress().toString()).arg(m_client_connection->peerPort()));
        else if (m_listening_socket.isListening())
            m_vboard->GetStatusBar()->showMessage(tr("Status: %1:%2 Listening").
                arg(m_listening_socket.serverAddress().toString()).
                arg(m_listening_socket.serverPort()));
        else
            m_vboard->GetStatusBar()->showMessage(tr("Status: Peer Disconnected"));
    }
}

void Communications::quit()
{
    /*
    ** Terminate all communications.
    */

    if (m_client_connection)
    {
        m_client_connection->abort();
    	m_client_connection->deleteLater();
    }
    m_listening_socket.close();
}

void Communications::send_move(const struct move_s& current_move)
{
    if (!m_client_connection)
        return;
    else if (m_client_connection->state() != QAbstractSocket::ConnectedState)
        return;

    QByteArray buffer;

    /*
    ** Copy the structure.
    */

    buffer.append(QByteArray::number(current_move.m_x1));
    buffer.append(" ");
    buffer.append(QByteArray::number(current_move.m_x2));
    buffer.append(" ");
    buffer.append(QByteArray::number(current_move.m_y1));
    buffer.append(" ");
    buffer.append(QByteArray::number(current_move.m_y2));
    buffer.append(" ");
    buffer.append(QByteArray::number(current_move.m_rook_x1));
    buffer.append(" ");
    buffer.append(QByteArray::number(current_move.m_rook_x2));
    buffer.append(" ");
    buffer.append(QByteArray::number(current_move.m_rook_y1));
    buffer.append(" ");
    buffer.append(QByteArray::number(current_move.m_rook_y2));
    buffer.append(" ");
    buffer.append(QByteArray::number(current_move.m_piece));
    buffer.append(" ");
    buffer.append(QByteArray::number(current_move.m_rook));
    buffer.append(" ");
    buffer.append(QByteArray::number(current_move.m_promoted));
    buffer.append(" ");
    buffer.append(QByteArray::number(current_move.m_pawn2));
    buffer.append(" ");
    buffer.append(QByteArray::number(current_move.m_enpassant));
    buffer.append(" ");
    buffer.append(QByteArray::number(current_move.m_is_opponent_king_threat));
    buffer.append(" ");
    buffer.append(current_move.m_departure);
    buffer.append(" ");

    for (int i = 0; i < NSQUARES; i++)
    {
        for (int j = 0; j < NSQUARES; j++)
        {
            buffer.append(QByteArray::number(current_move.m_board[i][j]));
            buffer.append(" ");
        }
    }

    buffer.append("\n");

    QApplication::setOverrideCursor(Qt::WaitCursor);

    if (m_client_connection->write(buffer.constData(), buffer.length()) !=
        static_cast<qint64> (buffer.length()))
    {
        QApplication::restoreOverrideCursor();

        QMessageBox::critical(nullptr, "", "Move could not be delivered.", QMessageBox::Ok, QMessageBox::Default);
    }
    else
    {
        QApplication::restoreOverrideCursor();

        if (m_vboard)
        {
            if (m_vboard->GetCurrentPlayer() == White)
            {
                m_vboard->SetCurrentPlayer(Black);
            }
            else
            {
                m_vboard->SetCurrentPlayer(White);
            }
        }
    }
}

void Communications::set_listen()
{
    if (m_listening_socket.isListening())
        return;

    m_listening_socket.setMaxPendingConnections(1);

    /*
    ** Listen!
    */

    QHostAddress address(QHostAddress::Any);
    quint16 port = 0;

    if (m_gui &&
        m_gui->get_local_port_field())
    {
        address = m_gui->get_listening_address();
        port = m_gui->get_local_port_field()->text().toUShort();
    }

    m_listening_socket.listen(address, port);

    /*
    ** Save the port number.
    */

    if (m_gui &&
        m_gui->get_local_port_field() &&
        m_listening_socket.isListening())
        m_gui->get_local_port_field()->setValue(static_cast<int> (m_listening_socket.serverPort()));

    prepare_connection_status();
}

void Communications::slot_accept_connection()
{
	const auto socket = m_listening_socket.nextPendingConnection();

    if (!socket)
        return;
    else if (m_client_connection)
    {
        socket->abort();
        socket->deleteLater();
        return;
    }
    else
        m_client_connection = socket;

    m_client_connection->setParent(this);

    /*
    ** Acceptable peer?
    */

    if (m_gui &&
        m_gui->get_allowed_host_field() &&
        m_gui->get_allowed_host_field()->text().trimmed().isEmpty() == false)
    {
        auto const str(m_gui->get_allowed_host_field()->text().trimmed());

        if (QHostAddress(str) != m_client_connection->peerAddress())
        {
            m_client_connection->abort();
            m_client_connection->deleteLater();
            return;
        }
    }

    emit connected_to_client();
    connect(m_client_connection,
        SIGNAL(disconnected()),
        this,
        SLOT(slot_client_disconnected()));
#if (QT_VERSION < QT_VERSION_CHECK(5, 15, 0))
    connect(m_client_connection,
        SIGNAL(error(QAbstractSocket::SocketError)),
        m_client_connection,
        SIGNAL(disconnected()));
#else
    connect(m_client_connection,
        SIGNAL(errorOccurred(QAbstractSocket::SocketError)),
        m_client_connection,
        SIGNAL(disconnected()));
#endif
    connect(m_client_connection,
        SIGNAL(readyRead()),
        this,
        SLOT(slot_update_board()));

    if (m_vboard)
        m_vboard->GetStatusBar()->showMessage(tr("Status: Peer %1:%2 Connected").arg(m_client_connection->peerAddress().toString()).arg(m_client_connection->peerPort()));
}

void Communications::slot_client_connected()
{
    if (!m_gui)
    {
        slot_client_disconnected();
        return;
    }

    if (m_gui && m_vboard)
    {
        if (m_gui->get_color() == tr("Beige"))
            m_vboard->SetCurrentPlayer(White);
        else if (m_gui->get_color() == tr("Crimson"))
            m_vboard->SetCurrentPlayer(Black);
        else
        {
            slot_client_disconnected();
            return;
        }

        if (m_client_connection)
            m_vboard->GetStatusBar()->showMessage(tr("Status: Peer %1:%2 Connected").arg(m_client_connection->peerAddress().toString()).arg(m_client_connection->peerPort()));
    }
}

void Communications::slot_client_disconnected()
{
	const auto socket = qobject_cast<QTcpSocket*> (sender());

    if (m_client_connection && m_client_connection == socket)
    {
        m_client_connection->abort();
        m_client_connection->deleteLater();
    }
    else if (socket)
    {
        socket->abort();
        socket->deleteLater();
    }

    if (m_vboard)
    {
        m_vboard->GetBoard()->Initialize();
    }

    emit disconnected_from_client();
    prepare_connection_status();
}

QString Communications::SocketErrorToString(QAbstractSocket::SocketError error)
{
    switch (error) {
    case QAbstractSocket::ConnectionRefusedError:
        return "Connection Refused";
    case QAbstractSocket::RemoteHostClosedError:
        return "Remote Host Closed";
    case QAbstractSocket::HostNotFoundError:
        return "Host Not Found";
    case QAbstractSocket::SocketAccessError:
        return "Socket Access Error";
    case QAbstractSocket::SocketResourceError:
        return "Socket Resource Error";
    case QAbstractSocket::SocketTimeoutError:
        return "Socket Timeout";
    case QAbstractSocket::DatagramTooLargeError:
        return "Datagram Too Large";
    case QAbstractSocket::NetworkError:
        return "Network Error";
    case QAbstractSocket::AddressInUseError:
        return "Address In Use";
    case QAbstractSocket::SocketAddressNotAvailableError:
        return "Socket Address Not Available";
    case QAbstractSocket::UnsupportedSocketOperationError:
        return "Unsupported Socket Operation";
    case QAbstractSocket::UnfinishedSocketOperationError:
        return "Unfinished Socket Operation";
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        return "Proxy Authentication Required";
    case QAbstractSocket::SslHandshakeFailedError:
        return "Ssl Handshake Failed";
    case QAbstractSocket::ProxyConnectionRefusedError:
        return "Proxy Connection Refused";
    case QAbstractSocket::ProxyConnectionClosedError:
        return "Proxy Connection Closed";
    case QAbstractSocket::ProxyConnectionTimeoutError:
        return "Proxy Connection Timeout";
    case QAbstractSocket::ProxyNotFoundError:
        return "Proxy Not Found";
    case QAbstractSocket::ProxyProtocolError:
        return "Proxy Protocol Error";
    case QAbstractSocket::OperationError:
        return "Operation Error";
    case QAbstractSocket::SslInternalError:
        return "Ssl Internal Error";
    case QAbstractSocket::SslInvalidUserDataError:
        return "Ssl Invalid User Data";
    case QAbstractSocket::TemporaryError:
        return "Temporary Error";
    case QAbstractSocket::UnknownSocketError:
    default:
        return "Unknown Socket Error";
    }
}

void Communications::slot_disconnected(QAbstractSocket::SocketError error) const
{
    QMessageBox::critical(nullptr, "", SocketErrorToString(error), QMessageBox::Ok, QMessageBox::Default);
}

void Communications::slot_update_board()
{
    int ntries = 1;

    while (m_client_connection &&
        m_client_connection->canReadLine() &&
        ntries <= 5)
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);

        QByteArray buffer(s_buffer_size, 0);

        if (m_client_connection->readLine(buffer.data(), buffer.length()) != -1)
        {
            QApplication::restoreOverrideCursor();

            /*if (chess)
            {
	            static constexpr int s_shax_output_size = 128;
	            buffer = buffer.mid(0, buffer.indexOf(s_eof));

                auto const d
                (QByteArray::fromHex(buffer.mid(buffer.length() -
                    s_shax_output_size)));

                buffer = buffer.mid(0, buffer.length() - s_shax_output_size);

                if (memcmp(d, digest(buffer)))
                    chess->update_board(buffer);
            }*/

            break;
        }
        else
            QApplication::restoreOverrideCursor();

        ntries += 1;
    }

    if (m_client_connection)
        m_client_connection->readAll();
}

void Communications::stop_listening()
{
    m_listening_socket.close();
    prepare_connection_status();
}
