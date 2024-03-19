#ifndef APPLICATION_H
#define APPLICATION_H

#include "commands/commands.h"
#include "commands/error.h"

#include "pproto/commands/pool.h"
#include "pproto/serialize/functions.h"
#include "pproto/transport/tcp.h"
#include "pproto/transport/local.h"
#include "pproto/func_invoker.h"

#include "config/appl_conf.h"
#include "shared/qt/quuidex.h"

#include <QCoreApplication>
#include <QObject>

#include <atomic>
using namespace pproto;
class Application : public QCoreApplication
{
    Q_OBJECT
private:

    QUuidEx _idAppl;
    QString _nameAppl;

    alog::atomic_bool _stop = {false};
    FunctionInvoker _funcInvoker;

public:
    Application(int argc, char**argv);

    bool init();
    bool deInit();
public slots:
    void socketConnected(pproto::SocketDescriptor socketDescript);
    void message(const pproto::Message::Ptr&);

    void command_ServerInformation(const pproto::Message::Ptr&);
};

#endif // APPLICATION_H
