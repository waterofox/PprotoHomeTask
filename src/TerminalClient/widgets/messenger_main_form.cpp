#include "messenger_main_form.h"
#include "ui_messenger_main_form.h"

messenger_main_form::messenger_main_form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::messenger_main_form)
{
    ui->setupUi(this);
    this->clientObj = new Client;
    QObject::connect(this->ui->ConnectionBut,SIGNAL(clicked(bool)),
                     this->clientObj,SLOT(startClinet_slot()));

    QObject::connect(this->clientObj,SIGNAL(clientHasConnected()),
                     this,SLOT(setStatusView()));
}

messenger_main_form::~messenger_main_form()
{
    delete ui;
}

void messenger_main_form::setStatusView()
{
    this->ui->label_status->setText("online");
    this->ui->label_status->setAlignment(Qt::AlignmentFlag::AlignCenter);
    this->ui->label_status->setStyleSheet("font: 10pt 'MS Serif'; color: rgb(104, 204, 22);");

    this->ui->name->setReadOnly(true);
    this->clientObj->setUserName(this->ui->name->text());

    this->ui->ConnectionBut->setEnabled(false);
}
