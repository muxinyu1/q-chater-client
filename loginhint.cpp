#include "loginhint.h"
#include "ui_loginhint.h"

LoginHint::LoginHint(const QString& msg, QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::LoginHint)
{
    ui->setupUi(this);
    this->ui->info->setText(msg);
    connect(this->ui->ok, &QPushButton::clicked, [this]() {
        //QApplication::beep();
        this->close();
    });
}

LoginHint::~LoginHint()
{
    delete ui;
}
