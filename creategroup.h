#ifndef CREATEGROUP_H
#define CREATEGROUP_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QCheckBox>
#include <QTcpSocket>

namespace Ui {
class CreateGroup;
}

class CreateGroup : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateGroup(QVector<QString>& friends, QTcpSocket* client, QWidget *parent = nullptr);
    ~CreateGroup();

private:
    Ui::CreateGroup *ui;
    QTcpSocket* client;
};

#endif // CREATEGROUP_H
