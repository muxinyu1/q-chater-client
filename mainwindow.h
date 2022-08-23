#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include "loginwidget.h"
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>
#include <QThread>
#include <memory>
#include <sstream>
#include <iostream>
#include "chatwindow.h"
#include "loginhint.h"
#include "signup.h"
#include "utility.h"

#include <style.h>
#include <variable.h>
#include "ui_signup.h"
#include "ui_chatwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    bool can_login;
    QPushButton* button1;
    QPushButton* button2;
    Ui::MainWindow *ui;
    LoginWidget* log_in;
    QTcpSocket* client;
    void my_slot();
    void recover_login_btn();
    void process_response(QByteArray& bytes);
    SignUp* sign_up;
    ChatWindow* chat_window;

    Style* style;

};
#endif // MAINWINDOW_H
