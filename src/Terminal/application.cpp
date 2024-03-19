#include "application.h"

Application::Application(int argc, char** argv) :
    QCoreApplication(argc, argv)
{}

bool Application::init()
{

}

bool Application::deInit()
{

}

void Application::socketConnected(SocketDescriptor socketDescript)
{

}

void Application::message(const Message::Ptr &)
{

}

void Application::command_ServerInformation(const Message::Ptr &)
{

}
