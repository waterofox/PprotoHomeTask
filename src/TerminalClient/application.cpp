#include "application.h"


#define log_debug_m alog::logger().debug (alog_line_location, "ApplicationDebug")
#define log_info_m  alog::logger().info  (alog_line_location,    "Jopaplication")

Application::Application(int argc, char** argv) :
    QApplication(argc, argv)
{

}

bool Application::init()
{
    _serverSocket = pproto::transport::tcp::Socket::Ptr {new pproto::transport::tcp::Socket()};

    QUuidEx appID = QUuidEx::createUuid();
    if(!config::base().getValue("application.id",appID))
    {
        log_debug_m << "--application id loading failed";
        return false;
    }
    this->_idAppl = appID;
    log_debug_m << "--application id loaded";

    QString appName = "";
    if(!config::base().getValue("application.name",appName))
    {
        log_debug_m << "--application name loading failed";
        return false;
    }
    this->_nameAppl = appName;
    log_debug_m << "--application name loaded";

    //вот эта хрень - непонятна и всё, что следует ниже
    QString pathSaver;
    if (!config::base().getValue("logger.file_win", pathSaver))
    {
        log_debug_m << "--error init application - " << pproto::error::init_appl_saverPath.description;
        return false;
    }

#define FUNC_REGISTRATION(COMMAND) \
    _funcInvoker.registration(command:: COMMAND, &Application::command_##COMMAND, this);

    FUNC_REGISTRATION(SendJopaToClient)
    FUNC_REGISTRATION(ServerInformation)

#undef FUNC_REGISTRATION

    log_info_m << "--application is Creating: " << _idAppl.toString() << " - " << _nameAppl;
    return true;
}

void Application::de_init()
{

}

void Application::command_SendJopaToClient(const pproto::Message::Ptr &m)
{
    if(m->type() == pproto::Message::Type::Command)
    {
        pproto::data::SendJopaToClient dataForJopa;
        pproto::readFromMessage(m,dataForJopa);
        log_info_m << dataForJopa.JopaMessage;

    }
}

void Application::command_ServerInformation(const Message::Ptr &m)
{

}

void Application::connectionToServer()
{
    QHostAddress ServerHost("0.0.0.0");
    if(!config::readHostAddress("server.address",ServerHost))
    {
        log_debug_m << "--failed to loaded server ip";
        return;
    }
    else {log_debug_m << "--server's ip loaded";}

    int port  = 41014;

    if(!_serverSocket->init({ServerHost,port}))
    {
        log_debug_m << "--failed to create socket";
        return;
    }
    else {log_debug_m << "--socket has created";}

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
    if (!_serverSocket->isConnected())
    {
        log_debug_m << "Failed Connect to Server";
        _serverSocket->stop();
        return;
    }

}
