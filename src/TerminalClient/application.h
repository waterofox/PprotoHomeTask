#ifndef APPLICATION_H
#define APPLICATION_H

#include <QCoreApplication>
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
#include <QHostInfo>

#include <unistd.h>

class Application : public QCoreApplication
{
    Q_OBJECT
public:
    Application(int argc, char**argv);
    void init();
    void de_init();
};

#endif // APPLICATION_H
