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

    QUuidEx _idAppl; //имя приложения
    QString _nameAppl; //Я дегенарут тупой. это имя. ID выше

    alog::atomic_bool _stop = {false}; //хз пока мирный атом
    FunctionInvoker _funcInvoker; //хз пока

public:
    Application(int argc, char**argv);//конструктор

    bool init(); //хз пока
    bool deInit(); //хз пока
public slots:
    void socketConnected(pproto::SocketDescriptor socketDescript);//хз пока
    void message(const pproto::Message::Ptr& m); //хз пока

    void command_ServerInformation(const pproto::Message::Ptr&);//обработчик комманды ServerInformation
    void command_SendJopaToClient (const pproto::Message::Ptr&);//обработчик функцйии jopas
};

#endif // APPLICATION_H
