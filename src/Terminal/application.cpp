#include "application.h"

#define log_debug_m alog::logger().debug (alog_line_location, "ApplicationDebug")
#define log_info_m  alog::logger().info  (alog_line_location,    "Jopaplication")

Application::Application(int argc, char** argv) :
    QCoreApplication(argc, argv)
{}

bool Application::init()
{
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

    FUNC_REGISTRATION(ServerInformation)

#undef FUNC_REGISTRATION

    log_info_m << "--application is Creating: " << _idAppl.toString() << " - " << _nameAppl;
    return true;
}

bool Application::deInit()
{

}

void Application::socketConnected(SocketDescriptor socketDescript)
{
    log_info_m << "---ЕБАТЬ ПОДКЛЮЧЕНИЕ";
}

void Application::message(const Message::Ptr & m)
{
    log_info_m << "--- new message";
    if (_stop)
        return;

    if (m->processed())
        return;

    if (lst::FindResult fr = _funcInvoker.findCommand(m->command()))
    {
        if (command::pool().commandIsSinglproc(m->command()))
            m->markAsProcessed();
        _funcInvoker.call(m, fr);
    }
}

void Application::command_ServerInformation(const Message::Ptr &)
{

}
