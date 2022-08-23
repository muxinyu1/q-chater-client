#ifndef LOGINHINT_H
#define LOGINHINT_H

#include <QDialog>

namespace Ui {
class LoginHint;
}

class LoginHint : public QDialog
{
    Q_OBJECT

public:
    explicit LoginHint(const QString& msg, QWidget *parent = nullptr);
    ~LoginHint();

private:
    Ui::LoginHint *ui;
};

#endif // LOGINHINT_H
