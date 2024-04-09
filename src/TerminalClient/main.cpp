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

#include "client.h"

#include <QApplication>

#define log_debug_m alog::logger().debug (alog_line_location, "ApplicationDebug")
#define log_info_m  alog::logger().info  (alog_line_location,    "Jopaplication")
int main(int argc, char* argv[])
{
    alog::logger().start();
    alog::logger().addSaverStdOut(alog::Level::Debug2);

    QString configFile = config::qdir() + "/TerminalClient.config";

    if(!QFile::exists(configFile))
    {
        log_debug_m << configFile;
        return 1;
    }

    config::base().setReadOnly(false);
    config::base().setSaveDisabled(false);

    if(!config::base().readFile(configFile.toStdString()))
    {
        return 1;
    }
    log_debug_m << "--config loaded";
    config::observerBase().start();

    alog::configDefaultSaver();
    alog::configExtendedSavers();
    alog::printSaversInfo();

    alog::logger().addSaverStdOut(alog::Level::Debug);
    alog::logger().addSaverStdOut(alog::Level::Info);

    log_debug_m << "--savers added";

    QApplication obj(argc,argv);
    Client* jopka = new Client;
    jopka->startClinet_slot();

    return obj.exec();;
}

