#ifndef APPLICATION_H
#define APPLICATION_H

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
#include <QHostInfo>
#include <QDateTime>

#include <unistd.h>
using namespace pproto;
class Application : public QApplication
{
    Q_OBJECT
private:
    QUuidEx _idAppl; //имя приложения
    QString _nameAppl; //Я дегенарут тупой. это имя. ID выше

    alog::atomic_bool _stop = {false}; //хз пока мирный атом
    pproto::FunctionInvoker _funcInvoker; //хз пока

    pproto::transport::tcp::Socket::Ptr _serverSocket;
public:
    Application(int argc, char**argv);
    bool init();
    void de_init();

public slots:
    void command_SendJopaToClient (const pproto::Message::Ptr& m);
    void command_ServerInformation(const pproto::Message::Ptr& m);
    void connectionToServer();
};

#endif // APPLICATION_H
