#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QListView>
#include <friendcard.h>
#include <QListWidget>
#include <QStandardItemModel>
#include <QTcpSocket>

#include "loginhint.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(const QVector<QString>& friends,
                        const QString& acc_name,
                        QTcpSocket* client,
                        QWidget *parent = nullptr);
    ~ChatWindow();
    void addFriend(const QString& friend_acc);
    Ui::ChatWindow* get_ui();
private:
    Ui::ChatWindow *ui;
    QListWidget* friends_list;
    QTcpSocket* client;
    QString acc_name;
    QString target_name;
    QListWidget* current_chat;
    QHash<QString, QListWidget*>* list_map;
private slots:
    void send_msg();
};

#endif // CHATWINDOW_H
