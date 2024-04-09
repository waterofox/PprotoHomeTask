#ifndef CLIENT_H
#define CLIENT_H
#include "commands/commands.h"
#include "commands/error.h"

#include "shared/simple_ptr.h"
#include "shared/defmac.h"
#include "shared/logger/logger.h"
#include "shared/logger/format.h"
#include "shared/config/appl_conf.h"
#include "shared/qt/logger_operators.h"

#include "pproto/func_invoker.h"
#include "pproto/transport/tcp.h"
#include "pproto/commands/base.h"
#include "pproto/commands/pool.h"
#include "pproto/logger_operators.h"

#include <QApplication>
#include <QMainWindow>
#include <QCloseEvent>
#include <QHostInfo>
#include <QMessageBox>
#include <QDateTime>

#include <unistd.h>
using namespace pproto;

class Client : public QObject
{
    Q_OBJECT
public:
    Client();
    ~Client();
private:
    pproto::FunctionInvoker _funcInvoker;

    pproto::transport::tcp::Socket::Ptr _serverSocket;

    QString userName = "";
public slots:
    void startClinet_slot();
    void setUserName(const QString& userName);
    void command_ServerInformation(const pproto::Message::Ptr& mes);
};

#endif // CLIENT_H
