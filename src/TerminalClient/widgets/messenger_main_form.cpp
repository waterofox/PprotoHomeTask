#include "messenger_main_form.h"
#include "ui_messenger_main_form.h"

messenger_main_form::messenger_main_form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::messenger_main_form)
{
    ui->setupUi(this);
}

messenger_main_form::~messenger_main_form()
{
    delete ui;
}
