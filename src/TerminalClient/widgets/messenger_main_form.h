#ifndef MESSENGER_MAIN_FORM_H
#define MESSENGER_MAIN_FORM_H

#include <QWidget>
#include "../client.h"
namespace Ui {
class messenger_main_form;
}

class messenger_main_form : public QWidget
{
    Q_OBJECT

public:
    explicit messenger_main_form(QWidget *parent = nullptr);
    ~messenger_main_form();

private:
    Ui::messenger_main_form *ui;

    Client* clientObj = nullptr;
public slots:
    void setStatusView();
};

#endif // MESSENGER_MAIN_FORM_H
