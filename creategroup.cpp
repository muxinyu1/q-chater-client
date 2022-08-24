#include "creategroup.h"
#include "ui_creategroup.h"

CreateGroup::CreateGroup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateGroup)
{
    ui->setupUi(this);
}

CreateGroup::~CreateGroup()
{
    delete ui;
}
