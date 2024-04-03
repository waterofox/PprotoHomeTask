#include <iostream>
#include <QString>
#include <QStringList>
#include <QNetworkProxy>
#include <QObject>
#include "config/appl_conf.h"
#include "config/logger_conf.h"
#include "shared/logger/logger.h"
#include "shared/logger/format.h"
#include "logger/config.h"
#include "pproto/transport/tcp.h"
#include "pproto/transport/local.h"
#include "application.h"


#define log_debug_m alog::logger().debug (alog_line_location, "ApplicationDebug")
#define log_info_m  alog::logger().info  (alog_line_location,    "Jopaplication")

int loadApplication();
using namespace pproto::transport;
int main(int argc, char* argv[])
{
    loadApplication();
    Application obj{argc,argv};
    obj.init();
    QNetworkProxy::setApplicationProxy(QNetworkProxy::NoProxy);
    //настраиваем эту ******
    QHostAddress host{"0.0.0.0"};
    config::readHostAddress("listener.socket.address",host);
    int port{20102};
    config::base().getValue("listener.socket.port",port);

    if(!pproto::transport::tcp::Listener().init({host,port}))
    {
        log_info_m << "---failed to start listener on " << host<<':' << port;
        return 1;
    }
    log_info_m << "---server is listening now on " << host << ':' << port;

    chk_connect_q(&tcp::listener(),&tcp::Listener::socketConnected,
                  &obj,&Application::socketConnected);

    obj.exec();
    return 0;
}
int loadApplication()
{
    alog::logger().start();
    alog::logger().addSaverStdOut(alog::Level::Debug2);

    QString configFile = config::qdir() + "/Terminal.config";

    //config::dirExpansion(configFile);
    if (!QFile::exists(configFile))
    {
        log_debug_m  <<  configFile;
        return 1;
    }
    else { log_debug_m << "--config had been loaded";}

    config::base().setReadOnly(false);
    config::base().setSaveDisabled(false);

    if (!config::base().readFile(configFile.toStdString()))
    {
        log_debug_m <<configFile;
        return 1;
    }
    //запуск конфига и донастройка логера
    config::observerBase().start();

    alog::configDefaultSaver();
    alog::configExtendedSavers();
    alog::printSaversInfo();
    //добавление сейверов
    alog::logger().addSaverStdOut(alog::Level::Debug);
    alog::logger().addSaverStdOut(alog::Level::Info);

    log_debug_m << "--savers added and logger had started";




    return 0;
}
