/*****************************************************************************
  В модуле представлен список идентификаторов команд для коммуникации между
  клиентской и серверной частями приложения.
  В данном модуле представлен список команд персональный для этого приложения.

  Требование надежности коммуникаций: однажды назначенный идентификатор коман-
  ды не должен более меняться.
*****************************************************************************/

#pragma once

#include "pproto/commands/base.h"
#include <QString>

namespace pproto {
namespace command {

//----------------------------- Список команд --------------------------------

/**
  Команда используется для поиска экземпляров Program. Команда отправляется
  как широковещательное сообщение, так же она используется в качестве ответа
*/
extern const QUuidEx CtlDiscovery;

/**
  Команда передачи информации клиенту о сервере при подключении
*/
extern const QUuidEx ServerInformation;

extern const QUuidEx SendJopaToClient;

extern const QUuidEx NewMessageInChat;


} // namespace command

//---------------- Структуры данных используемые в сообщениях ----------------

namespace data {

struct CtlDiscovery : Data<&command::CtlDiscovery,
                            Message::Type::Answer>
{
    // Краткая информация об экземпляре ctl
    QString info;

    // Идентификатор приложения времени исполнения
    QUuidEx applId;

    // Адрес ctl в локальной сети
    HostPoint hostPoint;

    DECLARE_B_SERIALIZE_FUNC
};

struct NewMessageInChat : Data<&command::NewMessageInChat, Message::Type::Command,Message::Type::Answer>
{
    QString DataMessage ="";
    QString DataUserName = "";
    QDateTime DataTime;

    DECLARE_B_SERIALIZE_FUNC
};
struct ServerInformation : Data<&command::ServerInformation,
                                 Message::Type::Command,
                                 Message::Type::Answer>
{
    typedef container_ptr<ServerInformation> Ptr;
    /// Тело Запроса

    QString HelloWorld;

    /// Тело Ответа

    // Имя сервера
    QString name;

    // Адрес сервера
    QString address;

    DECLARE_B_SERIALIZE_FUNC
};
struct SendJopaToClient : Data<&command::SendJopaToClient,Message::Type::Command,Message::Type::Answer>
{
    QString JopaMessage;
    DECLARE_B_SERIALIZE_FUNC
};


} // namespace data
} // namespace pproto
