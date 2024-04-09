#include "client.h"
#define log_debug_m alog::logger().debug (alog_line_location, "ApplicationDebug")
#define log_info_m  alog::logger().info  (alog_line_location,    "Jopaplication")
Client::Client()
{
    _serverSocket = pproto::transport::tcp::Socket::Ptr {new pproto::transport::tcp::Socket()};

    #define FUNC_REGISTRATION(COMMAND) \
    _funcInvoker.registration(command:: COMMAND, &Client::command_##COMMAND, this);

    FUNC_REGISTRATION(ServerInformation)

    #undef FUNC_REGISTRATION

}

Client::~Client()
{

}

void Client::startClinet_slot()
{
    QString hostAdress;
    if(!config::base().getValue("server.address",hostAdress))
    {
        log_debug_m << "failed to loaded host";
        return;
    }
    QHostAddress address("127.0.0.1");

    int port = 0;
    if(!config::base().getValue("server.port",port))
    {
        log_debug_m << "failed to loaded port";
        return;
    }

    if(!_serverSocket->init({address,port}))
    {
        log_debug_m << "failed to init socket";
        return;
    }
    _serverSocket->start();
 int attempts = 0;
    while (attempts++ < 60 /*ждем 6 сек*/)
    {
        _serverSocket->connect();
        qApp->processEvents();
        QThread::msleep(100 /*0.1 сек*/);
        if (_serverSocket->isConnected())
            break;
        _serverSocket->stop();
    }
    log_debug_m << "socket has connected to server";
}

void Client::setUserName(const QString &userName)
{
    this->userName = userName;
}

void Client::command_ServerInformation(const Message::Ptr& mes)
{

}
